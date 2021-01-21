﻿#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;

char SERVER[]= "62.149.7.206";
int PORT = 6660;

    QString NAME ="test_bot";
    QString IRCBOT_CHANNEL = "#ruschat";
    QString  joiq = "JOIN " + IRCBOT_CHANNEL + "\n";
    const char * joich = joiq.toLocal8Bit().constData();
    QString inchanq = "PRIVMSG "+ IRCBOT_CHANNEL;
    const char * inchanch = inchanq.toLocal8Bit().constData();
    QString msg_greet = "PRIVMSG " +IRCBOT_CHANNEL+ " :hi from netcat\n";
    const char * msg_greetings = msg_greet.toLocal8Bit().constData();

const char * BlockedRead(QTcpSocket *soc)
{
     while (!(soc->bytesAvailable()))
     {
        soc->waitForReadyRead(10000);
     }
     const char * ch = soc->readAll().constData();
     cout<<ch;
     return ch;
}

bool ircbot_connect(QTcpSocket *soc)
{
    soc->connectToHost(SERVER, PORT);
//    soc->connectToHost("127.0.0.1", 4567);
    if (!soc->waitForConnected(1000))
    {
       qDebug() << "Not Connected";
       return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_register(QTcpSocket *soc, QString dn )
{
    BlockedRead(soc);
    QString h = "NICK "+dn+'\n';
    const  char * n = h.toLocal8Bit().constData();
    soc->write(n);
    soc->write("PING\n");
    BlockedRead(soc);
    soc->write("USER qwert_zaq 8 x : qwert_zaq\n");
}

void ircbot_codepage(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("CODEPAGE UTF-8\n");
}

void ircbot_join(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write(joich);
    BlockedRead(soc);
    soc->write(msg_greetings);
}

void ircbot_disconnect(QTcpSocket *soc)
{
    soc->close();
}

QString ircbot_rename( QString oldn, QTcpSocket *soc, const char * ch)
 {
    QString str(ch);
    QStringList list2 = str.split(QLatin1Char(':'), Qt::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf(inchanch , 0) != -1) && (msg.startsWith("!nick")))
    {
        msg = msg.remove(0, 5);
        msg= msg.simplified();
        if (msg.contains(QRegExp("[^a-zA-Z_-/d]"))) // тут ошибка, так как в str что-то еще кроме букв от 'a' до 'z', 'A' до 'Z', '_' и '-'
        {
              qDebug()<<"error nick\n";
        }
        else
        {
            QString h = "NICK "+msg+'\n';
            const  char * n = h.toLocal8Bit().constData();
            soc->write(n);
            QString s = BlockedRead(soc);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            NAME = msg;
            return msg;
        }
    }
}

void ircbot_loop(QTcpSocket *soc, QString dn)
{
    while (1)
    {
        QString c = BlockedRead(soc);
        qDebug() << c;
        QString d = "you type: " + c;
        if (c.indexOf("!quit", 0)!= -1)
            ircbot_disconnect(soc);
        if ((c.indexOf(inchanch, 0) != -1) && (c.indexOf(dn , 0) != -1))
        {
            QString answq = "PRIVMSG " + IRCBOT_CHANNEL + " : i hear you\n";
            const char * answch = answq.toLocal8Bit().constData();
            soc->write(answch);
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0)!= -1)
            soc->write("PONG irc.lucky.net\n ");
        if ((c.indexOf(inchanch, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
        {
            char const* ch = c.toLocal8Bit().constData();
            dn = ircbot_rename(dn, soc, ch);
        }
    }
}

int main()
{
      QTcpSocket *socket;
      socket = new QTcpSocket(NULL);
      if (!(ircbot_connect(socket)))
         return  1;
      ircbot_register(socket, NAME);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket, NAME );
      return 0;
}

/*
int main()
{

    #define IRCBOT_CHANNEL "#ruschat"                                               //old
    const char* msg_greetings = "PRIVMSG " IRCBOT_CHANNEL " :hi from netcat\n";     //old
    const char * joich = "JOIN " IRCBOT_CHANNEL "\n";                               //old
    const char * inchanch = "PRIVMSG " IRCBOT_CHANNEL;                               //old
   cout<<msg_greetings;
   cout<<joich;
   cout<<inchanch<<endl;

    QString NAME ="test_bot";
    QString IRCBOT_CHANNEL_2 = "#ruschat";
    QString  joiq = "JOIN " + IRCBOT_CHANNEL_2 + "\n";
    const char * joich_2 = joiq.toLocal8Bit().constData();
    cout<<joich_2;
    QString inchanq_2 = "PRIVMSG "+ IRCBOT_CHANNEL_2;
    const char * inchanch_2 = inchanq_2.toLocal8Bit().constData();
    cout<<inchanch_2<<endl;
    QString msg_greet = "PRIVMSG " +IRCBOT_CHANNEL_2+ " :hi from netcat\n";
    const char * msg_greetings_2 = msg_greet.toLocal8Bit().constData();
    cout<<msg_greetings_2;
    QString answq = "PRIVMSG " + IRCBOT_CHANNEL_2 + " : i hear you\n";
    const char * answch = answq.toLocal8Bit().constData();
    cout<<answch<<endl;
}
*/

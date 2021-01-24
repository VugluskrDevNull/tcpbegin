#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include <QFile>
#include  <QAbstractSocket>
#include <fstream>
using namespace std;

    QFile file("bot_data.txt");
    int port = 6667;
    QString server = "irc.lucky.net";      // "62.149.7.206";  "irc.lucky.net"  "chat.freenode.net"
    QString name ="test_bot";
    QString ircbot_channel = "#ruschat";
    QString  joiq = "JOIN " + ircbot_channel + "\n";
    QString inchan = "PRIVMSG "+ ircbot_channel;
    QString msg_greetings = "PRIVMSG " + ircbot_channel + " :hi from netcat\n";

const char * ircbot_read_blocked(QTcpSocket *soc)
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
    soc->connectToHost(server.toLatin1().constData(), port);
 //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!soc->waitForConnected(1000))
    {
       qDebug() << "Not Connected";
       return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_send(QTcpSocket *soc, const  char * ch)
{
//    cout<<"i send (cout) - "<<ch<<endl;
    qDebug()<<"i send (qDebug() ) - "<<ch<<endl;
    soc->write(ch);
}

void ircbot_register(QTcpSocket *soc, QString dn )
{
    ircbot_read_blocked(soc);
    QString h = "NICK "+dn+'\n';
    ircbot_send(soc, h.toLatin1().constData());
    ircbot_send(soc,"PING\n");
    ircbot_read_blocked(soc);
    ircbot_send(soc,"USER qwert_zaq 8 x : qwert_zaq\n");
}

void ircbot_codepage(QTcpSocket *soc)
{
    ircbot_read_blocked(soc);
    ircbot_send(soc,"CODEPAGE UTF-8\n");
}

void ircbot_join(QTcpSocket *soc)
{
    ircbot_read_blocked(soc);
    ircbot_send(soc, joiq.toLatin1().constData());
    ircbot_read_blocked(soc);
    ircbot_send(soc, msg_greetings.toLatin1().constData());
}

void ircbot_config_save()
{
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       file.write(name.toLatin1());
    }
    else
        cout<<"cant open file bot_data for save\n";
    file.close();
}

void ircbot_disconnect(QTcpSocket *soc)
{
    ircbot_config_save();
    soc->close();
}

void ircbot_config_load()
{
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
           qDebug()<<"name is "<<name<<endl;
           ircbot_config_save();
         }
      }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();
        qDebug()<<"line is "<<line<<endl;
        name = line;
        file.close();
    }
}

QString ircbot_rename( QString oldn, QTcpSocket *soc, QString q)
 {
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf(inchan , 0) != -1) && (msg.startsWith("!nick")))
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
            ircbot_send(soc, h.toLatin1().constData());
            QString s = ircbot_read_blocked(soc);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            name = msg;
            ircbot_config_save();
            return msg;
        }
    }
}

void ircbot_loop(QTcpSocket *soc)
{
    while (1)
    {
        QString c = ircbot_read_blocked(soc);
        qDebug() << c;

        if (c.indexOf("!quit", 0)!= -1)
            ircbot_disconnect(soc);
        if ((c.indexOf(inchan, 0) != -1) && (c.indexOf(name , 0) != -1))
        {
            QString answq = "PRIVMSG " + ircbot_channel + " : i hear you\n";
            ircbot_send(soc, answq.toLatin1().constData());
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0)!= -1)
        {
            QString pong = "PONG " + server + "\n" ;
            ircbot_send(soc, pong.toLatin1().constData());
        }
        if ((c.indexOf(inchan, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
        {
            name = ircbot_rename(name, soc, c);
        }
    }
}

int main()
{
      ircbot_config_load();
      QTcpSocket *socket;
      socket = new QTcpSocket(NULL);
      if (!(ircbot_connect(socket)))
         return  1;
      ircbot_register(socket, name);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket);
      return 0;
}



#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;

char server []= "185.30.166.38";                                      // "62.149.7.206";
int port = 6667;

    QString name ="test_bot";
    QString ircbot_channel = "#ruschat";
    QString  joiq = "JOIN " + ircbot_channel + "\n";
    const char * joich = joiq.toLatin1().constData();
    QString inchanq = "PRIVMSG "+ ircbot_channel;
    const char * inchanch = inchanq.toLatin1().constData();
    QString msg_greet = "PRIVMSG " + ircbot_channel + " :hi from netcat\n";
    const char * msg_greetings = msg_greet.toLatin1().constData();

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
    soc->connectToHost(server, port);
//     soc->connectToHost("127.0.0.1", 4567);
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
   //cout<<"i send - "<<ch<<endl;
    qDebug()<<"i send - "<<ch<<endl;
    soc->write(ch);
}


void ircbot_register(QTcpSocket *soc, QString dn )
{
    ircbot_read_blocked(soc);
    QString h = "NICK "+dn+'\n';
    const  char * n = h.toLatin1().constData();
    ircbot_send(soc, n);
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
    ircbot_send(soc,joich);
    ircbot_read_blocked(soc);
    ircbot_send(soc, msg_greetings);
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
            const  char * n = h.toLatin1().constData();
            ircbot_send(soc, n);
            QString s = ircbot_read_blocked(soc);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            name = msg;
            return msg;
        }
    }
}

void ircbot_loop(QTcpSocket *soc, QString dn)
{
    while (1)
    {
        QString c = ircbot_read_blocked(soc);
        qDebug() << c;
        QString d = "you type: " + c;
        if (c.indexOf("!quit", 0)!= -1)
            ircbot_disconnect(soc);
        if ((c.indexOf(inchanch, 0) != -1) && (c.indexOf(dn , 0) != -1))
        {
            QString answq = "PRIVMSG " + ircbot_channel + " : i hear you\n";
            const char * answch = answq.toLatin1().constData();
            ircbot_send(soc, answch);
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0)!= -1)
            ircbot_send(soc, "PONG irc.lucky.net\n ");
        if ((c.indexOf(inchanch, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
        {
            char const* ch = c.toLatin1().constData();
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
      ircbot_register(socket, name);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket, name );
      return 0;
}

/*
int main ()
{
    QString name ="test_bot";
    QString ircbot_channel = "#ruschat";
    QString  joiq = "JOIN " + ircbot_channel + "\n";
    const char * joich = joiq.toLocal8Bit().constData();
    cout<<joich<<endl;
    QString inchanq = "PRIVMSG "+ ircbot_channel;
    const char * inchanch = inchanq.toLocal8Bit().constData();
     cout<<inchanch<<endl;
    QString msg_greet = "PRIVMSG " + ircbot_channel + " :hi from netcat\n";
    const char * msg_greetings = msg_greet.toLocal8Bit().constData();
    cout<<msg_greetings<<endl;
}
*/
/************************************************************************* //рабочий
#define SERVER "62.149.7.206"                     //"62.149.7.206"
#define PORT 6660                                       //6660

#define IRCBOT_CHANNEL "#ruschat"
const char* msg_greetings = "PRIVMSG " IRCBOT_CHANNEL " :hi from netcat\n";
const char * joich = "JOIN " IRCBOT_CHANNEL "\n";
const char * inchanch = "PRIVMSG " IRCBOT_CHANNEL;


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
            soc->write("PRIVMSG " IRCBOT_CHANNEL " : i hear you\n");
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
      QString defname ="test_bot";
      QTcpSocket *socket;
      socket = new QTcpSocket(NULL);
      if (!(ircbot_connect(socket)))
         return  1;
      ircbot_register(socket, defname);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket, defname );
      return 0;
}
*****************************************/    //рабочий

#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;


#define SERVER "62.149.7.206"
#define PORT 6660

#define IRCBOT_CHANNEL "#ruschat"
const char* msg_greetings = "PRIVMSG " IRCBOT_CHANNEL ": hi from netcat\n";
const char * joich = "JOIN " IRCBOT_CHANNEL "\n";
const char * inchanch = "PRIVMSG " IRCBOT_CHANNEL "\n";       // без двоеточий
const char * inchanch2 = "PRIVMSG " IRCBOT_CHANNEL " :\n ";      // с двоеточиями

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
    if ((head.indexOf(inchanch2 , 0) != -1) && (msg.startsWith("!nick")))
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
        if ((c.indexOf(inchanch2, 0) != -1) && (c.indexOf(dn , 0) != -1))
        {
            soc->write("PRIVMSG #ruschat  : i hear you\n");
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0)!= -1)
            soc->write("PONG irc.lucky.net\n ");
        if ((c.indexOf(inchanch2, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
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


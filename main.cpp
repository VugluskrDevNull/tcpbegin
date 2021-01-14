#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;

//    qDebug()<<socket->readAll();
//qDebug()<<"Reading"<<socket->bytesAvailable(); // кол во байт
//while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }  // ожидание ОТ сокета
//  socket->waitForBytesWritten(100);   // проталкивание В сокет
// QByteArray q="qwerty"; char * c=data(q);   cout<<c; // qwerty
//  cout << socket->readAll().constData();
// //const char *QByteArray::data() const
/***************************************************************************/ //  бот
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
    soc->connectToHost("62.149.7.206", 6660);
//    soc->connectToHost("127.0.0.1", 4567);
    if (!soc->waitForConnected(1000))
    {
       qDebug() << "Not Connected";
       return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_register(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("NICK test_bot\n ");
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
    soc->write("JOIN #ruschat \n");
    BlockedRead(soc);
    soc->write("PRIVMSG #ruschat  : hi from netcat\n");
}

void ircbot_disconnect(QTcpSocket *soc)
{
    soc->close();
}

void ircbot_loop(QTcpSocket *soc)
{
    while (1)
    {
        QString c = BlockedRead(soc);
        qDebug() << c;
        QString d = "you type: " + c;
        int j = 0;
        if (c.indexOf("!quit", j)!= -1)
            ircbot_disconnect(soc);
        if (c.indexOf("PRIVMSG #ruschat :test_bot", 0) != -1)
        {
            soc->write("PRIVMSG #ruschat  : i hear you\n");
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0) != -1)
            soc->write("PONG irc.lucky.net\n ");
   }
}

int main()
{
      QTcpSocket *socket;
      socket = new QTcpSocket(NULL);
      if (!(ircbot_connect(socket)))
         return  1;
      ircbot_register(socket);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket);
      return 0;
}

/*************************************************************************** //  бот начало
const char * BlockedRead (QTcpSocket *soc)
{
     while ( !(soc->bytesAvailable()))
     {
        soc->waitForReadyRead(10000);
     }
     const char * ch = soc->readAll().constData();
     cout<<ch;
     return ch;
}

int main()
{
      QTcpSocket *socket;

      socket = new QTcpSocket(NULL);
      socket->connectToHost("62.149.7.206", 6660);
  //  socket->connectToHost("127.0.0.1", 4567);
      if (!socket->waitForConnected(1000))
      {
         qDebug() << "Not Connected";
         return 1;
      }
      qDebug() << "Connected";

      BlockedRead (socket);
      socket->write( "NICK test_bot\n ");
      socket->write( "PING\n");

      BlockedRead (socket);
      socket->write( "USER qwert_zaq 8 x : qwert_zaq\n");

      BlockedRead (socket);
     // socket->write( "CODEPAGE UTF-8\n");

      BlockedRead (socket);
      socket->write("JOIN #ruschat \n");

      BlockedRead (socket);
      socket->write("PRIVMSG #ruschat  : hi from netcat\n");

      while (1)
      {
          QString c = BlockedRead (socket);
          qDebug() << c;
          QString d = "you type: " + c;
          int j = 0;
          if (c.indexOf("!quit", j)!= -1)
              break;
          if (c.indexOf("PRIVMSG #ruschat :test_bot", 0) != -1)
          {
              socket->write("PRIVMSG #ruschat  : i hear you\n");
              socket->waitForBytesWritten();
          }
          if (c.indexOf("PING", 0) != -1)
              socket->write("PONG irc.lucky.net\n ");
     }
     socket->close();

      return 0;
}
***************************************************************************/ //  бот начало
/*
QString str = "We must be <b>bold</b>, very <b>bold</b>";
int j = 0;

while ((j = str.indexOf("<b>", j)) != -1) {            // -1 if not found else position
    qDebug() << "Found <b> tag at index position" << j;
    ++j;
}
*/
/*
int main ()
{

QString str = "We must be <b>bold</b>, very <b>bold</b>";


while ((j = str.indexOf("<b>", j)) != -1) {
    qDebug() << "Found <b> tag at index position" << j;
    ++j;
}

    QString str = "We must be <b>bold</b>, very <b>bold</b!quit>";
    int j = 0;
    if (str.indexOf("!quit", j)!= -1) cout<<"ok";
    else cout<<"bad";
}
*/

/*
int main()
{
    QTcpSocket *socket;

    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);

    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 1;
    }

    qDebug() << "Connected";
    while (1) {
        socket->write("input> ");

        while(socket->bytesAvailable() == 0) {
            socket->waitForReadyRead(100);
        }

        qDebug() << "Reading" << socket->bytesAvailable();

        QString c = socket->readLine();
        qDebug() << c;

        if (c.simplified().compare("exit") == 0)
            break;

        QString d = "you type: " + c;
        socket->write(d.toLocal8Bit().constData());
    }

    socket->close();

    return 0;
}
*/

/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
        while (1){
        socket->write("input> ");
         socket->waitForBytesWritten(1000);
        while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }
         qDebug()<<"Reading"<<socket->bytesAvailable();
         QString c = socket->readLine(10);
         qDebug()<<c;
         QString d="you type: "+c;
         char const* ch = d.toLocal8Bit().constData();
         socket->write(ch);
         if (strcmp(ch,"exit")==0) socket->close();
        }

    }
    else  {  qDebug()<<"Not Connected";
  }
}
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
         socket->write("hello\n");
         socket->waitForBytesWritten(1000);
        while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }
         qDebug()<<"Reading"<<socket->bytesAvailable();
         //qDebug()<<socket->readLine(10);
         qDebug()<<socket->readAll();
         socket->close();
    }
    else  {  qDebug()<<"Not Connected";
  }
}
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
       for (int i=5; i>=0; --i)
       {
         QString c = QString::number(i);
         QString d="hello "+c;
         char const* ch = d.toLocal8Bit().constData();
         socket->write(ch);
         socket->write("\n");
         socket->waitForBytesWritten();
         QThread::sleep (1);
       }
       socket->write("BOOM!!!\n");
       socket->waitForBytesWritten();
       socket->close();
    }
    else  {  qDebug()<<"Not Connected";    }
  }
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
     }
         socket->write("Hello\n");
         socket->write("World\n");
       socket->waitForBytesWritten();
       socket->close();
    }
*/


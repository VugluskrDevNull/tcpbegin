#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;

int main()
{
    QTcpSocket *socket;

    socket = new QTcpSocket(NULL);
    socket->connectToHost("5.196.134.158", 6667);
    if (!socket->waitForConnected(1000))
    {
      qDebug() << "Not Connected";
      return 1;
    }
    qDebug() << "Connected";
    while (1)
    {
      while ( !(socket->bytesAvailable()))
      {
        socket->waitForReadyRead(10000);
      }

      qDebug() << socket->readAll();
      socket->write( "NICK test_bot\n ");
      socket->write( "PING\n");

      while (!( socket->bytesAvailable()))
      {
        socket->waitForBytesWritten(10000);
      }
      qDebug() << socket->readAll();
      socket->write( "USER qwert_zaq 8 x : qwert_zaq\n");

      while (!( socket->bytesAvailable()))
      {
        socket->waitForBytesWritten(10000);
      }
      qDebug() << socket->readAll();
      socket->write("JOIN #RusChat\n");

      while (!( socket->bytesAvailable()))
      {
        socket->waitForBytesWritten(10000);
      }
      qDebug() << socket->readAll();
      socket->write("PRIVMSG #RusChat : hi from netcat\n");

      while (!( socket->bytesAvailable()))
      {
        socket->waitForBytesWritten(10000);
      }
      qDebug() << socket->readAll();
      socket->write("PONG irc.lucky.net\n ");

      while(socket->bytesAvailable() == 0) {
      socket->waitForReadyRead(100);
      }
      socket->close();
   }


      return 0;
}

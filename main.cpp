#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;
//  послать боту пять строчек, каждую секунду, "hello <число>", где число от 5 до 0, и под конец послать "boom!" и отключится

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


 /*
int main()
{
   QTcpSocket * socket;
   socket = new QTcpSocket(NULL);
   socket->connectToHost("62.149.7.206", 6660);    // 62.149.7.200/29
   if (socket->waitForConnected (1000))
   {
       qDebug() << "Connected";
       socket->write(" /nick testB /motd /join #politics_open /privmsg #politics_open hello! /quit");
       socket->waitForBytesWritten();
       socket->close();
   }
   else  {  qDebug()<<"Not Connected";    }
  // void QThread::sleep (unsigned long  secs);
    QThread::sleep (1);
}
*/
/*
int main()
{
   QTcpSocket * socket;
  // socket = new QTcpSocket(this);
     socket = new QTcpSocket(NULL);
   socket->connectToHost("127.0.0.1", 4567);
   if (socket->waitForConnected (1000))
   {
       qDebug() << "Connected";
       //flush();
       socket->write("hello\r\n");
       socket->waitForBytesWritten();
       socket->close();
   }
   else  {  qDebug()<<"Not Connected";    }
}
*/

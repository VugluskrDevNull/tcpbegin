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



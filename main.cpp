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


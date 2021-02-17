#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>

#ifndef IRCBOT_H
#define IRCBOT_H

class Bot : public QObject
{
    Q_OBJECT;
    int port;
    QString server;
    QString nick;
    QString channel;
    QTcpSocket *socket;

public :
     Bot (const QString _server = "irc.lucky.net",
          const int _port = 6667,
          const  QString _nick ="test_bot",
          const QString _channel = "#ruschat" )
     {
         port = _port;
         server = _server;
         nick = _nick;
         channel = _channel;
         socket = new QTcpSocket(NULL);
         QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected ()));
     };
     ~Bot ()
     {
         delete socket;
     }

    QString read_blocked();
    bool connect();
    void send(QString );

    void config_save();
    void disconnect();
    void config_load();
    QString rename(QString , QString);
    void loop();
    void registr();
    void codepage();
    void join();
public slots :
     void connected ();

//  signals:
};

#endif


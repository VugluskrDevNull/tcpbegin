#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>

#ifndef IRCBOT_H
#define IRCBOT_H

#define DEFAULT_SERVER "irc.lucky.net"
#define DEFAULT_PORT 6667
#define DEFAULT_NICK "test_bot"
#define DEFAULT_CHAN "#ruschat"

struct BotConfig
{
    QString ser;
    int por ;
    QString ni ;
    QString chan;
 };

BotConfig conf = { .ser = DEFAULT_SERVER, .por = DEFAULT_PORT, .ni = DEFAULT_NICK, .chan = DEFAULT_CHAN };

class Bot : public QObject
{
    Q_OBJECT;
    int port;
    QString server;
    QString nick;
    QString channel;
    QTcpSocket *socket;

public :
    Bot ()
    {
        BotConfig login = config_load();
        port = login.por;
        server = login.ser;
        nick = login.ni;
        channel = login.chan;
        socket = new QTcpSocket(NULL);
        QObject::connect(socket, SIGNAL(connected()), this, SLOT(config_load()));
        QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected ()));
        QObject::connect(socket, SIGNAL(connected()), this, SLOT(loop ()));
        QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected ()));
        QObject::connect (socket, SIGNAL (connected()), this, SLOT (foo()));
        QObject::connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
     };

     ~Bot ()
     {
         delete socket;
     }

    QString read_blocked();
    bool connect();
    void send(QString );
    void config_save();
    QString rename(QString , QString);
    void registr();
    void codepage();
    void join();
public slots :
     void connected ();
     void disconnected();
     BotConfig config_load();
     void loop();
     void foo() {qDebug()<<"foo()\n";  if(socket->QAbstractSocket::bytesAvailable()) qDebug()<<"get line\n";}
     void bytesWritten(qint64);
//  signals:
};

#endif


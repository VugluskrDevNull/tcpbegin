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

        QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected ()));
        QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected ()));

        QObject::connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
        //QObject::connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
        QObject::connect(socket, SIGNAL(signal_channel_joined()),this, SLOT(slot_channel_joined()));
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
    void codepage();
    void join();

    BotConfig config_load();

    void channel_msg(const QString *msg);

public slots :
     //void connected ();
     void disconnected();
     void readyRead();
     void slot_channel_joined();
  signals:
     void signal_channel_joined();
};

#endif

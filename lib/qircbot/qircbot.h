#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include "Interface.h"


#ifndef IRCBOT_H
#define IRCBOT_H

#define DEFAULT_SERVER "irc.lucky.net"
#define DEFAULT_PORT 7777
#define DEFAULT_NICK "test_bot"
#define DEFAULT_CHAN "#ruschat"

struct BotConfig
{
    QString ser;
    int por ;
    QString ni ;
    QString chan;
 };

class Bot : public Interface
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
        QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected ()));
        QObject::connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
     };

     ~Bot ()
     {
         delete socket;
     }
    void send_raw(QString);
    QString read_blocked();
    bool connect();

    void config_save();
    QString rename(QString , QString);
    void codepage();
    void join();
    BotConfig config_load();
    void channel_msg(const QString *msg);

    signals:
        void channelMessage( const QString &, const  QString &);
        void statusMessage(QString);
        void debugMessage(QString);

    public slots :
         void disconnected();
         void readyRead();
         void send(QString );
         void consoleInput(QString );
};

#endif


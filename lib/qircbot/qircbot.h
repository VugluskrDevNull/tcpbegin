#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include "Interface.h"


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

    QString read_blocked();
    bool connect();
    void send(QString );
    void config_save();
    QString rename(QString , QString);
    void codepage();
    void join();
    BotConfig config_load();
    void channel_msg(const QString *msg);

    signals:
        void userInput(QString);
    public slots :
         void disconnected();
         void readyRead();
};

#endif


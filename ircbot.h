#include <QTcpSocket>
#include <QFile>

#ifndef IRCBOT_H
#define IRCBOT_H

#include <QTcpSocket>
#include <QFile>

class Bot
{
    int prt;
    QString def_server;
    QString def_nick;
    QString def_channel;
    QTcpSocket *socket;

    public :
     Bot (const int port = 6667,
          const QString server = "irc.lucky.net",
          const  QString nick ="test_bot",
          const QString ircbot_channel = "#ruschat" )
     {
         int prt = port;
         QString def_server = server;
         QString def_nick = nick;
         QString def_channel = ircbot_channel;
         socket = new QTcpSocket(NULL);
     };

    ~Bot () {}


    QString read_blocked();
    bool connect();
    void send(QString );
    void registr();
    void codepage();
    void join();
    void config_save();
    void disconnect();
    void config_load();
    QString rename(QString , QString);
    void loop();
};

#endif


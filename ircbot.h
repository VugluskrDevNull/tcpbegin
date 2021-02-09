#include <QTcpSocket>
#include <QFile>

#ifndef IRCBOT_H
#define IRCBOT_H

#include <QTcpSocket>
#include <QFile>

class Bot
{
    public :
    int prt;
    QString def_server;
    QString def_nick ;
    QString def_channel;
    QTcpSocket *socket;
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


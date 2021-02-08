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
    QString read_blocked(Bot *);
    bool connect(Bot *);
    void send(Bot *, QString );
    void registr(Bot *);
    void codepage(Bot *);
    void join(Bot *);
    void config_save(Bot *);
    void disconnect(Bot *);
    void config_load(Bot *);
    QString rename(Bot *, QString , QString );
    void loop(Bot *);
};

#endif

/*
#ifndef IRCBOT_H
#define IRCBOT_H

#include <QTcpSocket>
#include <QFile>

struct ircbot
{
    int prt;
    QString def_server;
    QString def_nick ;
    QString def_channel;
    QTcpSocket *socket;
};

QString ircbot_read_blocked(ircbot *);
bool ircbot_connect(ircbot *);
void ircbot_send(QTcpSocket *, QString );
void ircbot_register(ircbot *);
void ircbot_codepage(ircbot *);
void ircbot_join(ircbot *);
void ircbot_config_save(ircbot *);
void ircbot_disconnect(ircbot *);
void ircbot_config_load(ircbot *);
QString ircbot_rename(ircbot *, QString , QString );
void ircbot_loop(ircbot *);

#endif
*/

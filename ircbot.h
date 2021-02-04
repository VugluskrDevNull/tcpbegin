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
};

QString ircbot_read_blocked(QTcpSocket *);
bool ircbot_connect(ircbot *, QTcpSocket *);
void ircbot_send(QTcpSocket *, QString );
void ircbot_register(ircbot *, QTcpSocket *);
void ircbot_codepage(QTcpSocket *);
void ircbot_join(ircbot *, QTcpSocket *);
void ircbot_config_save(ircbot *);
void ircbot_disconnect(QTcpSocket *, ircbot *);
void ircbot_config_load(ircbot *);
QString ircbot_rename(ircbot *, QString , QTcpSocket *, QString );
void ircbot_loop(ircbot *, QTcpSocket *);

#endif

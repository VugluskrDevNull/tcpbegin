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

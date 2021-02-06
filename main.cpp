#include <QTcpSocket>
#include "ini.h"
#include "ircbot.h"
using namespace std;


int main()
{
    ircbot *ptrini = new ircbot;
    ptrini->prt  =port;
    ptrini->def_server= server;
    ptrini->def_nick=nick;
    ptrini->def_channel=ircbot_channel;

    ircbot_config_load(ptrini);
    QTcpSocket *socket;
    socket = new QTcpSocket(NULL);
    if (!(ircbot_connect(ptrini, socket)))
        return  1;
    ircbot_register(ptrini, socket);
    ircbot_codepage(socket);
    ircbot_join(ptrini, socket);
    ircbot_loop(ptrini, socket);
    return 0;
}


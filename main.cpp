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
    ptrini->socket = new QTcpSocket(NULL);
    ircbot_config_load(ptrini);

    if (!(ircbot_connect(ptrini)))
        return  1;
    ircbot_register(ptrini);
    ircbot_codepage(ptrini);
    ircbot_join(ptrini);
    ircbot_loop(ptrini);
    return 0;
}


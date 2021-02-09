#include <QTcpSocket>
#include "ini.h"
#include "ircbot.h"
using namespace std;

int main()
{
    Bot  *ptrini = new Bot;
    ptrini->prt  =port;
    ptrini->def_server= server;
    ptrini->def_nick=nick;
    ptrini->def_channel=ircbot_channel;
    ptrini->socket = new QTcpSocket(NULL);
    ptrini->config_load();

    if (!(ptrini->connect()))
        return  1;
    ptrini->registr();
    ptrini->codepage();
    ptrini->join();
    ptrini->loop();
    return 0;
}


// 1. надо релизнуть поставив таг  - git tag -a v1.0 -m "Version 2.0"  git push --follow-tags


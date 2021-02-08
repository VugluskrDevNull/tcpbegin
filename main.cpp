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
    ptrini->config_load(ptrini);

    if (!(ptrini->connect(ptrini)))
        return  1;
    ptrini->registr(ptrini);
    ptrini->codepage(ptrini);
    ptrini->join(ptrini);
    ptrini->loop(ptrini);
    return 0;
}

/*
 то что ты сделал, это типичный процедурный подход. есть некий API (application programming interface) который описан в .h.
 структура содержит данные, все функции как первый параметр принимают указатель на него
 вот потом появился страуструп и добавил классы. так что 1. надо релизнуть поставив таг 2. сделать новый бранч
 refactoring/oop 3. и преобразовать libircbot.cpp в c++ стиль. с классом ircbot, всеми данными и
13:07:28 ... функциями внутри этого класса
 сделать новый бранч refactoring/oop 3. и преобразовать libircbot.cpp в c++ стиль. с классом ircbot, всеми данными
 и  функциями внутри этого класса
 1. надо релизнуть поставив таг  - git tag -a v1.0 -m "Version 1.0"  git push --follow-tags

struct в class, пересети объявление всех функций внутрь класса, убрать из названия функций префикс "ircbot_"
 */

/*
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
*/

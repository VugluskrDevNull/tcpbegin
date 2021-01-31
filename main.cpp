#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include <QFile>
#include  <QAbstractSocket>
#include <fstream>
#include "ini.h"
#include "ircbot.h"
#include "libircbot.cpp"
using namespace std;

/*
1. создать новый бранч refactoring/lib (lib от слова "library" библиотека) на основе master
2. создать новый файл в libircbot.cpp
3. скопировать всё функции начинающиеся с ircbot в  этот файл
4. создать ircbot.h в  который нужно перенести описание структуры ircbot и предописание всех фунукций в libircbot.cpp
5. #include "ircbot.h" в main.cpp
6. добавить в .pro файл (не .user.pro) имя  нового .cpp файла
 */



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


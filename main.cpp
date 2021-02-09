#include <QTcpSocket>
//#include "ini.h"
#include "ircbot.h"
using namespace std;

int main()
{
    Bot  * botptr = new Bot;
    botptr->config_load();

    if (!(botptr->connect()))
        return  1;
    botptr->registr();
    botptr->codepage();
    botptr->join();
    botptr->loop();
    return 0;
}


// 1. надо релизнуть поставив таг  - git tag -a v1.0 -m "Version 2.0"  git push --follow-tags


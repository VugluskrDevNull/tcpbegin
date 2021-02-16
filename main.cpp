#include <QTcpSocket>
#include "ircbot.h"
using namespace std;

int main()
{
    Bot  * botptr = new Bot;
    botptr->config_load();
    if (!(botptr->connect()))
        return  1;

    botptr->loop();
    return 0;
}





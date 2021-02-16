#include <QTcpSocket>
#include "ircbot.h"
using namespace std;

// дать таки назвать foo как и задумывалось "connected", и там уже делать всякие register(), codepage() и join()

int main()
{
    Bot  * botptr = new Bot;
    botptr->config_load();
    if (!(botptr->connect()))
        return  1;

    botptr->loop();
    return 0;
}





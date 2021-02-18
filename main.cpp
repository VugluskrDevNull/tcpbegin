#include <QTcpSocket>
#include "ircbot.h"
using namespace std;

int main()
{
    Bot  * botptr = new Bot;
    if (!(botptr->connect()))
        return  1;
    return 0;
}


/*
прикрути к боту слот который реагирует на то что данные от QTcpSocket пришли.
 внутри функции слота просто выводить в лог "данные пришли" не читая сами данные
 я правада не уверен что оно без QCoreApplication и его exec() лупа работать будет, вот как раз и проверим :)
*/


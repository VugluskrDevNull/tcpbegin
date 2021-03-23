#include "ircbot.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Bot *botptr = new Bot;
    if (!(botptr->connect()))
        return  1;

    return a.exec();
}


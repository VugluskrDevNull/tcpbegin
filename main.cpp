#include "ircbot.h"
using namespace std;

int main()
{
    Bot  * botptr = new Bot;
    if (!(botptr->connect()))
        return  1;
    return 0;
}





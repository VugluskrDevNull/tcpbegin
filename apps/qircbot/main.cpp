#include <qircbot.h>
#include "timebomb.h"
#include "console.h"
using namespace std;


int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    QCoreApplication a(argc, argv);
        Bot * bot= new Bot;
        GameTimeBomb * game = new GameTimeBomb (bot);
        if (!(bot->connect()))
            return  1;
        QObject::connect(bot, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));  //  запуск игры онлайн
        return a.exec();
}



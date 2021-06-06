#include <qircbot.h>
#include "timebomb.h"
#include "console.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Bot * bot= new Bot;
    GameTimeBomb * game = new GameTimeBomb (bot);
    if (!(bot->connect()))
        return  1;    
    QObject::connect(bot, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));  //  запуск игры онлайн
    return a.exec();
}

/*
    QCoreApplication app(argc, argv);

    qDebug()<<"enter !bomb\n";
    Console *cons = new Console();
    GameTimeBomb *pg = new GameTimeBomb(cons);
    cons->run();
    QObject::connect(cons, SIGNAL (userInput(QString)), pg,  SLOT(userInput(QString)));    //  запуск интерфейса офлайн
    QObject::connect(cons, SIGNAL(quit()), &app, SLOT(quit()));
    QObject::connect(cons, SIGNAL(quit()), pg, SLOT(quit()));
    return app.exec();
 */

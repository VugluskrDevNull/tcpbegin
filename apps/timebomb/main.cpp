#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QTime>

 #include "console.h"
#include "qircbot.h"        // не видится
 #include <timebomb.h>

int main(int argc, char** argv)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    QCoreApplication app(argc, argv);

    qDebug()<<"enter !bomb\n";
    Console *cons = new Console();
    Bot * bot = new Bot;
    GameTimeBomb * game = new GameTimeBomb(cons);
   //  pg->game_bomb("!bomb");
   //  pg->game_bomb("krasniy");
    cons->run();
    QObject::connect(cons, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));    //  запуск игры офлайн
   QObject::connect(game, SIGNAL (userInput(QString)), bot,  SLOT(send(QString)));           // send как слт
    QObject::connect(cons, SIGNAL(quit()), &app, SLOT(quit()));
    QObject::connect(cons, SIGNAL(quit()), game, SLOT(quit()));
    return app.exec();
}



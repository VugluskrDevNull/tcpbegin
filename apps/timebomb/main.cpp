#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QTime>

 #include "console.h"
 #include "Interface.h"        //
 #include <timebomb.h>

int main(int argc, char** argv)
{
#ifdef Q_OS_WIN
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    QCoreApplication app(argc, argv);

    qDebug()<<"enter !bomb\n";
    Console *cons = new Console();
    GameTimeBomb * game = new GameTimeBomb(cons);
   //  pg->game_bomb("!bomb");
   //  pg->game_bomb("krasniy");
    cons->run();
    QObject::connect(cons, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));    //  запуск игры офлайн
    QObject::connect(game, SIGNAL (send(QString)), cons,  SLOT(send(QString)));           // send как слт
    QObject::connect(cons, SIGNAL(quit()), &app, SLOT(quit()));
    QObject::connect(cons, SIGNAL(quit()), game, SLOT(quit()));
    return app.exec();
}



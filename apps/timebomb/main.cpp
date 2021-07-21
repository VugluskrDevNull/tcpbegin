#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QTime>

#include "console.h"
//#include "Interface.h"        //
#include <timebomb.h>

int main(int argc, char** argv)
{
#ifndef Q_OS_WIN32
  setlocale(LC_ALL, "");
#endif
    QCoreApplication app(argc, argv);

    qDebug()<<"enter !bomb\n";
    Console *cons = new Console();
    GameTimeBomb * game = new GameTimeBomb(cons);

    cons->run();
    QObject::connect(cons, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));    //  запуск игры офлайн
    QObject::connect(game, SIGNAL (send(QString)), cons,  SLOT(send(QString)));
    QObject::connect(cons, SIGNAL(quit()), &app, SLOT(quit()));
    QObject::connect(cons, SIGNAL(quit()), game, SLOT(quit()));
    return app.exec();
}



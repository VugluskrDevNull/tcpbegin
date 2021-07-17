#include "mainwindow.h"
#include "qircbot.h"
#include "timebomb.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Bot * bot= new Bot;
    GameTimeBomb * game = new GameTimeBomb (bot);
    QObject::connect(bot, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));
    w.show();
    return a.exec();
}




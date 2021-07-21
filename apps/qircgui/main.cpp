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
    QObject::connect(bot, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));  // соединение бота с игрой
    QObject::connect(& w, SIGNAL (send(QString)), bot,  SLOT(send(QString)));      // соединение бота с гуи
    w.show();
    return a.exec();
}




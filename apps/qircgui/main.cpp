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

    if (!(bot->connect()))
        return  1;

    // соединение бота с игрой
    QObject::connect(bot, SIGNAL (channelMessage(QString)), game, SLOT(userInput(QString)));
    QObject::connect(game, SIGNAL (send(QString)), bot,  SLOT(send(QString)));           // сообщения от игры к боту

    // соединение бота с гуи
    QObject::connect(&w,  SIGNAL(sendChannelMessage(QString)), bot,  SLOT(send(QString)));
    QObject::connect(bot, SIGNAL(channelMessage(QString)),     &w,   SLOT(addChannelLog(QString)));
    QObject::connect(bot, SIGNAL(statusMessage(QString)),      &w,   SLOT(addStatusLog(QString)));
    QObject::connect(bot, SIGNAL(debugMessage(QString)),       &w,   SLOT(addDebugLog(QString)));
    w.show();
    return a.exec();
}

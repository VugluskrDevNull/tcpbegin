#include <qircbot.h>
#include "timebomb.h"
#include "console.h"
#include "mainwindow.h"
using namespace std;


int main(int argc, char *argv[])
{
#ifndef Q_OS_WIN32
  setlocale(LC_ALL, "");
#endif
    QCoreApplication a(argc, argv);
    Bot * bot= new Bot;
    GameTimeBomb * game = new GameTimeBomb (bot);
    Console * cons = new Console;
    MainWindow w;                       // подключаем гуй
    if (!(bot->connect()))
        return  1;
    QObject::connect(bot, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));  //  запуск игры онлайн
    QObject::connect(game, SIGNAL (send(QString)), bot,  SLOT(send(QString)));           // сообщения от игры к боту
    QObject::connect(cons, SIGNAL (userInput(QString)), bot,  SLOT(consoleInput(QString)));            // пишем в чат через консоль
    QObject::connect(& w, SIGNAL (send(QString)), bot,  SLOT(send(QString)));      // посыл строки из окна в чат
    return a.exec();
}


/*
 ну тоесть в Interface он у тебя описан как виртуальная функция. а в Console ты его описываешь как слот. ниче не смущает?
но Console наследуется от Interface
*/

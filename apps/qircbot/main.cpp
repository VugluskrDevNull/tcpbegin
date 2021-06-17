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
        Console * cons = new Console;
        GameTimeBomb * game = new GameTimeBomb (bot);
        if (!(bot->connect()))
            return  1;
        QObject::connect(bot, SIGNAL (userInput(QString)), game,  SLOT(userInput(QString)));  //  запуск игры онлайн
        QObject::connect(game, SIGNAL (send(QString)), bot,  SLOT(send(QString)));           // send как слoт
        QObject::connect(cons, SIGNAL (userInput(QString)), bot,  SLOT(consoleInput(QString)));            // пишем в чат через консоль
        return a.exec();
}


/*
 ну тоесть в Interface он у тебя описан как виртуальная функция. а в Console ты его описываешь как слот. ниче не смущает?
но Console наследуется от Interface

: QObject::connect(game, SIGNAL (userInput(QString)), bot,  SLOT(send(QString)));
 соединить (объект) игры сигналом "пользовательский вход" со слотом send() объекта бота. тоесть по сути
объект game должен делать у тебя emit userInput(). много у тебя в игре emit userInput()? можешь их
 посчитать?
*/

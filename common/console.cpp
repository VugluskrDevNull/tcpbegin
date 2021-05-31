#include <iostream>                   // console.cpp
#include "console.h"
#include <QString>
#include <QDebug>

Console::Console()
{
   // m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
#ifdef Q_OS_WIN
    m_notifier = new QWinEventNotifier(GetStdHandle(STD_INPUT_HANDLE));
    connect(m_notifier, &QWinEventNotifier::activated
#else
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated
#endif
        , this, &Console::readCommand);

}

void Console::run()
{
    std::cout << "First message" << std::endl;
    std::cout << "> " << std::flush;
}

void Console::readCommand()
{
    std::cout << "readCommand()" << std::endl;    // debug
    std::string line;
    std::getline(std::cin, line);
    if (std::cin.eof() || line == "quit") {
        std::cout << "Good bye!" << std::endl;
        emit quit();
    } else {
        std::cout << "Echo: " << line << std::endl;
        std::cout << "> " << std::flush;
        retline=line.c_str();
        emit userInput(retline);
    }
}

void Console::send(QString str)
{
    qDebug() << str << '\n';
}


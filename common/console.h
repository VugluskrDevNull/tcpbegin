#ifndef CONSOLE_H
#define CONSOLE_H
#pragma once                                   // console.h

#include <QObject>
#include "Interface.h"
#ifdef Q_OS_WIN
#include <QWinEventNotifier>
#include <windows.h>
#else
#include <QSocketNotifier>
#endif
#include <iostream>

class Console : public Interface
{
    QString retline;
    Q_OBJECT;
public:
    Console();
    void run();
    void send(QString);
signals:
    void quit();
    void userInput(QString);
private:

#ifdef Q_OS_WIN
    QWinEventNotifier *m_notifier;
#else
    QSocketNotifier *m_notifier;
#endif


private slots:
    void readCommand();
};

#endif // CONSOLE_H

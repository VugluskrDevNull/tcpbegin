#ifndef CONSOLE_H
#define CONSOLE_H
#pragma once                                   // console.h

#include <QObject>
#include <QThread>
#include "Interface.h"
#ifdef Q_OS_WIN
#include <QWinEventNotifier>
#include <windows.h>
#include <fcntl.h>
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
signals:
    void quit();
    void userInput(QString);

private:
    QThread m_thread;
#ifdef Q_OS_WIN
    QWinEventNotifier *m_notifier;
#else
    QSocketNotifier *m_notifier;
#endif

private slots:
    void readCommand();
    void send(QString);
    void on_finishedGetLine(const QString &);

signals:
    // finishedGetLine if for internal use
    void finishedGetLine(const QString &strNewLine);
};

#endif // CONSOLE_H

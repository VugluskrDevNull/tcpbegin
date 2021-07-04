#include <iostream>                   // console.cpp
#include "console.h"
#include <QString>
#include <QDebug>
#include <QTextStream>

Console::Console()
{
    QObject::connect(
            this, &Console::finishedGetLine,
            this, &Console::on_finishedGetLine,
            Qt::QueuedConnection
    );

#ifdef Q_OS_WIN
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);

    m_notifier = new QWinEventNotifier(GetStdHandle(STD_INPUT_HANDLE));

    // NOTE : move to thread because std::getline blocks,
    //        then we sync with main thread using a QueuedConnection with finishedGetLine
    m_notifier->moveToThread(&m_thread);
    QObject::connect(
            &m_thread , &QThread::finished,
            m_notifier, &QObject::deleteLater
    );
    m_thread.start();
    connect(m_notifier, &QWinEventNotifier::activated
#else
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read);
    connect(m_notifier, &QSocketNotifier::activated
#endif
        , this, &Console::readCommand);

}

void Console::run()
{
    send("> ");
}


void Console::readCommand()
{
    QString res;
#ifdef Q_OS_WIN32
    const int bufsize = 512;
    wchar_t buf[bufsize];
    DWORD read;

    do {
      ReadConsoleW(GetStdHandle(STD_INPUT_HANDLE),
          buf, bufsize, &read, NULL);
      res += QString::fromWCharArray(buf, read);
    } while (read > 0 && res[res.length() - 1] != '\n');

    while (res.length() > 0
           && (res[res.length() - 1] == '\r' || res[res.length() - 1] == '\n'))
      res.truncate(res.length() - 1);
#else
    res = QTextStream(stdin).readLine(0);
#endif
    send (res);
    emit finishedGetLine(res);
}

void Console::on_finishedGetLine(const QString &strNewLine)
{
    emit userInput(strNewLine);
}

void Console::send(QString str)
{
#ifdef Q_OS_WIN
      WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
          str.utf16(), str.size(), NULL, NULL);
#else
    QTextStream(stdout) << str << "\n";
#endif
}

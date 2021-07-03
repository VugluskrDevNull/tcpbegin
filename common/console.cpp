#include <iostream>                   // console.cpp
#include "console.h"
#include <QString>
#include <QDebug>
#include <QTextStream>

Console::Console()
{
#ifdef Q_OS_WIN
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);

    m_notifier = new QWinEventNotifier(GetStdHandle(STD_INPUT_HANDLE));

    QObject::connect(
            this, &Console::finishedGetLine,
            this, &Console::on_finishedGetLine,
            Qt::QueuedConnection
    );

    connect(m_notifier, &QWinEventNotifier::activated
#else
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated
#endif
        , this, &Console::readCommand);

    m_notifier->moveToThread(&m_thread);      // 30.06

    QObject::connect(                          //30.06
            &m_thread , &QThread::finished,
            m_notifier, &QObject::deleteLater
    );
}

void Console::run()
{
    send("> ");
}


void Console::readCommand()
{
    #ifdef Q_OS_WIN32
      const int bufsize = 512;
      wchar_t buf[bufsize];
      DWORD read;
      QString res;
      do {
        ReadConsoleW(GetStdHandle(STD_INPUT_HANDLE),
            buf, bufsize, &read, NULL);
        res += QString::fromWCharArray(buf, read);
      } while (read > 0 && res[res.length() - 1] != '\n');
      while (res.length() > 0
             && (res[res.length() - 1] == '\r' || res[res.length() - 1] == '\n'))
        res.truncate(res.length() - 1);
      #else
      return QTextStream::readLine();
    #endif
        send (res);
        send ("\n");
        emit finishedGetLine(res);     // 30.06

}

void Console::on_finishedGetLine(const QString &strNewLine)     // 30.06
{
    Q_EMIT this->userInput(strNewLine);
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

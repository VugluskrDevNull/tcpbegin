#include <QCoreApplication>                                                 // GameTimeBomb.cpp
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include "timebomb.h"
#include <QTimer>
#include "QTime"
#include <QRandomGenerator>

void GameTimeBomb::slotTimerAlarm()
{
    qDebug()<<"BOOM!!!BANG!!!";
    state = STATE_OFF;
}

void GameTimeBomb::userInput(QString qs)
{

    if(qs.indexOf("!bomb")!=-1)                    // проверка ввода
    {
        if (state == STATE_GAME) return;
        start_game();
    }
   if(state == STATE_GAME && qs==provodki_rand[yes])    // проверяем угадал ли пользователь цвет проводка
    {
        iface->send("WIN!");
        timer->stop();
        state = STATE_OFF;
    }
}

void GameTimeBomb::start_game()
{
    state = STATE_GAME;
    n = QRandomGenerator::global()->bounded(2, 8);
    int SZ=7;
    int ind[SZ];

    for (int i = 0; i < SZ; i++)
    {
        ind[i]=  i;
    }

    for (int i = 0; i < SZ; i++)
    {
        int n1 =  QRandomGenerator::global()->bounded(0, n);
        std::swap(ind[i], ind[n1]);   // или int n2 =  rand()%SZ; std::swap(m[n1], m[n2]);
    }

    for (int i = 0; i < n; i++)
    {
         provodki_rand[i]=provodki[ind[i]];
    }

    yes =  QRandomGenerator::global()->bounded(0, n);
    qDebug()<<" otrej "<<provodki_rand[yes]<<endl;
    timer->start(30000);
    iface->send("pered Vami bomba s taymerom ustanovlennym na 30 sec i "+ QVariant(n).toString() +" provodkov");
    for (int i=0; i<n; i++)
    {
        iface->send(provodki_rand[i]);
    }
}

void GameTimeBomb::quit()
{
    qInfo() << "Good bye!";
}

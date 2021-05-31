#ifndef GAMETIMEBOMB_H                               // GameTimeBomb.h
#define GAMETIMEBOMB_H

#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include "console.h"

class GameTimeBomb: public QObject
{
    Q_OBJECT
   // Console * cons2;
    Interface * iface;
    enum { STATE_IDLE = 1, STATE_GAME, STATE_OFF };
    inline static constexpr const char* const provodki[] ={"krasniy", "orangeviy", "jeltiy", "zelyoniy", "goluboy", "siniy", "fioletoviy"};
    void start_game();
    public:
    GameTimeBomb(Console * _iface)  {
        iface=_iface;
        timer = new QTimer();
        timer->setSingleShot(true);
        state = STATE_IDLE;
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    }
    private slots:
    void slotTimerAlarm();
    void userInput(QString);
    void quit();
    private:
    QTimer *timer;
    int n;                              // число проводков
    const char *provodki_rand[sizeof(provodki)/sizeof(provodki[0])];       // массив случайных проводков
    int yes=0;                          // порядковый номер правильного проводка
    int state=0;                          // состояние игры
};


#endif // GAMETIMEBOMB_H


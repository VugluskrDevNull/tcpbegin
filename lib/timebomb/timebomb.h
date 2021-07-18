#ifndef GAMETIMEBOMB_H                               // GameTimeBomb.h
#define GAMETIMEBOMB_H

#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include "Interface.h"

class GameTimeBomb: public QObject
{
    Q_OBJECT
    Interface * iface;
    enum { STATE_IDLE = 1, STATE_GAME, STATE_OFF };
    inline static constexpr const char* const provodki[] ={"красный", "оранжевый", "жёлтый", "зелёный", "голубой", "синий", "фиолетовый"};
    void start_game();
    public:
    GameTimeBomb(Interface * _iface)  {
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
    signals :
    void send(QString);
    private:
    QTimer *timer;
    int n;                              // число проводков
    const char *provodki_rand[sizeof(provodki)/sizeof(provodki[0])];       // массив случайных проводков
    int yes=0;                          // порядковый номер правильного проводка
    int state=0;                          // состояние игры
};


#endif // GAMETIMEBOMB_H


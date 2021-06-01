#ifndef INTERFACE_H                                  // Interface.h
#define INTERFACE_H

#include <QString>
#include <QObject>

class Interface : public QObject
{
    Q_OBJECT;
public:
    void run();                         // from console
    virtual   void send(QString)=0;
signals:
    void quit();
    void userInput(QString);
};

#endif // INTERFACE_H

#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
/*
только что "в случае успешного вызова ф-ции connected() указателем socket" тут connected() вообще не функция. они её сделали что бы она
 выглядела в виде функции что бы типы slot-ов которые  подсоеденяются к этому сигналу проверять. если бы connected() была функцией, то где
то должно быть её тело. но его нет. но в принципе в твоём определении ничего противоречивого нет
 ты ж в Object::connect это и описываешь. сигнал connected идёт от QTcpSocket, и по его приходу вызывается слот connected в MyTcpSocket
 ну в QTcpSocket-е сигнал connected() описан. ага, для галочки
: у тебя пока нет своего сигнала. ты принимаешь сигнал от QTcpSocket, путём подключения к своему slot-у
соединить свой слот connected() с сигналом connected() от QTcpSocket ты можешь и в конструкторе или в Bot::connect() перед тем
как конектится к  серверу и внутри своего слова connected() уже вызывать register(), codepage() и join()
*/


#ifndef IRCBOT_H
#define IRCBOT_H

class Bot : public QObject
{
    Q_OBJECT;
    int port;
    QString server;
    QString nick;
    QString channel;
    QTcpSocket *socket;

public :
     Bot (const QString _server = "irc.lucky.net",
          const int _port = 6667,
          const  QString _nick ="test_bot",
          const QString _channel = "#ruschat" )
     {
         port = _port;
         server = _server;
         nick = _nick;
         channel = _channel;
         socket = new QTcpSocket(NULL);
         QObject::connect(socket, SIGNAL(QObject::connected()), SLOT( connected ()));
     };
     ~Bot ()
     {
         delete socket;
     }

    QString read_blocked();
    bool connect();
    void send(QString );



    void config_save();
    void disconnect();
    void config_load();
    QString rename(QString , QString);
    void loop();

public slots :
     void connected ();
     void registr();
     void codepage();
     void join();
//  signals:
};

#endif


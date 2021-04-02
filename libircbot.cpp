#include <iostream>
#include <QSettings>
#include "ircbot.h"
using namespace std;

BotConfig conf = { .ser = DEFAULT_SERVER, .por = DEFAULT_PORT, .ni = DEFAULT_NICK, .chan = DEFAULT_CHAN };

QSettings * settings = new QSettings( "settings.conf", QSettings::IniFormat );

QString Bot::read_blocked()
{
    while (!(socket->bytesAvailable()))
    {
        socket->waitForReadyRead(10000);
    }
    QString q = socket->readAll().constData();
    return q;
}

bool Bot::connect()
{
    socket->connectToHost(server.toLatin1().constData(), port);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void Bot::send(QString str)
{
    qDebug()<<">> " << str;

    socket->write(str.toLatin1().constData());
}
/*
void Bot::registr()
{
    send( "NICK "+ nick +"\n");
    send("USER qwert_zaq 8 x : qwert_zaq\n");
}
*/
void Bot::codepage()
{
    send("CODEPAGE UTF-8\n");
}

void Bot::join()
{
    send("JOIN " + channel + "\n");
    emit signal_channel_joined ();
}

void Bot::config_save()
{
    settings->beginGroup("login");
    settings->setValue("settings/server", server);
    settings->setValue("settings/port", port);
    settings->setValue("settings/nick", nick);
    settings->setValue("settings/channel", channel);
    settings->endGroup();
    settings->sync();
}


void Bot::disconnected()
{
    config_save();
    socket->close();
}

BotConfig Bot::config_load()
{
     BotConfig config;

     settings->beginGroup("login");
     config.ser = settings->value("settings/server", conf.ser).toString();
     config.por = settings->value("settings/port", conf.por).toInt();
     config.ni = settings->value("settings/nick", conf.ni).toString();
     config.chan = settings->value("settings/channel", conf.chan).toString();
     settings->endGroup();

     return config;
}


QString Bot::rename( QString oldn, QString q)
{
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG "+ channel , 0) != -1) && (msg.startsWith("!nick")))
    {
        msg = msg.remove(0, 5);
        msg= msg.simplified();
        if (msg.contains(QRegExp("[^a-zA-Z_-/d]")))
        {
            qDebug()<<"error nick\n";
        }
        else
        {
            QString h = "NICK "+msg+'\n';
            send(h);
            QString s = read_blocked();
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            nick = msg;
            config_save();
            return msg;
        }
    }
    return msg;
}

void Bot::channel_msg(const QString *msg)
{
    if (msg == NULL)
        return;

    if (msg->indexOf("!quit", 0)!= -1)
        disconnected();

    if ((msg->indexOf("PRIVMSG "+ channel, 0) != -1) && (msg->indexOf(nick , 0) != -1))
    {
        send("PRIVMSG " + channel + " : i hear you\n");
        socket->waitForBytesWritten();
    }

    if (msg->indexOf("PING", 0)!= -1)
    {
        send("PONG " + server + "\n");
    }

    if ((msg->indexOf("PRIVMSG "+ channel, 0) != -1) && (msg->indexOf("!nick" , 0) != -1))
    {
        nick = rename(nick, *msg);
    }
}

 void Bot::readyRead()
 {
     QString str = read_blocked();
     QStringList list = str.split(QLatin1Char('\n'), QString::SkipEmptyParts);

     QStringList::iterator  it;
     QString head;
     QString msg;
     for (it = list.begin(); it!=list.end(); ++it)
     {
         QString s=*it;

         qDebug() << "<<" << s;

         int n0=s.indexOf(':');                  // ищем 0е :
         if (s[0] != ':')
             continue;    //qDebug()<<"s[0] -"<<s[0]<<endl;  //
         if (s.indexOf(':', n0+1)==-1)
             continue;
         {
             int n1=s.indexOf(':', n0+1);            // ищем 1е :
             QStringRef head(&s, n0, n1-n0);
            // qDebug()<<"head - "<<head<<endl;
             QStringRef msg(&s, n1, (*it).length()-n1);
             //qDebug()<<"msg -"<<msg<<endl;
              QStringList header_fields;
              QString str3;
              str3.append(head);
              header_fields = str3.split(QLatin1Char(' '), QString::SkipEmptyParts);
              bool ok;
              int type = header_fields[1].toInt(&ok, 10);
              if ((header_fields[0].indexOf(server) != -1) && type == 20 && (header_fields[2].indexOf(server) != -1)) {
                  //исключение для 1 строки где нет nick
                  qDebug() << "!! type: " << type << "reply form server: " << msg;
                  send("NICK "+ nick +"\n");
                  send("USER qwert_zaq 8 x : qwert_zaq\n");

              } else if ((header_fields[0].indexOf(server) != -1) && ok && (header_fields[2].indexOf(nick) != -1)) {
                  qDebug() << "!! type: " << type << "reply form server: " << msg;

                  switch (type)
                  {
                      case 1 :
                          join();
                          break;
                  }
              } else if (header_fields[1].indexOf("JOIN") != -1 && msg.indexOf(channel) != -1) {
                  qDebug() << "!! joined to " << msg;
                  send("PRIVMSG " + channel + " :hi from netcat\n");
              } else if (header_fields[1].indexOf("PRIVMSG") != -1 && header_fields[2].indexOf(channel) != -1) {
                  qDebug() << "!! channel msg: " << msg;
                  channel_msg(msg.string());
              } else {
                  qDebug()<<"!! cannot parse\n";
              }

           }
       }
   }
 /*
  1. описать слот slot_channel_joined() (где выводишь на канал "hi from bot"  2. вставить отсылание сигнала в
правильном месте emit signal_channel_joined() 3. в конструкторе соедини с помощью QObject::connect() слот slot_channel_joined()
с сигналом signal_channel_joined() изменение топика уже потом, вторым шагом
сигнал   channel_joined()  делает send("PRIVMSG " + channel + " :hi from netcat\n"); и меняет топик

QObject::connect(socket почему socket-то? если slot_channel_joined() это твой сигнал в Bot, который ты опишешь
 в разделе signals  emit это излучать. излучают сигнал, а не слот
// QObject::connect(socket, SIGNAL(signal_channel_joined()),this, SLOT(slot_channel_joined()));
signals:
  void MySetValueSignal(int);
в сырцах, где надо послать сигнал, пишем:

emit MySetValueSignal(value);
ну и не забыть законнектить:

connect(this, SIGNAL(MySetValueSignal(int)), spinBox, SLOT(setValue(int)));
*/
 void Bot :: slot_channel_joined()
 {
     send("PRIVMSG " + channel + " :hi from netcat\n");
     send("SETTOPIC " + channel + " topic\n");
 }








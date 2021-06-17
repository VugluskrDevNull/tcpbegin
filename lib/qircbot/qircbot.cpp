#include <iostream>
#include <QSettings>

#include <qircbot.h>

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
    socket->connectToHost(server.toUtf8().constData(), port);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void Bot::send(QString msg)
{
    send_raw("PRIVMSG "+ channel + "  :" + msg + "\n");
}

void Bot::send_raw(QString str)
{
    qDebug()<<">> " << str;
    socket->write(str.toUtf8().constData());
}

void Bot::codepage()
{
    send_raw("CODEPAGE UTF-8\n");
}

void Bot::join()
{
    send_raw("JOIN " + channel + "\n");
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
            send_raw(h);
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
        send_raw("PRIVMSG " + channel + " : ась?\n");
        socket->waitForBytesWritten();
    }

    if ((msg->indexOf("PRIVMSG "+ channel, 0) != -1) && (msg->indexOf("!nick" , 0) != -1))
    {
        nick = rename(nick, *msg);
    }   
 }

  void Bot :: consoleInput(QString msg)
  {
       send( msg);
  }

 void Bot::readyRead()
 {
     QString str = read_blocked();
     if (str.indexOf("PING", 0)!= -1){                        // ping
         send_raw("PONG " + server + "\n");
     }
     QStringList list = str.split(QLatin1Char('\n'), QString::SkipEmptyParts);

     QStringList::iterator  it;
     QString head;
     QString msg;
     for (it = list.begin(); it!=list.end(); ++it)
     {
         QString s = *it;
         qDebug() << "<<" << s;
         int n0=s.indexOf(':');                  // ищем 0е :
         if (s[0] != ':')
             continue;    //qDebug()<<"s[0] -"<<s[0]<<endl;  //
         if (s.indexOf(':', n0+1)==-1)
             continue;
         {
             int n1=s.indexOf(':', n0+1);            // ищем 1е :
             QStringRef head(&s, n0, n1-n0);
           // qDebug()<<"head - "<<head<<endl;           // qdebug  head
           //  QStringRef msg(&s, n1, (*it).length()-n1);
             /*******************************************************************************************************/
             QStringRef msg(&s, n1 + 1, (*it).length() - n1 - 2); // - 2: remove \r\n in the end удаляем : и \r
             emit userInput(msg.toString());                                              // запуск игры со строкой без : и \r
             emit consoleInput(msg.toString());
             /*******************************************************************************************************/
           // qDebug()<<"msg -"<<msg<<endl;           // qdebug  msg
              QStringList header_fields;
              QString str3;
              str3.append(head);
              header_fields = str3.split(QLatin1Char(' '), QString::SkipEmptyParts);
              bool ok;
              int type = header_fields[1].toInt(&ok, 10);
              if ((header_fields[0].indexOf(server) != -1) && type == 20 && (header_fields[2].indexOf(server) != -1)) {
                  //исключение для 1 строки где нет nick
                  qDebug() << "!! type: " << type << "reply form server: " << msg;
                  send_raw("NICK "+ nick +"\n");
                  send_raw("USER qwert_zaq 8 x : qwert_zaq\n");
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
                  send_raw("PRIVMSG " + channel + " :здрасти!\n");
              } else if (header_fields[1].indexOf("PRIVMSG") != -1 && header_fields[2].indexOf(channel) != -1) {
                  qDebug() << "!! channel msg: " << msg;
                  channel_msg(msg.string());
              }  else {
                  qDebug()<<"!! cannot parse\n";
              }
           }
      }

   }




#include <iostream>
#include "ircbot.h"
using namespace std;

const char * reg_data = "bot_data.txt";
QFile init_file(reg_data);

#include <ircbot.h>

QString Bot::read_blocked()
{
    while (!(socket->bytesAvailable()))
    {
        socket->waitForReadyRead(10000);
    }
    QString q = socket->readAll().constData();
    qDebug()<<q;
    return q;
}

bool Bot::connect()
{
    socket->connectToHost(def_server.toLatin1().constData(), prt);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void Bot::send(QString q)
{
    //    cout<<"i send (cout) - "<<ch<<endl;
    qDebug()<<"i send (qDebug() ) - "<<q<<endl;
    socket->write(q.toLatin1().constData());
}

void Bot::registr()
{
    read_blocked();
    send( "NICK "+ def_nick +"\n");
    send("PING\n");
    read_blocked();
    send("USER qwert_zaq 8 x : qwert_zaq\n");
}

void Bot::codepage()
{
    read_blocked();
    send("CODEPAGE UTF-8\n");
}

void Bot::join()
{
    read_blocked();
    send("JOIN " + def_channel + "\n");
    read_blocked();
    send("PRIVMSG " + def_channel + " :hi from netcat\n");
}

void Bot::config_save()
{
    if(init_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        init_file.write(def_nick.toLatin1());
        init_file.close();
    }
    else
        cout<<"cant open file bot_data for save\n";
}

void Bot::disconnect()
{
    config_save();
    socket->close();
}

void Bot::config_load()
{
    if (!init_file.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
        qDebug()<<"name is "<<def_nick<<endl;
        config_save();
    }
    else
    {
        QTextStream in(&init_file);
        QString line = in.readLine();
        qDebug()<<"line is "<<line<<endl;
        def_nick = line;
        init_file.close();
    }
}

QString Bot::rename( QString oldn, QString q)
{
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG "+ def_channel , 0) != -1) && (msg.startsWith("!nick")))
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
            def_nick = msg;
            config_save();
            return msg;
        }
    }
}

void Bot::loop()
{
while (1)
{
    QString c = read_blocked();
    qDebug() << c;
    if (c.indexOf("!quit", 0)!= -1)
        disconnect();
    if ((c.indexOf("PRIVMSG "+ def_channel, 0) != -1) && (c.indexOf(def_nick , 0) != -1))
    {
        send("PRIVMSG " + def_channel + " : i hear you\n");
        socket->waitForBytesWritten();
    }
    if (c.indexOf("PING", 0)!= -1)
    {
        send("PONG " + def_server + "\n");
    }
    if ((c.indexOf("PRIVMSG "+ def_channel, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
    {
        def_nick = rename(def_nick, c);
    }
}
}


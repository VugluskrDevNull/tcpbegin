#ifndef LIBIRCBOT_CPP
#define LIBIRCBOT_CPP

QString ircbot_read_blocked(QTcpSocket *soc)
{
    while (!(soc->bytesAvailable()))
    {
        soc->waitForReadyRead(10000);
    }
    QString q = soc->readAll().constData();
    qDebug()<<q;
    return q;
}

bool ircbot_connect(ircbot *pi, QTcpSocket *soc)
{
    soc->connectToHost(pi->def_server.toLatin1().constData(), pi->prt);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!soc->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_send(QTcpSocket *soc, QString q)
{
    //    cout<<"i send (cout) - "<<ch<<endl;
    qDebug()<<"i send (qDebug() ) - "<<q<<endl;
    soc->write(q.toLatin1().constData());
}

void ircbot_register(ircbot *pi, QTcpSocket *soc)
{
    ircbot_read_blocked(soc);
    ircbot_send(soc, "NICK "+ pi->def_nick +"\n");
    ircbot_send(soc,"PING\n");
    ircbot_read_blocked(soc);
    ircbot_send(soc,"USER qwert_zaq 8 x : qwert_zaq\n");
}

void ircbot_codepage(QTcpSocket *soc)
{
    ircbot_read_blocked(soc);
    ircbot_send(soc,"CODEPAGE UTF-8\n");
}

void ircbot_join(ircbot *pi, QTcpSocket *soc)
{
    ircbot_read_blocked(soc);
    ircbot_send(soc, "JOIN " + pi->def_channel + "\n");
    ircbot_read_blocked(soc);
    ircbot_send(soc, "PRIVMSG " + pi->def_channel + " :hi from netcat\n");
}

void ircbot_config_save(ircbot *pi)
{
    if(init_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        init_file.write(pi->def_nick.toLatin1());
        init_file.close();
    }
    else
        cout<<"cant open file bot_data for save\n";
}

void ircbot_disconnect(QTcpSocket *soc, ircbot *pi)
{
    ircbot_config_save(pi);
    soc->close();
}

void ircbot_config_load(ircbot *pi)
{
    if (!init_file.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
        qDebug()<<"name is "<<pi->def_nick<<endl;
        ircbot_config_save(pi);
    }
    else
    {
        QTextStream in(&init_file);
        QString line = in.readLine();
        qDebug()<<"line is "<<line<<endl;
        pi->def_nick = line;
        init_file.close();
    }
}

QString ircbot_rename(ircbot *pi, QString oldn, QTcpSocket *soc, QString q)
{
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG "+ pi->def_channel , 0) != -1) && (msg.startsWith("!nick")))
    {
        msg = msg.remove(0, 5);
        msg= msg.simplified();
        if (msg.contains(QRegExp("[^a-zA-Z_-/d]"))) // ??? ??????, ??? ??? ? str ???-?? ??? ????? ???? ?? 'a' ?? 'z', 'A' ?? 'Z', '_' ? '-'
        {
            qDebug()<<"error nick\n";
        }
        else
        {
            QString h = "NICK "+msg+'\n';
            ircbot_send(soc, h);
            QString s = ircbot_read_blocked(soc);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            pi->def_nick = msg;
            ircbot_config_save(pi);
            return msg;
        }
    }
}

void ircbot_loop(ircbot *pi, QTcpSocket *soc)
{
while (1)
{
    QString c = ircbot_read_blocked(soc);
    qDebug() << c;
    if (c.indexOf("!quit", 0)!= -1)
        ircbot_disconnect(soc, pi);
    if ((c.indexOf("PRIVMSG "+ pi->def_channel, 0) != -1) && (c.indexOf(pi->def_nick , 0) != -1))
    {
        ircbot_send(soc, "PRIVMSG " + pi->def_channel + " : i hear you\n");
        soc->waitForBytesWritten();
    }
    if (c.indexOf("PING", 0)!= -1)
    {
        ircbot_send(soc, "PONG " + pi->def_server + "\n");
    }
    if ((c.indexOf("PRIVMSG "+ pi->def_channel, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
    {
        pi->def_nick = ircbot_rename(pi, pi->def_nick, soc, c);
    }
}
}

#endif
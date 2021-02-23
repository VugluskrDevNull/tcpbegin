#include <QTcpSocket>
#include <QSettings>
#include "ircbot.h"
using namespace std;
//в main надо сначала считать параметры, потом ими инициализировать конструктор, а потом уж конектится

struct Login
{
    QString ser;
    int por ;
    QString ni ;
    QString chan;
 };

int main()
{
    const QString _server = "irc.lucky.net";
    const int _port = 6667;
    const  QString _nick ="test_bot";
    const QString _channel = "#ruschat";

    QSettings * settings = new QSettings( "settings.conf", QSettings::IniFormat );
    settings->beginGroup("login");
    settings->setValue("settings/server",_server);
    settings->setValue("settings/port",_port);
    settings->setValue("settings/nick",_nick);
    settings->setValue("settings/channel",_channel);
    settings->endGroup();
    settings->sync();
    // qDebug() <<settings2->value("login/settings/userName");
     Login login;
      settings->beginGroup("login");
     login.ser = settings->value("settings/server", -1).toString();
     login.por = settings->value("settings/port", -1).toInt();
     login.ni = settings->value("settings/nick", -1).toString();
     login.chan = settings->value("settings/channel", -1).toString();
     settings->endGroup();

    Bot  * botptr = new Bot(login.ser, login.por, login.ni, login.chan);
    if (!(botptr->connect()))
        return  1;
    return 0;
}





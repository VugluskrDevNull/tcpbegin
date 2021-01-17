#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;

/***************************************************************************/ //  бот

const char * BlockedRead(QTcpSocket *soc)
{
     while (!(soc->bytesAvailable()))
     {
        soc->waitForReadyRead(10000);
     }
     const char * ch = soc->readAll().constData();
     cout<<ch;
     return ch;
}

bool ircbot_connect(QTcpSocket *soc)
{
    soc->connectToHost("62.149.7.206", 6660);
//    soc->connectToHost("127.0.0.1", 4567);
    if (!soc->waitForConnected(1000))
    {
       qDebug() << "Not Connected";
       return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_register(QTcpSocket *soc, QString dn )
{
    BlockedRead(soc);
    QString h = "NICK "+dn+'\n';
    const  char * n = h.toLocal8Bit().constData();
    soc->write(n);
    soc->write("PING\n");
    BlockedRead(soc);
    soc->write("USER qwert_zaq 8 x : qwert_zaq\n");
}

void ircbot_codepage(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("CODEPAGE UTF-8\n");
}

void ircbot_join(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("JOIN #ruschat \n");
    BlockedRead(soc);
    soc->write("PRIVMSG #ruschat  : hi from netcat\n");
}

void ircbot_disconnect(QTcpSocket *soc)
{
    soc->close();
}

QString ircbot_rename( QString oldn, QTcpSocket *soc, const char * ch)
 {
    QString str(ch);
    QStringList list2 = str.split(QLatin1Char(':'), Qt::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG #ruschat", 0) != -1) && (msg.startsWith("!nick")))
    {
        msg = msg.remove(0, 5);
        msg= msg.simplified();
        if (msg.contains(QRegExp("[^a-zA-Z_-/d]"))) // тут ошибка, так как в str что-то еще кроме букв от 'a' до 'z', 'A' до 'Z', '_' и '-'
        {
              qDebug()<<"error nick\n";
        }
        else
        {
            QString h = "NICK "+msg+'\n';
            const  char * n = h.toLocal8Bit().constData();
            soc->write(n);
            QString s = BlockedRead(soc);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            return msg;
        }
    }

}

void ircbot_loop(QTcpSocket *soc, QString dn)
{
    while (1)
    {
        QString c = BlockedRead(soc);
        qDebug() << c;
        QString d = "you type: " + c;
        if (c.indexOf("!quit", 0)!= -1)
            ircbot_disconnect(soc);
        if ((c.indexOf("PRIVMSG #ruschat :", 0) != -1) && (c.indexOf(dn , 0) != -1))
        {
            soc->write("PRIVMSG #ruschat  : i hear you\n");
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0)!= -1)
            soc->write("PONG irc.lucky.net\n ");
        if ((c.indexOf("PRIVMSG #ruschat :", 0) != -1) && (c.indexOf("!nick" , 0) != -1))
        {
            char const* ch = c.toLocal8Bit().constData();
            dn = ircbot_rename(dn, soc, ch);
        }
    }
}

int main()
{
      QString defname ="test_bot";
      QTcpSocket *socket;
      socket = new QTcpSocket(NULL);
      if (!(ircbot_connect(socket)))
         return  1;
      ircbot_register(socket, defname);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket, defname );
      return 0;
}



/************************************************************************** // рэгэксп
int main ()
{

      QRegExp rx("(\\d+)");
      QString str = "Offsets: 12 14 99 231 7";
      QStringList list;
      int pos = 0;

      while ((pos = rx.indexIn(str, pos)) != -1) {
          list << rx.cap(1);
          pos += rx.matchedLength();
      }
      qDebug()<<list<<endl;

      QRegExp rx2("*.txt");
      rx2.setPatternSyntax(QRegExp::Wildcard);
      qDebug()<<rx2.exactMatch("README.txt")<<endl;        // возвращает true
      qDebug()<<rx2.exactMatch("welcome.txt.bak")<<endl;   // возвращает false
*/
    /*
    QString c="dfdfdgfgfg PRIVMSG #ruschat :!nick qwer ";
    QString dn;
    if ((c.startsWith("PRIVMSG #ruschat :")) && (c.startsWith("!nick")))
      {
        cout<<"find";
        QString newn;
         int j=0;
         for (int v = 0; v < c.length(); v++)
         {
            if (c[v]=='k' && c[v-1]=='c' && c[v-2]=='i' && c[v-3]=='n' && c[v-4]== '!')
            cout<<"number of c[v] = "<<v<<endl;
            for (int k = v; k < c.length(); k++)
            {
              if (c[k]!=" ")
              {
                 newn[j] = c[k];
                 j++;
              }
              dn = newn;
              QString h = "NICK "+dn+'\n';
              const  char * n = h.toLocal8Bit().constData();
             qDebug()<<h;
            }

         }
       }
     cout<<"not found";
     */
/*
}
************************************************************/

/****
int main()
{
    QString c = "qwer tyui ";
    QString dn = " ty";
    if ((c.indexOf("qw", 0) != -1) && (c.indexOf(dn , 0) != -1))
        cout<<"ok";
    else
        cout<<"bad";
}
****/

/*******************************************************************************  // бот с функциями

const char * BlockedRead(QTcpSocket *soc)
{
     while (!(soc->bytesAvailable()))
     {
        soc->waitForReadyRead(10000);
     }
     const char * ch = soc->readAll().constData();
     cout<<ch;
     return ch;
}

bool ircbot_connect(QTcpSocket *soc)
{
    soc->connectToHost("62.149.7.206", 6660);
//    soc->connectToHost("127.0.0.1", 4567);
    if (!soc->waitForConnected(1000))
    {
       qDebug() << "Not Connected";
       return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_register(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("NICK test_bot\n ");
    soc->write("PING\n");
    BlockedRead(soc);
    soc->write("USER qwert_zaq 8 x : qwert_zaq\n");
}

void ircbot_codepage(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("CODEPAGE UTF-8\n");
}

void ircbot_join(QTcpSocket *soc)
{
    BlockedRead(soc);
    soc->write("JOIN #ruschat \n");
    BlockedRead(soc);
    soc->write("PRIVMSG #ruschat  : hi from netcat\n");
}

void ircbot_disconnect(QTcpSocket *soc)
{
    soc->close();
}

void ircbot_loop(QTcpSocket *soc)
{
    while (1)
    {
        QString c = BlockedRead(soc);
        qDebug() << c;
        QString d = "you type: " + c;
        if (c.indexOf("!quit", 0)!= -1)
            ircbot_disconnect(soc);
        if (c.indexOf("PRIVMSG #ruschat :test_bot", 0) != -1)
        {
            soc->write("PRIVMSG #ruschat  : i hear you\n");
            soc->waitForBytesWritten();
        }
        if (c.indexOf("PING", 0)!= -1)
            soc->write("PONG irc.lucky.net\n ");
   }
}

int main()
{
      QTcpSocket *socket;
      socket = new QTcpSocket(NULL);
      if (!(ircbot_connect(socket)))
         return  1;
      ircbot_register(socket);
      ircbot_codepage(socket);
      ircbot_join(socket);
      ircbot_loop(socket);
      return 0;
}
******************************************************************************/  // конец бота с фциями

/*************************************************************************** //  бот начало

const char * BlockedRead (QTcpSocket *soc)
{
     while ( !(soc->bytesAvailable()))
     {
        soc->waitForReadyRead(10000);
     }
     const char * ch = soc->readAll().constData();
     cout<<ch;
     return ch;
}

int main()
{
      QTcpSocket *socket;

      socket = new QTcpSocket(NULL);
      socket->connectToHost("62.149.7.206", 6660);
  //  socket->connectToHost("127.0.0.1", 4567);
      if (!socket->waitForConnected(1000))
      {
         qDebug() << "Not Connected";
         return 1;
      }
      qDebug() << "Connected";

      BlockedRead (socket);
      socket->write( "NICK test_bot\n ");
      socket->write( "PING\n");

      BlockedRead (socket);
      socket->write( "USER qwert_zaq 8 x : qwert_zaq\n");

      BlockedRead (socket);
     // socket->write( "CODEPAGE UTF-8\n");

      BlockedRead (socket);
      socket->write("JOIN #ruschat \n");

      BlockedRead (socket);
      socket->write("PRIVMSG #ruschat  : hi from netcat\n");

      while (1)
      {
          QString c = BlockedRead (socket);
          qDebug() << c;
          QString d = "you type: " + c;
          int j = 0;
          if (c.indexOf("!quit", j)!= -1)
              break;
          if (c.indexOf("PRIVMSG #ruschat :test_bot", 0) != -1)
          {
              socket->write("PRIVMSG #ruschat  : i hear you\n");
              socket->waitForBytesWritten();
          }
          if (c.indexOf("PING", 0) != -1)
              socket->write("PONG irc.lucky.net\n ");
     }
     socket->close();

      return 0;
}
***************************************************************************/ //  бот начало
/*
QString str = "We must be <b>bold</b>, very <b>bold</b>";
int j = 0;

while ((j = str.indexOf("<b>", j)) != -1) {            // -1 if not found else position
    qDebug() << "Found <b> tag at index position" << j;
    ++j;
}
*/
/*
int main ()
{

QString str = "We must be <b>bold</b>, very <b>bold</b>";


while ((j = str.indexOf("<b>", j)) != -1) {
    qDebug() << "Found <b> tag at index position" << j;
    ++j;
}

    QString str = "We must be <b>bold</b>, very <b>bold</b!quit>";
    int j = 0;
    if (str.indexOf("!quit", j)!= -1) cout<<"ok";
    else cout<<"bad";
}
*/

/*
int main()
{
    QTcpSocket *socket;

    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);

    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 1;
    }

    qDebug() << "Connected";
    while (1) {
        socket->write("input> ");

        while(socket->bytesAvailable() == 0) {
            socket->waitForReadyRead(100);
        }

        qDebug() << "Reading" << socket->bytesAvailable();

        QString c = socket->readLine();
        qDebug() << c;

        if (c.simplified().compare("exit") == 0)
            break;

        QString d = "you type: " + c;
        socket->write(d.toLocal8Bit().constData());
    }

    socket->close();

    return 0;
}
*/

/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
        while (1){
        socket->write("input> ");
         socket->waitForBytesWritten(1000);
        while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }
         qDebug()<<"Reading"<<socket->bytesAvailable();
         QString c = socket->readLine(10);
         qDebug()<<c;
         QString d="you type: "+c;
         char const* ch = d.toLocal8Bit().constData();
         socket->write(ch);
         if (strcmp(ch,"exit")==0) socket->close();
        }

    }
    else  {  qDebug()<<"Not Connected";
  }
}
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
         socket->write("hello\n");
         socket->waitForBytesWritten(1000);
        while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }
         qDebug()<<"Reading"<<socket->bytesAvailable();
         //qDebug()<<socket->readLine(10);
         qDebug()<<socket->readAll();
         socket->close();
    }
    else  {  qDebug()<<"Not Connected";
  }
}
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
       for (int i=5; i>=0; --i)
       {
         QString c = QString::number(i);
         QString d="hello "+c;
         char const* ch = d.toLocal8Bit().constData();
         socket->write(ch);
         socket->write("\n");
         socket->waitForBytesWritten();
         QThread::sleep (1);
       }
       socket->write("BOOM!!!\n");
       socket->waitForBytesWritten();
       socket->close();
    }
    else  {  qDebug()<<"Not Connected";    }
  }
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
     }
         socket->write("Hello\n");
         socket->write("World\n");
       socket->waitForBytesWritten();
       socket->close();
    }
*/
/*************************************************************** заготовки
//    qDebug()<<socket->readAll();
//qDebug()<<"Reading"<<socket->bytesAvailable(); // кол во байт
//while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }  // ожидание ОТ сокета
//  socket->waitForBytesWritten(100);   // проталкивание В сокет
// QByteArray q="qwerty"; char * c=data(q);   cout<<c; // qwerty
//  cout << socket->readAll().constData();
// //const char *QByteArray::data() const
// QString d="hello "+c; char const* ch = d.toLocal8Bit().constData(); // qstring to char
//if (c.simplified().compare("exit") == 0) поиск экзит среди пробелов
// QString str = "Bananas";
// str.startsWith("Ban");     // returns true
// str.startsWith("Car");     // returns false
// QString x = "Pineapple";
// QString y = x.right(5);      // y == "apple"
/*
QString str;
QString csv = "forename,middlename,surname,phone";
QString path = "/usr/local/bin/myapp"; // First field is empty
QString::SectionFlag flag = QString::SectionSkipEmpty;

str = csv.section(',', 2, 2);   // str == "surname"
str = path.section('/', 3, 4);  // str == "bin/myapp"
str = path.section('/', 3, 3, flag); // str == "myapp"
*/
/*
QString s = "Montreal";
s.remove(1, 4);
// s == "Meal"
  */


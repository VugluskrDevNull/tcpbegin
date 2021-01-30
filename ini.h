#ifndef INI_H
#define INI_H   

const char * reg_data = "bot_data.txt";
QFile init_file(reg_data);
const int port = 6667;
const QString server = "irc.lucky.net";      // "62.149.7.206";  "irc.lucky.net"  "chat.freenode.net"
const  QString nick ="test_bot";
const QString ircbot_channel = "#ruschat";

#endif
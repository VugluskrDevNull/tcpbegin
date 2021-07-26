#include "mainwindow.h"
#include "qircbot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QObject::connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendChannelMessage()));  // связь события нажатия и отсылки строки в чат
      QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendChannelMessage()));  // связь события нажатия и отсылки строки в чат
 }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow :: sendChannelMessage()
{
    emit sendChannelMessage(ui->lineEdit->text());   // реализация отсылки строки в чат
}
#if 0
void MainWindow :: addChannelLog(const QString & text)
{
 //   ui->channelLogView->appendPlainText(text);
}

void MainWindow :: addStatusLog(const QString & text)
{
 //   ui->statusLogView->appendPlainText(text);
}

void MainWindow :: addDebugLog(const QString & text)
{
 //   ui->debugLogView->appendPlainText(text);
}
#endif

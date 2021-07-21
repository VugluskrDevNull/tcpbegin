#include "mainwindow.h"
#include "qircbot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendmsg()));  // связь события нажатия и отсылки строки в чат
 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: sendmsg ()
{
    emit send(ui->lineEdit->text());   // реализация отсылки строки в чат
}


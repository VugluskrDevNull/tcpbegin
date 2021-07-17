#include "mainwindow.h"
#include "qircbot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendmsg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: sendmsg ()
{
     Bot::send(ui->lineEdit->text());
}

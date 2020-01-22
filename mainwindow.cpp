#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "GameLogic.h"
#include <QGraphicsScene>


GameLogic* oknodwa;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Close");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete oknodwa;
}


void MainWindow::on_start_clicked()
{

    oknodwa = new GameLogic();
    oknodwa->setModal(true);

    this->close();
    oknodwa->exec();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    M_Player = new QMediaPlayer ;

                                                                                          // all of standard icons
    ui->PB_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->PB_pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->PB_go_nextsong->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward)) ;
    ui->PB_go_prevsong->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_play_clicked()
{

}

void MainWindow::on_PB_pause_clicked()
{

}





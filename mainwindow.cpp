#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QTime>


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


    //adjusting volume
    ui->volume_controler->setMinimum(1);
    ui->volume_controler->setMaximum(100);
    ui->volume_controler->setValue(30);

    M_Player->setPosition(ui->horizontalSlider->value());

    //connect the time line
    connect(M_Player , &QMediaPlayer::durationChanged , this , &MainWindow::durationChanged) ;
    connect(M_Player , &QMediaPlayer::positionChanged , this , &MainWindow::positionChanged) ;
    connect(ui->horizontalSlider , &QSlider::sliderMoved , this , &MainWindow::on_horizontalSlider_sliderMoved) ;

    //set range of slider
    ui->horizontalSlider->setRange(0 , M_Player->duration() / 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_duration(int seconds)
{
//    QString timestr ;
//    if(duration || Mduration)
//    {
//        QTime CurrentTime((duration/3600) %60 , (duration/60)%60 , duration%60 , (duration*1000)%1000) ;
//        QTime totaltime ((Mduration/3600) %60 , (Mduration/60)%60 , Mduration%60 , (Mduration*1000)%1000) ;
//        QString format = "mm:ss" ;
//        if(Mduration > 3600)
//            format = "hh:mm:ss" ;
//        ui->LA_current_time->setText(CurrentTime.toString(format));
//        ui->LA_total_time->setText(totaltime.toString(format));


//    }
    ui->LA_current_time->setText(QTime(0, 0).addSecs(seconds).toString("mm:ss"));
}

void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000 ;
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 progress)
{
    if (!ui->horizontalSlider->isSliderDown())
    {
        ui->horizontalSlider->setValue(progress / 1000);
    }
    update_duration( progress/ 1000);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if (M_Player->duration() > 0 )
    {
        M_Player->setPosition(position * 1000);
    }
}

void MainWindow::on_PB_play_clicked()
{
    M_Player->play();
}

void MainWindow::on_PB_pause_clicked()
{
    M_Player->pause();
}


void MainWindow::on_PB_Add_newsong_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Audio File") , "", tr("MP3 File (*.mp3)")) ;
    M_Player->setMedia(QUrl(FileName));

    QFileInfo fileinfo(FileName) ;
    ui->LA_songname->setText(fileinfo.fileName());

}

void MainWindow::on_volume_controler_valueChanged(int value)
{
    M_Player->setVolume(value);
}



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QTime>
#include <QIcon>
#include <QMessageBox>


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
    ui->PB_go_prevsong->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward)) ;


    //adjusting volume
    ui->volume_controler->setMinimum(1);
    ui->volume_controler->setMaximum(100);
    ui->volume_controler->setValue(30);

    M_Player->setPosition(ui->horizontalSlider->value());

    //connect the time line
    connect(M_Player , &QMediaPlayer::durationChanged , this , &MainWindow::durationChanged) ;
    connect(M_Player , &QMediaPlayer::positionChanged , this , &MainWindow::positionChanged) ;
    connect(ui->horizontalSlider , &QSlider::sliderMoved , this , &MainWindow::on_horizontalSlider_sliderMoved) ;
    connect(M_Player , &QMediaPlayer::mediaStatusChanged , this ,&MainWindow::on_M_Player_mediaStatusChanged) ;

    //set range of slider
    ui->horizontalSlider->setRange(0 , M_Player->duration() / 1000);


    //set some button icons
    ui->PB_search->setIcon(QIcon(":/img/search_icon.ico"));
    ui->PB_random_music->setIcon(QIcon(":/img/shuffle_icon.ico"));
    ui->PB_repetition->setIcon(QIcon(":/img/repeat_icon.ico"));

}

MainWindow::~MainWindow()
{
    delete ui;
}


//                                                                 slider timeline of music
//====================================================================================================
void MainWindow::update_duration(int seconds)
{
//    QString timestr ;
//    if(duration || Mduration)
//    {
//        QTime CurrentTime((duration/3600) %60 , (duration/60)%60 , duration%60 , (duration*1000)%1000) ;
        QTime totaltime ((Mduration/3600) %60 , (Mduration/60)%60 , Mduration%60 , (Mduration*1000)%1000) ;
        QString format = "mm:ss" ;
        if(Mduration > 3600)
            format = "hh:mm:ss" ;
//        ui->LA_current_time->setText(CurrentTime.toString(format));
        ui->LA_total_time->setText(totaltime.toString(format));


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
//                                                                   play and pause button
//====================================================================================================
void MainWindow::on_PB_play_clicked()
{
    M_Player->play();
}

void MainWindow::on_PB_pause_clicked()
{
    M_Player->pause();
}
//                                                                     Add new playlist
//====================================================================================================
void MainWindow:: on_PB_Add_new_playlist_clicked() {
        QVBoxLayout* layout_me = qobject_cast<QVBoxLayout*>(ui->verticalLayout_3->layout());
        Linklist* new_playlist = new Linklist(); // Create a new playlist

        QString playlist_name = tr("Playlist: #%1").arg(layout_me->count());
        QPushButton* playlistButton = new QPushButton(playlist_name);
        layout_me->insertWidget(0, playlistButton);

        // Store the playlist in the QMap with the button text as the key
        m_playlists.insert(playlist_name, new_playlist);

        QObject::connect(playlistButton, &QPushButton::clicked, this, [this, playlist_name] {
            MainWindow:: click_on_specific_playlist(m_playlists.value(playlist_name));
        });
}

//                                                             show songs of a specific playlist
//====================================================================================================
void MainWindow::clearLayout(QLayout* layout)
{
    if (layout == nullptr) return;
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (item->widget())
        {
            item->widget()->deleteLater();
        }
        else if (item->layout())
        {
            clearLayout(item->layout());
        }
        delete item;
    }
}
void MainWindow::click_on_specific_playlist(Linklist* X_playlist)
{
    clearLayout(ui->Layout_musics) ;
    G_Playlist_button_name = m_playlists.key(X_playlist) ;
    G_Playlist_song_list = X_playlist ;
    is_a_playlist_chosen =true ;

    if ( X_playlist->head == nullptr)
    {
         qDebug() << "The playlist is empty.";
         return;
    }
    Node * current = X_playlist->head ;
    while (current!= nullptr)
    {
        QVBoxLayout * layout_me = qobject_cast<QVBoxLayout*>(ui->Layout_musics->layout()) ;

        QString name_of_music = current->Data.P_name ;
        QPushButton* music_button = new QPushButton(name_of_music) ;
        layout_me->insertWidget(0,music_button);

        QObject::connect(music_button , & QPushButton::clicked , this , &MainWindow::on_PB_play_clicked) ;
        current = current->next ;
    }


}
//                                                        add new song from pc
//====================================================================================================

void MainWindow::on_PB_Add_newsong_clicked()
{
    if(MainWindow::is_a_playlist_chosen == false)
    {
        QMessageBox::warning(nullptr , "Warning" , "first choose a playlist to add") ;
        return ;
    }


    QString FileName = QFileDialog::getOpenFileName(this, tr("Select Audio File") , "", tr("MP3 File (*.mp3)")) ;
    QFileInfo fileinfo(FileName) ;
    ui->LA_songname->setText(fileinfo.fileName());

    Music new_music(fileinfo.fileName() , FileName) ;
    MainWindow::G_Playlist_song_list->pushback(new_music);

    QVBoxLayout *layout_me = qobject_cast<QVBoxLayout*>(ui->Layout_musics->layout());
    QPushButton* music_button = new QPushButton(fileinfo.fileName());
    layout_me->insertWidget(0, music_button);

    if (M_Player->state() == QMediaPlayer::PlayingState)
    {
        M_Player->pause();

    }

    M_Player->setMedia(QUrl(FileName));
    M_Player->play();

    QObject::connect(music_button, &QPushButton::clicked, this, [this, FileName]
    {
        if (M_Player->state() == QMediaPlayer::PlayingState)
        {
            M_Player->pause();
        }
        ui->LA_songname->setText(FileName);
        M_Player->setMedia(QUrl(FileName));
        M_Player->play();
    });
}

void MainWindow::on_volume_controler_valueChanged(int value)
{
    M_Player->setVolume(value);
}

//                                                  go to next song
//====================================================================================================
void MainWindow::on_PB_go_nextsong_clicked()
{
    if (G_Playlist_song_list->head == nullptr)
    {
        return;
    }

    if (G_Playlist_song_list->head->next == nullptr)
    {
        M_Player->setMedia(QUrl(G_Playlist_song_list->head->Data.P_song_path));
        M_Player->play();
        return;
    }

    G_Playlist_song_list->head = G_Playlist_song_list->head->next;
    ui->LA_songname->setText(G_Playlist_song_list->head->Data.P_name);
    M_Player->setMedia(QUrl(G_Playlist_song_list->head->Data.P_song_path));
    M_Player->play();
}

void MainWindow::on_M_Player_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        MainWindow:: on_PB_go_nextsong_clicked();
    }
}
//====================================================================================================




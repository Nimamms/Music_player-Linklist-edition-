#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QStyle>
#include <QMap>
#include <QWidget>
#include <QLayout>
#include <vector>
#include <QVBoxLayout>
#include <music.h>
#include "linklist.h"
using namespace std ;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void add_playlist() ;

private slots:
    void durationChanged(qint64 duration) ;

    void positionChanged(qint64 progress) ;

    void on_horizontalSlider_sliderMoved(int position) ;

    void update_duration(int seconds) ;

    void on_PB_play_clicked();

    void on_PB_pause_clicked();

    void on_PB_Add_newsong_clicked();

    void on_volume_controler_valueChanged(int value);

    void on_PB_Add_new_playlist_clicked();

    void click_on_specific_playlist(Linklist* X_playlist) ;

    void clearLayout(QLayout* layout);

    void on_PB_go_nextsong_clicked() ;

    void on_M_Player_mediaStatusChanged(QMediaPlayer::MediaStatus status) ;


private:
    Ui::MainWindow *ui;
    QMediaPlayer * M_Player ;
    qint64 Mduration ;
    bool is_a_playlist_chosen = false;                                                //check if any playlist hasn't chosen to add (prrint warning)
    QVBoxLayout* m_layout;
    QMap<QString, Linklist*> m_playlists;       //name of buttons  ,   it's linklist
    QString G_Playlist_button_name ;
    Linklist * G_Playlist_song_list ;

};

#endif // MAINWINDOW_H

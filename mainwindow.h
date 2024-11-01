#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QStyle>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void durationChanged(qint64 duration) ;

    void positionChanged(qint64 progress) ;

    void on_horizontalSlider_sliderMoved(int position) ;

    void update_duration(int seconds) ;

    void on_PB_play_clicked();

    void on_PB_pause_clicked();

    void on_PB_Add_newsong_clicked();

    void on_volume_controler_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QMediaPlayer * M_Player ;
    qint64 Mduration ;

};

#endif // MAINWINDOW_H

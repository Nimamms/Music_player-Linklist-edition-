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
    void on_PB_play_clicked();

    void on_PB_pause_clicked();



private:
    Ui::MainWindow *ui;
    QMediaPlayer * M_Player ;

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void getAudioInfo(QString& path);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_play_clicked();


private:
    Ui::MainWindow *ui;
    QString  lastOpenPath;
    QMediaPlayer mediaPlayer;
};

#endif // MAINWINDOW_H

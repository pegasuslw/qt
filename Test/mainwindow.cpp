#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMediaObject>
#include <QFileInfo>
#include <QTime>

QString secondsToTime(qint64 seconds) {
    QTime time(0, 0);
    time = time.addSecs(seconds);
    if (seconds < 60 * 60 )
    {
        return time.toString("mm:ss");
    }
    else
    {
        return time.toString("hh:mm:ss");
    }

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QString filePathName;

    if(lastOpenPath.isEmpty())
    {
        lastOpenPath = QCoreApplication::applicationFilePath();
    }

    filePathName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      lastOpenPath,
                                                      tr("Audios (*.mp3 *.wav *.mid)"));

    if (!filePathName.isEmpty())
    {
        ui->label_music_path->setText(filePathName);
        QFileInfo fileInfo(filePathName);
        qDebug() << "File Name:" << fileInfo.fileName();
        qDebug() << "File Path:" << fileInfo.absoluteFilePath();
        qDebug() << "File Size:" << fileInfo.size() << "bytes";
        lastOpenPath = fileInfo.path();
        qDebug() << "last open file path:" << lastOpenPath;
    }

    getAudioInfo(filePathName);
}

void MainWindow::getAudioInfo(QString& path)
{
    if (path.isEmpty())
    {
        qDebug() << "Error: getAudioInfo path is empty";
        return;
    }

    // 创建MediaPlayer
       mediaPlayer.setMedia(QUrl::fromLocalFile(path));

       // 等待mediaStatusChanged信号，确保媒体状态准备好
        QEventLoop loop;
        QObject::connect(&mediaPlayer, &QMediaPlayer::mediaStatusChanged, &loop, &QEventLoop::quit);
        loop.exec();

       // 获取持续时间（毫秒）
       qint64 duration = mediaPlayer.duration();
       QString  sDuration = secondsToTime(duration/1000);
       qDebug() << "Duration:" << sDuration << "ms";


}


void MainWindow::on_pushButton_play_clicked()
{
    if(mediaPlayer.isAvailable())
    {
        qDebug() << "play: meidiaplay is Available";
        if (mediaPlayer.state() == mediaPlayer.PlayingState)
        {
            mediaPlayer.pause();
        }else if (mediaPlayer.state() == mediaPlayer.PausedState)
        {
            mediaPlayer.play();
        }else if (mediaPlayer.state() == mediaPlayer.StoppedState)
        {
            mediaPlayer.play();
        }

    }
    else
    {
        qDebug() << "play: meidiaplay is not Available";
    }
}


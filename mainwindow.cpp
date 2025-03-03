#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gstProcess(new QProcess(this))
{
    ui->setupUi(this);

    // Butonlara tıklanınca fonksiyonları çalıştır
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startStream);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopStream);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startStream()
{
    qDebug() << "Kamera akışı başlatılıyor...";

    // Eğer daha önce çalışan bir işlem varsa önce durdur
    if (gstProcess->state() == QProcess::Running) {
        stopStream();
    }

    // GStreamer pipeline komutu
    QString gstCmd = "gst-launch-1.0 autovideosrc ! videoconvert ! autovideosink";

    // Terminalde komutu çalıştır
    gstProcess->start("cmd.exe", QStringList() << "/c" << gstCmd);

    if (!gstProcess->waitForStarted()) {
        qDebug() << "GStreamer başlatılamadı!";
    } else {
        qDebug() << "GStreamer çalışıyor...";
    }
}

void MainWindow::stopStream()
{
    qDebug() << "Kamera akışı durduruluyor...";

    if (gstProcess->state() == QProcess::Running) {
        // Önce terminate() dene
        gstProcess->terminate();

        if (!gstProcess->waitForFinished(2000)) { // 2 saniye bekle
            qDebug() << "Normal şekilde kapanmadı, zorla kapatılıyor...";
            gstProcess->kill(); // Eğer kapanmazsa zorla kapat
        }

        qDebug() << "GStreamer süreci durduruldu.";
    } else {
        qDebug() << "GStreamer zaten çalışmıyor.";
    }
}

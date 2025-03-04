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
    if (gstProcess->state() == QProcess::Running) {
        stopStream();
    }

    // GStreamer'ın gerçek yolu - sizin belirttiğiniz yol
    QString gstPath = "C:/gstreamer/1.0/mingw_x86_64/bin/gst-launch-1.0.exe";

    QStringList arguments;
    arguments << "-v" << "autovideosrc" << "!" << "videoconvert" << "!" << "autovideosink";

    qDebug() << "Çalıştırılacak komut:" << gstPath << arguments.join(" ");

    // Bağlantıları temizle ve yeniden oluştur
    disconnect(gstProcess, &QProcess::readyReadStandardOutput, nullptr, nullptr);
    disconnect(gstProcess, &QProcess::readyReadStandardError, nullptr, nullptr);

    // Çıktıları yakalamak için bağlantıları ekleyin
    connect(gstProcess, &QProcess::readyReadStandardOutput, [this]() {
        qDebug() << "GST OUTPUT:" << gstProcess->readAllStandardOutput();
    });
    connect(gstProcess, &QProcess::readyReadStandardError, [this]() {
        qDebug() << "GST ERROR:" << gstProcess->readAllStandardError();
    });

    // Doğrudan GStreamer programını çalıştır
    gstProcess->start(gstPath, arguments);

    if (!gstProcess->waitForStarted(3000)) {
        qDebug() << "GStreamer başlatılamadı! Hata:" << gstProcess->errorString();
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

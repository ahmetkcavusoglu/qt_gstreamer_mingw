#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gst/gst.h>  // GStreamer kütüphanesi
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStream();
    void stopStream();

private:
    Ui::MainWindow *ui;
    QProcess *gstProcess;
};

#endif // MAINWINDOW_H

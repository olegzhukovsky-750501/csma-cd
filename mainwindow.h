#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "csmacd.h"

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
    void on_textEdit_textChanged();
    void updateOutput(QString output);
    void updateDebug(QString debug);
signals:
    void textChanged(QString frame, bool burstMode);

private:
    QString burstPacket;
    Ui::MainWindow *ui;
    QThread *processThread;
    CsmaCd *csmaCD;
};
#endif // MAINWINDOW_H

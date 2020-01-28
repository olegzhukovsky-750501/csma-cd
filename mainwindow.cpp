#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Создание потока для алгоритма CSMA/CD
    processThread = new QThread;
    csmaCD = new CsmaCd();

    csmaCD->moveToThread(processThread);

    connect(csmaCD, SIGNAL(toUpdateDebug(QString)), this, SLOT(updateDebug(QString)));
    connect(csmaCD, SIGNAL(toUpdateOutput(QString)), this, SLOT(updateOutput(QString)));
    connect(this, SIGNAL(textChanged(QString, bool)), csmaCD, SLOT(process(QString, bool)));

    processThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_textEdit_textChanged()
{
    QString inputText = ui->textEdit->toPlainText();
    QChar writtenChar = inputText.at(inputText.length() - 1);

    //IF BURST MODE
    if(ui->checkBox->isChecked())
    {
        burstPacket.append(writtenChar);
        if(burstPacket.length() == 4)
        {
            emit textChanged(burstPacket, 1);
            burstPacket.clear();
        }
    }
    else
    {
        burstPacket.clear();
        emit textChanged(writtenChar, 0);
    }
}

void MainWindow::updateOutput(QString output)
{
    ui->textEdit_2->moveCursor(QTextCursor::End);
    ui->textEdit_2->insertPlainText(output);
    ui->textEdit_2->moveCursor(QTextCursor::End);
}

void MainWindow::updateDebug(QString debug)
{
    ui->textEdit_3->moveCursor(QTextCursor::End);
    ui->textEdit_3->insertPlainText(debug);
    ui->textEdit_3->moveCursor(QTextCursor::End);
}

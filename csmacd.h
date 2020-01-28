#ifndef CSMACD_H
#define CSMACD_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QtCore/qmath.h>

class CsmaCd : public QObject
{
    Q_OBJECT
public:
    explicit CsmaCd(QObject *parent = nullptr);
    QChar sendFrame(QChar frame);

signals:
    void toUpdateOutput(QString output);
    void toUpdateDebug(QString debug);
public slots:
    void process(QString frame, bool burstMode);
private:
    int global = 0;
    int attemptCounter;
    const int SLOT_TIME = 2;
    const int COLLISION_WINDOW_TIME = 50;
};

#endif // CSMACD_H

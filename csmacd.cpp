#include "csmacd.h"

CsmaCd::CsmaCd(QObject *parent) : QObject(parent)
{
}


QChar CsmaCd::sendFrame(QChar frame)
{
    return frame;
}

void CsmaCd::process(QString frame, bool burstMode)
{
    attemptCounter = 0;
    int frameNum = burstMode ? 4 : 1;
    int frameCounter = 0;

    while(true)
    {
        int ms;
        if(!burstMode)
        {
            //WAITING WHEN CHANNEL WILL BE FREE
            do
            {
                ms = QDateTime::currentDateTime().time().msec();
            }
            while(ms % 2 == 0);
        }

        //SENDING FRAME
        QChar sendedFrame = sendFrame(frame.at(0));

        //WAIT COLLISION WINDOW
        QThread::msleep(COLLISION_WINDOW_TIME);
        ms = QDateTime::currentDateTime().time().msec();
        //IF COLLISION DETECTED
        if(ms % 2 == 1)
        {
            toUpdateDebug("x");
            attemptCounter++;
            if(attemptCounter > 10)
            {
                emit toUpdateDebug("\n");
                return;
            }

            int rand = SLOT_TIME * (qrand() % (int)((qPow(2, attemptCounter) + 1)));

            QThread::msleep(rand);
        }
        else
        {
            break;
        }
    }
    frameCounter++;
    emit toUpdateDebug("\n");

    //ONLY FOR BURST MODE
    while(frameCounter != frameNum)
    {
        QChar sendedFrame = sendFrame(frame.at(frameCounter));
        int ms = QDateTime::currentDateTime().time().msec();
        //IF LATE COLLISION DETECTED
        if(ms % 2 == 1)
        {
            emit toUpdateDebug("lx\n");
            return;
        }
        frameCounter++;
        emit toUpdateDebug("\n");
    }

    emit toUpdateOutput(frame);
}

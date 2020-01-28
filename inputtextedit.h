#ifndef INPUTTEXTEDIT_H
#define INPUTTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class InputTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    InputTextEdit(QFrame *parent = nullptr);
protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
signals:
    void sendData(QString data);
};

#endif // INPUTTEXTEDIT_H

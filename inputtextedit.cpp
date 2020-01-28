#include "inputtextedit.h"

InputTextEdit::InputTextEdit(QFrame *frame)
    :QTextEdit(frame)
{

}

void InputTextEdit::keyPressEvent(QKeyEvent *e)
{
    QString oldText = toPlainText();
    QString str = e->text();

    int curPos = oldText.length();

    if((str >= " ") && (str <= "~"))
    {
        QString newText = oldText + str;
        setText(newText);

        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
        setTextCursor(cursor);
    }
}

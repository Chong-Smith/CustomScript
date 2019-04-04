#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QColor>
#include <QDebug>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlockFormat>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int  lineNumberAreaWidth();

    inline void initialROPos(void)
    {
        /*清除所有textblock的颜色*/
        QTextCursor cursor = this->textCursor();
        QTextBlockFormat format;
        format.clearBackground();
        cursor.select(QTextCursor::Document);
        cursor.setBlockFormat(format);
        cursor.clearSelection();
        this->setTextCursor(cursor);

        ROPos = 0;
        LastNoEmptyBlock = -1;
    }
    inline void ChangeROPos(void)
    {
        if((LastNoEmptyBlock+1)==blockCount()){
            /*在改变ROPos位置之前，需要判断是否存在可编辑的块，
             *没有需要额外添加，若有则无需添加，这样防止设置只读区域后后续无法输入情况
            */
            this->appendPlainText("");
        }
        SetBlocksColor(ROPos,LastNoEmptyBlock);
        ROPos = LastNoEmptyBlock+1;
    }
    inline int GetROPos(void)
    {
        return ROPos;
    }
    void SetBlocksColor(int &from,int &to);
    void GetNewInput(QString &str);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void PosChangeDeal();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget   *lineNumberArea;
    int       ROPos;//在ROPos(readly only position)之前的块都变为只读模式
    int       LastNoEmptyBlock;/*记录内容不为零的最后输入的块*/
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

//![extraarea]

#endif

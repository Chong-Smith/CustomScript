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
        /*�������textblock����ɫ*/
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
            /*�ڸı�ROPosλ��֮ǰ����Ҫ�ж��Ƿ���ڿɱ༭�Ŀ飬
             *û����Ҫ������ӣ�������������ӣ�������ֹ����ֻ�����������޷��������
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
    int       ROPos;//��ROPos(readly only position)֮ǰ�Ŀ鶼��Ϊֻ��ģʽ
    int       LastNoEmptyBlock;/*��¼���ݲ�Ϊ����������Ŀ�*/
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

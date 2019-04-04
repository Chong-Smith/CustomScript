#include <QtWidgets>

#include "codeeditor.h"


CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(PosChangeDeal()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    ROPos = 0;
    LastNoEmptyBlock = -1;
}


int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::PosChangeDeal()
{
    if(textCursor().blockNumber() < ROPos){
        this->setReadOnly(true);
    }
    else{
        this->setReadOnly(false);
    }
    highlightCurrentLine();
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int)contentOffset().y();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
/*把from到to的块设置为指定颜色*/
void CodeEditor::SetBlocksColor(int &from, int &to)
{
    QTextDocument *doc = this->document();
    QTextCursor cursor = this->textCursor();
    QTextBlockFormat format;
    format.setBackground(QColor("lightGray"));
    for(int i=from; i<=to; ++i){
        cursor.setPosition(doc->findBlockByNumber(i).position());
        cursor.setBlockFormat(format);
        this->setTextCursor(cursor);
    }
}
/*
 * 获取ROPos到(size-1)的块中的文字
 * 使用LastNoEmptyBlock变量记录内容不为空的最后块号
*/
void CodeEditor::GetNewInput(QString &str)
{
    QTextDocument *document = this->document();
    int size = document->blockCount();
    str.clear();
    if(size > ROPos){
        QString text;
        for(int i=ROPos; i<size;){
            /* 一个行就是一个textBlock；
             * 下面得到的text不包括换行符；
             * 所以需要手动正确添加换行符（要不然词法扫描器不能输出正确的行号）；
            */
            text = document->findBlockByNumber(i).text();
            if(!text.isEmpty()){ str.append(text); LastNoEmptyBlock = i; }
            i++;
            if(i<size){ str.append('\n'); }/*这句判断上个TextBlock后面是否存在换行*/
        }
    }
}

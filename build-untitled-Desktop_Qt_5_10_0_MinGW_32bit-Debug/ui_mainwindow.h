/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <codeeditor/codeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter_3;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    CodeEditor *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_test;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_clever;
    QSpacerItem *horizontalSpacer_3;
    QTextBrowser *textBrowser;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter_2;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(931, 585);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        frame_3 = new QFrame(splitter_3);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        splitter = new QSplitter(frame_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        frame = new QFrame(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plainTextEdit = new CodeEditor(frame);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(10);
        plainTextEdit->setFont(font);
        plainTextEdit->setFrameShape(QFrame::Panel);
        plainTextEdit->setFrameShadow(QFrame::Sunken);
        plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        plainTextEdit->setPlaceholderText(QStringLiteral(""));

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(7, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setIconSize(QSize(13, 17));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_test = new QPushButton(frame);
        pushButton_test->setObjectName(QStringLiteral("pushButton_test"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_test->sizePolicy().hasHeightForWidth());
        pushButton_test->setSizePolicy(sizePolicy);
        pushButton_test->setMinimumSize(QSize(40, 30));
        pushButton_test->setMaximumSize(QSize(40, 30));

        horizontalLayout->addWidget(pushButton_test);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_clever = new QPushButton(frame);
        pushButton_clever->setObjectName(QStringLiteral("pushButton_clever"));
        sizePolicy.setHeightForWidth(pushButton_clever->sizePolicy().hasHeightForWidth());
        pushButton_clever->setSizePolicy(sizePolicy);
        pushButton_clever->setMinimumSize(QSize(40, 30));
        pushButton_clever->setMaximumSize(QSize(40, 30));

        horizontalLayout->addWidget(pushButton_clever);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(frame);
        textBrowser = new QTextBrowser(splitter);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setStyleSheet(QStringLiteral("background-color: rgb(161, 241, 241);"));
        textBrowser->setFrameShape(QFrame::Panel);
        textBrowser->setFrameShadow(QFrame::Sunken);
        textBrowser->setPlaceholderText(QStringLiteral(""));
        textBrowser->setSearchPaths(QStringList());
        textBrowser->setOpenLinks(false);
        splitter->addWidget(textBrowser);

        horizontalLayout_2->addWidget(splitter);

        splitter_3->addWidget(frame_3);
        frame_2 = new QFrame(splitter_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(4);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter_2 = new QSplitter(frame_2);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        textBrowser_2 = new QTextBrowser(splitter_2);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        QFont font1;
        font1.setPointSize(10);
        textBrowser_2->setFont(font1);
        splitter_2->addWidget(textBrowser_2);
        textBrowser_3 = new QTextBrowser(splitter_2);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        splitter_2->addWidget(textBrowser_3);

        verticalLayout_2->addWidget(splitter_2);

        splitter_3->addWidget(frame_2);

        horizontalLayout_3->addWidget(splitter_3);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\350\257\255\346\263\225\347\274\226\350\257\221\346\265\213\350\257\225\357\274\210Qt\347\216\257\345\242\203\357\274\211", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234\350\276\223\345\207\272", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        pushButton_test->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        pushButton_clever->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#-------------------------------------------------
#
# Project created by QtCreator 2018-12-23T15:08:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    compiler/parser.cpp \
    compiler/scanner.cpp \
    codeeditor/codeeditor.cpp \
    public/information.cpp \
    compiler/compiler.cpp \
    compiler/symboltable.cpp \
    public/varmanage.cpp \
    executor/executor.cpp \
    function/UF/userfunc.cpp \
    function/function.cpp





HEADERS += \
        mainwindow.h \
    compiler/parser.h \
    compiler/scanner.h \
    codeeditor/codeeditor.h \
    public/information.h \
    compiler/compiler.h \
    compiler/symboltable.h \
    public/varmanage.h \
    executor/executor.h \
    function/UF/userfunc.h \
    function/function.h



FORMS += \
        mainwindow.ui

DISTFILES += \
C:/Users/k/Desktop/bianyi1/untitled/compiler/parser.y \
C:/Users/k/Desktop/bianyi1/untitled/compiler/scanner.l


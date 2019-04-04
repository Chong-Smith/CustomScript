#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QDebug>

#include "compiler/scanner.h"
#include "compiler/parser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    CCompiler = &Compiler_C::GetInstance();
    VRmachine.SetOutputDev(ui->textBrowser_3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_test_clicked()
{ 
    QString str;

    ui->textBrowser->clear();
    ui->textBrowser_2->clear();

    ui->plainTextEdit->GetNewInput(str);
    /*行号是从1开始标记的，所有要加1*/
    int linenum = ui->plainTextEdit->GetROPos() + 1;
    if(CCompiler->compiler(str,linenum) == 0){
        ui->plainTextEdit->ChangeROPos();
    }
    ui->textBrowser->setPlainText(CCompiler->GetCompilerInfo());
    CCompiler->printfinstructs(ui->textBrowser_2);
}

void MainWindow::on_pushButton_clever_clicked()
{
    ui->plainTextEdit->clear();
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    ui->textBrowser_3->clear();
}

void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->initialROPos();
    CCompiler->initial();
}

void MainWindow::on_pushButton_2_clicked()
{
   if(!VRmachine.Run(CCompiler->GetAllInstruct())){
       qDebug()<<"success";
   }
   else{
       qDebug()<<"failure";
   }
}

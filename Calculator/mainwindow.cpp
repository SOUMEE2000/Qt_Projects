#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

double calcval = 0.0;
bool divTrigger = 0;
bool mulTrigger = 0;
bool addTrigger = 0;
bool subTrigger = 0;

double mem = 0.0;
bool memAddTrigger = 0;
bool memSubTrigger = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcval));  // conversion of double to qstring happening because setText takes qstring
    QPushButton *numButtons[10];
    for (int i=0; i < 10; ++i)
    {
        QString butname = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton*>(butname);
        connect(numButtons[i], SIGNAL(released()),this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()),this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()),this, SLOT(EqualButtonSign()));
    connect(ui->ChangeSign, SIGNAL(released()),this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()),this, SLOT(AcPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString butval = button->text();
    QString dispVal = ui->Display->text();

    if ((dispVal.toDouble() == 0) || (dispVal.toDouble() == 0.0))
        ui->Display->setText(butval);
    else
    {
        QString newval = dispVal + butval;
        double dblNewVal = newval.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}


void MainWindow::MathButtonPressed()
{
    divTrigger = 0;
    mulTrigger = 0;
    addTrigger = 0;
    subTrigger = 0;

    QPushButton *button = (QPushButton*)sender();
    QString butval = button->text();
    QString dispval = ui->Display->text();
    calcval = dispval.toDouble();

    if (QString::compare(butval,"/") == 0)
    {
        divTrigger = 1;
    }
    else if (QString::compare(butval,"+") == 0)
    {
        addTrigger = 1;
    }
    else if (QString::compare(butval,"-") == 0)
    {
        subTrigger = 1;
    }
    else if (QString::compare(butval,"*") == 0)
    {
        mulTrigger = 1;
    }
    ui->Display->setText("");
}


void MainWindow::EqualButtonSign()
{
    double solution =0.0;
    QString dispval = ui->Display->text();
    double dblDispval = dispval.toDouble();
    if(divTrigger || addTrigger || subTrigger || mulTrigger)
    {
        if(addTrigger)
        {
            solution = calcval + dblDispval;
        }
        else if(subTrigger)
        {
            solution = calcval - dblDispval;
        }
        else if(mulTrigger)
        {
            solution = calcval * dblDispval;
        }
        else
        {
            solution = calcval / dblDispval;
        }
    }
    ui->Display->setText(QString::number(solution));
}


void MainWindow::ChangeNumberSign()
{
    QString dispval = ui->Display->text();
    //QRegExp reg("[-]?[0-9.]*");

    double dblDispval = dispval.toDouble();
    dblDispval = (-1)*dblDispval;
    ui->Display->setText(QString::number(dblDispval));
}



void MainWindow::AcPressed()
{
    ui->Display->setText("0");
}

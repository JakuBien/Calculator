#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0;
bool divTrigger = false;
bool multiTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(calcVal));

    QPushButton *numButtons[10];
    for(int i = 0; i<10; i++){
        QString butName = "button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->buttonPlus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttonMinus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttonDevide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->buttonMulti, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->buttonEqual, SIGNAL(released()), this, SLOT(EqualButton()));

    connect(ui->buttonSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->buttonClear, SIGNAL(released()), this, SLOT(ClearPressed()));

    connect(ui->buttonComma, SIGNAL(released()), this, SLOT(CommaPressed()));

    connect(ui->buttonDel, SIGNAL(released()), this, SLOT(DelPressed()));

    connect(ui->buttonProcent, SIGNAL(released()), this, SLOT(ProcentPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    QString dispVal = ui->display->text();

    if(dispVal.toDouble() == 0 || dispVal.toDouble() == 0.0 || addTrigger || subTrigger || multiTrigger || divTrigger){
        ui->display->setText(butVal);
    }
    else{
        QString newVal = dispVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    multiTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multiTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    }

}

void Calculator::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multiTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
            addTrigger = false;
        }
        else if(subTrigger){
            solution = calcVal - dblDisplayVal;
            subTrigger = false;
        }
        else if(divTrigger){
            solution = calcVal / dblDisplayVal;
            divTrigger = false;
        }
        else if(multiTrigger){
            solution = calcVal * dblDisplayVal;
            multiTrigger = false;
        }
    }

    ui->display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(dblDisplayVal != 0.0){
        dblDisplayVal *= -1;
        ui->display->setText(QString::number(dblDisplayVal));
    }
}

void Calculator::ClearPressed(){
    calcVal = 0;
    ui->display->setText(QString::number(calcVal));
}

void Calculator::CommaPressed(){
    QString displayVal = ui->display->text();
    if(!displayVal.contains('.')){
        QString newVal = displayVal + ".";
        ui->display->setText(newVal);
    }
}

void Calculator::DelPressed(){
    QString displayVal = ui->display->text();
    if(displayVal.toDouble() != 0.0){
        displayVal.chop(1);
        ui->display->setText(displayVal);
    }
}

void Calculator::ProcentPressed(){
    QString displayVal = ui->display->text();
    double dblDisplayVal = displayVal.toDouble();
    double solution = dblDisplayVal * 0.01;
    ui->display->setText(QString::number(solution));
}

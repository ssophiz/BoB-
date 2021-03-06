#include "venwidget.h"
#include "ui_venwidget.h"
#include "QMessageBox"
VenWidget::VenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VenWidget)
{
    QMessageBox m;
    ui->setupUi(this);
    m.information(nullptr,"HomeWork","[bob8][취약점]vending_machine[김원겸]");

    ui->coke->setDisabled(true);
    ui->milk->setDisabled(true);
    ui->tea->setDisabled(true);
}
VenWidget::~VenWidget()
{
    delete ui;
}
void VenWidget :: MoneyChange(int number)
{
    QMessageBox m;
    int n;

    if(VenWidget ::number + number < 0 )
        m.information(nullptr,"Please","Do not this action, Please Input your more money");

    else

        VenWidget :: number += number;

    ui->lcdNumber->display(QString::number(VenWidget::number));
    n = ui->lcdNumber->intValue();


    if(n<100)//VenWidget ::number < 100)
       ui->coke->setDisabled(true);
    else
        ui->coke->setEnabled(true);

    if(n<300)//VenWidget ::number < 300 )
       ui->tea->setDisabled(true);
    else
        ui->tea->setEnabled(true);

    if(n<500)//VenWidget ::number < 500)
       ui->milk->setDisabled(true);
    else
        ui->milk->setEnabled(true);

    ui->lcdNumber->display(QString::number(VenWidget::number));

}

void VenWidget::on_n10_clicked()
{
   MoneyChange(10);// MoneyChange(10);
}

void VenWidget::on_n50_clicked()
{
    MoneyChange(50);
}


void VenWidget::on_n100_clicked()
{
    MoneyChange(100);
}


void VenWidget::on_n500_clicked()
{
    MoneyChange(500);
}

void VenWidget::on_coke_clicked()
{
    MoneyChange(-100);
}

void VenWidget::on_tea_clicked()
{
    MoneyChange(-300);
}

void VenWidget::on_milk_clicked()
{
    MoneyChange(-500);
}

void VenWidget::on_reset_clicked()
{
  QMessageBox m;
  int number=VenWidget :: number ;
  int n500{0}, n100{0}, n50{0}, n10{0};

  if(number / 500 > 0 ){
  n500 = number / 500 ;
  number -= (n500 *500);
  }

  if( number / 100 > 0 ){
  n100 = number /100;
  number -= (n100*100);
  }

  if( number / 50 > 0 ){
  n50 = number /50;
  number -= (n50*50);
  }

  if(number / 10 >0){
    n10 = number / 10;
    number -= (n10 * 10);
  }
   m.information(nullptr,"Reset your coin","500 : "+ QString::number(n500) + ", 100: " + QString::number(n100) + ", 50:"+QString::number(n50)+", 10:"+QString::number(n10));
   VenWidget::number = number;
   ui->lcdNumber->display(QString::number(VenWidget::number));

}

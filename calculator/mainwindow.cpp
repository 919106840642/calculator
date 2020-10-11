#include "mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

void MainWindow::myLayout(){
    QWidget *centerWindow = new QWidget;
    this->setCentralWidget(centerWindow);

    s = "";
    init_data();
    data = new QLineEdit("");

    button_0 = new QPushButton("0");
    button_1 = new QPushButton("1");
    button_2 = new QPushButton("2");
    button_3 = new QPushButton("3");
    button_4 = new QPushButton("4");
    button_5 = new QPushButton("5");
    button_6 = new QPushButton("6");
    button_7 = new QPushButton("7");
    button_8 = new QPushButton("8");
    button_9 = new QPushButton("9");
    button_ce = new QPushButton("CE");
    button_jia = new QPushButton("+");
    button_jian = new QPushButton("-");
    button_cheng = new QPushButton("*");
    button_chu = new QPushButton("/");
    button_result = new QPushButton("=");
    button_c2 = new QPushButton("c2");
    button_c10 = new QPushButton("c10");
    button_c16 = new QPushButton("c16");
    button_compare = new QPushButton("compare");

    data->setFixedHeight(30);
    button_0->setMinimumHeight(50);
    button_1->setMinimumHeight(50);
    button_2->setMinimumHeight(50);
    button_3->setMinimumHeight(50);
    button_4->setMinimumHeight(50);
    button_5->setMinimumHeight(50);
    button_6->setMinimumHeight(50);
    button_7->setMinimumHeight(50);
    button_8->setMinimumHeight(50);
    button_9->setMinimumHeight(50);
    button_ce->setMinimumHeight(50);
    button_jia->setMinimumHeight(50);
    button_jian->setMinimumHeight(50);
    button_cheng->setMinimumHeight(50);
    button_chu->setMinimumHeight(50);
    button_result->setMinimumHeight(50);
    button_c2->setMinimumHeight(50);
    button_c10->setMinimumHeight(50);
    button_c16->setMinimumHeight(50);
    button_compare->setMinimumHeight(50);


    //连接信号
    connect(button_0,SIGNAL(clicked(bool)),this,SLOT(button_0_clicked()));
    connect(button_1,SIGNAL(clicked(bool)),this,SLOT(button_1_clicked()));
    connect(button_2,SIGNAL(clicked(bool)),this,SLOT(button_2_clicked()));
    connect(button_3,SIGNAL(clicked(bool)),this,SLOT(button_3_clicked()));
    connect(button_4,SIGNAL(clicked(bool)),this,SLOT(button_4_clicked()));
    connect(button_5,SIGNAL(clicked(bool)),this,SLOT(button_5_clicked()));
    connect(button_6,SIGNAL(clicked(bool)),this,SLOT(button_6_clicked()));
    connect(button_7,SIGNAL(clicked(bool)),this,SLOT(button_7_clicked()));
    connect(button_8,SIGNAL(clicked(bool)),this,SLOT(button_8_clicked()));
    connect(button_9,SIGNAL(clicked(bool)),this,SLOT(button_9_clicked()));
    connect(button_jia,SIGNAL(clicked(bool)),this,SLOT(button_jia_clicked()));
    connect(button_jian,SIGNAL(clicked(bool)),this,SLOT(button_jian_clicked()));
    connect(button_cheng,SIGNAL(clicked(bool)),this,SLOT(button_cheng_clicked()));
    connect(button_chu,SIGNAL(clicked(bool)),this,SLOT(button_chu_clicked()));
    connect(button_ce,SIGNAL(clicked(bool)),this,SLOT(button_ce_clicked()));
    connect(button_result,SIGNAL(clicked(bool)),this,SLOT(button_result_clicked()));
    connect(button_c2,SIGNAL(clicked(bool)),this,SLOT(button_c2_clicked()));
    connect(button_c10,SIGNAL(clicked(bool)),this,SLOT(button_c10_clicked()));
    connect(button_c16,SIGNAL(clicked(bool)),this,SLOT(button_c16_clicked()));
    connect(button_compare,SIGNAL(clicked(bool)),this,SLOT(button_compare_clicked()));

    QGridLayout * layout = new QGridLayout;

    layout->addWidget(data,1,1,1,4,Qt::Alignment());

    layout->addWidget(button_1,2,1,Qt::Alignment());
    layout->addWidget(button_2,2,2,Qt::Alignment());
    layout->addWidget(button_3,2,3,Qt::Alignment());
    layout->addWidget(button_jia,2,4,Qt::Alignment());

    layout->addWidget(button_4,3,1,Qt::Alignment());
    layout->addWidget(button_5,3,2,Qt::Alignment());
    layout->addWidget(button_6,3,3,Qt::Alignment());
    layout->addWidget(button_jian,3,4,Qt::Alignment());

    layout->addWidget(button_7,4,1,Qt::Alignment());
    layout->addWidget(button_8,4,2,Qt::Alignment());
    layout->addWidget(button_9,4,3,Qt::Alignment());
    layout->addWidget(button_cheng,4,4,Qt::Alignment());

    layout->addWidget(button_ce,5,1,Qt::Alignment());
    layout->addWidget(button_0,5,2,Qt::Alignment());
    layout->addWidget(button_result,5,3,Qt::Alignment());
    layout->addWidget(button_chu,5,4,Qt::Alignment());

    layout->addWidget(button_c2,6,1,Qt::Alignment());
    layout->addWidget(button_c10,6,2,Qt::Alignment());
    layout->addWidget(button_c16,6,3,Qt::Alignment());


    layout->addWidget(button_compare,7,1,Qt::Alignment());
    layout->setMargin(8);
    centerWindow->setLayout(layout);
    }
MainWindow::~MainWindow()
{

}

void MainWindow::init_data()
{
    num1 = 0;
    num2 = 0;
    operat_flag = 0;
}

void MainWindow::readNum(int num)
{
      //如果是第一个操作数
      if(operat_flag == 0){
          num1 = num1 * 10 + num;
      }
      //如果是第二个操作数
      else{
          num2 = num2 * 10 + num;
      }
}
void MainWindow::operation()
{
    switch(operat){
    case 1:
        result = num1 + num2;
        break;
    case 2:
        result = num1 - num2;
        break;
    case 3:
        result = num1 * num2;
        break;
    case 4:
        result = num1 / num2;
        break;
    }
    //把结果存到num1中，清零num2
    num1 = result;
    num2 = 0;
    s = QString::number(result,10);
}

void MainWindow::button_0_clicked(){
    s += "0";
    data->setText(s);
    readNum(0);
}

void MainWindow::button_1_clicked(){
    s += "1";
    data->setText(s);
    readNum(1);
}

void MainWindow::button_2_clicked(){
    s += "2";
    data->setText(s);
    readNum(2);
}
void MainWindow::button_3_clicked(){
    s += "3";
    data->setText(s);
    readNum(3);
}

void MainWindow::button_4_clicked(){
    s += "4";
    data->setText(s);
    readNum(4);
}

void MainWindow::button_5_clicked(){
    s += "5";
    data->setText(s);
    readNum(5);
}

void MainWindow::button_6_clicked(){
    s += "6";
    data->setText(s);
    readNum(6);
}

void MainWindow::button_7_clicked(){
    s += "7";
    data->setText(s);
    readNum(7);
}

void MainWindow::button_8_clicked(){
    s += "8";
    data->setText(s);
    readNum(8);
}

void MainWindow::button_9_clicked(){
    s += "9";
    data->setText(s);
    readNum(9);
}

void MainWindow::button_ce_clicked(){
    s = "";
    data->setText("");
    //初始化数据
    init_data();
}
void MainWindow::button_jia_clicked(){
    s += "+";
    data->setText(s);
    operat_flag = 1;
    operat = 1;
}

void MainWindow::button_jian_clicked(){
    s += "-";
    data->setText(s);
    operat_flag = 1;
    operat = 2;
}

void MainWindow::button_cheng_clicked(){
    s += "*";
    data->setText(s);
    operat_flag = 1;
    operat = 3;
}

void MainWindow::button_chu_clicked(){
    s += "/";
    data->setText(s);
    operat_flag = 1;
    operat = 4;
}

void MainWindow::button_result_clicked(){
    operation();
    QString a = QString::number(result,10);
    data->setText(a);
}

void MainWindow::button_c2_clicked(){
    int n,m;
    n=s.toInt();
    while(n>=0)
    {
        for(;n/2>0;n=n/2)
        {
            m=n%2;
            data->setText(QString::number(m));
        }
        if(n/2==0)
        data->setText(QString::number(n));
        break;
     }
}
//二进制转化
void MainWindow::button_c10_clicked(){

}
//10进制转化
void MainWindow::button_c16_clicked(){

}
//16进制转化
void MainWindow::button_compare_clicked(){

}

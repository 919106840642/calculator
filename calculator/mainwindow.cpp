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
    button_A = new QPushButton("A");
    button_B = new QPushButton("B");
    button_C = new QPushButton("C");
    button_D = new QPushButton("D");
    button_E = new QPushButton("E");
    button_F = new QPushButton("F");
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
    button_gy = new QPushButton("gy");
    button_gb = new QPushButton("gb");
    button_m = new QPushButton("(");
    button_n = new QPushButton(")");
    button_log = new QPushButton("log");
    button_mi = new QPushButton("x^y");
    button_sin = new QPushButton("sin");
    button_cos = new QPushButton("cos");
    button_tan = new QPushButton("tan");
    //按钮内容

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
    button_A->setMinimumHeight(50);
    button_B->setMinimumHeight(50);
    button_C->setMinimumHeight(50);
    button_D->setMinimumHeight(50);
    button_E->setMinimumHeight(50);
    button_F->setMinimumHeight(50);
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
    button_gy->setMinimumHeight(50);
    button_gb->setMinimumHeight(50);
    button_m->setMinimumHeight(50);
    button_n->setMinimumHeight(50);
    button_log->setMinimumHeight(50);
    button_mi->setMinimumHeight(50);
    button_sin->setMinimumHeight(50);
    button_cos->setMinimumHeight(50);
    button_tan->setMinimumHeight(50);

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
    connect(button_A,SIGNAL(clicked(bool)),this,SLOT(button_A_clicked()));
    connect(button_B,SIGNAL(clicked(bool)),this,SLOT(button_B_clicked()));
    connect(button_C,SIGNAL(clicked(bool)),this,SLOT(button_C_clicked()));
    connect(button_D,SIGNAL(clicked(bool)),this,SLOT(button_D_clicked()));
    connect(button_E,SIGNAL(clicked(bool)),this,SLOT(button_E_clicked()));
    connect(button_F,SIGNAL(clicked(bool)),this,SLOT(button_F_clicked()));
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
    connect(button_gy,SIGNAL(clicked(bool)),this,SLOT(button_gy_clicked()));
    connect(button_gb,SIGNAL(clicked(bool)),this,SLOT(button_gb_clicked()));
    connect(button_m,SIGNAL(clicked(bool)),this,SLOT(button_m_clicked()));
    connect(button_n,SIGNAL(clicked(bool)),this,SLOT(button_n_clicked()));
    connect(button_log,SIGNAL(clicked(bool)),this,SLOT(button_log_clicked()));
    connect(button_mi,SIGNAL(clicked(bool)),this,SLOT(button_mi_clicked()));
    connect(button_sin,SIGNAL(clicked(bool)),this,SLOT(button_sin_clicked()));
    connect(button_cos,SIGNAL(clicked(bool)),this,SLOT(button_cos_clicked()));
    connect(button_tan,SIGNAL(clicked(bool)),this,SLOT(button_tan_clicked()));


    QGridLayout * layout = new QGridLayout;

    layout->addWidget(data,1,2,1,3,Qt::Alignment());

    layout->addWidget(button_log,2,1,Qt::Alignment());
    layout->addWidget(button_mi,2,2,Qt::Alignment());
    layout->addWidget(button_sin,2,3,Qt::Alignment());
    layout->addWidget(button_cos,2,4,Qt::Alignment());
    layout->addWidget(button_tan,2,5,Qt::Alignment());

    layout->addWidget(button_A,3,1,Qt::Alignment());
    layout->addWidget(button_c2,3,2,Qt::Alignment());
    layout->addWidget(button_c10,3,3,Qt::Alignment());
    layout->addWidget(button_c16,3,4,Qt::Alignment());
    layout->addWidget(button_m,3,5,Qt::Alignment());

    layout->addWidget(button_B,4,1,Qt::Alignment());
    layout->addWidget(button_compare,4,2,Qt::Alignment());
    layout->addWidget(button_gy,4,3,Qt::Alignment());
    layout->addWidget(button_gb,4,4,Qt::Alignment());
    layout->addWidget(button_n,4,5,Qt::Alignment());

    layout->addWidget(button_C,5,1,Qt::Alignment());
    layout->addWidget(button_1,5,2,Qt::Alignment());
    layout->addWidget(button_2,5,3,Qt::Alignment());
    layout->addWidget(button_3,5,4,Qt::Alignment());
    layout->addWidget(button_jia,5,5,Qt::Alignment());

    layout->addWidget(button_D,6,1,Qt::Alignment());
    layout->addWidget(button_4,6,2,Qt::Alignment());
    layout->addWidget(button_5,6,3,Qt::Alignment());
    layout->addWidget(button_6,6,4,Qt::Alignment());
    layout->addWidget(button_jian,6,5,Qt::Alignment());

    layout->addWidget(button_E,7,1,Qt::Alignment());
    layout->addWidget(button_7,7,2,Qt::Alignment());
    layout->addWidget(button_8,7,3,Qt::Alignment());
    layout->addWidget(button_9,7,4,Qt::Alignment());
    layout->addWidget(button_cheng,7,5,Qt::Alignment());

    layout->addWidget(button_F,8,1,Qt::Alignment());
    layout->addWidget(button_ce,8,2,Qt::Alignment());
    layout->addWidget(button_0,8,3,Qt::Alignment());
    layout->addWidget(button_result,8,4,Qt::Alignment());
    layout->addWidget(button_chu,8,5,Qt::Alignment());



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

void MainWindow::button_A_clicked(){
    s += "A";
    data->setText(s);
}

void MainWindow::button_B_clicked(){
    s += "B";
    data->setText(s);
}

void MainWindow::button_C_clicked(){
    s += "C";
    data->setText(s);
}

void MainWindow::button_D_clicked(){
    s += "D";
    data->setText(s);
}

void MainWindow::button_E_clicked(){
    s += "E";
    data->setText(s);
}

void MainWindow::button_F_clicked(){
    s += "F";
    data->setText(s);
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
//比大小

void MainWindow::button_gy_clicked(){

}
//最大公约数

void MainWindow::button_gb_clicked(){

}
//最小公倍数

void MainWindow::button_m_clicked(){

}
//"("

void MainWindow::button_n_clicked(){

}
//")"

void MainWindow::button_log_clicked(){

}
//对数函数

void MainWindow::button_mi_clicked(){

}
//幂函数

//三角函数
void MainWindow::button_sin_clicked(){

}

void MainWindow::button_cos_clicked(){

}

void MainWindow::button_tan_clicked(){

}

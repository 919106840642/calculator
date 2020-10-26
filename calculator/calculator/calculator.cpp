#include "calculator.h"
#include "ui_calculator.h"
#include <QString>
#include <string.h>
#include <QDebug>
#include "math.h"
#include <QtCore/qmath.h>

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->button_0,SIGNAL(clicked()),this,SLOT(push_button_0()));
    connect(ui->button_1,SIGNAL(clicked()),this,SLOT(push_button_1()));
    connect(ui->button_2,SIGNAL(clicked()),this,SLOT(push_button_2()));
    connect(ui->button_3,SIGNAL(clicked()),this,SLOT(push_button_3()));
    connect(ui->button_4,SIGNAL(clicked()),this,SLOT(push_button_4()));
    connect(ui->button_5,SIGNAL(clicked()),this,SLOT(push_button_5()));
    connect(ui->button_6,SIGNAL(clicked()),this,SLOT(push_button_6()));
    connect(ui->button_7,SIGNAL(clicked()),this,SLOT(push_button_7()));
    connect(ui->button_8,SIGNAL(clicked()),this,SLOT(push_button_8()));
    connect(ui->button_9,SIGNAL(clicked()),this,SLOT(push_button_9()));
    connect(ui->button_point,SIGNAL(clicked()),this,SLOT(push_button_point()));

    connect(ui->button_left,SIGNAL(clicked()),this,SLOT(push_button_left()));   // (
    connect(ui->button_right,SIGNAL(clicked()),this,SLOT(push_button_right())); // )

    connect(ui->button_add,SIGNAL(clicked()),this,SLOT(push_button_add()));       //  +
    connect(ui->button_minus,SIGNAL(clicked()),this,SLOT(push_button_minus()));   //  -
    connect(ui->button_ride,SIGNAL(clicked()),this,SLOT(push_button_ride()));     //  *
    connect(ui->button_divide,SIGNAL(clicked()),this,SLOT(push_button_divide())); //  /
    connect(ui->button_equal,SIGNAL(clicked()),this,SLOT(push_button_equal()));   //  =

    connect(ui->button_AC,SIGNAL(clicked()),this,SLOT(push_button_AC()));
    connect(ui->button_CE,SIGNAL(clicked()),this,SLOT(push_button_CE()));
//所有按键，信号连接
}

Calculator::~Calculator()
{
    delete ui;
}

int Calculator::Priority(QString data)
{
    int priority;
    if(data == "(")
        priority = 1;
    else if(data == "+" || data == "-")
        priority = 2;
    else if(data == "*" || data == "/")
        priority = 3;
    else if (data == ")")
        priority = 4;
    else
        priority = -1;
    return priority;
}
//获取操作符优先级

int Calculator::mask_data(QString expression, QString *mask_buffer)
{
    int i,k = 0,cnt = 0;
    QString::iterator p = expression.begin();
    int length = expression.length();
    for(i = 0 ; i < length ; i += cnt,k++)
    {
        cnt = 0;
        if(*p >= '0' && *p <= '9')
        {
            QString temp = *p;
            p ++;
            cnt ++;
            while((*p >= '0' && *p <= '9') || *p == '.')
            {
                temp += *p;
                p++;
                cnt ++;
            }
            mask_buffer[k] = temp;
        }
        else
        {
            QString temp = *p;
            p++;
            cnt ++;
            mask_buffer[k] = temp;
        }
    }
    return k;
}
//将表达式的数据，操作符分割，依次存入mask_buffer数组中

int Calculator::re_polish(QString *mask_buffer,QString *repolish,int length)
{
    QStack<QString> st2;
    int i = 0;
    for(int j = 0 ; j < length ; j++)
    {
        if(mask_buffer[j] != "(" && mask_buffer[j] != ")" && mask_buffer[j] != "+" && mask_buffer[j] != "-" && mask_buffer[j] != "*" && mask_buffer[j] != "/" )
            repolish[i++] = mask_buffer[j];
        else if(mask_buffer[j] == "("){
            st2.push(mask_buffer[j]);
        }
        else if(mask_buffer[j] == ")"){
            while(st2.top() != "(")
            {
                repolish[i++] = st2.top();
                st2.pop();
            }
            if(st2.top() == "(")
                st2.pop();
        }
        else if(st2.empty() || Priority(mask_buffer[j]) > Priority(st2.top()))
            st2.push(mask_buffer[j]);
        else{
            while(Priority(mask_buffer[j]) <= Priority(st2.top()))
            {
                repolish[i++] = st2.top();
                st2.pop();
                if(st2.empty())
                    break;
            }
            st2.push(mask_buffer[j]);
        }
    }
    while(!st2.empty())
    {
        repolish[i++] = st2.top();
        st2.pop();
    }
    return i;
}
//将获取到的分割好的表达式数组，转化为逆波兰表达式，存入数组repolish中d

double Calculator::repolish_calculat(QString *repolish,int length)
{
    QStack <double> st;
    for(int m = 0 ; m < length ; m ++)
    {
        if(repolish[m] != "+" && repolish[m] != "-" && repolish[m] != "*" && repolish[m] != "/" )
        {
            st.push(repolish[m].toDouble());
        }
        else
        {
            if(repolish[m] == "+")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                st.push(b + a);
            }
            else if(repolish[m] == "-")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                st.push(b - a);
            }
            else if(repolish[m] == "*")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                st.push(b * a);
            }
            else if(repolish[m] == "/")
            {
                double a = st.top();
                st.pop();
                double b = st.top();
                st.pop();
                if(a != 0)
                   st.push(b/a);
                else
                {
                    ui->display->clear();
                    ui->put_data->setText("0 不能做除数");
                    return -1;
                }
            }
        }
    }
    QString res = QString::number(st.top(),'g',10);
    ui->display->clear();
    ui->put_data->setText(res);
    return st.top();
}
//计算逆波兰表达式值并显示

void Calculator::calculate_result(QString expression)
{
    QString mask_buffer[100]={"0"},repolish[100]={"0"};
    int length = mask_data(expression,mask_buffer);
    length = re_polish(mask_buffer,repolish,length);
    double result;
    result = repolish_calculat(repolish,length);
}
//表达式计算整合

//数据按键输入
void Calculator::push_button_0()
{
    if(put_ctrl.new_put == "0"){
        put_ctrl.new_put = "0";
        put_ctrl.update_flag = 1;
    }
    else
        put_ctrl.new_put += "0";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::push_button_1()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "1";
    else
        put_ctrl.new_put += "1";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::push_button_2()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "2";
    else
        put_ctrl.new_put += "2";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_3()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "3";
    else
        put_ctrl.new_put += "3";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_4()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "4";
    else
        put_ctrl.new_put += "4";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_5()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "5";
    else
        put_ctrl.new_put += "5";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_6()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "6";
    else
        put_ctrl.new_put += "6";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_7()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "7";
    else
        put_ctrl.new_put += "7";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_8()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "8";
    else
        put_ctrl.new_put += "8";
    ui->put_data->setText(put_ctrl.new_put);
}
void Calculator::push_button_9()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "9";
    else
        put_ctrl.new_put += "9";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::push_button_point()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "0.";
    else{
        if(-1 == put_ctrl.new_put.indexOf("."))
            put_ctrl.new_put += ".";
    }
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_A_clicked()
{
    if(put_ctrl.new_put == "0")
    {
        put_ctrl.new_put = "A";
    }
    else
    {
        put_ctrl.new_put += "A";
    }
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_B_clicked()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "B";
    else
        put_ctrl.new_put += "B";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_C_clicked()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "C";
    else
        put_ctrl.new_put += "C";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_D_clicked()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "D";
    else
        put_ctrl.new_put += "D";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_E_clicked()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "E";
    else
        put_ctrl.new_put += "E";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_F_clicked()
{
    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = "F";
    else
        put_ctrl.new_put += "F";
    ui->put_data->setText(put_ctrl.new_put);
}


void Calculator::push_button_left()
{
    if(put_ctrl.old_put == "0"){
        put_ctrl.old_put = "(";
        put_ctrl.brackets_cnt ++;
    }
    else{
        put_ctrl.old_put += "(";
        put_ctrl.brackets_cnt ++;
    }
    ui->display->setText(put_ctrl.old_put);
}

void Calculator::push_button_right()
{
    if(put_ctrl.brackets_cnt > 0){
        QString::iterator p = put_ctrl.old_put.end()-1;
        if(*p != ')')
            put_ctrl.old_put += put_ctrl.new_put;
        put_ctrl.old_put += ")";
        put_ctrl.brackets_cnt --;
        put_ctrl.new_put = "0";
        put_ctrl.update_flag = 0;
        ui->display->setText(put_ctrl.old_put);
    }
}
//+ - * / = 按键输入
void Calculator::push_button_add()
{
    if(put_ctrl.old_put == "0"){
        put_ctrl.old_put = put_ctrl.new_put;
        put_ctrl.old_put += "+";
        put_ctrl.new_put = "0";
        put_ctrl.update_flag = 0;
    }
    else{
        QString::iterator p = put_ctrl.old_put.end()-1;
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' )
        {
            if(put_ctrl.new_put == "0")
            {
                if(put_ctrl.update_flag)
                {
                    put_ctrl.old_put += put_ctrl.new_put;
                    put_ctrl.old_put += "+";
                    put_ctrl.new_put = "0";
                    put_ctrl.update_flag = 0;
                }
            }
            else
            {
                put_ctrl.old_put += put_ctrl.new_put;
                put_ctrl.old_put += "+";
                put_ctrl.new_put = "0";
                put_ctrl.update_flag = 0;
            }
        }
        else if(*p == ')')
        {
            put_ctrl.old_put += "+";
        }
    }
    ui->display->setText(put_ctrl.old_put);
}

void Calculator::push_button_minus()
{
    if(put_ctrl.old_put == "0")
    {
        put_ctrl.old_put = put_ctrl.new_put;
        put_ctrl.old_put += "-";
        put_ctrl.new_put = "0";
        put_ctrl.update_flag = 0;
    }
    else
    {
        QString::iterator p = put_ctrl.old_put.end()-1;
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' )
        {
            if(put_ctrl.new_put == "0")
            {
                if(put_ctrl.update_flag || *p == '(')
                {
                    put_ctrl.old_put += put_ctrl.new_put;
                    put_ctrl.old_put += "-";
                    put_ctrl.new_put = "0";
                    put_ctrl.update_flag = 0;
                }
            }
            else
            {
                put_ctrl.old_put += put_ctrl.new_put;
                put_ctrl.old_put += "-";
                put_ctrl.new_put = "0";
                put_ctrl.update_flag = 0;
            }
        }
        else if(*p == ')')
        {
            put_ctrl.old_put += "-";
        }
    }
    ui->display->setText(put_ctrl.old_put);
}

void Calculator::push_button_ride()
{
    if(put_ctrl.old_put == "0")
    {
        put_ctrl.old_put = put_ctrl.new_put;
        put_ctrl.old_put += "*";
        put_ctrl.new_put = "0";
        put_ctrl.update_flag = 0;
    }
    else{
        QString::iterator p = put_ctrl.old_put.end()-1;
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' )
        {
            if(put_ctrl.new_put == "0")
            {
                if(put_ctrl.update_flag)
                {
                    put_ctrl.old_put += put_ctrl.new_put;
                    put_ctrl.old_put += "*";
                    put_ctrl.new_put = "0";
                    put_ctrl.update_flag = 0;
                }
            }
            else
            {
                put_ctrl.old_put += put_ctrl.new_put;
                put_ctrl.old_put += "*";
                put_ctrl.new_put = "0";
                put_ctrl.update_flag = 0;
            }
        }
        else if(*p == ')')
        {
            put_ctrl.old_put += "*";
        }
    }
    ui->display->setText(put_ctrl.old_put);
}

void Calculator::push_button_divide()
{
    if(put_ctrl.old_put == "0")
    {
        put_ctrl.old_put = put_ctrl.new_put;
        put_ctrl.old_put += "/";
        put_ctrl.new_put = "0";
        put_ctrl.update_flag = 0;
    }
    else
    {
        QString::iterator p = put_ctrl.old_put.end()-1;
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' )
        {
            if(put_ctrl.new_put == "0")
            {
                if(put_ctrl.update_flag)
                {
                    put_ctrl.old_put += put_ctrl.new_put;
                    put_ctrl.old_put += "/";
                    put_ctrl.new_put = "0";
                    put_ctrl.update_flag = 0;
                }
            }
            else
            {
                put_ctrl.old_put += put_ctrl.new_put;
                put_ctrl.old_put += "/";
                put_ctrl.new_put = "0";
                put_ctrl.update_flag = 0;
            }
        }
        else if(*p == ')')
        {
            put_ctrl.old_put += "/";
        }
    }
    ui->display->setText(put_ctrl.old_put);
}

void Calculator::push_button_equal()
{
    if(put_ctrl.old_put == "0")
    {
        push_button_AC();
        return;
    }
    else
    {
        QString::iterator p = put_ctrl.old_put.end()-1;
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' )
        {
            put_ctrl.old_put += put_ctrl.new_put;
            if(put_ctrl.brackets_cnt > 0)
            {
                for(int i = 0 ; i < put_ctrl.brackets_cnt ; i++)
                    put_ctrl.old_put += ")";
            }
            put_ctrl.new_put = "0";
            put_ctrl.update_flag = 0;
        }
        else if(*p == ')')
        {
            if(put_ctrl.brackets_cnt > 0)
            {
                for(int i = 0 ; i < put_ctrl.brackets_cnt ; i++)
                    put_ctrl.old_put += ")";
            }
            put_ctrl.new_put = "0";
            put_ctrl.update_flag = 0;
        }
    }
    calculate_result(put_ctrl.old_put);
    put_ctrl.old_put = "0";
    put_ctrl.brackets_cnt = 0;
    put_ctrl.update_flag = 0;
    put_ctrl.new_put = "0";
}

void Calculator::push_button_CE()
{
    put_ctrl.old_put = "0";
    ui->display->clear();
}

void Calculator::push_button_AC()
{
    put_ctrl.old_put = "0";
    put_ctrl.new_put = "0";
    put_ctrl.brackets_cnt = 0;
    put_ctrl.update_flag = 0;
    ui->display->clear();
    ui->put_data->setText(put_ctrl.new_put);
}


void Calculator::on_blank_clicked()
{

    if(put_ctrl.new_put == "0")
        put_ctrl.new_put = " ";
    else
        put_ctrl.new_put += " ";
    ui->put_data->setText(put_ctrl.new_put);
}

void Calculator::on_c10to2_clicked()
{
    int n;
    n=put_ctrl.new_put.toInt();
    put_ctrl.new_put.clear();
    _toBin(n);
    ui->display->setText(put_ctrl.old_put);
}
void Calculator::_toBin(int n)
{
    if(n<=0) return;
    int m=n%2;
    _toBin(n/2);
    QString str = str.number(m);
    put_ctrl.old_put += str;
}
//10进制转化2进制

void Calculator::on_c10to16_clicked()
{
    int n;
    n=put_ctrl.new_put.toInt();
    put_ctrl.new_put.clear();
    _toHex(n);
    ui->display->setText(put_ctrl.old_put);
}
void Calculator::_toHex(int n)
{
    if(n<=0) return;
    int m=n%16;
    _toHex(n/16);
    QString str;
    if(m<=9) str = str.number(m);
    else if(m==10) str += "A";
    else if(m==11) str += "B";
    else if(m==12) str += "C";
    else if(m==13) str += "D";
    else if(m==14) str += "E";
    else if(m==15) str += "F";
    put_ctrl.old_put += str;
}
//10进制转化16进制

void Calculator::on_c2to10_clicked()
{
    int k=1;
    int len=put_ctrl.new_put.length();
    if(len!=1)
    {
        for(int i=1;put_ctrl.new_put[i]!='1'&&put_ctrl.new_put[i]!='0';i++)
        {
            ui->put_data->setText("二进制输入错误");
            break;
        }
        for(int i=1;i<len;i++)
        {
            k=k*2;
            if(put_ctrl.new_put[i]=='1')
                    k++;
        }
    }
    QString str = str.number(k);
    ui->display->setText(str);
}
//2进制转10进制

void Calculator::on_c16to10_clicked()
{
    int k;
    int len=put_ctrl.new_put.length();
    if(len!=1)
    {
        for(int i=1;i<len;i++)
        {
            if(put_ctrl.new_put[i]=='1')    k=1;
            if(put_ctrl.new_put[i]=='2')    k=2;
            if(put_ctrl.new_put[i]=='3')    k=3;
            if(put_ctrl.new_put[i]=='4')    k=4;
            if(put_ctrl.new_put[i]=='5')    k=5;
            if(put_ctrl.new_put[i]=='6')    k=6;
            if(put_ctrl.new_put[i]=='7')    k=7;
            if(put_ctrl.new_put[i]=='8')    k=8;
            if(put_ctrl.new_put[i]=='9')    k=9;
            if(put_ctrl.new_put[i]=='A')    k=10;
            if(put_ctrl.new_put[i]=='B')    k=11;
            if(put_ctrl.new_put[i]=='C')    k=12;
            if(put_ctrl.new_put[i]=='D')    k=13;
            if(put_ctrl.new_put[i]=='E')    k=14;
            if(put_ctrl.new_put[i]=='F')    k=15;
            k=k*16;
            if(put_ctrl.new_put[i]=='1')    k=k+1;
            if(put_ctrl.new_put[i]=='2')    k=k+2;
            if(put_ctrl.new_put[i]=='3')    k=k+3;
            if(put_ctrl.new_put[i]=='4')    k=k+4;
            if(put_ctrl.new_put[i]=='5')    k=k+5;
            if(put_ctrl.new_put[i]=='6')    k=k+6;
            if(put_ctrl.new_put[i]=='7')    k=k+7;
            if(put_ctrl.new_put[i]=='8')    k=k+8;
            if(put_ctrl.new_put[i]=='9')    k=k+9;
            if(put_ctrl.new_put[i]=='0')    k=k+0;
            if(put_ctrl.new_put[i]=='A')    k=k+10;
            if(put_ctrl.new_put[i]=='B')    k=k+11;
            if(put_ctrl.new_put[i]=='C')    k=k+12;
            if(put_ctrl.new_put[i]=='D')    k=k+13;
            if(put_ctrl.new_put[i]=='E')    k=k+14;
            if(put_ctrl.new_put[i]=='F')    k=k+15;
        }
    }
    if(len==1)
    {
        k=put_ctrl.new_put.toInt();
    }
    QString str = str.number(k);
    ui->display->setText(str);
}
//16进制转10进制

void Calculator::on_compare_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m=c[0]-48;
    int n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    if(m-n>0)   ui->display->setText(">");
    if(m-n==0)   ui->display->setText("=");
    if(m-n<0)   ui->display->setText("<");
}
//比较

void Calculator::on_gy_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m=c[0]-48;
    int n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    int z;
    while (n != 0)
    {
        z = m%n;
        m = n;
        n = z;
    }
    s =s.number(m);
    ui->display->setText(s);
}
//最大公约数

void Calculator::on_gb_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m=c[0]-48;
    int n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    int x,y,z;
    x=m;
    y=n;
    while (n != 0)
    {
        z = m%n;
        m = n;
        n = z;
    }
    s =s.number(x*y/m);
    ui->display->setText(s);
}
//最小公倍数

void Calculator::on_sin_clicked()
{
    double x=put_ctrl.new_put.toInt();
    double y=sin(x);
    s =s.number(y);
    ui->display->setText(s);
}
void Calculator::on_cos_clicked()
{
    double x=put_ctrl.new_put.toInt();
    double y=cos(x);
    s =s.number(y);
    ui->display->setText(s);
}
void Calculator::on_tan_clicked()
{
    double x=put_ctrl.new_put.toInt();
    double y=tan(x);
    s =s.number(y);
    ui->display->setText(s);
}
//三角函数

void Calculator::on_log_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    double m=c[0]-48;
    double n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    double y = qLn(m)/qLn(n);
    s =s.number(y);
    ui->display->setText(s);
}
//求对数

void Calculator::on_powerfunction_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m=c[0]-48;
    int n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    int x=n;
    for(;m>1;m--)
    {
        x=x*n;
    }
    int y = x;
    s =s.number(y);
    ui->display->setText(s);
}
//幂运算

void Calculator::on_qf_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m[4];
    int j=0;
    m[j]=c[0]-48;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]!=' ')
            {
           m[j]=m[j]*10+c[i]-48;
        }
        else
        {
            j++;
            i++;
            m[j]=c[i]-48;
        }
    }
    int y=m[0]*m[1]*m[1]+m[2]*m[1]+m[3];
    s =s.number(y);
    ui->display->setText(s);
}
//二次函数

void Calculator::on_expf_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m=c[0]-48;
    int n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    int x=n;
    for(;m>1;m--)
    { 
        x=x*n;
    }
    int y = x;
    s =s.number(y);
    ui->display->setText(s);
}
//指数函数

void Calculator::on_logfunction_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    double m=c[0]-48;
    double n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    double y = qLn(m)/qLn(n);
    s =s.number(y);
    ui->display->setText(s);
}
//对数函数

void Calculator::on_firstof_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    int m[3];
    int j=0;
    m[j]=c[0]-48;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]!=' ')
            {
           m[j]=m[j]*10+c[i]-48;
        }
        else
        {
            j++;
            i++;
            m[j]=c[i]-48;
        }
    }
    int y=m[0]*m[1]+m[2];
    s =s.number(y);
    ui->display->setText(s);
}
//一次函数

void Calculator::on_fan_clicked()
{
    QByteArray c=put_ctrl.new_put.toUtf8();
    double m=c[0]-48;
    double n;
    for(int i=1;i<put_ctrl.new_put.length();i++)
    {
        if(put_ctrl.new_put[i]==" ")
        {
            i=i+1;
            n=c[i]-48;
            i++;
            for(;i<put_ctrl.new_put.length();i++)
            {
                n=n*10+c[i]-48;
            }
        }
        else
        {
            m=m*10+c[i]-48;
        }
    }
    double x = m/n;
    s =s.number(x);
    ui->display->setText(s);
}
//反比例函数

void Calculator::on_jiecheng_clicked()
{
    int n = put_ctrl.new_put.toInt();
    for(int i=n-1;i>0;i--)
    {
        n=n*i;
    }
    s =s.number(n);
    ui->display->setText(s);
}
//阶乘


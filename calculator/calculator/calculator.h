#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QDebug>
#include <QStack>
#include <QString>

struct put_ctrl_t{
    QString old_put="0";//用于表达式的存储
    QString new_put="0";//用于输入的数据存储
    int brackets_cnt=0;//左括号输入个数
    int update_flag=0;//当new_put为“0”时，重新输入0表示更新置1
};


namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

    QString puts;
    struct put_ctrl_t put_ctrl;

    QString s;
    QString t;

private:
    Ui::Calculator *ui;
    int Priority(QString data);
    int mask_data(QString expression, QString *mask_buffer);
    int re_polish(QString *mask_buffer,QString *repolish,int length);
    double repolish_calculat(QString *repolish,int length);
    void calculate_result(QString expression);

private slots:

    void push_button_0();
    void push_button_1();
    void push_button_2();
    void push_button_3();
    void push_button_4();
    void push_button_5();
    void push_button_6();
    void push_button_7();
    void push_button_8();
    void push_button_9();
    void push_button_point();

    void push_button_left();
    void push_button_right();

    void push_button_add();
    void push_button_minus();
    void push_button_ride();
    void push_button_divide();
    void push_button_equal();

    void push_button_CE();
    void push_button_AC();

    void on_blank_clicked();
    void on_c10to2_clicked();
    void on_c10to16_clicked();
    void on_c2to10_clicked();
    void on_c16to10_clicked();
    void on_compare_clicked();
    void on_gy_clicked();
    void on_gb_clicked();
    void on_sin_clicked();
    void on_cos_clicked();
    void on_tan_clicked();
    void on_log_clicked();
    void on_powerfunction_clicked();
    void on_qf_clicked();
    void on_expf_clicked();
    void on_logfunction_clicked();
    void on_firstof_clicked();
    void on_fan_clicked();

    void _toBin(int);
    void _toHex(int);
    void on_A_clicked();
    void on_B_clicked();
    void on_C_clicked();
    void on_D_clicked();
    void on_E_clicked();
    void on_F_clicked();

    void on_jiecheng_clicked();
};

#endif // CALCULATOR_H


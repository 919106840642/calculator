#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    int num1,num2,result; //标记第一个数，第二个数和结果
    int operat; //运算符号
    int operat_flag;//标记是否输入符号
    QLineEdit *data;
    QPushButton *button_0;
    QPushButton *button_1;
    QPushButton *button_2;
    QPushButton *button_3;
    QPushButton *button_4;
    QPushButton *button_5;
    QPushButton *button_6;
    QPushButton *button_7;
    QPushButton *button_8;
    QPushButton *button_9;
    QPushButton *button_A;
    QPushButton *button_B;
    QPushButton *button_C;
    QPushButton *button_D;
    QPushButton *button_E;
    QPushButton *button_F;
    QPushButton *button_ce;
    QPushButton *button_jia;
    QPushButton *button_jian;
    QPushButton *button_cheng;
    QPushButton *button_chu;
    QPushButton *button_result;
    QPushButton *button_c2;
    QPushButton *button_c10;
    QPushButton *button_c16;
    QPushButton *button_compare;
    QPushButton *button_gy;
    QPushButton *button_gb;
    QPushButton *button_m;
    QPushButton *button_n;
    QPushButton *button_log;
    QPushButton *button_mi;
    QPushButton *button_sin;
    QPushButton *button_cos;
    QPushButton *button_tan;

    QString s;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void myLayout();
    void operation();
    void readNum(int num);
    void init_data();
private slots:
    void button_0_clicked();
    void button_1_clicked();
    void button_2_clicked();
    void button_3_clicked();
    void button_4_clicked();
    void button_5_clicked();
    void button_6_clicked();
    void button_7_clicked();
    void button_8_clicked();
    void button_9_clicked();
    void button_A_clicked();
    void button_B_clicked();
    void button_C_clicked();
    void button_D_clicked();
    void button_E_clicked();
    void button_F_clicked();
    void button_ce_clicked();
    void button_result_clicked();
    void button_cheng_clicked();
    void button_chu_clicked();
    void button_jia_clicked();
    void button_jian_clicked();
    void button_c2_clicked();
    void button_c10_clicked();
    void button_c16_clicked();
    void button_compare_clicked();
    void button_gy_clicked();
    void button_gb_clicked();
    void button_m_clicked();
    void button_n_clicked();
    void button_log_clicked();
    void button_mi_clicked();
    void button_sin_clicked();
    void button_cos_clicked();
    void button_tan_clicked();
};


#endif // MAINWINDOW_H

#include "widget.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("计算器");

    QPushButton b;
    b.setText("开始");
    b.setParent(&w);
    b.move(50,200);

    QPushButton c;
    c.setText("关闭");
    c.setParent(&w);
    c.move(250,200);

    w.show();

    return a.exec();
}

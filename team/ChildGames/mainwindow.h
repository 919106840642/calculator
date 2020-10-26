#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgame.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setBackground(QString image);

private slots:
    void on_btnSnake_clicked();

    void on_btnLinks_clicked();

    void on_btnMaze_clicked();

    void on_btnExit_clicked();

private:
    Ui::MainWindow *ui;
    QGame *game;
    int timerID;


    void resizeEvent(QResizeEvent *e);
    void timerEvent(QTimerEvent *e);
};
#endif // MAINWINDOW_H

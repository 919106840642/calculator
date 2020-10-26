#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qgame.h"
#include "snakegame.h"
#include "linksgame.h"
#include "mazegame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //窗口固定大小，实际上游戏设置的是自动适应窗口大小
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    game = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置背景图片
void MainWindow::setBackground(QString image)
{
    QPixmap pixmap = QPixmap(image).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
}

//窗口缩放
void MainWindow::resizeEvent(QResizeEvent *e)
{
    setBackground(":/assets/background.jpg");

    /*
    double scale = this->width() / 800.0;
    QFont f = this->font();
    f.setPixelSize(f.pixelSize() * scale);// .setPointSize(f.pointSizeF() * scale);
    this->setFont(f);
    */

    ui->gridFrame->setGeometry(0, 0, this->width(), this->height());

    //QObjectList obj = this->children();
    if(game){
        game->setGeometry(0, 0, width(), height());
    }
}

//计时器事件。timer在子控件里面执行的效果不理想，就放到主窗口里面了
void MainWindow::timerEvent(QTimerEvent *e)
{
    if(game){
        //判断游戏是否结束
        if(game->isEnd()){
            //关闭计时器
            this->killTimer(timerID);

            //释放游戏对象
            delete game;
            game = nullptr;
            return;
        }

        //执行游戏
        game->repaint();
    }
}

void MainWindow::on_btnSnake_clicked()
{
    game = new SnakeGame(this);
    game->setGeometry(0, 0, width(), height());
    game->show();
    game->setFocus();   //设置焦点， 不然不响应按键

    //开启计时器
    timerID = this->startTimer(40);
}

void MainWindow::on_btnLinks_clicked()
{
    game = new LinksGame(this);
    game->setGeometry(0, 0, width(), height());
    game->show();
    game->setFocus();   //设置焦点， 不然不响应按键

    //开启计时器
    timerID = this->startTimer(40);
}

void MainWindow::on_btnMaze_clicked()
{
    game = new MazeGame(this);
    game->setGeometry(0, 0, width(), height());
    game->show();
    game->setFocus();   //设置焦点， 不然不响应按键

    //开启计时器
    timerID = this->startTimer(40);
}

void MainWindow::on_btnExit_clicked()
{
    this->close();
}

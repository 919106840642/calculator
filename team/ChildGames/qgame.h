#ifndef QGAME_H
#define QGAME_H

#include <qframe.h>
#include <qpainter.h>
#include <qmessagebox.h>

#include <QKeyEvent>

#include "gametype.h"

//
// 游戏框架
// mainwindow里面有个game指针，不同游戏从这个类派生
// 需要那个游戏，game就new成那个类就行
// 关闭游戏就是释放掉game
//

class QGame : public QFrame
{
public:
    explicit QGame(QWidget *parent = nullptr);
    ~QGame();

    //游戏是否运行
    bool isRunning() { return m_running; }

    //判断游戏是否结束
    bool isEnd() { return m_isEnd; }

    //执行游戏进程
    virtual bool doGame();

    //绘制背景图片
    void drawBackground(QPainter& painter);

    //绘制文字
    void drawtext(QPainter& p, int x, int y, QString text, QColor color);

    //获得文字宽度
    int fontsize(QPainter& p);
    int textwidth(QPainter& p, const QString& text);
    int textheight(QPainter& p);

    //显示消息
    void msgbox(QString title, QString text);

protected:
    bool m_running; //游戏是否运行
    bool m_isEnd;   //游戏是否结束
    int m_border;   //绘制空白边框宽度

    QString message;    //提示消息

private:
    QFont textfont;     //游戏字体
    QPixmap background; //背景图片

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void mouseMoveEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

};

#endif // QGAME_H

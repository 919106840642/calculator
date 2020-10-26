#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <qgame.h>

class SnakeGame : public QGame
{
public:
    const int MAP_CX = 40;
    const int MAP_CY = 27;

public:
    explicit SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

private:
    array2<int> m_map;      //地图
    deque<vec2i> m_snake;   //蛇的身体，用了个双向数组
    clock_t m_speed;        //游戏速度
    clock_t m_lastinput;    //最后响应输入时间

    int JudgeDirection;     //蛇的方向
    int JudgeSum;           //。。。
    int Hard;               //游戏难度

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);


    bool isEmpty(int x, int y);
    void foodRand();
    void controlMove();
    void move();

    bool Jfood();
    bool Jwall();
    bool Jsnake();

};

#endif // SNAKEGAME_H

#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <qgame.h>

class MazeGame : public QGame
{
public:
    //这个根据那个代码，都要是偶数
    const int MAP_CX = 20;
    const int MAP_CY = 20;

    struct Node
    {
        int x, y;
    };

public:
    explicit MazeGame(QWidget *parent = nullptr);
    ~MazeGame();

private:
    vec2i player;           //玩家位置
    array2<int> m_map;      //地图
    array2<int> m_vis;      //寻路标记
    clock_t m_speed;        //游戏速度
    clock_t m_lastinput;    //最后一次操作时间

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);

    void Creative();
    bool Ismaze();
    void move(Direction dir);

    //判断是否出口
    bool isExit(int x, int y)
    {
        return x == MAP_CX - 2 && y == MAP_CY - 2;
    }
};

#endif // MAZEGAME_H

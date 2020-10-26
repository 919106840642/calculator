#ifndef LINKSGAME_H
#define LINKSGAME_H

#include <qgame.h>

class LinksGame : public QGame
{
public:
    const int MAP_CX = 16;
    const int MAP_CY = 8;

public:
    explicit LinksGame(QWidget *parent = nullptr);
    ~LinksGame();

private:
    array2<int> m_map;
    vec2i mouse;        //鼠标位置方块
    vec2i first;        //第一个选中的方块
    int score;          //分数

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void Creative();
    bool Ismaze();
    void move(Direction dir);

    void init();
};

#endif // LINKSGAME_H

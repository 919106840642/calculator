#include "mazegame.h"

MazeGame::MazeGame(QWidget *parent) :
    QGame(parent),
    m_map(),
    m_vis()
{
    m_map.resize(MAP_CX, MAP_CY);
    m_vis.resize(MAP_CX, MAP_CY);

    //迷宫边框
    m_map.set_wall(1);

    player = vec2i(1, 1);

    m_speed = 200;
    m_lastinput = clock();
}

MazeGame::~MazeGame()
{
}

void MazeGame::keyPressEvent(QKeyEvent *e)
{
    //开始游戏
    if(e->key() == Qt::Key_Return && m_running == false){
        //初始化迷宫
        message = "正在初始化迷宫。";
        Creative();
        this->repaint();
        while (!Ismaze()){
            Creative();
            this->repaint();
        }
        message = "迷宫初始化完成。";
        m_running = true;
        return;
    }

    //退出游戏
    if(e->key() == Qt::Key_Escape){
        m_running = false;
        m_isEnd = true;
        return;
    }

    //如果游戏没有执行，返回
    if(m_running == false){
        return;
    }

    if (e->key() == Qt::Key_Up)
    {
        move(dirUp);
    }
    else if (e->key() == Qt::Key_Down)
    {
        move(dirDown);
    }

    if (e->key() == Qt::Key_Left)
    {
        move(dirLeft);
    }
    else if (e->key() == Qt::Key_Right)
    {
        move(dirRight);
    }
}

void MazeGame::keyReleaseEvent(QKeyEvent *e)
{

}

void MazeGame::paintEvent(QPaintEvent *e)
{
    if(m_running){
        //处理按键
        if(clock() - m_lastinput > m_speed){
            //controlMove();
            m_lastinput = clock();
        }
    }

    //绘制
    QPainter painter(this);
    //QRect client = QRect(0, 0, this->width(), this->height());
    drawBackground(painter);

    QRectF rc;
    float tx, ty;
    float h = float(height() - m_border) / MAP_CY;
    float w = h;

    QImage wall(":/assets/wall.png");
    QImage mouse(":/assets/mouse.png");

    //绘制地图
    for(size_t y=0; y<m_map.sizeY(); ++y){
        ty = m_border / 2 + h * y;
        for(size_t x=0; x<m_map.sizeX(); ++x){
            tx = m_border / 2 + w * x;
            rc = QRectF(tx, ty, w, h);
            if(player == vec2i(x, y)){
                //painter.setBrush(Qt::yellow);
                //painter.drawEllipse(rc);
                painter.drawImage(rc, mouse);
            }
            else if(m_map[y][x]){
                //painter.setBrush(Qt::black);
                //painter.drawRect(rc);
                painter.drawImage(rc, wall);
            }
            else if(isExit(x, y)){
                painter.setBrush(Qt::green);
                painter.drawRect(rc);
            }
        }
    }

    //绘制信息
    int x = width() - m_border - 250;
    QString s;
    drawtext(painter, x, 300, "方向键：上下左右", Qt::black);
    drawtext(painter, x, 330, "到达出口游戏结束", Qt::black);
    drawtext(painter, x, 360, "ENTER键 开 始", Qt::black);
    drawtext(painter, x, 390, "ESC键　 结 束", Qt::black);

    drawtext(painter, x, 450, message, Qt::black);
}

//随机迷宫
void MazeGame::Creative()
{
    srand((unsigned)time(NULL));
    for (int i = 1; i<MAP_CY - 1; i++)
    {
        for (int j = 1; j<MAP_CX - 1; j++)
        {
            if ((rand() % 99)<34){
                m_map[i][j] = 1;
            }
            else {
                m_map[i][j] = 0;
            }
        }
    }
    m_map[1][1] = m_map[MAP_CY - 2][MAP_CX - 2] = 0;
}

//判断是否能够到达终点
bool MazeGame::Ismaze()
{
    m_vis.fill(0);
    int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
    queue<Node> q;
    Node tmp, next;
    tmp.x = 1;
    tmp.y = 1;
    m_vis[1][1] = 1;
    q.push(tmp);

    int x, y;
    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        if (isExit(tmp.x, tmp.y)){
            //找到终点
            return 1;
        }
        for (int i = 0; i<4; i++){
            x = tmp.x + dx[i];
            y = tmp.y + dy[i];

            if(m_vis[y][x]){//已经查找过，直接跳过!!!
                continue;
            }

            if (x==0 || x==MAP_CX - 1 || y==0 || y==MAP_CY - 1){
                //在边界上面，也要标记一下
                m_vis[y][x] = 1;
                continue;
            }

            if (!m_map[y][x] && !m_map[y][x])
            {
                next.x = x;
                next.y = y;
                q.push(next);
                m_vis[y][x] = 1;
            }
        }
    }
    return 0;
}

void MazeGame::move(Direction dir)
{
    vec2i p = player;
    switch(dir){
    case dirUp:
        p.y--;
        break;
    case dirDown:
        p.y++;
        break;
    case dirLeft:
        p.x--;
        break;
    case dirRight:
        p.x++;
        break;
    }

    if(p.x <= 0 || p.x >= MAP_CX || p.y <= 0 || p.y >= MAP_CY || m_map[p.y][p.x]){
        message = "此路不通!";
        return ;
    }

    player = p;

    if(isExit(player.x, player.y)){
        m_running = false;
        msgbox("到达终点", "恭喜你到达了终点，游戏结束!");
        m_isEnd = true;
    }
}

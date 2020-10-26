#include "snakegame.h"

SnakeGame::SnakeGame(QWidget *parent) :
    QGame(parent),
    m_map(),
    m_snake()
{
    m_map.resize(MAP_CX, MAP_CY);

    //迷宫边框
    m_map.set_wall(1);

    //初始化蛇的位置
    m_snake.push_back(vec2i(MAP_CX / 2, MAP_CY / 2));

    //随机一个食物
    foodRand();

    m_speed = 500;  //初始化游戏速度
    m_lastinput = clock();//最后一次操作时间

    JudgeDirection = dirUp;
    JudgeSum = 0;
    Hard = 0;
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::keyPressEvent(QKeyEvent *e)
{
    //开始游戏
    if(e->key() == Qt::Key_Return){
        m_running = true;
    }

    //退出游戏
    if(e->key() == Qt::Key_Escape){
        m_running = false;
        m_isEnd = true;
        return;
    }

    //相应按键
    if (e->key() == Qt::Key_Up)
    {
        if(JudgeDirection != dirDown){//防止回头
            JudgeDirection = dirUp;
        }
    }
    else if (e->key() == Qt::Key_Down)
    {
        if(JudgeDirection != dirUp){
            JudgeDirection = dirDown;
        }
    }

    if (e->key() == Qt::Key_Left)
    {
        if(JudgeDirection != dirRight){
            JudgeDirection = dirLeft;
        }
    }
    else if (e->key() == Qt::Key_Right)
    {
        if(JudgeDirection != dirLeft){
            JudgeDirection = dirRight;
        }
    }
}

void SnakeGame::keyReleaseEvent(QKeyEvent *e)
{

}

void SnakeGame::paintEvent(QPaintEvent *e)
{
    if(m_running){
        //处理按键
        if(clock() - m_lastinput > m_speed){
            //controlMove();
            move();
            m_lastinput = clock();
        }
    }

    //绘制
    QPainter painter(this);
    drawBackground(painter);

    QRectF rc;
    float tx, ty;
    float w = float(width() - m_border - 200) / MAP_CX;
    float h = float(height() - m_border) / MAP_CY;

    QImage wall(":/assets/wall.png");
    QImage food(":/assets/cake.png");

    //绘制地图
    for(size_t y=0; y<m_map.sizeY(); ++y){
        ty = m_border / 2 + h * y;
        for(size_t x=0; x<m_map.sizeX(); ++x){
            tx = m_border / 2 + w * x;
            rc = QRectF(tx, ty, w, h);
            switch(m_map[y][x]){
            case 1:
                //painter.setBrush(Qt::black);
                painter.drawImage(rc, wall);
                break;
            case 2:
                //painter.setBrush(Qt::yellow);
                painter.drawImage(rc, food);
                break;
            default:
                continue;
            }
            //painter.drawRect(QRectF(tx, ty, w, h));
        }
    }

    //绘制蛇
    painter.setBrush(Qt::green);
    for(size_t i=0; i<m_snake.size(); ++i){
        tx = m_border / 2 + w * m_snake[i].x;
        ty = m_border / 2 + h * m_snake[i].y;
        painter.drawRect(tx, ty, w, h);
    }

    //绘制信息
    int x = width() - m_border - 150;
    QString s;
    drawtext(painter, x, 120, "得分：", Qt::black);
    s.setNum(m_snake.size() - 1);
    drawtext(painter, x + 60, 120, s, Qt::black);

    drawtext(painter, x, 150, "难度：", Qt::black);
    s.setNum(Hard);
    drawtext(painter, x + 60, 150, s, Qt::black);

    drawtext(painter, x, 300, "方向键：上下左右", Qt::black);
    drawtext(painter, x, 330, "每5分增一个难度 (速度)", Qt::black);
    drawtext(painter, x, 360, "ENTER键 开 始", Qt::black);
    drawtext(painter, x, 390, "ESC键　 结 束", Qt::black);
}

bool SnakeGame::isEmpty(int x, int y)
{
    if(m_map[y][x] == 0 &&
        std::find(m_snake.begin(), m_snake.end(), vec2i(x, y)) == m_snake.end()){
        return true;
    }
    return false;
}

void SnakeGame::foodRand()
{
    srand((int)time(0));

    //随机一个空位，放置食物
    vec2i p = m_map.random_space();
    if(p.is_valid()){
        m_map[p.y][p.x] = 2;
    }
}

void SnakeGame::move()
{
    vec2i head = m_snake.front();
    switch(JudgeDirection){
    case dirUp:
        head.y--;
        break;
    case dirDown:
        head.y++;
        break;
    case dirLeft:
        head.x--;
        break;
    case dirRight:
        head.x++;
        break;
    }

    m_snake.push_front(head);

    if(Jwall() || Jsnake()){
        m_running = false;
        msgbox("游戏结束", "抱歉，你撞到了自己/墙壁，游戏结束!");
        m_isEnd = true;//这个要等到提示框关闭才设置
        return;
    }

    if(Jfood() == false){
        m_snake.pop_back();
    }
}

bool SnakeGame::Jfood()
{
    vec2i head = m_snake.front();
    if(m_map[head.y][head.x] == 2){

        m_map[head.y][head.x] = 0;

        JudgeSum += 1;
        if (JudgeSum == 5)
        {
            JudgeSum = 0;
            Hard += 1;

            //游戏加速，20毫秒
            m_speed -= 20;
            if(m_speed < 20){//游戏最低速度
                m_speed = 20;
            }
        }

        foodRand();

        return true;
    }
    return false;
}

//碰墙判断
bool SnakeGame::Jwall()
{
    vec2i head = m_snake.front();
    if (head.x <= 0 || head.x >= MAP_CX || head.y <= 0 || head.y >= MAP_CY){
        return true;
    }
    else{
        return false;
    }
}

//碰自己判断
bool SnakeGame::Jsnake()
{
    vec2i head = m_snake.front();
    if(std::find(m_snake.begin()+1, m_snake.end(), head) != m_snake.end()){
        return true;
    }
    else{
        return false;
    }
}

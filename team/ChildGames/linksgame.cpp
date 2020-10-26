#include "linksgame.h"

vec2i direct[4] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };

//寻路封装的一个类，这个改改也可以用到迷宫哪里
class findpath
{
public:
    struct node
    {
        int x;
        int y;
        int dir;
        int turn;

        bool operator < (const node &c) const
        {
            //return c.turn < turn;
            return turn < c.turn;
        }
    };

private:
    priority_queue<node> openlist;  //开放列表
    array2<char> m_tag;             //标记地图是否查询过

    //判断是否可走
    bool judge(const array2<int>& map, int x, int y)
    {
        if(!map.is_valid(x, y)){//坐标是否合法
            return false;
        }
        if (m_tag[y][x]){//是否已经查找过
            return false;
        }
        if (map[y][x] != 0){//目的地是否为空
            return false;
        }
        return true;
    }

public:
    //查找路径，如果找到返回转弯次数，否则返回-1
    int find(const array2<int>& map, int x1, int y1, int x2, int y2)
    {
        //坐标不合法
        if(!map.is_valid(x1, y1) || !map.is_valid(x2, y1)){
            return -1;
        }

        //位置不能相等
        if(x1 == x2 && y1 == y2){
            return -1;
        }

        //不能为空
        if(!map[y1][x1] || !map[y2][x2]){
            return -1;
        }

        //再加一个，两个量要相等
        if(map[y1][x1] != map[y2][x2]){
            return -1;
        }

        //情况列表
        while(openlist.size()){
            openlist.pop();
        }

        //初始化标记缓冲
        m_tag.resize(map.sizeX(), map.sizeY());
        m_tag.fill(0);

        //先压入第一个元素
        node temp;
        temp.x = x1;
        temp.y = y1;
        temp.turn = -1;
        temp.dir = 9999;

        openlist.push(temp);
        m_tag[y1][x1] = 1;

        node n;
        while (!openlist.empty()){
            temp = openlist.top();
            openlist.pop();

            //遍历上下左右
            for (int i = 0; i < 4; ++i){
                //初始化n
                n.x = temp.x + direct[i].x;
                n.y = temp.y + direct[i].y;
                n.dir = i;

                //判断n方向是否和temp一样，判断转弯次数
                if (temp.dir == 9999 || (temp.dir + i) % 2 == 1){
                    n.turn = temp.turn + 1;
                }
                else{
                    n.turn = temp.turn;
                }


                if(n.turn >= 3){
                    continue;
                }

                if(n.x == x2 && n.y == y2){
                    return n.turn;
                }

                //判断是否可走，把n压入开放列表
                if(judge(map, n.x, n.y)){
                    openlist.push(n);
                    m_tag[n.y][n.x] = 1;
                    //qDebug("find x %d, y %d", n.x, n.y);
                }
            }
        }
        return -2;
    }

};



LinksGame::LinksGame(QWidget *parent) :
    QGame(parent),
    m_map()
{
    m_map.resize(MAP_CX, MAP_CY);

    //支持鼠标移动消息
    setMouseTracking(true);

    first = vec2i::invalid();

    init();
    m_running = true;
}

LinksGame::~LinksGame()
{
}

void LinksGame::keyPressEvent(QKeyEvent *e)
{
    //开始游戏
    if(e->key() == Qt::Key_Return && m_running == false){
        //初始化
        //init();
        //m_running = true;
        return;
    }

    //退出游戏
    if(e->key() == Qt::Key_Escape){
        m_running = false;
        m_isEnd = true;
        return;
    }
}

void LinksGame::keyReleaseEvent(QKeyEvent *e)
{

}

void LinksGame::mousePressEvent(QMouseEvent *e)
{
    if(!first.is_valid()){
        first = mouse;
    }
    else{
        findpath f;
        int n = f.find(m_map, first.x, first.y, mouse.x, mouse.y);
        if(n < 0){
        }
        else{
            if(n < 4){//小于3步，消除
                m_map[first.y][first.x] = 0;
                m_map[mouse.y][mouse.x] = 0;
                score += 20;
            }
        }
        first = vec2i::invalid();
        //qDebug("n = %d", n);
    }
}

void LinksGame::mouseReleaseEvent(QMouseEvent *e)
{

}

void LinksGame::mouseMoveEvent(QMouseEvent *e)
{
    //根据鼠标位置计算方块位置
    mouse = vec2i(e->x(), e->y());
    mouse.x -= m_border / 2;
    mouse.y -= m_border / 2;

    //无效值
    if(mouse.x < 0 || mouse.y < 0){
        mouse = vec2i::invalid();
        return;
    }

    float w = float(width() - m_border - 200) / MAP_CX;
    float h = float(height() - m_border) / MAP_CY;

    if(mouse.x >= w*MAP_CX || mouse.y>=h*MAP_CY){
        mouse = vec2i::invalid();
        return;
    }

    //计算当前位置
    mouse.x /= w;
    mouse.y /= h;
}

void LinksGame::paintEvent(QPaintEvent *e)
{
    //绘制
    QPainter painter(this);
    drawBackground(painter);

    QRectF rc;
    float tx, ty;
    float w = float(width() - m_border - 200) / MAP_CX;
    float h = float(height() - m_border) / MAP_CY;

    char buf[2] = {0};
    float cw;

    QImage image(":/assets/button.png");
    QImage select(":/assets/select.png");

    //绘制地图
    for(size_t y=0; y<m_map.sizeY(); ++y){
        ty = m_border / 2 + h * y;
        for(size_t x=0; x<m_map.sizeX(); ++x){
            tx = m_border / 2 + w * x;
            rc = QRectF(tx, ty, w, h);

            if(m_map[y][x]){
                //绘制背景
                if(x == size_t(first.x) && y == size_t(first.y)){
                    //选择的第一个
                    painter.drawImage(QRectF(tx + 2, ty + 2, w - 4, h - 4), select);
                }
                else{
                    if(x == size_t(mouse.x) && y == size_t(mouse.y)){
                        painter.drawImage(QRectF(tx + 2, ty + 2, w - 4, h - 4), select);
                    }
                    else{
                        painter.drawImage(QRectF(tx + 2, ty + 2, w - 4, h - 4), image);
                    }
                }

                //绘制字符
                buf[0] = 'a' + m_map[y][x] - 1;
                cw = textwidth(painter, buf);
                drawtext(painter, tx + (w - cw) / 2,
                         ty + (h - textheight(painter)) / 2 + fontsize(painter),
                         buf, Qt::black);
            }

            if(x == size_t(mouse.x) && y == size_t(mouse.y)){
                //绘制鼠标位置
                painter.setPen(Qt::red);
                painter.setBrush(Qt::NoBrush);
                painter.drawRect(rc);
            }
        }
    }

    //绘制信息

    int x = width() - m_border - 150;
    QString s;
    s.setNum(score);
    drawtext(painter, x, 150, "分数：", Qt::black);
    drawtext(painter, x + 50, 150, s, Qt::black);
    drawtext(painter, x, 200, "鼠标点选两个", Qt::black);
    drawtext(painter, x, 220, "相同的卡消除", Qt::black);
    drawtext(painter, x, 250, "ESC键　 结 束", Qt::black);
}

void LinksGame::init()
{
    int sum = (MAP_CX - 2) * (MAP_CY - 2);
    int t = 0;
    int ch;
    vec2i p1, p2;
    srand(time(0));
    m_map.fill(0);
    m_map.set_wall(1);

    while (t != sum)    {
        //随机一个字符
        ch = random(1, 27);

        //放置两对
        p1 = m_map.random_space();
        m_map[p1.y][p1.x] = ch;

        p2 = m_map.random_space();
        m_map[p2.y][p2.x] = ch;

        /*
        //这个效率很差，指不定要随机多长时间
        for (int i = 1; i <= 2; ++i){
            while (true){
                x = random(1, MAP_CX);
                y = random(1, MAP_CY);
                if (m_map[y][x] == 0){
                    m_map[y][x] = ch;
                    break;
                }
            }
        }
        */
        t += 2;
    }
    m_map.set_wall(0);

    score = 0;
}

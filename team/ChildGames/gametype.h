#ifndef GAMETYPE_H
#define GAMETYPE_H

//标准库
#include <algorithm>
#include <cmath>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

//随机数
int random(int value);
int random(int minVal, int maxVal);

//点向量
struct vec2i
{
    int x;
    int y;

    vec2i() : x(), y(){}
    vec2i(int _x, int _y) : x(_x), y(_y){}

    //判断是否相等
    bool operator==(const vec2i& v)
    {
        return x == v.x && y == v.y;
    }

    //判断坐标是否有效
    bool is_valid()
    {
        return x != INT_MAX && y != INT_MAX;
    }

    //返回一个无效坐标
    static vec2i invalid()
    {
        return vec2i(INT_MAX, INT_MAX);
    }

    //相加
    vec2i operator+(const vec2i& p)
    {
        return vec2i(x += p.x, y += p.y);
    }
};

//动态二维数组
template<typename T>
class array2
{
private:
    vector< vector<T> > m_data;
    size_t m_cx;
    size_t m_cy;

public:
    array2() : m_data(), m_cx(), m_cy()
    {

    }

    //返回大小
    size_t sizeX()const
    {
        return m_cx;
    }

    size_t sizeY()const
    {
        return m_cy;
    }

    //重新设置大小
    void resize(size_t x, size_t y)
    {
        m_data.resize(y);
        for(size_t i=0; i<y; ++i)
        {
            m_data[i].resize(x);
        }
        m_cx = x;
        m_cy = y;
    }

    //整个二维数组填充成value
    void fill(const T& value)
    {
        for(size_t i=0; i<m_data.size(); ++i){
            std::fill(m_data[i].begin(), m_data[i].end(), value);
        }
    }

    //清空
    void clear()
    {
        m_data.clear();
        m_cx = m_cy = 0;
    }

    //取值
    vector<T>& operator[](size_t i)
    {
        return m_data[i];
    }

    const vector<T>& operator[](size_t i)const
    {
        return m_data[i];
    }

    //判断坐标是否有效
    bool is_valid(int x, int y)const
    {
        return size_t(x) < m_cx && size_t(y) < m_cy;
    }

    //返回一个随机的空位置
    vec2i random_space()const
    {
        //列表所有空白的区域
        vector<vec2i> space;
        for(size_t y=0; y<m_cy; ++y){
            for(size_t x=0; x<m_cx; ++x){
                if(!m_data[y][x]){
                    space.push_back(vec2i(x, y));
                }
            }
        }

        if(space.size() != 0){
            return space[random(space.size())];
        }
        else{
            return vec2i::invalid();
        }
    }

    //设置周围一圈的边框
    void set_wall(int value)
    {
        if(m_cx < 2 || m_cy < 2){
            this->fill(value);
            return;
        }

        for(int y=0; y<m_cy; ++y){
            m_data[y][0] = value;
            m_data[y][m_cx - 1] = value;
        }

        for(int x=0; x<m_cx; ++x){
            m_data[0][x] = value;
            m_data[m_cy - 1][x] = value;
        }
    }
};

//方向
enum Direction
{
    dirLeft,
    dirRight,
    dirUp,
    dirDown,
};

#endif // GAMETYPE_H

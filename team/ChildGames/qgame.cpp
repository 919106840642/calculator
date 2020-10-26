#include "qgame.h"

QGame::QGame(QWidget *parent) :
    QFrame(parent)
{
    m_running = false;
    m_isEnd = false;

    m_border = 60;

    textfont = this->font();
    textfont.setPixelSize(16);
}

QGame::~QGame()
{
}

void QGame::keyPressEvent(QKeyEvent *e)
{
    //keyboard[e->key()] = 1;
}

void QGame::keyReleaseEvent(QKeyEvent *e)
{
    //keyboard[e->key()] = 0;
}

void QGame::mouseMoveEvent(QMouseEvent *e)
{

}

void QGame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //QRect client = QRect(0, 0, this->width(), this->height());
    drawBackground(painter);
    //qDebug("painter: %d", (int)clock());
}

void QGame::resizeEvent(QResizeEvent *e)
{
    background = QPixmap(":/assets/background.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(background));
    this->setPalette(palette);
}

void QGame::drawBackground(QPainter& painter)
{
    painter.fillRect(0, 0, this->width(), this->height(), QBrush(background));

    //this->keyPressEvent()
}

void QGame::drawtext(QPainter& p, int x, int y, QString text, QColor color)
{
    p.setFont(textfont);
    p.setPen(color);
    p.drawText(x, y, text);
}

int QGame::fontsize(QPainter& p)
{
    return p.fontMetrics().ascent();
}

int QGame::textwidth(QPainter& p, const QString& text)
{
    return p.fontMetrics().width(text);
}

int QGame::textheight(QPainter& p)
{
    return p.fontMetrics().height();
}

bool QGame::doGame()
{
    return true;
}

void QGame::msgbox(QString title, QString text)
{
    QMessageBox::information(this, title, text, QMessageBox::Ok);
}

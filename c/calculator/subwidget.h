#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>

class subwidget : public QWidget
{
    Q_OBJECT
public:
    explicit subwidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SUBWIDGET_H
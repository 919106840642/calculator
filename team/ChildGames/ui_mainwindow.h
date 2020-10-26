/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *gridFrame;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QPushButton *btnSnake;
    QPushButton *btnLinks;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnMaze;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnExit;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 576);
        MainWindow->setMinimumSize(QSize(1024, 576));
        MainWindow->setMaximumSize(QSize(1024, 576));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        MainWindow->setFont(font);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridFrame = new QFrame(centralwidget);
        gridFrame->setObjectName(QString::fromUtf8("gridFrame"));
        gridFrame->setGeometry(QRect(10, 10, 521, 391));
        gridLayout = new QGridLayout(gridFrame);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(40, 40, 40, 40);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 7, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 5, 1, 1, 1);

        btnSnake = new QPushButton(gridFrame);
        btnSnake->setObjectName(QString::fromUtf8("btnSnake"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        btnSnake->setFont(font1);
        btnSnake->setCursor(QCursor(Qt::PointingHandCursor));
        btnSnake->setAutoDefault(false);
        btnSnake->setFlat(true);

        gridLayout->addWidget(btnSnake, 4, 1, 1, 1);

        btnLinks = new QPushButton(gridFrame);
        btnLinks->setObjectName(QString::fromUtf8("btnLinks"));
        btnLinks->setFont(font1);
        btnLinks->setCursor(QCursor(Qt::PointingHandCursor));
        btnLinks->setFlat(true);

        gridLayout->addWidget(btnLinks, 6, 1, 1, 1);

        label = new QLabel(gridFrame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 6, 0, 1, 1);

        btnMaze = new QPushButton(gridFrame);
        btnMaze->setObjectName(QString::fromUtf8("btnMaze"));
        btnMaze->setFont(font1);
        btnMaze->setCursor(QCursor(Qt::PointingHandCursor));
        btnMaze->setFlat(true);

        gridLayout->addWidget(btnMaze, 8, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 9, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 6, 2, 1, 1);

        btnExit = new QPushButton(gridFrame);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        btnExit->setFont(font1);
        btnExit->setCursor(QCursor(Qt::PointingHandCursor));
        btnExit->setFlat(true);

        gridLayout->addWidget(btnExit, 10, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 11, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnSnake->setText(QCoreApplication::translate("MainWindow", "\350\264\252\345\220\203\350\233\207", nullptr));
        btnLinks->setText(QCoreApplication::translate("MainWindow", "\350\277\236\350\277\236\347\234\213", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\260\217 \346\270\270 \346\210\217 \351\233\206", nullptr));
        btnMaze->setText(QCoreApplication::translate("MainWindow", "\350\277\267\345\256\253", nullptr));
        btnExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

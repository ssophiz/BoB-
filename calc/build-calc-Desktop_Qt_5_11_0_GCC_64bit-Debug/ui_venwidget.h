/********************************************************************************
** Form generated from reading UI file 'venwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENWIDGET_H
#define UI_VENWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VenWidget
{
public:
    QLCDNumber *lcdNumber;
    QPushButton *n10;
    QPushButton *n100;
    QPushButton *n500;
    QPushButton *coke;
    QPushButton *tea;
    QPushButton *milk;
    QPushButton *n50;
    QPushButton *reset;

    void setupUi(QWidget *VenWidget)
    {
        if (VenWidget->objectName().isEmpty())
            VenWidget->setObjectName(QStringLiteral("VenWidget"));
        VenWidget->resize(400, 300);
        lcdNumber = new QLCDNumber(VenWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(100, 20, 141, 51));
        n10 = new QPushButton(VenWidget);
        n10->setObjectName(QStringLiteral("n10"));
        n10->setGeometry(QRect(20, 100, 89, 25));
        n100 = new QPushButton(VenWidget);
        n100->setObjectName(QStringLiteral("n100"));
        n100->setGeometry(QRect(20, 180, 89, 25));
        n500 = new QPushButton(VenWidget);
        n500->setObjectName(QStringLiteral("n500"));
        n500->setGeometry(QRect(20, 220, 89, 25));
        coke = new QPushButton(VenWidget);
        coke->setObjectName(QStringLiteral("coke"));
        coke->setGeometry(QRect(180, 120, 89, 25));
        tea = new QPushButton(VenWidget);
        tea->setObjectName(QStringLiteral("tea"));
        tea->setGeometry(QRect(180, 160, 89, 25));
        milk = new QPushButton(VenWidget);
        milk->setObjectName(QStringLiteral("milk"));
        milk->setGeometry(QRect(180, 200, 89, 25));
        n50 = new QPushButton(VenWidget);
        n50->setObjectName(QStringLiteral("n50"));
        n50->setGeometry(QRect(20, 140, 89, 25));
        reset = new QPushButton(VenWidget);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(270, 40, 89, 25));

        retranslateUi(VenWidget);

        QMetaObject::connectSlotsByName(VenWidget);
    } // setupUi

    void retranslateUi(QWidget *VenWidget)
    {
        VenWidget->setWindowTitle(QApplication::translate("VenWidget", "VenWidget", nullptr));
        n10->setText(QApplication::translate("VenWidget", "10", nullptr));
        n100->setText(QApplication::translate("VenWidget", "100", nullptr));
        n500->setText(QApplication::translate("VenWidget", "500", nullptr));
        coke->setText(QApplication::translate("VenWidget", "coke(100)", nullptr));
        tea->setText(QApplication::translate("VenWidget", "tea(300)", nullptr));
        milk->setText(QApplication::translate("VenWidget", "milk(500)", nullptr));
        n50->setText(QApplication::translate("VenWidget", "50", nullptr));
        reset->setText(QApplication::translate("VenWidget", "reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VenWidget: public Ui_VenWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENWIDGET_H

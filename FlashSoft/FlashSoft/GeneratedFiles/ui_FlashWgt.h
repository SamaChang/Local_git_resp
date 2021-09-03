/********************************************************************************
** Form generated from reading UI file 'FlashWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHWGT_H
#define UI_FLASHWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "singlewgt.h"

QT_BEGIN_NAMESPACE

class Ui_FlashWgt
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer;
    QWidget *singleWgts;
    QGridLayout *gridLayout;
    SingleWgt *singleWgt_1;
    SingleWgt *singleWgt_2;
    SingleWgt *singleWgt_3;
    SingleWgt *singleWgt_4;
    SingleWgt *singleWgt_5;
    SingleWgt *singleWgt_6;
    SingleWgt *singleWgt_7;
    SingleWgt *singleWgt_8;

    void setupUi(QWidget *FlashWgt)
    {
        if (FlashWgt->objectName().isEmpty())
            FlashWgt->setObjectName(QString::fromUtf8("FlashWgt"));
        FlashWgt->resize(740, 492);
        verticalLayout = new QVBoxLayout(FlashWgt);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(FlashWgt);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_1 = new QPushButton(widget_2);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));

        horizontalLayout->addWidget(pushButton_1);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_2);

        singleWgts = new QWidget(FlashWgt);
        singleWgts->setObjectName(QString::fromUtf8("singleWgts"));
        gridLayout = new QGridLayout(singleWgts);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        singleWgt_1 = new SingleWgt(singleWgts);
        singleWgt_1->setObjectName(QString::fromUtf8("singleWgt_1"));

        gridLayout->addWidget(singleWgt_1, 0, 0, 1, 1);

        singleWgt_2 = new SingleWgt(singleWgts);
        singleWgt_2->setObjectName(QString::fromUtf8("singleWgt_2"));

        gridLayout->addWidget(singleWgt_2, 0, 1, 1, 1);

        singleWgt_3 = new SingleWgt(singleWgts);
        singleWgt_3->setObjectName(QString::fromUtf8("singleWgt_3"));

        gridLayout->addWidget(singleWgt_3, 0, 2, 1, 1);

        singleWgt_4 = new SingleWgt(singleWgts);
        singleWgt_4->setObjectName(QString::fromUtf8("singleWgt_4"));

        gridLayout->addWidget(singleWgt_4, 0, 3, 1, 1);

        singleWgt_5 = new SingleWgt(singleWgts);
        singleWgt_5->setObjectName(QString::fromUtf8("singleWgt_5"));

        gridLayout->addWidget(singleWgt_5, 1, 0, 1, 1);

        singleWgt_6 = new SingleWgt(singleWgts);
        singleWgt_6->setObjectName(QString::fromUtf8("singleWgt_6"));

        gridLayout->addWidget(singleWgt_6, 1, 1, 1, 1);

        singleWgt_7 = new SingleWgt(singleWgts);
        singleWgt_7->setObjectName(QString::fromUtf8("singleWgt_7"));

        gridLayout->addWidget(singleWgt_7, 1, 2, 1, 1);

        singleWgt_8 = new SingleWgt(singleWgts);
        singleWgt_8->setObjectName(QString::fromUtf8("singleWgt_8"));

        gridLayout->addWidget(singleWgt_8, 1, 3, 1, 1);


        verticalLayout->addWidget(singleWgts);


        retranslateUi(FlashWgt);

        QMetaObject::connectSlotsByName(FlashWgt);
    } // setupUi

    void retranslateUi(QWidget *FlashWgt)
    {
        FlashWgt->setWindowTitle(QCoreApplication::translate("FlashWgt", "FlashWgt", nullptr));
        pushButton_1->setText(QCoreApplication::translate("FlashWgt", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FlashWgt", "\346\243\200\346\265\213\345\217\257\347\224\250\344\270\262\345\217\243", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FlashWgt", "\345\274\200\345\247\213\347\203\247\345\206\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlashWgt: public Ui_FlashWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHWGT_H

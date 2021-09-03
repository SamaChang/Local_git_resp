/********************************************************************************
** Form generated from reading UI file 'SingleWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEWGT_H
#define UI_SINGLEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ArrowWorkChartWgt.h"
#include "RingsProgressBar.h"

QT_BEGIN_NAMESPACE

class Ui_SingleWgt
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_burn;
    QVBoxLayout *verticalLayout;
    RingsProgressBar *ringWgt;
    ArrowWorkChartWgt *arrowWgt;

    void setupUi(QWidget *SingleWgt)
    {
        if (SingleWgt->objectName().isEmpty())
            SingleWgt->setObjectName(QString::fromUtf8("SingleWgt"));
        SingleWgt->resize(255, 265);
        SingleWgt->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(SingleWgt);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        groupBox_burn = new QGroupBox(SingleWgt);
        groupBox_burn->setObjectName(QString::fromUtf8("groupBox_burn"));
        verticalLayout = new QVBoxLayout(groupBox_burn);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, -1, 3, 3);
        ringWgt = new RingsProgressBar(groupBox_burn);
        ringWgt->setObjectName(QString::fromUtf8("ringWgt"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ringWgt->sizePolicy().hasHeightForWidth());
        ringWgt->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(ringWgt);

        arrowWgt = new ArrowWorkChartWgt(groupBox_burn);
        arrowWgt->setObjectName(QString::fromUtf8("arrowWgt"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(arrowWgt->sizePolicy().hasHeightForWidth());
        arrowWgt->setSizePolicy(sizePolicy1);
        arrowWgt->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(arrowWgt);


        verticalLayout_2->addWidget(groupBox_burn);


        retranslateUi(SingleWgt);

        QMetaObject::connectSlotsByName(SingleWgt);
    } // setupUi

    void retranslateUi(QWidget *SingleWgt)
    {
        SingleWgt->setWindowTitle(QCoreApplication::translate("SingleWgt", "SingleWgt", nullptr));
        groupBox_burn->setTitle(QCoreApplication::translate("SingleWgt", "\347\203\247\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleWgt: public Ui_SingleWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEWGT_H

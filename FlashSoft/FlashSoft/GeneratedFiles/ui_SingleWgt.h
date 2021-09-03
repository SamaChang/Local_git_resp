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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleWgt
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_burn;
    QVBoxLayout *verticalLayout;
    QLabel *lab_image;
    QWidget *widget_state;
    QHBoxLayout *horizontalLayout;
    QToolButton *tbtn_ws;
    QToolButton *tbtn_bl;
    QToolButton *tbtn_erase;
    QToolButton *tbtn_prag;
    QToolButton *tbtn_finish;
    QProgressBar *progressBar;

    void setupUi(QWidget *SingleWgt)
    {
        if (SingleWgt->objectName().isEmpty())
            SingleWgt->setObjectName(QString::fromUtf8("SingleWgt"));
        SingleWgt->resize(210, 278);
        SingleWgt->setMaximumSize(QSize(210, 278));
        verticalLayout_2 = new QVBoxLayout(SingleWgt);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        groupBox_burn = new QGroupBox(SingleWgt);
        groupBox_burn->setObjectName(QString::fromUtf8("groupBox_burn"));
        verticalLayout = new QVBoxLayout(groupBox_burn);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, -1, 3, -1);
        lab_image = new QLabel(groupBox_burn);
        lab_image->setObjectName(QString::fromUtf8("lab_image"));
        lab_image->setPixmap(QPixmap(QString::fromUtf8(":/Img/Resources/load.png")));
        lab_image->setScaledContents(false);
        lab_image->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lab_image);

        widget_state = new QWidget(groupBox_burn);
        widget_state->setObjectName(QString::fromUtf8("widget_state"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_state->sizePolicy().hasHeightForWidth());
        widget_state->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(widget_state);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tbtn_ws = new QToolButton(widget_state);
        tbtn_ws->setObjectName(QString::fromUtf8("tbtn_ws"));
        tbtn_ws->setMaximumSize(QSize(30, 12));
        tbtn_ws->setFocusPolicy(Qt::NoFocus);
        tbtn_ws->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout->addWidget(tbtn_ws);

        tbtn_bl = new QToolButton(widget_state);
        tbtn_bl->setObjectName(QString::fromUtf8("tbtn_bl"));
        tbtn_bl->setMaximumSize(QSize(30, 12));
        tbtn_bl->setFocusPolicy(Qt::NoFocus);
        tbtn_bl->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout->addWidget(tbtn_bl);

        tbtn_erase = new QToolButton(widget_state);
        tbtn_erase->setObjectName(QString::fromUtf8("tbtn_erase"));
        tbtn_erase->setMaximumSize(QSize(30, 12));
        tbtn_erase->setFocusPolicy(Qt::NoFocus);
        tbtn_erase->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout->addWidget(tbtn_erase);

        tbtn_prag = new QToolButton(widget_state);
        tbtn_prag->setObjectName(QString::fromUtf8("tbtn_prag"));
        tbtn_prag->setMaximumSize(QSize(30, 12));
        tbtn_prag->setFocusPolicy(Qt::NoFocus);
        tbtn_prag->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout->addWidget(tbtn_prag);

        tbtn_finish = new QToolButton(widget_state);
        tbtn_finish->setObjectName(QString::fromUtf8("tbtn_finish"));
        tbtn_finish->setMaximumSize(QSize(30, 12));
        tbtn_finish->setFocusPolicy(Qt::NoFocus);
        tbtn_finish->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout->addWidget(tbtn_finish);


        verticalLayout->addWidget(widget_state);

        progressBar = new QProgressBar(groupBox_burn);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);


        verticalLayout_2->addWidget(groupBox_burn);


        retranslateUi(SingleWgt);

        QMetaObject::connectSlotsByName(SingleWgt);
    } // setupUi

    void retranslateUi(QWidget *SingleWgt)
    {
        SingleWgt->setWindowTitle(QCoreApplication::translate("SingleWgt", "SingleWgt", nullptr));
        groupBox_burn->setTitle(QCoreApplication::translate("SingleWgt", "\347\203\247\345\275\225", nullptr));
        lab_image->setText(QString());
        tbtn_ws->setText(QString());
        tbtn_bl->setText(QString());
        tbtn_erase->setText(QString());
        tbtn_prag->setText(QString());
        tbtn_finish->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SingleWgt: public Ui_SingleWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEWGT_H

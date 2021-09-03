/********************************************************************************
** Form generated from reading UI file 'FlashSoft.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLASHSOFT_H
#define UI_FLASHSOFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlashSoftClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FlashSoftClass)
    {
        if (FlashSoftClass->objectName().isEmpty())
            FlashSoftClass->setObjectName(QString::fromUtf8("FlashSoftClass"));
        FlashSoftClass->resize(720, 547);
        centralWidget = new QWidget(FlashSoftClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(centralWidget);
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
        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_2);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        FlashSoftClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(FlashSoftClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FlashSoftClass->setStatusBar(statusBar);

        retranslateUi(FlashSoftClass);

        QMetaObject::connectSlotsByName(FlashSoftClass);
    } // setupUi

    void retranslateUi(QMainWindow *FlashSoftClass)
    {
        FlashSoftClass->setWindowTitle(QCoreApplication::translate("FlashSoftClass", "Flash\347\203\247\345\206\231\350\275\257\344\273\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FlashSoftClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FlashSoftClass", "\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        pushButton->setText(QCoreApplication::translate("FlashSoftClass", "\347\203\247\345\205\245\347\250\213\345\272\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlashSoftClass: public Ui_FlashSoftClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLASHSOFT_H

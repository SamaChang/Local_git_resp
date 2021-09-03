/********************************************************************************
** Form generated from reading UI file 'QConfigIO.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCONFIGIO_H
#define UI_QCONFIGIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QConfigIO
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *QConfigIO)
    {
        if (QConfigIO->objectName().isEmpty())
            QConfigIO->setObjectName(QString::fromUtf8("QConfigIO"));
        QConfigIO->resize(433, 130);
        verticalLayout = new QVBoxLayout(QConfigIO);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(QConfigIO);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(QConfigIO);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 2, -1, 2);
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(widget_2);


        retranslateUi(QConfigIO);
        QObject::connect(pushButton, SIGNAL(clicked()), QConfigIO, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), QConfigIO, SLOT(reject()));

        QMetaObject::connectSlotsByName(QConfigIO);
    } // setupUi

    void retranslateUi(QDialog *QConfigIO)
    {
        QConfigIO->setWindowTitle(QCoreApplication::translate("QConfigIO", "\351\237\263\351\242\221IO\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("QConfigIO", "\351\237\263\351\242\221\350\276\223\345\205\245", nullptr));
        label_2->setText(QCoreApplication::translate("QConfigIO", "\351\237\263\351\242\221\350\276\223\345\207\272", nullptr));
        pushButton->setText(QCoreApplication::translate("QConfigIO", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QConfigIO", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QConfigIO: public Ui_QConfigIO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCONFIGIO_H

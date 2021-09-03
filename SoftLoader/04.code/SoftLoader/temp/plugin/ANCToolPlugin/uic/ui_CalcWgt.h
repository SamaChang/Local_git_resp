/********************************************************************************
** Form generated from reading UI file 'CalcWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCWGT_H
#define UI_CALCWGT_H

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

class Ui_CalcWgt
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *CalcWgt)
    {
        if (CalcWgt->objectName().isEmpty())
            CalcWgt->setObjectName(QString::fromUtf8("CalcWgt"));
        CalcWgt->resize(400, 172);
        verticalLayout = new QVBoxLayout(CalcWgt);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(CalcWgt);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        comboBox_3 = new QComboBox(widget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox_3, 2, 1, 1, 1);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(CalcWgt);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(75, 28));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 28));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(widget_2);


        retranslateUi(CalcWgt);

        QMetaObject::connectSlotsByName(CalcWgt);
    } // setupUi

    void retranslateUi(QDialog *CalcWgt)
    {
        CalcWgt->setWindowTitle(QCoreApplication::translate("CalcWgt", "\350\277\220\347\256\227\346\250\241\345\274\217", nullptr));
        label->setText(QCoreApplication::translate("CalcWgt", "\347\272\277\346\256\2651\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CalcWgt", "Line 2", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("CalcWgt", "Line 3", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("CalcWgt", "Line 4", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("CalcWgt", "Line 5", nullptr));

        label_2->setText(QCoreApplication::translate("CalcWgt", "\347\272\277\346\256\2652\357\274\232", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("CalcWgt", "Line 2", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("CalcWgt", "Line 3", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("CalcWgt", "Line 4", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("CalcWgt", "Line 5", nullptr));

        label_3->setText(QCoreApplication::translate("CalcWgt", "\350\277\220\347\256\227\346\226\271\345\274\217\357\274\232", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("CalcWgt", "\347\272\277\346\256\2651-\347\272\277\346\256\2652", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("CalcWgt", "\347\272\277\346\256\2651+\347\272\277\346\256\2652", nullptr));

        pushButton->setText(QCoreApplication::translate("CalcWgt", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CalcWgt", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalcWgt: public Ui_CalcWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCWGT_H

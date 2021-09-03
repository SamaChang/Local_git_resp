/********************************************************************************
** Form generated from reading UI file 'LinkDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINKDLG_H
#define UI_LINKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LinkDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cmb_port;
    QLabel *label_2;
    QComboBox *cmb_baudRate;
    QLabel *label_3;
    QComboBox *cmb_dataBits;
    QLabel *label_4;
    QComboBox *cmb_parity;
    QLabel *label_5;
    QComboBox *cmb_stopBits;
    QLabel *label_6;
    QComboBox *cmb_flowCtrl;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *LinkDlg)
    {
        if (LinkDlg->objectName().isEmpty())
            LinkDlg->setObjectName(QString::fromUtf8("LinkDlg"));
        LinkDlg->resize(238, 247);
        verticalLayout = new QVBoxLayout(LinkDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(LinkDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cmb_port = new QComboBox(groupBox);
        cmb_port->setObjectName(QString::fromUtf8("cmb_port"));

        gridLayout->addWidget(cmb_port, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        cmb_baudRate = new QComboBox(groupBox);
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->addItem(QString());
        cmb_baudRate->setObjectName(QString::fromUtf8("cmb_baudRate"));
        cmb_baudRate->setEditable(true);

        gridLayout->addWidget(cmb_baudRate, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        cmb_dataBits = new QComboBox(groupBox);
        cmb_dataBits->addItem(QString());
        cmb_dataBits->addItem(QString());
        cmb_dataBits->addItem(QString());
        cmb_dataBits->addItem(QString());
        cmb_dataBits->setObjectName(QString::fromUtf8("cmb_dataBits"));

        gridLayout->addWidget(cmb_dataBits, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        cmb_parity = new QComboBox(groupBox);
        cmb_parity->addItem(QString());
        cmb_parity->addItem(QString());
        cmb_parity->addItem(QString());
        cmb_parity->addItem(QString());
        cmb_parity->addItem(QString());
        cmb_parity->setObjectName(QString::fromUtf8("cmb_parity"));

        gridLayout->addWidget(cmb_parity, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        cmb_stopBits = new QComboBox(groupBox);
        cmb_stopBits->addItem(QString());
        cmb_stopBits->addItem(QString());
        cmb_stopBits->addItem(QString());
        cmb_stopBits->setObjectName(QString::fromUtf8("cmb_stopBits"));

        gridLayout->addWidget(cmb_stopBits, 4, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        cmb_flowCtrl = new QComboBox(groupBox);
        cmb_flowCtrl->addItem(QString());
        cmb_flowCtrl->addItem(QString());
        cmb_flowCtrl->addItem(QString());
        cmb_flowCtrl->setObjectName(QString::fromUtf8("cmb_flowCtrl"));

        gridLayout->addWidget(cmb_flowCtrl, 5, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        widget = new QWidget(LinkDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(widget);


        retranslateUi(LinkDlg);

        cmb_baudRate->setCurrentIndex(8);
        cmb_dataBits->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(LinkDlg);
    } // setupUi

    void retranslateUi(QDialog *LinkDlg)
    {
        LinkDlg->setWindowTitle(QCoreApplication::translate("LinkDlg", "LinkDlg", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LinkDlg", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("LinkDlg", "\347\253\257 \345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("LinkDlg", "\346\263\242\347\211\271\347\216\207", nullptr));
        cmb_baudRate->setItemText(0, QCoreApplication::translate("LinkDlg", "1200", nullptr));
        cmb_baudRate->setItemText(1, QCoreApplication::translate("LinkDlg", "2400", nullptr));
        cmb_baudRate->setItemText(2, QCoreApplication::translate("LinkDlg", "4800", nullptr));
        cmb_baudRate->setItemText(3, QCoreApplication::translate("LinkDlg", "9600", nullptr));
        cmb_baudRate->setItemText(4, QCoreApplication::translate("LinkDlg", "19200", nullptr));
        cmb_baudRate->setItemText(5, QCoreApplication::translate("LinkDlg", "38400", nullptr));
        cmb_baudRate->setItemText(6, QCoreApplication::translate("LinkDlg", "57600", nullptr));
        cmb_baudRate->setItemText(7, QCoreApplication::translate("LinkDlg", "115200", nullptr));
        cmb_baudRate->setItemText(8, QCoreApplication::translate("LinkDlg", "500000", nullptr));

        label_3->setText(QCoreApplication::translate("LinkDlg", "\346\225\260\346\215\256\344\275\215", nullptr));
        cmb_dataBits->setItemText(0, QCoreApplication::translate("LinkDlg", "5", nullptr));
        cmb_dataBits->setItemText(1, QCoreApplication::translate("LinkDlg", "6", nullptr));
        cmb_dataBits->setItemText(2, QCoreApplication::translate("LinkDlg", "7", nullptr));
        cmb_dataBits->setItemText(3, QCoreApplication::translate("LinkDlg", "8", nullptr));

        label_4->setText(QCoreApplication::translate("LinkDlg", "\346\240\241\351\252\214\344\275\215", nullptr));
        cmb_parity->setItemText(0, QCoreApplication::translate("LinkDlg", "None", nullptr));
        cmb_parity->setItemText(1, QCoreApplication::translate("LinkDlg", "Even", nullptr));
        cmb_parity->setItemText(2, QCoreApplication::translate("LinkDlg", "Odd", nullptr));
        cmb_parity->setItemText(3, QCoreApplication::translate("LinkDlg", "Space", nullptr));
        cmb_parity->setItemText(4, QCoreApplication::translate("LinkDlg", "Mark", nullptr));

        label_5->setText(QCoreApplication::translate("LinkDlg", "\345\201\234\346\255\242\344\275\215", nullptr));
        cmb_stopBits->setItemText(0, QCoreApplication::translate("LinkDlg", "1", nullptr));
        cmb_stopBits->setItemText(1, QCoreApplication::translate("LinkDlg", "1.5", nullptr));
        cmb_stopBits->setItemText(2, QCoreApplication::translate("LinkDlg", "2", nullptr));

        label_6->setText(QCoreApplication::translate("LinkDlg", "\346\265\201\346\216\247\345\210\266", nullptr));
        cmb_flowCtrl->setItemText(0, QCoreApplication::translate("LinkDlg", "None", nullptr));
        cmb_flowCtrl->setItemText(1, QCoreApplication::translate("LinkDlg", "RTS/CTS", nullptr));
        cmb_flowCtrl->setItemText(2, QCoreApplication::translate("LinkDlg", "XON/XOFF", nullptr));

        pushButton->setText(QCoreApplication::translate("LinkDlg", "\350\277\236\346\216\245", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LinkDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LinkDlg: public Ui_LinkDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINKDLG_H

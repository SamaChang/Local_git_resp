/********************************************************************************
** Form generated from reading UI file 'SerialPortDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORTDLG_H
#define UI_SERIALPORTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPortDlg
{
public:
    QVBoxLayout *verticalLayout_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
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
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbtn_recv_ascii;
    QRadioButton *rbtn_recv_hex;
    QCheckBox *ckb_autoWrap;
    QCheckBox *ckb_showSend;
    QCheckBox *ckb_showTm;
    QSpacerItem *verticalSpacer;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QPlainTextEdit *plainTextEdit_recv;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *tedt_send;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btn_send;
    QPushButton *btn_send_IIR;
    QPushButton *btn_clear;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lab_info;

    void setupUi(QDialog *SerialPortDlg)
    {
        if (SerialPortDlg->objectName().isEmpty())
            SerialPortDlg->setObjectName(QString::fromUtf8("SerialPortDlg"));
        SerialPortDlg->resize(1057, 739);
        verticalLayout_5 = new QVBoxLayout(SerialPortDlg);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(SerialPortDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(0, 50));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 1, 9, 1);
        btn_start = new QPushButton(widget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btn_start);

        btn_stop = new QPushButton(widget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        btn_stop->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btn_stop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_5->addWidget(widget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        widget_2 = new QWidget(SerialPortDlg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(200, 0));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 5, -1, -1);
        groupBox = new QGroupBox(widget_2);
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


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rbtn_recv_ascii = new QRadioButton(groupBox_2);
        rbtn_recv_ascii->setObjectName(QString::fromUtf8("rbtn_recv_ascii"));
        rbtn_recv_ascii->setChecked(true);

        horizontalLayout->addWidget(rbtn_recv_ascii);

        rbtn_recv_hex = new QRadioButton(groupBox_2);
        rbtn_recv_hex->setObjectName(QString::fromUtf8("rbtn_recv_hex"));

        horizontalLayout->addWidget(rbtn_recv_hex);


        verticalLayout->addLayout(horizontalLayout);

        ckb_autoWrap = new QCheckBox(groupBox_2);
        ckb_autoWrap->setObjectName(QString::fromUtf8("ckb_autoWrap"));
        ckb_autoWrap->setChecked(true);

        verticalLayout->addWidget(ckb_autoWrap);

        ckb_showSend = new QCheckBox(groupBox_2);
        ckb_showSend->setObjectName(QString::fromUtf8("ckb_showSend"));
        ckb_showSend->setChecked(true);

        verticalLayout->addWidget(ckb_showSend);

        ckb_showTm = new QCheckBox(groupBox_2);
        ckb_showTm->setObjectName(QString::fromUtf8("ckb_showTm"));
        ckb_showTm->setChecked(true);

        verticalLayout->addWidget(ckb_showTm);


        verticalLayout_2->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_5->addWidget(widget_2);

        widget_3 = new QWidget(SerialPortDlg);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        plainTextEdit_recv = new QPlainTextEdit(widget_3);
        plainTextEdit_recv->setObjectName(QString::fromUtf8("plainTextEdit_recv"));
        plainTextEdit_recv->setReadOnly(true);

        verticalLayout_4->addWidget(plainTextEdit_recv);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tedt_send = new QTextEdit(widget_3);
        tedt_send->setObjectName(QString::fromUtf8("tedt_send"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tedt_send->sizePolicy().hasHeightForWidth());
        tedt_send->setSizePolicy(sizePolicy1);
        tedt_send->setMaximumSize(QSize(16777215, 120));

        horizontalLayout_3->addWidget(tedt_send);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btn_send = new QPushButton(widget_3);
        btn_send->setObjectName(QString::fromUtf8("btn_send"));
        btn_send->setMinimumSize(QSize(75, 30));

        verticalLayout_3->addWidget(btn_send);

        btn_send_IIR = new QPushButton(widget_3);
        btn_send_IIR->setObjectName(QString::fromUtf8("btn_send_IIR"));
        btn_send_IIR->setMinimumSize(QSize(75, 30));

        verticalLayout_3->addWidget(btn_send_IIR);

        btn_clear = new QPushButton(widget_3);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setMinimumSize(QSize(75, 30));

        verticalLayout_3->addWidget(btn_clear);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_5->addWidget(widget_3);


        verticalLayout_5->addLayout(horizontalLayout_5);

        widget_4 = new QWidget(SerialPortDlg);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 40));
        horizontalLayout_6 = new QHBoxLayout(widget_4);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lab_info = new QLabel(widget_4);
        lab_info->setObjectName(QString::fromUtf8("lab_info"));
        lab_info->setIndent(10);

        horizontalLayout_6->addWidget(lab_info);


        verticalLayout_5->addWidget(widget_4);


        retranslateUi(SerialPortDlg);

        cmb_baudRate->setCurrentIndex(8);
        cmb_dataBits->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SerialPortDlg);
    } // setupUi

    void retranslateUi(QDialog *SerialPortDlg)
    {
        SerialPortDlg->setWindowTitle(QCoreApplication::translate("SerialPortDlg", "\344\270\262\345\217\243\345\212\251\346\211\213", nullptr));
        btn_start->setText(QCoreApplication::translate("SerialPortDlg", "\345\274\200\345\247\213", nullptr));
        btn_stop->setText(QCoreApplication::translate("SerialPortDlg", "\345\201\234\346\255\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SerialPortDlg", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("SerialPortDlg", "\347\253\257 \345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("SerialPortDlg", "\346\263\242\347\211\271\347\216\207", nullptr));
        cmb_baudRate->setItemText(0, QCoreApplication::translate("SerialPortDlg", "1200", nullptr));
        cmb_baudRate->setItemText(1, QCoreApplication::translate("SerialPortDlg", "2400", nullptr));
        cmb_baudRate->setItemText(2, QCoreApplication::translate("SerialPortDlg", "4800", nullptr));
        cmb_baudRate->setItemText(3, QCoreApplication::translate("SerialPortDlg", "9600", nullptr));
        cmb_baudRate->setItemText(4, QCoreApplication::translate("SerialPortDlg", "19200", nullptr));
        cmb_baudRate->setItemText(5, QCoreApplication::translate("SerialPortDlg", "38400", nullptr));
        cmb_baudRate->setItemText(6, QCoreApplication::translate("SerialPortDlg", "57600", nullptr));
        cmb_baudRate->setItemText(7, QCoreApplication::translate("SerialPortDlg", "115200", nullptr));
        cmb_baudRate->setItemText(8, QCoreApplication::translate("SerialPortDlg", "500000", nullptr));

        label_3->setText(QCoreApplication::translate("SerialPortDlg", "\346\225\260\346\215\256\344\275\215", nullptr));
        cmb_dataBits->setItemText(0, QCoreApplication::translate("SerialPortDlg", "5", nullptr));
        cmb_dataBits->setItemText(1, QCoreApplication::translate("SerialPortDlg", "6", nullptr));
        cmb_dataBits->setItemText(2, QCoreApplication::translate("SerialPortDlg", "7", nullptr));
        cmb_dataBits->setItemText(3, QCoreApplication::translate("SerialPortDlg", "8", nullptr));

        label_4->setText(QCoreApplication::translate("SerialPortDlg", "\346\240\241\351\252\214\344\275\215", nullptr));
        cmb_parity->setItemText(0, QCoreApplication::translate("SerialPortDlg", "None", nullptr));
        cmb_parity->setItemText(1, QCoreApplication::translate("SerialPortDlg", "Even", nullptr));
        cmb_parity->setItemText(2, QCoreApplication::translate("SerialPortDlg", "Odd", nullptr));
        cmb_parity->setItemText(3, QCoreApplication::translate("SerialPortDlg", "Space", nullptr));
        cmb_parity->setItemText(4, QCoreApplication::translate("SerialPortDlg", "Mark", nullptr));

        label_5->setText(QCoreApplication::translate("SerialPortDlg", "\345\201\234\346\255\242\344\275\215", nullptr));
        cmb_stopBits->setItemText(0, QCoreApplication::translate("SerialPortDlg", "1", nullptr));
        cmb_stopBits->setItemText(1, QCoreApplication::translate("SerialPortDlg", "1.5", nullptr));
        cmb_stopBits->setItemText(2, QCoreApplication::translate("SerialPortDlg", "2", nullptr));

        label_6->setText(QCoreApplication::translate("SerialPortDlg", "\346\265\201\346\216\247\345\210\266", nullptr));
        cmb_flowCtrl->setItemText(0, QCoreApplication::translate("SerialPortDlg", "None", nullptr));
        cmb_flowCtrl->setItemText(1, QCoreApplication::translate("SerialPortDlg", "RTS/CTS", nullptr));
        cmb_flowCtrl->setItemText(2, QCoreApplication::translate("SerialPortDlg", "XON/XOFF", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("SerialPortDlg", "\346\216\245\346\224\266\350\256\276\347\275\256", nullptr));
        rbtn_recv_ascii->setText(QCoreApplication::translate("SerialPortDlg", "ASCII", nullptr));
        rbtn_recv_hex->setText(QCoreApplication::translate("SerialPortDlg", "Hex", nullptr));
        ckb_autoWrap->setText(QCoreApplication::translate("SerialPortDlg", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
        ckb_showSend->setText(QCoreApplication::translate("SerialPortDlg", "\346\230\276\347\244\272\345\217\221\351\200\201", nullptr));
        ckb_showTm->setText(QCoreApplication::translate("SerialPortDlg", "\346\230\276\347\244\272\346\227\266\351\227\264", nullptr));
        btn_send->setText(QCoreApplication::translate("SerialPortDlg", "\345\217\221\351\200\201", nullptr));
        btn_send_IIR->setText(QCoreApplication::translate("SerialPortDlg", "\345\217\221\351\200\201IIR", nullptr));
        btn_clear->setText(QCoreApplication::translate("SerialPortDlg", "\346\270\205\347\251\272", nullptr));
        lab_info->setText(QCoreApplication::translate("SerialPortDlg", "\346\217\220\347\244\272\345\214\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPortDlg: public Ui_SerialPortDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORTDLG_H

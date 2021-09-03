/********************************************************************************
** Form generated from reading UI file 'ANCSoft.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANCSOFT_H
#define UI_ANCSOFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "anctool.h"

QT_BEGIN_NAMESPACE

class Ui_ANCSoft
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *mainToolWgt;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btn_tool_open;
    QPushButton *btn_tool_save;
    QLabel *label;
    QComboBox *comboBox_type;
    QPushButton *btn_tool_record;
    QPushButton *btn_tool_suspend;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_tool_record_param;
    QPushButton *btn_tool_conf_io;
    QPushButton *btn_tool_conf_axis;
    QPushButton *btn_optimal_show;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QComboBox *comboBox_points;
    QPushButton *btn_save_data_fr;
    QPushButton *btn_save_data_phase;
    QSpacerItem *horizontalSpacer;
    QWidget *devStateWgt;
    QGridLayout *gridLayout_5;
    QLabel *lab_dev_state_input_freq;
    QLabel *lab_dev_state_input_bits;
    QLabel *lab_dev_state_input;
    QLabel *lab_dev_state_input_channel;
    ANCTool *ancWgt;

    void setupUi(QWidget *ANCSoft)
    {
        if (ANCSoft->objectName().isEmpty())
            ANCSoft->setObjectName(QString::fromUtf8("ANCSoft"));
        ANCSoft->resize(1456, 788);
        ANCSoft->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(ANCSoft);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        mainToolWgt = new QWidget(ANCSoft);
        mainToolWgt->setObjectName(QString::fromUtf8("mainToolWgt"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolWgt->sizePolicy().hasHeightForWidth());
        mainToolWgt->setSizePolicy(sizePolicy);
        horizontalLayout_8 = new QHBoxLayout(mainToolWgt);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 3, -1, 3);
        btn_tool_open = new QPushButton(mainToolWgt);
        btn_tool_open->setObjectName(QString::fromUtf8("btn_tool_open"));
        btn_tool_open->setMinimumSize(QSize(50, 28));
        btn_tool_open->setCheckable(false);

        horizontalLayout_8->addWidget(btn_tool_open);

        btn_tool_save = new QPushButton(mainToolWgt);
        btn_tool_save->setObjectName(QString::fromUtf8("btn_tool_save"));
        btn_tool_save->setMinimumSize(QSize(50, 28));
        btn_tool_save->setCheckable(false);

        horizontalLayout_8->addWidget(btn_tool_save);

        label = new QLabel(mainToolWgt);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_8->addWidget(label);

        comboBox_type = new QComboBox(mainToolWgt);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName(QString::fromUtf8("comboBox_type"));
        comboBox_type->setMinimumSize(QSize(80, 28));

        horizontalLayout_8->addWidget(comboBox_type);

        btn_tool_record = new QPushButton(mainToolWgt);
        btn_tool_record->setObjectName(QString::fromUtf8("btn_tool_record"));
        btn_tool_record->setMinimumSize(QSize(50, 28));
        btn_tool_record->setCheckable(true);

        horizontalLayout_8->addWidget(btn_tool_record);

        btn_tool_suspend = new QPushButton(mainToolWgt);
        btn_tool_suspend->setObjectName(QString::fromUtf8("btn_tool_suspend"));
        btn_tool_suspend->setEnabled(false);
        btn_tool_suspend->setMinimumSize(QSize(50, 28));
        btn_tool_suspend->setCheckable(true);

        horizontalLayout_8->addWidget(btn_tool_suspend);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        btn_tool_record_param = new QPushButton(mainToolWgt);
        btn_tool_record_param->setObjectName(QString::fromUtf8("btn_tool_record_param"));
        btn_tool_record_param->setMinimumSize(QSize(75, 28));
        btn_tool_record_param->setCheckable(false);

        horizontalLayout_8->addWidget(btn_tool_record_param);

        btn_tool_conf_io = new QPushButton(mainToolWgt);
        btn_tool_conf_io->setObjectName(QString::fromUtf8("btn_tool_conf_io"));
        btn_tool_conf_io->setMinimumSize(QSize(75, 28));

        horizontalLayout_8->addWidget(btn_tool_conf_io);

        btn_tool_conf_axis = new QPushButton(mainToolWgt);
        btn_tool_conf_axis->setObjectName(QString::fromUtf8("btn_tool_conf_axis"));
        btn_tool_conf_axis->setMinimumSize(QSize(75, 28));

        horizontalLayout_8->addWidget(btn_tool_conf_axis);

        btn_optimal_show = new QPushButton(mainToolWgt);
        btn_optimal_show->setObjectName(QString::fromUtf8("btn_optimal_show"));
        btn_optimal_show->setMinimumSize(QSize(75, 28));

        horizontalLayout_8->addWidget(btn_optimal_show);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        label_2 = new QLabel(mainToolWgt);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_8->addWidget(label_2);

        comboBox_points = new QComboBox(mainToolWgt);
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->addItem(QString());
        comboBox_points->setObjectName(QString::fromUtf8("comboBox_points"));
        comboBox_points->setMinimumSize(QSize(75, 28));

        horizontalLayout_8->addWidget(comboBox_points);

        btn_save_data_fr = new QPushButton(mainToolWgt);
        btn_save_data_fr->setObjectName(QString::fromUtf8("btn_save_data_fr"));
        btn_save_data_fr->setMinimumSize(QSize(75, 28));

        horizontalLayout_8->addWidget(btn_save_data_fr);

        btn_save_data_phase = new QPushButton(mainToolWgt);
        btn_save_data_phase->setObjectName(QString::fromUtf8("btn_save_data_phase"));
        btn_save_data_phase->setMinimumSize(QSize(75, 28));

        horizontalLayout_8->addWidget(btn_save_data_phase);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        devStateWgt = new QWidget(mainToolWgt);
        devStateWgt->setObjectName(QString::fromUtf8("devStateWgt"));
        devStateWgt->setMinimumSize(QSize(300, 0));
        gridLayout_5 = new QGridLayout(devStateWgt);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(1, 1, 1, 1);
        lab_dev_state_input_freq = new QLabel(devStateWgt);
        lab_dev_state_input_freq->setObjectName(QString::fromUtf8("lab_dev_state_input_freq"));
        lab_dev_state_input_freq->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lab_dev_state_input_freq, 0, 1, 1, 1);

        lab_dev_state_input_bits = new QLabel(devStateWgt);
        lab_dev_state_input_bits->setObjectName(QString::fromUtf8("lab_dev_state_input_bits"));
        lab_dev_state_input_bits->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lab_dev_state_input_bits, 0, 2, 1, 1);

        lab_dev_state_input = new QLabel(devStateWgt);
        lab_dev_state_input->setObjectName(QString::fromUtf8("lab_dev_state_input"));
        lab_dev_state_input->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lab_dev_state_input, 0, 0, 1, 1);

        lab_dev_state_input_channel = new QLabel(devStateWgt);
        lab_dev_state_input_channel->setObjectName(QString::fromUtf8("lab_dev_state_input_channel"));
        lab_dev_state_input_channel->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(lab_dev_state_input_channel, 0, 3, 1, 1);


        horizontalLayout_8->addWidget(devStateWgt);


        verticalLayout_2->addWidget(mainToolWgt);

        ancWgt = new ANCTool(ANCSoft);
        ancWgt->setObjectName(QString::fromUtf8("ancWgt"));

        verticalLayout_2->addWidget(ancWgt);


        retranslateUi(ANCSoft);

        QMetaObject::connectSlotsByName(ANCSoft);
    } // setupUi

    void retranslateUi(QWidget *ANCSoft)
    {
        ANCSoft->setWindowTitle(QCoreApplication::translate("ANCSoft", "ANCSoft", nullptr));
        btn_tool_open->setText(QCoreApplication::translate("ANCSoft", "\346\211\223\345\274\200", nullptr));
        btn_tool_save->setText(QCoreApplication::translate("ANCSoft", "\344\277\235\345\255\230", nullptr));
        label->setText(QCoreApplication::translate("ANCSoft", "\344\277\241\345\217\267\347\261\273\345\236\213:", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("ANCSoft", "\345\256\236\346\227\266\351\207\207\351\233\206", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("ANCSoft", "\347\231\275\345\231\252\345\243\260", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("ANCSoft", "\347\262\211\345\231\252\345\243\260", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("ANCSoft", "1K\346\255\243\345\274\246\346\263\242", nullptr));

        btn_tool_record->setText(QCoreApplication::translate("ANCSoft", "\345\274\200\345\247\213", nullptr));
        btn_tool_suspend->setText(QCoreApplication::translate("ANCSoft", "\345\201\234\346\255\242", nullptr));
        btn_tool_record_param->setText(QCoreApplication::translate("ANCSoft", "\351\237\263\351\242\221\345\217\202\346\225\260", nullptr));
        btn_tool_conf_io->setText(QCoreApplication::translate("ANCSoft", "\351\205\215\347\275\256IO", nullptr));
        btn_tool_conf_axis->setText(QCoreApplication::translate("ANCSoft", "\346\230\276\347\244\272\351\205\215\347\275\256", nullptr));
        btn_optimal_show->setText(QCoreApplication::translate("ANCSoft", "\346\234\200\344\274\230\346\230\276\347\244\272", nullptr));
        label_2->setText(QCoreApplication::translate("ANCSoft", "\350\256\276\347\275\256\347\247\257\347\264\257:", nullptr));
        comboBox_points->setItemText(0, QCoreApplication::translate("ANCSoft", "1", nullptr));
        comboBox_points->setItemText(1, QCoreApplication::translate("ANCSoft", "2", nullptr));
        comboBox_points->setItemText(2, QCoreApplication::translate("ANCSoft", "3", nullptr));
        comboBox_points->setItemText(3, QCoreApplication::translate("ANCSoft", "4", nullptr));
        comboBox_points->setItemText(4, QCoreApplication::translate("ANCSoft", "5", nullptr));
        comboBox_points->setItemText(5, QCoreApplication::translate("ANCSoft", "6", nullptr));
        comboBox_points->setItemText(6, QCoreApplication::translate("ANCSoft", "7", nullptr));
        comboBox_points->setItemText(7, QCoreApplication::translate("ANCSoft", "8", nullptr));
        comboBox_points->setItemText(8, QCoreApplication::translate("ANCSoft", "9", nullptr));
        comboBox_points->setItemText(9, QCoreApplication::translate("ANCSoft", "10", nullptr));
        comboBox_points->setItemText(10, QCoreApplication::translate("ANCSoft", "11", nullptr));
        comboBox_points->setItemText(11, QCoreApplication::translate("ANCSoft", "12", nullptr));
        comboBox_points->setItemText(12, QCoreApplication::translate("ANCSoft", "13", nullptr));
        comboBox_points->setItemText(13, QCoreApplication::translate("ANCSoft", "14", nullptr));
        comboBox_points->setItemText(14, QCoreApplication::translate("ANCSoft", "15", nullptr));
        comboBox_points->setItemText(15, QCoreApplication::translate("ANCSoft", "16", nullptr));
        comboBox_points->setItemText(16, QCoreApplication::translate("ANCSoft", "17", nullptr));
        comboBox_points->setItemText(17, QCoreApplication::translate("ANCSoft", "18", nullptr));
        comboBox_points->setItemText(18, QCoreApplication::translate("ANCSoft", "19", nullptr));
        comboBox_points->setItemText(19, QCoreApplication::translate("ANCSoft", "20", nullptr));
        comboBox_points->setItemText(20, QCoreApplication::translate("ANCSoft", "infinite", nullptr));

        btn_save_data_fr->setText(QCoreApplication::translate("ANCSoft", "FR\345\217\246\345\255\230\344\270\272", nullptr));
        btn_save_data_phase->setText(QCoreApplication::translate("ANCSoft", "PHASE\345\217\246\345\255\230\344\270\272", nullptr));
        lab_dev_state_input_freq->setText(QCoreApplication::translate("ANCSoft", "--", nullptr));
        lab_dev_state_input_bits->setText(QCoreApplication::translate("ANCSoft", "--", nullptr));
        lab_dev_state_input->setText(QCoreApplication::translate("ANCSoft", "\351\237\263\351\242\221\345\217\202\346\225\260", nullptr));
        lab_dev_state_input_channel->setText(QCoreApplication::translate("ANCSoft", "--", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ANCSoft: public Ui_ANCSoft {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANCSOFT_H

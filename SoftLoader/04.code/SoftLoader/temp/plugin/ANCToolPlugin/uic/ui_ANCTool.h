/********************************************************************************
** Form generated from reading UI file 'ANCTool.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANCTOOL_H
#define UI_ANCTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "..\common\customplot\QFreqLinesChart.h"

QT_BEGIN_NAMESPACE

class Ui_ANCTool
{
public:
    QAction *actOpen;
    QAction *actConfIO;
    QVBoxLayout *verticalLayout_7;
    QWidget *mainWgt;
    QHBoxLayout *horizontalLayout_7;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout;
    QLabel *lab_debug;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *ff_btn_4;
    QPushButton *ff_btn_7;
    QPushButton *ff_btn_5;
    QPushButton *ff_btn_8;
    QPushButton *ff_btn_2;
    QPushButton *ff_btn_1;
    QPushButton *ff_btn_10;
    QCheckBox *ff_ckb_8;
    QCheckBox *ff_ckb_5;
    QPushButton *ff_btn_9;
    QCheckBox *ff_ckb_9;
    QCheckBox *ff_ckb_2;
    QCheckBox *ff_ckb_1;
    QCheckBox *ff_ckb_4;
    QCheckBox *ff_ckb_6;
    QCheckBox *ff_ckb_7;
    QPushButton *ff_btn_3;
    QPushButton *ff_btn_6;
    QLabel *lab_ff;
    QCheckBox *ff_ckb_3;
    QCheckBox *ff_ckb_10;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QCheckBox *fb_ckb_9;
    QPushButton *fb_btn_6;
    QPushButton *fb_btn_7;
    QPushButton *fb_btn_1;
    QLabel *lab_fb;
    QPushButton *fb_btn_4;
    QCheckBox *fb_ckb_8;
    QCheckBox *fb_ckb_3;
    QCheckBox *fb_ckb_1;
    QCheckBox *fb_ckb_2;
    QCheckBox *fb_ckb_10;
    QPushButton *fb_btn_8;
    QCheckBox *fb_ckb_4;
    QCheckBox *fb_ckb_5;
    QCheckBox *fb_ckb_6;
    QPushButton *fb_btn_2;
    QPushButton *fb_btn_9;
    QPushButton *fb_btn_10;
    QPushButton *fb_btn_3;
    QPushButton *fb_btn_5;
    QCheckBox *fb_ckb_7;
    QPushButton *btn_write_hardware;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QWidget *widget22;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_5;
    QFreqLinesChart *frChartWgt;
    QWidget *widget_8;
    QGridLayout *gridLayout_4;
    QPushButton *fr_line_btn_4;
    QPushButton *fr_line_btn_1;
    QCheckBox *fr_line_3;
    QCheckBox *fr_line_1;
    QCheckBox *fr_line_2;
    QPushButton *fr_line_btn_2;
    QCheckBox *fr_line_5;
    QCheckBox *fr_line_6;
    QPushButton *fr_line_btn_3;
    QCheckBox *fr_line_4;
    QPushButton *frChart_btn_conf;
    QPushButton *fr_line_btn_5;
    QPushButton *fr_line_btn_6;
    QCheckBox *fr_line_FF;
    QCheckBox *fr_line_FB;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_2;
    QFreqLinesChart *phaseChartWgt;
    QWidget *widget_11;
    QGridLayout *gridLayout_5;
    QPushButton *phase_line_btn_1;
    QCheckBox *phase_line_1;
    QPushButton *phase_line_btn_2;
    QCheckBox *phase_line_2;
    QPushButton *phase_line_btn_3;
    QCheckBox *phase_line_3;
    QPushButton *phase_line_btn_4;
    QCheckBox *phase_line_4;
    QPushButton *phase_line_btn_5;
    QCheckBox *phase_line_5;
    QPushButton *phase_line_btn_6;
    QCheckBox *phase_line_6;
    QCheckBox *phase_line_FF;
    QCheckBox *phase_line_FB;
    QPushButton *phaseChart_btn_conf;

    void setupUi(QWidget *ANCTool)
    {
        if (ANCTool->objectName().isEmpty())
            ANCTool->setObjectName(QString::fromUtf8("ANCTool"));
        ANCTool->resize(1300, 777);
        ANCTool->setStyleSheet(QString::fromUtf8(""));
        actOpen = new QAction(ANCTool);
        actOpen->setObjectName(QString::fromUtf8("actOpen"));
        actConfIO = new QAction(ANCTool);
        actConfIO->setObjectName(QString::fromUtf8("actConfIO"));
        verticalLayout_7 = new QVBoxLayout(ANCTool);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        mainWgt = new QWidget(ANCTool);
        mainWgt->setObjectName(QString::fromUtf8("mainWgt"));
        horizontalLayout_7 = new QHBoxLayout(mainWgt);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 2);
        widget_7 = new QWidget(mainWgt);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy);
        widget_7->setMinimumSize(QSize(250, 0));
        verticalLayout = new QVBoxLayout(widget_7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lab_debug = new QLabel(widget_7);
        lab_debug->setObjectName(QString::fromUtf8("lab_debug"));
        lab_debug->setMinimumSize(QSize(0, 35));
        lab_debug->setIndent(5);

        verticalLayout->addWidget(lab_debug);

        widget_4 = new QWidget(widget_7);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 2, -1, 2);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(widget_4);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_3->addWidget(comboBox);

        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 0));
        pushButton_2->setMaximumSize(QSize(75, 16777215));
        pushButton_2->setCheckable(true);

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout->addWidget(widget_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(widget_7);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMaximumSize(QSize(120, 16777215));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        ff_btn_4 = new QPushButton(widget);
        ff_btn_4->setObjectName(QString::fromUtf8("ff_btn_4"));
        ff_btn_4->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_4, 4, 1, 1, 1);

        ff_btn_7 = new QPushButton(widget);
        ff_btn_7->setObjectName(QString::fromUtf8("ff_btn_7"));
        ff_btn_7->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_7, 7, 1, 1, 1);

        ff_btn_5 = new QPushButton(widget);
        ff_btn_5->setObjectName(QString::fromUtf8("ff_btn_5"));
        ff_btn_5->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_5, 5, 1, 1, 1);

        ff_btn_8 = new QPushButton(widget);
        ff_btn_8->setObjectName(QString::fromUtf8("ff_btn_8"));
        ff_btn_8->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_8, 8, 1, 1, 1);

        ff_btn_2 = new QPushButton(widget);
        ff_btn_2->setObjectName(QString::fromUtf8("ff_btn_2"));
        ff_btn_2->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_2, 2, 1, 1, 1);

        ff_btn_1 = new QPushButton(widget);
        ff_btn_1->setObjectName(QString::fromUtf8("ff_btn_1"));
        ff_btn_1->setMinimumSize(QSize(0, 28));
        ff_btn_1->setCheckable(false);
        ff_btn_1->setChecked(false);

        gridLayout->addWidget(ff_btn_1, 1, 1, 1, 1);

        ff_btn_10 = new QPushButton(widget);
        ff_btn_10->setObjectName(QString::fromUtf8("ff_btn_10"));
        ff_btn_10->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_10, 10, 1, 1, 1);

        ff_ckb_8 = new QCheckBox(widget);
        ff_ckb_8->setObjectName(QString::fromUtf8("ff_ckb_8"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ff_ckb_8->sizePolicy().hasHeightForWidth());
        ff_ckb_8->setSizePolicy(sizePolicy1);
        ff_ckb_8->setChecked(true);

        gridLayout->addWidget(ff_ckb_8, 8, 0, 1, 1);

        ff_ckb_5 = new QCheckBox(widget);
        ff_ckb_5->setObjectName(QString::fromUtf8("ff_ckb_5"));
        sizePolicy1.setHeightForWidth(ff_ckb_5->sizePolicy().hasHeightForWidth());
        ff_ckb_5->setSizePolicy(sizePolicy1);
        ff_ckb_5->setChecked(true);

        gridLayout->addWidget(ff_ckb_5, 5, 0, 1, 1);

        ff_btn_9 = new QPushButton(widget);
        ff_btn_9->setObjectName(QString::fromUtf8("ff_btn_9"));
        ff_btn_9->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_9, 9, 1, 1, 1);

        ff_ckb_9 = new QCheckBox(widget);
        ff_ckb_9->setObjectName(QString::fromUtf8("ff_ckb_9"));
        sizePolicy1.setHeightForWidth(ff_ckb_9->sizePolicy().hasHeightForWidth());
        ff_ckb_9->setSizePolicy(sizePolicy1);
        ff_ckb_9->setChecked(true);

        gridLayout->addWidget(ff_ckb_9, 9, 0, 1, 1);

        ff_ckb_2 = new QCheckBox(widget);
        ff_ckb_2->setObjectName(QString::fromUtf8("ff_ckb_2"));
        sizePolicy1.setHeightForWidth(ff_ckb_2->sizePolicy().hasHeightForWidth());
        ff_ckb_2->setSizePolicy(sizePolicy1);
        ff_ckb_2->setChecked(true);

        gridLayout->addWidget(ff_ckb_2, 2, 0, 1, 1);

        ff_ckb_1 = new QCheckBox(widget);
        ff_ckb_1->setObjectName(QString::fromUtf8("ff_ckb_1"));
        sizePolicy1.setHeightForWidth(ff_ckb_1->sizePolicy().hasHeightForWidth());
        ff_ckb_1->setSizePolicy(sizePolicy1);
        ff_ckb_1->setChecked(true);

        gridLayout->addWidget(ff_ckb_1, 1, 0, 1, 1);

        ff_ckb_4 = new QCheckBox(widget);
        ff_ckb_4->setObjectName(QString::fromUtf8("ff_ckb_4"));
        sizePolicy1.setHeightForWidth(ff_ckb_4->sizePolicy().hasHeightForWidth());
        ff_ckb_4->setSizePolicy(sizePolicy1);
        ff_ckb_4->setChecked(true);

        gridLayout->addWidget(ff_ckb_4, 4, 0, 1, 1);

        ff_ckb_6 = new QCheckBox(widget);
        ff_ckb_6->setObjectName(QString::fromUtf8("ff_ckb_6"));
        sizePolicy1.setHeightForWidth(ff_ckb_6->sizePolicy().hasHeightForWidth());
        ff_ckb_6->setSizePolicy(sizePolicy1);
        ff_ckb_6->setChecked(true);

        gridLayout->addWidget(ff_ckb_6, 6, 0, 1, 1);

        ff_ckb_7 = new QCheckBox(widget);
        ff_ckb_7->setObjectName(QString::fromUtf8("ff_ckb_7"));
        sizePolicy1.setHeightForWidth(ff_ckb_7->sizePolicy().hasHeightForWidth());
        ff_ckb_7->setSizePolicy(sizePolicy1);
        ff_ckb_7->setChecked(true);

        gridLayout->addWidget(ff_ckb_7, 7, 0, 1, 1);

        ff_btn_3 = new QPushButton(widget);
        ff_btn_3->setObjectName(QString::fromUtf8("ff_btn_3"));
        ff_btn_3->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_3, 3, 1, 1, 1);

        ff_btn_6 = new QPushButton(widget);
        ff_btn_6->setObjectName(QString::fromUtf8("ff_btn_6"));
        ff_btn_6->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(ff_btn_6, 6, 1, 1, 1);

        lab_ff = new QLabel(widget);
        lab_ff->setObjectName(QString::fromUtf8("lab_ff"));

        gridLayout->addWidget(lab_ff, 0, 0, 1, 2);

        ff_ckb_3 = new QCheckBox(widget);
        ff_ckb_3->setObjectName(QString::fromUtf8("ff_ckb_3"));
        sizePolicy1.setHeightForWidth(ff_ckb_3->sizePolicy().hasHeightForWidth());
        ff_ckb_3->setSizePolicy(sizePolicy1);
        ff_ckb_3->setChecked(true);

        gridLayout->addWidget(ff_ckb_3, 3, 0, 1, 1);

        ff_ckb_10 = new QCheckBox(widget);
        ff_ckb_10->setObjectName(QString::fromUtf8("ff_ckb_10"));
        sizePolicy1.setHeightForWidth(ff_ckb_10->sizePolicy().hasHeightForWidth());
        ff_ckb_10->setSizePolicy(sizePolicy1);
        ff_ckb_10->setChecked(true);

        gridLayout->addWidget(ff_ckb_10, 10, 0, 1, 1);


        horizontalLayout->addWidget(widget);

        widget_3 = new QWidget(widget_7);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setMaximumSize(QSize(120, 16777215));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        fb_ckb_9 = new QCheckBox(widget_3);
        fb_ckb_9->setObjectName(QString::fromUtf8("fb_ckb_9"));
        sizePolicy1.setHeightForWidth(fb_ckb_9->sizePolicy().hasHeightForWidth());
        fb_ckb_9->setSizePolicy(sizePolicy1);
        fb_ckb_9->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_9, 9, 0, 1, 1);

        fb_btn_6 = new QPushButton(widget_3);
        fb_btn_6->setObjectName(QString::fromUtf8("fb_btn_6"));
        fb_btn_6->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_6, 6, 1, 1, 1);

        fb_btn_7 = new QPushButton(widget_3);
        fb_btn_7->setObjectName(QString::fromUtf8("fb_btn_7"));
        fb_btn_7->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_7, 7, 1, 1, 1);

        fb_btn_1 = new QPushButton(widget_3);
        fb_btn_1->setObjectName(QString::fromUtf8("fb_btn_1"));
        fb_btn_1->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_1, 1, 1, 1, 1);

        lab_fb = new QLabel(widget_3);
        lab_fb->setObjectName(QString::fromUtf8("lab_fb"));

        gridLayout_2->addWidget(lab_fb, 0, 0, 1, 2);

        fb_btn_4 = new QPushButton(widget_3);
        fb_btn_4->setObjectName(QString::fromUtf8("fb_btn_4"));
        fb_btn_4->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_4, 4, 1, 1, 1);

        fb_ckb_8 = new QCheckBox(widget_3);
        fb_ckb_8->setObjectName(QString::fromUtf8("fb_ckb_8"));
        sizePolicy1.setHeightForWidth(fb_ckb_8->sizePolicy().hasHeightForWidth());
        fb_ckb_8->setSizePolicy(sizePolicy1);
        fb_ckb_8->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_8, 8, 0, 1, 1);

        fb_ckb_3 = new QCheckBox(widget_3);
        fb_ckb_3->setObjectName(QString::fromUtf8("fb_ckb_3"));
        sizePolicy1.setHeightForWidth(fb_ckb_3->sizePolicy().hasHeightForWidth());
        fb_ckb_3->setSizePolicy(sizePolicy1);
        fb_ckb_3->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_3, 3, 0, 1, 1);

        fb_ckb_1 = new QCheckBox(widget_3);
        fb_ckb_1->setObjectName(QString::fromUtf8("fb_ckb_1"));
        sizePolicy1.setHeightForWidth(fb_ckb_1->sizePolicy().hasHeightForWidth());
        fb_ckb_1->setSizePolicy(sizePolicy1);
        fb_ckb_1->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_1, 1, 0, 1, 1);

        fb_ckb_2 = new QCheckBox(widget_3);
        fb_ckb_2->setObjectName(QString::fromUtf8("fb_ckb_2"));
        sizePolicy1.setHeightForWidth(fb_ckb_2->sizePolicy().hasHeightForWidth());
        fb_ckb_2->setSizePolicy(sizePolicy1);
        fb_ckb_2->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_2, 2, 0, 1, 1);

        fb_ckb_10 = new QCheckBox(widget_3);
        fb_ckb_10->setObjectName(QString::fromUtf8("fb_ckb_10"));
        sizePolicy1.setHeightForWidth(fb_ckb_10->sizePolicy().hasHeightForWidth());
        fb_ckb_10->setSizePolicy(sizePolicy1);
        fb_ckb_10->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_10, 10, 0, 1, 1);

        fb_btn_8 = new QPushButton(widget_3);
        fb_btn_8->setObjectName(QString::fromUtf8("fb_btn_8"));
        fb_btn_8->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_8, 8, 1, 1, 1);

        fb_ckb_4 = new QCheckBox(widget_3);
        fb_ckb_4->setObjectName(QString::fromUtf8("fb_ckb_4"));
        sizePolicy1.setHeightForWidth(fb_ckb_4->sizePolicy().hasHeightForWidth());
        fb_ckb_4->setSizePolicy(sizePolicy1);
        fb_ckb_4->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_4, 4, 0, 1, 1);

        fb_ckb_5 = new QCheckBox(widget_3);
        fb_ckb_5->setObjectName(QString::fromUtf8("fb_ckb_5"));
        sizePolicy1.setHeightForWidth(fb_ckb_5->sizePolicy().hasHeightForWidth());
        fb_ckb_5->setSizePolicy(sizePolicy1);
        fb_ckb_5->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_5, 5, 0, 1, 1);

        fb_ckb_6 = new QCheckBox(widget_3);
        fb_ckb_6->setObjectName(QString::fromUtf8("fb_ckb_6"));
        sizePolicy1.setHeightForWidth(fb_ckb_6->sizePolicy().hasHeightForWidth());
        fb_ckb_6->setSizePolicy(sizePolicy1);
        fb_ckb_6->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_6, 6, 0, 1, 1);

        fb_btn_2 = new QPushButton(widget_3);
        fb_btn_2->setObjectName(QString::fromUtf8("fb_btn_2"));
        fb_btn_2->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_2, 2, 1, 1, 1);

        fb_btn_9 = new QPushButton(widget_3);
        fb_btn_9->setObjectName(QString::fromUtf8("fb_btn_9"));
        fb_btn_9->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_9, 9, 1, 1, 1);

        fb_btn_10 = new QPushButton(widget_3);
        fb_btn_10->setObjectName(QString::fromUtf8("fb_btn_10"));
        fb_btn_10->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_10, 10, 1, 1, 1);

        fb_btn_3 = new QPushButton(widget_3);
        fb_btn_3->setObjectName(QString::fromUtf8("fb_btn_3"));
        fb_btn_3->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_3, 3, 1, 1, 1);

        fb_btn_5 = new QPushButton(widget_3);
        fb_btn_5->setObjectName(QString::fromUtf8("fb_btn_5"));
        fb_btn_5->setMinimumSize(QSize(0, 28));

        gridLayout_2->addWidget(fb_btn_5, 5, 1, 1, 1);

        fb_ckb_7 = new QCheckBox(widget_3);
        fb_ckb_7->setObjectName(QString::fromUtf8("fb_ckb_7"));
        sizePolicy1.setHeightForWidth(fb_ckb_7->sizePolicy().hasHeightForWidth());
        fb_ckb_7->setSizePolicy(sizePolicy1);
        fb_ckb_7->setChecked(true);

        gridLayout_2->addWidget(fb_ckb_7, 7, 0, 1, 1);


        horizontalLayout->addWidget(widget_3);


        verticalLayout->addLayout(horizontalLayout);

        btn_write_hardware = new QPushButton(widget_7);
        btn_write_hardware->setObjectName(QString::fromUtf8("btn_write_hardware"));
        btn_write_hardware->setMinimumSize(QSize(0, 28));

        verticalLayout->addWidget(btn_write_hardware);

        widget_2 = new QWidget(widget_7);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(label);

        plainTextEdit = new QPlainTextEdit(widget_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setContextMenuPolicy(Qt::NoContextMenu);
        plainTextEdit->setReadOnly(true);

        verticalLayout_2->addWidget(plainTextEdit);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 28));

        verticalLayout_2->addWidget(pushButton);


        verticalLayout->addWidget(widget_2);


        horizontalLayout_7->addWidget(widget_7);

        widget22 = new QWidget(mainWgt);
        widget22->setObjectName(QString::fromUtf8("widget22"));
        verticalLayout_6 = new QVBoxLayout(widget22);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_9 = new QWidget(widget22);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        horizontalLayout_5 = new QHBoxLayout(widget_9);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        frChartWgt = new QFreqLinesChart(widget_9);
        frChartWgt->setObjectName(QString::fromUtf8("frChartWgt"));

        horizontalLayout_5->addWidget(frChartWgt);

        widget_8 = new QWidget(widget_9);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        sizePolicy.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy);
        widget_8->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(widget_8);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        fr_line_btn_4 = new QPushButton(widget_8);
        fr_line_btn_4->setObjectName(QString::fromUtf8("fr_line_btn_4"));
        fr_line_btn_4->setMinimumSize(QSize(23, 23));
        fr_line_btn_4->setMaximumSize(QSize(23, 16777215));

        gridLayout_4->addWidget(fr_line_btn_4, 3, 0, 1, 1);

        fr_line_btn_1 = new QPushButton(widget_8);
        fr_line_btn_1->setObjectName(QString::fromUtf8("fr_line_btn_1"));
        fr_line_btn_1->setEnabled(false);
        fr_line_btn_1->setMinimumSize(QSize(23, 23));
        fr_line_btn_1->setMaximumSize(QSize(23, 16777215));

        gridLayout_4->addWidget(fr_line_btn_1, 0, 0, 1, 1);

        fr_line_3 = new QCheckBox(widget_8);
        fr_line_3->setObjectName(QString::fromUtf8("fr_line_3"));
        fr_line_3->setChecked(true);

        gridLayout_4->addWidget(fr_line_3, 2, 1, 1, 1);

        fr_line_1 = new QCheckBox(widget_8);
        fr_line_1->setObjectName(QString::fromUtf8("fr_line_1"));
        fr_line_1->setEnabled(false);
        fr_line_1->setChecked(true);

        gridLayout_4->addWidget(fr_line_1, 0, 1, 1, 1);

        fr_line_2 = new QCheckBox(widget_8);
        fr_line_2->setObjectName(QString::fromUtf8("fr_line_2"));
        fr_line_2->setChecked(true);

        gridLayout_4->addWidget(fr_line_2, 1, 1, 1, 1);

        fr_line_btn_2 = new QPushButton(widget_8);
        fr_line_btn_2->setObjectName(QString::fromUtf8("fr_line_btn_2"));
        fr_line_btn_2->setMinimumSize(QSize(23, 23));
        fr_line_btn_2->setMaximumSize(QSize(23, 16777215));

        gridLayout_4->addWidget(fr_line_btn_2, 1, 0, 1, 1);

        fr_line_5 = new QCheckBox(widget_8);
        fr_line_5->setObjectName(QString::fromUtf8("fr_line_5"));
        fr_line_5->setChecked(true);

        gridLayout_4->addWidget(fr_line_5, 4, 1, 1, 1);

        fr_line_6 = new QCheckBox(widget_8);
        fr_line_6->setObjectName(QString::fromUtf8("fr_line_6"));
        fr_line_6->setChecked(true);

        gridLayout_4->addWidget(fr_line_6, 5, 1, 1, 1);

        fr_line_btn_3 = new QPushButton(widget_8);
        fr_line_btn_3->setObjectName(QString::fromUtf8("fr_line_btn_3"));
        fr_line_btn_3->setMinimumSize(QSize(23, 23));
        fr_line_btn_3->setMaximumSize(QSize(23, 16777215));

        gridLayout_4->addWidget(fr_line_btn_3, 2, 0, 1, 1);

        fr_line_4 = new QCheckBox(widget_8);
        fr_line_4->setObjectName(QString::fromUtf8("fr_line_4"));
        fr_line_4->setChecked(true);

        gridLayout_4->addWidget(fr_line_4, 3, 1, 1, 1);

        frChart_btn_conf = new QPushButton(widget_8);
        frChart_btn_conf->setObjectName(QString::fromUtf8("frChart_btn_conf"));
        frChart_btn_conf->setMinimumSize(QSize(0, 28));

        gridLayout_4->addWidget(frChart_btn_conf, 8, 0, 1, 2);

        fr_line_btn_5 = new QPushButton(widget_8);
        fr_line_btn_5->setObjectName(QString::fromUtf8("fr_line_btn_5"));
        fr_line_btn_5->setMinimumSize(QSize(23, 23));
        fr_line_btn_5->setMaximumSize(QSize(23, 16777215));

        gridLayout_4->addWidget(fr_line_btn_5, 4, 0, 1, 1);

        fr_line_btn_6 = new QPushButton(widget_8);
        fr_line_btn_6->setObjectName(QString::fromUtf8("fr_line_btn_6"));
        fr_line_btn_6->setMinimumSize(QSize(23, 23));
        fr_line_btn_6->setMaximumSize(QSize(23, 16777215));

        gridLayout_4->addWidget(fr_line_btn_6, 5, 0, 1, 1);

        fr_line_FF = new QCheckBox(widget_8);
        fr_line_FF->setObjectName(QString::fromUtf8("fr_line_FF"));
        fr_line_FF->setChecked(false);

        gridLayout_4->addWidget(fr_line_FF, 6, 0, 1, 2);

        fr_line_FB = new QCheckBox(widget_8);
        fr_line_FB->setObjectName(QString::fromUtf8("fr_line_FB"));
        fr_line_FB->setChecked(false);

        gridLayout_4->addWidget(fr_line_FB, 7, 0, 1, 2);


        horizontalLayout_5->addWidget(widget_8);


        verticalLayout_6->addWidget(widget_9);

        widget_10 = new QWidget(widget22);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        horizontalLayout_2 = new QHBoxLayout(widget_10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        phaseChartWgt = new QFreqLinesChart(widget_10);
        phaseChartWgt->setObjectName(QString::fromUtf8("phaseChartWgt"));

        horizontalLayout_2->addWidget(phaseChartWgt);

        widget_11 = new QWidget(widget_10);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        sizePolicy.setHeightForWidth(widget_11->sizePolicy().hasHeightForWidth());
        widget_11->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(widget_11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        phase_line_btn_1 = new QPushButton(widget_11);
        phase_line_btn_1->setObjectName(QString::fromUtf8("phase_line_btn_1"));
        phase_line_btn_1->setEnabled(false);
        phase_line_btn_1->setMinimumSize(QSize(23, 23));
        phase_line_btn_1->setMaximumSize(QSize(23, 16777215));

        gridLayout_5->addWidget(phase_line_btn_1, 0, 0, 1, 1);

        phase_line_1 = new QCheckBox(widget_11);
        phase_line_1->setObjectName(QString::fromUtf8("phase_line_1"));
        phase_line_1->setEnabled(false);
        phase_line_1->setChecked(true);

        gridLayout_5->addWidget(phase_line_1, 0, 1, 1, 1);

        phase_line_btn_2 = new QPushButton(widget_11);
        phase_line_btn_2->setObjectName(QString::fromUtf8("phase_line_btn_2"));
        phase_line_btn_2->setMinimumSize(QSize(23, 23));
        phase_line_btn_2->setMaximumSize(QSize(23, 16777215));

        gridLayout_5->addWidget(phase_line_btn_2, 1, 0, 1, 1);

        phase_line_2 = new QCheckBox(widget_11);
        phase_line_2->setObjectName(QString::fromUtf8("phase_line_2"));
        phase_line_2->setChecked(true);

        gridLayout_5->addWidget(phase_line_2, 1, 1, 1, 1);

        phase_line_btn_3 = new QPushButton(widget_11);
        phase_line_btn_3->setObjectName(QString::fromUtf8("phase_line_btn_3"));
        phase_line_btn_3->setMinimumSize(QSize(23, 23));
        phase_line_btn_3->setMaximumSize(QSize(23, 16777215));

        gridLayout_5->addWidget(phase_line_btn_3, 2, 0, 1, 1);

        phase_line_3 = new QCheckBox(widget_11);
        phase_line_3->setObjectName(QString::fromUtf8("phase_line_3"));
        phase_line_3->setChecked(true);

        gridLayout_5->addWidget(phase_line_3, 2, 1, 1, 1);

        phase_line_btn_4 = new QPushButton(widget_11);
        phase_line_btn_4->setObjectName(QString::fromUtf8("phase_line_btn_4"));
        phase_line_btn_4->setMinimumSize(QSize(23, 23));
        phase_line_btn_4->setMaximumSize(QSize(23, 16777215));

        gridLayout_5->addWidget(phase_line_btn_4, 3, 0, 1, 1);

        phase_line_4 = new QCheckBox(widget_11);
        phase_line_4->setObjectName(QString::fromUtf8("phase_line_4"));
        phase_line_4->setChecked(true);

        gridLayout_5->addWidget(phase_line_4, 3, 1, 1, 1);

        phase_line_btn_5 = new QPushButton(widget_11);
        phase_line_btn_5->setObjectName(QString::fromUtf8("phase_line_btn_5"));
        phase_line_btn_5->setMinimumSize(QSize(23, 23));
        phase_line_btn_5->setMaximumSize(QSize(23, 16777215));

        gridLayout_5->addWidget(phase_line_btn_5, 4, 0, 1, 1);

        phase_line_5 = new QCheckBox(widget_11);
        phase_line_5->setObjectName(QString::fromUtf8("phase_line_5"));
        phase_line_5->setChecked(true);

        gridLayout_5->addWidget(phase_line_5, 4, 1, 1, 1);

        phase_line_btn_6 = new QPushButton(widget_11);
        phase_line_btn_6->setObjectName(QString::fromUtf8("phase_line_btn_6"));
        phase_line_btn_6->setMinimumSize(QSize(23, 23));
        phase_line_btn_6->setMaximumSize(QSize(23, 16777215));

        gridLayout_5->addWidget(phase_line_btn_6, 5, 0, 1, 1);

        phase_line_6 = new QCheckBox(widget_11);
        phase_line_6->setObjectName(QString::fromUtf8("phase_line_6"));
        phase_line_6->setChecked(true);

        gridLayout_5->addWidget(phase_line_6, 5, 1, 1, 1);

        phase_line_FF = new QCheckBox(widget_11);
        phase_line_FF->setObjectName(QString::fromUtf8("phase_line_FF"));
        phase_line_FF->setChecked(false);

        gridLayout_5->addWidget(phase_line_FF, 6, 0, 1, 2);

        phase_line_FB = new QCheckBox(widget_11);
        phase_line_FB->setObjectName(QString::fromUtf8("phase_line_FB"));
        phase_line_FB->setChecked(false);

        gridLayout_5->addWidget(phase_line_FB, 7, 0, 1, 2);

        phaseChart_btn_conf = new QPushButton(widget_11);
        phaseChart_btn_conf->setObjectName(QString::fromUtf8("phaseChart_btn_conf"));
        phaseChart_btn_conf->setMinimumSize(QSize(0, 28));

        gridLayout_5->addWidget(phaseChart_btn_conf, 8, 0, 1, 2);


        horizontalLayout_2->addWidget(widget_11);


        verticalLayout_6->addWidget(widget_10);


        horizontalLayout_7->addWidget(widget22);


        verticalLayout_7->addWidget(mainWgt);


        retranslateUi(ANCTool);

        QMetaObject::connectSlotsByName(ANCTool);
    } // setupUi

    void retranslateUi(QWidget *ANCTool)
    {
        ANCTool->setWindowTitle(QCoreApplication::translate("ANCTool", "ANC\350\260\203\350\257\225\345\267\245\345\205\267", nullptr));
        actOpen->setText(QCoreApplication::translate("ANCTool", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actOpen->setToolTip(QCoreApplication::translate("ANCTool", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actOpen->setShortcut(QCoreApplication::translate("ANCTool", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actConfIO->setText(QCoreApplication::translate("ANCTool", "\350\256\276\347\275\256IO", nullptr));
#if QT_CONFIG(tooltip)
        actConfIO->setToolTip(QCoreApplication::translate("ANCTool", "\350\256\276\347\275\256IO", nullptr));
#endif // QT_CONFIG(tooltip)
        lab_debug->setText(QCoreApplication::translate("ANCTool", "\350\260\203\350\257\225\345\214\272", nullptr));
        label_2->setText(QCoreApplication::translate("ANCTool", "\347\253\257\345\217\243:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ANCTool", "\350\277\236\346\216\245", nullptr));
        ff_btn_4->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_7->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_5->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_8->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_2->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_1->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_10->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_ckb_8->setText(QString());
        ff_ckb_5->setText(QString());
        ff_btn_9->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_ckb_9->setText(QString());
        ff_ckb_2->setText(QString());
        ff_ckb_1->setText(QString());
        ff_ckb_4->setText(QString());
        ff_ckb_6->setText(QString());
        ff_ckb_7->setText(QString());
        ff_btn_3->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        ff_btn_6->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        lab_ff->setText(QCoreApplication::translate("ANCTool", "ff", nullptr));
        ff_ckb_3->setText(QString());
        ff_ckb_10->setText(QString());
        fb_ckb_9->setText(QString());
        fb_btn_6->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_btn_7->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_btn_1->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        lab_fb->setText(QCoreApplication::translate("ANCTool", "fb", nullptr));
        fb_btn_4->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_ckb_8->setText(QString());
        fb_ckb_3->setText(QString());
        fb_ckb_1->setText(QString());
        fb_ckb_2->setText(QString());
        fb_ckb_10->setText(QString());
        fb_btn_8->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_ckb_4->setText(QString());
        fb_ckb_5->setText(QString());
        fb_ckb_6->setText(QString());
        fb_btn_2->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_btn_9->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_btn_10->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_btn_3->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_btn_5->setText(QCoreApplication::translate("ANCTool", "bypass", nullptr));
        fb_ckb_7->setText(QString());
        btn_write_hardware->setText(QCoreApplication::translate("ANCTool", "\345\206\231\345\205\245\347\241\254\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("ANCTool", "\346\217\220\347\244\272\346\266\210\346\201\257", nullptr));
        pushButton->setText(QCoreApplication::translate("ANCTool", "\346\270\205\347\251\272", nullptr));
        fr_line_btn_4->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        fr_line_btn_1->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        fr_line_3->setText(QCoreApplication::translate("ANCTool", "Line 3", nullptr));
        fr_line_1->setText(QCoreApplication::translate("ANCTool", "Line 1", nullptr));
        fr_line_2->setText(QCoreApplication::translate("ANCTool", "Line 2", nullptr));
        fr_line_btn_2->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        fr_line_5->setText(QCoreApplication::translate("ANCTool", "Line 5", nullptr));
        fr_line_6->setText(QCoreApplication::translate("ANCTool", "\350\277\220\347\256\227\347\272\277\346\256\265", nullptr));
        fr_line_btn_3->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        fr_line_4->setText(QCoreApplication::translate("ANCTool", "Line 4", nullptr));
        frChart_btn_conf->setText(QCoreApplication::translate("ANCTool", "FR\351\205\215\347\275\256", nullptr));
        fr_line_btn_5->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        fr_line_btn_6->setText(QCoreApplication::translate("ANCTool", "A", nullptr));
        fr_line_FF->setText(QCoreApplication::translate("ANCTool", "\346\230\276\347\244\272FF", nullptr));
        fr_line_FB->setText(QCoreApplication::translate("ANCTool", "\346\230\276\347\244\272FB", nullptr));
        phase_line_btn_1->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        phase_line_1->setText(QCoreApplication::translate("ANCTool", "Line 1", nullptr));
        phase_line_btn_2->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        phase_line_2->setText(QCoreApplication::translate("ANCTool", "Line 2", nullptr));
        phase_line_btn_3->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        phase_line_3->setText(QCoreApplication::translate("ANCTool", "Line 3", nullptr));
        phase_line_btn_4->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        phase_line_4->setText(QCoreApplication::translate("ANCTool", "Line 4", nullptr));
        phase_line_btn_5->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        phase_line_5->setText(QCoreApplication::translate("ANCTool", "Line 5", nullptr));
        phase_line_btn_6->setText(QCoreApplication::translate("ANCTool", "S", nullptr));
        phase_line_6->setText(QCoreApplication::translate("ANCTool", "\350\277\220\347\256\227\347\272\277\346\256\265", nullptr));
        phase_line_FF->setText(QCoreApplication::translate("ANCTool", "\346\230\276\347\244\272FF", nullptr));
        phase_line_FB->setText(QCoreApplication::translate("ANCTool", "\346\230\276\347\244\272FB", nullptr));
        phaseChart_btn_conf->setText(QCoreApplication::translate("ANCTool", "PHASE\351\205\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ANCTool: public Ui_ANCTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANCTOOL_H

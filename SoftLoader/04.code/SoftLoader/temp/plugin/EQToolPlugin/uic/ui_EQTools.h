/********************************************************************************
** Form generated from reading UI file 'EQTools.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQTOOLS_H
#define UI_EQTOOLS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../common/customplot/QEQLinesChart.h"

QT_BEGIN_NAMESPACE

class Ui_EQTools
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *toolWgt;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btn_setting;
    QSpacerItem *horizontalSpacer_4;
    QEQLinesChart *chartWgt;
    QWidget *ctrlWgt;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *comboBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QPushButton *pushButton_5;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QWidget *voiceWgt;
    QVBoxLayout *verticalLayout_12;
    QLabel *lab_voice;
    QSlider *slider_voice;
    QLineEdit *edt_voice;
    QSpacerItem *horizontalSpacer;
    QWidget *bandWgt;
    QVBoxLayout *verticalLayout_2;
    QLabel *lab_freq;
    QSlider *slider_band;
    QDoubleSpinBox *spinBox_boost;
    QLabel *lab_Q;
    QLineEdit *edt_Q;
    QWidget *bandWgt_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *lab_freq_2;
    QSlider *slider_band_2;
    QDoubleSpinBox *spinBox_boost_2;
    QLabel *lab_Q_2;
    QLineEdit *edt_Q_2;
    QWidget *bandWgt_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *lab_freq_3;
    QSlider *slider_band_3;
    QDoubleSpinBox *spinBox_boost_3;
    QLabel *lab_Q_3;
    QLineEdit *edt_Q_3;
    QWidget *bandWgt_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *lab_freq_4;
    QSlider *slider_band_4;
    QDoubleSpinBox *spinBox_boost_4;
    QLabel *lab_Q_4;
    QLineEdit *edt_Q_4;
    QWidget *bandWgt_5;
    QVBoxLayout *verticalLayout_6;
    QLabel *lab_freq_5;
    QSlider *slider_band_5;
    QDoubleSpinBox *spinBox_boost_5;
    QLabel *lab_Q_5;
    QLineEdit *edt_Q_5;
    QWidget *bandWgt_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *lab_freq_6;
    QSlider *slider_band_6;
    QDoubleSpinBox *spinBox_boost_6;
    QLabel *lab_Q_6;
    QLineEdit *edt_Q_6;
    QWidget *bandWgt_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *lab_freq_7;
    QSlider *slider_band_7;
    QDoubleSpinBox *spinBox_boost_7;
    QLabel *lab_Q_7;
    QLineEdit *edt_Q_7;
    QWidget *bandWgt_8;
    QVBoxLayout *verticalLayout_9;
    QLabel *lab_freq_8;
    QSlider *slider_band_8;
    QDoubleSpinBox *spinBox_boost_8;
    QLabel *lab_Q_8;
    QLineEdit *edt_Q_8;
    QWidget *bandWgt_9;
    QVBoxLayout *verticalLayout_10;
    QLabel *lab_freq_9;
    QSlider *slider_band_9;
    QDoubleSpinBox *spinBox_boost_9;
    QLabel *lab_Q_9;
    QLineEdit *edt_Q_9;
    QWidget *bandWgt_10;
    QVBoxLayout *verticalLayout_11;
    QLabel *lab_freq_10;
    QSlider *slider_band_10;
    QDoubleSpinBox *spinBox_boost_10;
    QLabel *lab_Q_10;
    QLineEdit *edt_Q_10;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *EQTools)
    {
        if (EQTools->objectName().isEmpty())
            EQTools->setObjectName(QString::fromUtf8("EQTools"));
        EQTools->resize(1258, 879);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Img/image/wave.ico"), QSize(), QIcon::Normal, QIcon::Off);
        EQTools->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(EQTools);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolWgt = new QWidget(EQTools);
        toolWgt->setObjectName(QString::fromUtf8("toolWgt"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolWgt->sizePolicy().hasHeightForWidth());
        toolWgt->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(toolWgt);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(toolWgt);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(toolWgt);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(toolWgt);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(toolWgt);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(80, 25));
        comboBox->setEditable(true);

        horizontalLayout_2->addWidget(comboBox);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        label_3 = new QLabel(toolWgt);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        spinBox = new QSpinBox(toolWgt);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(75, 25));
        spinBox->setValue(30);

        horizontalLayout_2->addWidget(spinBox);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        btn_setting = new QPushButton(toolWgt);
        btn_setting->setObjectName(QString::fromUtf8("btn_setting"));
        btn_setting->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btn_setting);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(toolWgt);

        chartWgt = new QEQLinesChart(EQTools);
        chartWgt->setObjectName(QString::fromUtf8("chartWgt"));

        verticalLayout->addWidget(chartWgt);

        ctrlWgt = new QWidget(EQTools);
        ctrlWgt->setObjectName(QString::fromUtf8("ctrlWgt"));
        sizePolicy.setHeightForWidth(ctrlWgt->sizePolicy().hasHeightForWidth());
        ctrlWgt->setSizePolicy(sizePolicy);
        ctrlWgt->setMinimumSize(QSize(0, 300));
        horizontalLayout_5 = new QHBoxLayout(ctrlWgt);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_2 = new QGroupBox(ctrlWgt);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_13 = new QVBoxLayout(groupBox_2);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        horizontalLayout_3->addWidget(comboBox_2);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(75, 0));
        pushButton_3->setMaximumSize(QSize(75, 16777215));
        pushButton_3->setCheckable(true);

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(75, 0));
        pushButton_4->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout_13->addLayout(horizontalLayout_3);

        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_14 = new QVBoxLayout(widget);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_4);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(70, 0));
        pushButton_5->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(pushButton_5);


        verticalLayout_14->addLayout(horizontalLayout_4);

        plainTextEdit = new QPlainTextEdit(widget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout_14->addWidget(plainTextEdit);


        verticalLayout_13->addWidget(widget);


        horizontalLayout_5->addWidget(groupBox_2);

        groupBox = new QGroupBox(ctrlWgt);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        voiceWgt = new QWidget(groupBox);
        voiceWgt->setObjectName(QString::fromUtf8("voiceWgt"));
        sizePolicy1.setHeightForWidth(voiceWgt->sizePolicy().hasHeightForWidth());
        voiceWgt->setSizePolicy(sizePolicy1);
        voiceWgt->setMinimumSize(QSize(75, 0));
        voiceWgt->setMaximumSize(QSize(75, 16777215));
        verticalLayout_12 = new QVBoxLayout(voiceWgt);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(6, 6, 6, 6);
        lab_voice = new QLabel(voiceWgt);
        lab_voice->setObjectName(QString::fromUtf8("lab_voice"));
        sizePolicy2.setHeightForWidth(lab_voice->sizePolicy().hasHeightForWidth());
        lab_voice->setSizePolicy(sizePolicy2);
        lab_voice->setContextMenuPolicy(Qt::NoContextMenu);
        lab_voice->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(lab_voice);

        slider_voice = new QSlider(voiceWgt);
        slider_voice->setObjectName(QString::fromUtf8("slider_voice"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(slider_voice->sizePolicy().hasHeightForWidth());
        slider_voice->setSizePolicy(sizePolicy3);
        slider_voice->setMinimum(-30);
        slider_voice->setMaximum(30);
        slider_voice->setOrientation(Qt::Vertical);

        verticalLayout_12->addWidget(slider_voice);

        edt_voice = new QLineEdit(voiceWgt);
        edt_voice->setObjectName(QString::fromUtf8("edt_voice"));
        sizePolicy.setHeightForWidth(edt_voice->sizePolicy().hasHeightForWidth());
        edt_voice->setSizePolicy(sizePolicy);
        edt_voice->setAlignment(Qt::AlignCenter);
        edt_voice->setReadOnly(true);

        verticalLayout_12->addWidget(edt_voice);


        horizontalLayout->addWidget(voiceWgt);

        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bandWgt = new QWidget(groupBox);
        bandWgt->setObjectName(QString::fromUtf8("bandWgt"));
        sizePolicy1.setHeightForWidth(bandWgt->sizePolicy().hasHeightForWidth());
        bandWgt->setSizePolicy(sizePolicy1);
        bandWgt->setMaximumSize(QSize(70, 16777215));
        verticalLayout_2 = new QVBoxLayout(bandWgt);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        lab_freq = new QLabel(bandWgt);
        lab_freq->setObjectName(QString::fromUtf8("lab_freq"));
        sizePolicy2.setHeightForWidth(lab_freq->sizePolicy().hasHeightForWidth());
        lab_freq->setSizePolicy(sizePolicy2);
        lab_freq->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lab_freq);

        slider_band = new QSlider(bandWgt);
        slider_band->setObjectName(QString::fromUtf8("slider_band"));
        sizePolicy3.setHeightForWidth(slider_band->sizePolicy().hasHeightForWidth());
        slider_band->setSizePolicy(sizePolicy3);
        slider_band->setMinimum(-300);
        slider_band->setMaximum(300);
        slider_band->setSingleStep(1);
        slider_band->setPageStep(10);
        slider_band->setOrientation(Qt::Vertical);

        verticalLayout_2->addWidget(slider_band);

        spinBox_boost = new QDoubleSpinBox(bandWgt);
        spinBox_boost->setObjectName(QString::fromUtf8("spinBox_boost"));
        spinBox_boost->setAlignment(Qt::AlignCenter);
        spinBox_boost->setDecimals(1);
        spinBox_boost->setMinimum(-30.000000000000000);
        spinBox_boost->setMaximum(30.000000000000000);
        spinBox_boost->setSingleStep(0.100000000000000);

        verticalLayout_2->addWidget(spinBox_boost);

        lab_Q = new QLabel(bandWgt);
        lab_Q->setObjectName(QString::fromUtf8("lab_Q"));
        sizePolicy2.setHeightForWidth(lab_Q->sizePolicy().hasHeightForWidth());
        lab_Q->setSizePolicy(sizePolicy2);
        lab_Q->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lab_Q);

        edt_Q = new QLineEdit(bandWgt);
        edt_Q->setObjectName(QString::fromUtf8("edt_Q"));
        sizePolicy.setHeightForWidth(edt_Q->sizePolicy().hasHeightForWidth());
        edt_Q->setSizePolicy(sizePolicy);
        edt_Q->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(edt_Q);


        horizontalLayout->addWidget(bandWgt);

        bandWgt_2 = new QWidget(groupBox);
        bandWgt_2->setObjectName(QString::fromUtf8("bandWgt_2"));
        sizePolicy1.setHeightForWidth(bandWgt_2->sizePolicy().hasHeightForWidth());
        bandWgt_2->setSizePolicy(sizePolicy1);
        bandWgt_2->setMaximumSize(QSize(70, 16777215));
        verticalLayout_3 = new QVBoxLayout(bandWgt_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        lab_freq_2 = new QLabel(bandWgt_2);
        lab_freq_2->setObjectName(QString::fromUtf8("lab_freq_2"));
        sizePolicy2.setHeightForWidth(lab_freq_2->sizePolicy().hasHeightForWidth());
        lab_freq_2->setSizePolicy(sizePolicy2);
        lab_freq_2->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lab_freq_2);

        slider_band_2 = new QSlider(bandWgt_2);
        slider_band_2->setObjectName(QString::fromUtf8("slider_band_2"));
        sizePolicy3.setHeightForWidth(slider_band_2->sizePolicy().hasHeightForWidth());
        slider_band_2->setSizePolicy(sizePolicy3);
        slider_band_2->setMinimum(-300);
        slider_band_2->setMaximum(300);
        slider_band_2->setSingleStep(1);
        slider_band_2->setPageStep(10);
        slider_band_2->setOrientation(Qt::Vertical);

        verticalLayout_3->addWidget(slider_band_2);

        spinBox_boost_2 = new QDoubleSpinBox(bandWgt_2);
        spinBox_boost_2->setObjectName(QString::fromUtf8("spinBox_boost_2"));
        spinBox_boost_2->setAlignment(Qt::AlignCenter);
        spinBox_boost_2->setDecimals(1);
        spinBox_boost_2->setMinimum(-30.000000000000000);
        spinBox_boost_2->setMaximum(30.000000000000000);
        spinBox_boost_2->setSingleStep(0.100000000000000);

        verticalLayout_3->addWidget(spinBox_boost_2);

        lab_Q_2 = new QLabel(bandWgt_2);
        lab_Q_2->setObjectName(QString::fromUtf8("lab_Q_2"));
        sizePolicy2.setHeightForWidth(lab_Q_2->sizePolicy().hasHeightForWidth());
        lab_Q_2->setSizePolicy(sizePolicy2);
        lab_Q_2->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lab_Q_2);

        edt_Q_2 = new QLineEdit(bandWgt_2);
        edt_Q_2->setObjectName(QString::fromUtf8("edt_Q_2"));
        sizePolicy.setHeightForWidth(edt_Q_2->sizePolicy().hasHeightForWidth());
        edt_Q_2->setSizePolicy(sizePolicy);
        edt_Q_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(edt_Q_2);


        horizontalLayout->addWidget(bandWgt_2);

        bandWgt_3 = new QWidget(groupBox);
        bandWgt_3->setObjectName(QString::fromUtf8("bandWgt_3"));
        sizePolicy1.setHeightForWidth(bandWgt_3->sizePolicy().hasHeightForWidth());
        bandWgt_3->setSizePolicy(sizePolicy1);
        bandWgt_3->setMaximumSize(QSize(70, 16777215));
        verticalLayout_4 = new QVBoxLayout(bandWgt_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(6, 6, 6, 6);
        lab_freq_3 = new QLabel(bandWgt_3);
        lab_freq_3->setObjectName(QString::fromUtf8("lab_freq_3"));
        sizePolicy2.setHeightForWidth(lab_freq_3->sizePolicy().hasHeightForWidth());
        lab_freq_3->setSizePolicy(sizePolicy2);
        lab_freq_3->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lab_freq_3);

        slider_band_3 = new QSlider(bandWgt_3);
        slider_band_3->setObjectName(QString::fromUtf8("slider_band_3"));
        sizePolicy3.setHeightForWidth(slider_band_3->sizePolicy().hasHeightForWidth());
        slider_band_3->setSizePolicy(sizePolicy3);
        slider_band_3->setMinimum(-300);
        slider_band_3->setMaximum(300);
        slider_band_3->setSingleStep(1);
        slider_band_3->setPageStep(10);
        slider_band_3->setOrientation(Qt::Vertical);

        verticalLayout_4->addWidget(slider_band_3);

        spinBox_boost_3 = new QDoubleSpinBox(bandWgt_3);
        spinBox_boost_3->setObjectName(QString::fromUtf8("spinBox_boost_3"));
        spinBox_boost_3->setAlignment(Qt::AlignCenter);
        spinBox_boost_3->setDecimals(1);
        spinBox_boost_3->setMinimum(-30.000000000000000);
        spinBox_boost_3->setMaximum(30.000000000000000);
        spinBox_boost_3->setSingleStep(0.100000000000000);

        verticalLayout_4->addWidget(spinBox_boost_3);

        lab_Q_3 = new QLabel(bandWgt_3);
        lab_Q_3->setObjectName(QString::fromUtf8("lab_Q_3"));
        sizePolicy2.setHeightForWidth(lab_Q_3->sizePolicy().hasHeightForWidth());
        lab_Q_3->setSizePolicy(sizePolicy2);
        lab_Q_3->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lab_Q_3);

        edt_Q_3 = new QLineEdit(bandWgt_3);
        edt_Q_3->setObjectName(QString::fromUtf8("edt_Q_3"));
        sizePolicy.setHeightForWidth(edt_Q_3->sizePolicy().hasHeightForWidth());
        edt_Q_3->setSizePolicy(sizePolicy);
        edt_Q_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(edt_Q_3);


        horizontalLayout->addWidget(bandWgt_3);

        bandWgt_4 = new QWidget(groupBox);
        bandWgt_4->setObjectName(QString::fromUtf8("bandWgt_4"));
        sizePolicy1.setHeightForWidth(bandWgt_4->sizePolicy().hasHeightForWidth());
        bandWgt_4->setSizePolicy(sizePolicy1);
        bandWgt_4->setMaximumSize(QSize(70, 16777215));
        verticalLayout_5 = new QVBoxLayout(bandWgt_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(6, 6, 6, 6);
        lab_freq_4 = new QLabel(bandWgt_4);
        lab_freq_4->setObjectName(QString::fromUtf8("lab_freq_4"));
        sizePolicy2.setHeightForWidth(lab_freq_4->sizePolicy().hasHeightForWidth());
        lab_freq_4->setSizePolicy(sizePolicy2);
        lab_freq_4->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_4->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lab_freq_4);

        slider_band_4 = new QSlider(bandWgt_4);
        slider_band_4->setObjectName(QString::fromUtf8("slider_band_4"));
        sizePolicy3.setHeightForWidth(slider_band_4->sizePolicy().hasHeightForWidth());
        slider_band_4->setSizePolicy(sizePolicy3);
        slider_band_4->setMinimum(-300);
        slider_band_4->setMaximum(300);
        slider_band_4->setSingleStep(1);
        slider_band_4->setPageStep(10);
        slider_band_4->setOrientation(Qt::Vertical);

        verticalLayout_5->addWidget(slider_band_4);

        spinBox_boost_4 = new QDoubleSpinBox(bandWgt_4);
        spinBox_boost_4->setObjectName(QString::fromUtf8("spinBox_boost_4"));
        spinBox_boost_4->setAlignment(Qt::AlignCenter);
        spinBox_boost_4->setDecimals(1);
        spinBox_boost_4->setMinimum(-30.000000000000000);
        spinBox_boost_4->setMaximum(30.000000000000000);
        spinBox_boost_4->setSingleStep(0.100000000000000);

        verticalLayout_5->addWidget(spinBox_boost_4);

        lab_Q_4 = new QLabel(bandWgt_4);
        lab_Q_4->setObjectName(QString::fromUtf8("lab_Q_4"));
        sizePolicy2.setHeightForWidth(lab_Q_4->sizePolicy().hasHeightForWidth());
        lab_Q_4->setSizePolicy(sizePolicy2);
        lab_Q_4->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_4->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lab_Q_4);

        edt_Q_4 = new QLineEdit(bandWgt_4);
        edt_Q_4->setObjectName(QString::fromUtf8("edt_Q_4"));
        sizePolicy.setHeightForWidth(edt_Q_4->sizePolicy().hasHeightForWidth());
        edt_Q_4->setSizePolicy(sizePolicy);
        edt_Q_4->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(edt_Q_4);


        horizontalLayout->addWidget(bandWgt_4);

        bandWgt_5 = new QWidget(groupBox);
        bandWgt_5->setObjectName(QString::fromUtf8("bandWgt_5"));
        sizePolicy1.setHeightForWidth(bandWgt_5->sizePolicy().hasHeightForWidth());
        bandWgt_5->setSizePolicy(sizePolicy1);
        bandWgt_5->setMaximumSize(QSize(70, 16777215));
        verticalLayout_6 = new QVBoxLayout(bandWgt_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(6, 6, 6, 6);
        lab_freq_5 = new QLabel(bandWgt_5);
        lab_freq_5->setObjectName(QString::fromUtf8("lab_freq_5"));
        sizePolicy2.setHeightForWidth(lab_freq_5->sizePolicy().hasHeightForWidth());
        lab_freq_5->setSizePolicy(sizePolicy2);
        lab_freq_5->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_5->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(lab_freq_5);

        slider_band_5 = new QSlider(bandWgt_5);
        slider_band_5->setObjectName(QString::fromUtf8("slider_band_5"));
        sizePolicy3.setHeightForWidth(slider_band_5->sizePolicy().hasHeightForWidth());
        slider_band_5->setSizePolicy(sizePolicy3);
        slider_band_5->setMinimum(-300);
        slider_band_5->setMaximum(300);
        slider_band_5->setSingleStep(1);
        slider_band_5->setPageStep(10);
        slider_band_5->setOrientation(Qt::Vertical);

        verticalLayout_6->addWidget(slider_band_5);

        spinBox_boost_5 = new QDoubleSpinBox(bandWgt_5);
        spinBox_boost_5->setObjectName(QString::fromUtf8("spinBox_boost_5"));
        spinBox_boost_5->setAlignment(Qt::AlignCenter);
        spinBox_boost_5->setDecimals(1);
        spinBox_boost_5->setMinimum(-30.000000000000000);
        spinBox_boost_5->setMaximum(30.000000000000000);
        spinBox_boost_5->setSingleStep(0.100000000000000);

        verticalLayout_6->addWidget(spinBox_boost_5);

        lab_Q_5 = new QLabel(bandWgt_5);
        lab_Q_5->setObjectName(QString::fromUtf8("lab_Q_5"));
        sizePolicy2.setHeightForWidth(lab_Q_5->sizePolicy().hasHeightForWidth());
        lab_Q_5->setSizePolicy(sizePolicy2);
        lab_Q_5->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_5->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(lab_Q_5);

        edt_Q_5 = new QLineEdit(bandWgt_5);
        edt_Q_5->setObjectName(QString::fromUtf8("edt_Q_5"));
        sizePolicy.setHeightForWidth(edt_Q_5->sizePolicy().hasHeightForWidth());
        edt_Q_5->setSizePolicy(sizePolicy);
        edt_Q_5->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(edt_Q_5);


        horizontalLayout->addWidget(bandWgt_5);

        bandWgt_6 = new QWidget(groupBox);
        bandWgt_6->setObjectName(QString::fromUtf8("bandWgt_6"));
        sizePolicy1.setHeightForWidth(bandWgt_6->sizePolicy().hasHeightForWidth());
        bandWgt_6->setSizePolicy(sizePolicy1);
        bandWgt_6->setMaximumSize(QSize(70, 16777215));
        verticalLayout_7 = new QVBoxLayout(bandWgt_6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(6, 6, 6, 6);
        lab_freq_6 = new QLabel(bandWgt_6);
        lab_freq_6->setObjectName(QString::fromUtf8("lab_freq_6"));
        sizePolicy2.setHeightForWidth(lab_freq_6->sizePolicy().hasHeightForWidth());
        lab_freq_6->setSizePolicy(sizePolicy2);
        lab_freq_6->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_6->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(lab_freq_6);

        slider_band_6 = new QSlider(bandWgt_6);
        slider_band_6->setObjectName(QString::fromUtf8("slider_band_6"));
        sizePolicy3.setHeightForWidth(slider_band_6->sizePolicy().hasHeightForWidth());
        slider_band_6->setSizePolicy(sizePolicy3);
        slider_band_6->setMinimum(-300);
        slider_band_6->setMaximum(300);
        slider_band_6->setSingleStep(1);
        slider_band_6->setPageStep(10);
        slider_band_6->setOrientation(Qt::Vertical);

        verticalLayout_7->addWidget(slider_band_6);

        spinBox_boost_6 = new QDoubleSpinBox(bandWgt_6);
        spinBox_boost_6->setObjectName(QString::fromUtf8("spinBox_boost_6"));
        spinBox_boost_6->setAlignment(Qt::AlignCenter);
        spinBox_boost_6->setDecimals(1);
        spinBox_boost_6->setMinimum(-30.000000000000000);
        spinBox_boost_6->setMaximum(30.000000000000000);
        spinBox_boost_6->setSingleStep(0.100000000000000);

        verticalLayout_7->addWidget(spinBox_boost_6);

        lab_Q_6 = new QLabel(bandWgt_6);
        lab_Q_6->setObjectName(QString::fromUtf8("lab_Q_6"));
        sizePolicy2.setHeightForWidth(lab_Q_6->sizePolicy().hasHeightForWidth());
        lab_Q_6->setSizePolicy(sizePolicy2);
        lab_Q_6->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_6->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(lab_Q_6);

        edt_Q_6 = new QLineEdit(bandWgt_6);
        edt_Q_6->setObjectName(QString::fromUtf8("edt_Q_6"));
        sizePolicy.setHeightForWidth(edt_Q_6->sizePolicy().hasHeightForWidth());
        edt_Q_6->setSizePolicy(sizePolicy);
        edt_Q_6->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(edt_Q_6);


        horizontalLayout->addWidget(bandWgt_6);

        bandWgt_7 = new QWidget(groupBox);
        bandWgt_7->setObjectName(QString::fromUtf8("bandWgt_7"));
        sizePolicy1.setHeightForWidth(bandWgt_7->sizePolicy().hasHeightForWidth());
        bandWgt_7->setSizePolicy(sizePolicy1);
        bandWgt_7->setMaximumSize(QSize(70, 16777215));
        verticalLayout_8 = new QVBoxLayout(bandWgt_7);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(6, 6, 6, 6);
        lab_freq_7 = new QLabel(bandWgt_7);
        lab_freq_7->setObjectName(QString::fromUtf8("lab_freq_7"));
        sizePolicy2.setHeightForWidth(lab_freq_7->sizePolicy().hasHeightForWidth());
        lab_freq_7->setSizePolicy(sizePolicy2);
        lab_freq_7->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_7->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(lab_freq_7);

        slider_band_7 = new QSlider(bandWgt_7);
        slider_band_7->setObjectName(QString::fromUtf8("slider_band_7"));
        sizePolicy3.setHeightForWidth(slider_band_7->sizePolicy().hasHeightForWidth());
        slider_band_7->setSizePolicy(sizePolicy3);
        slider_band_7->setMinimum(-300);
        slider_band_7->setMaximum(300);
        slider_band_7->setSingleStep(1);
        slider_band_7->setPageStep(10);
        slider_band_7->setOrientation(Qt::Vertical);

        verticalLayout_8->addWidget(slider_band_7);

        spinBox_boost_7 = new QDoubleSpinBox(bandWgt_7);
        spinBox_boost_7->setObjectName(QString::fromUtf8("spinBox_boost_7"));
        spinBox_boost_7->setAlignment(Qt::AlignCenter);
        spinBox_boost_7->setDecimals(1);
        spinBox_boost_7->setMinimum(-30.000000000000000);
        spinBox_boost_7->setMaximum(30.000000000000000);
        spinBox_boost_7->setSingleStep(0.100000000000000);

        verticalLayout_8->addWidget(spinBox_boost_7);

        lab_Q_7 = new QLabel(bandWgt_7);
        lab_Q_7->setObjectName(QString::fromUtf8("lab_Q_7"));
        sizePolicy2.setHeightForWidth(lab_Q_7->sizePolicy().hasHeightForWidth());
        lab_Q_7->setSizePolicy(sizePolicy2);
        lab_Q_7->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_7->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(lab_Q_7);

        edt_Q_7 = new QLineEdit(bandWgt_7);
        edt_Q_7->setObjectName(QString::fromUtf8("edt_Q_7"));
        sizePolicy.setHeightForWidth(edt_Q_7->sizePolicy().hasHeightForWidth());
        edt_Q_7->setSizePolicy(sizePolicy);
        edt_Q_7->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(edt_Q_7);


        horizontalLayout->addWidget(bandWgt_7);

        bandWgt_8 = new QWidget(groupBox);
        bandWgt_8->setObjectName(QString::fromUtf8("bandWgt_8"));
        sizePolicy1.setHeightForWidth(bandWgt_8->sizePolicy().hasHeightForWidth());
        bandWgt_8->setSizePolicy(sizePolicy1);
        bandWgt_8->setMaximumSize(QSize(70, 16777215));
        verticalLayout_9 = new QVBoxLayout(bandWgt_8);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(6, 6, 6, 6);
        lab_freq_8 = new QLabel(bandWgt_8);
        lab_freq_8->setObjectName(QString::fromUtf8("lab_freq_8"));
        sizePolicy2.setHeightForWidth(lab_freq_8->sizePolicy().hasHeightForWidth());
        lab_freq_8->setSizePolicy(sizePolicy2);
        lab_freq_8->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_8->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(lab_freq_8);

        slider_band_8 = new QSlider(bandWgt_8);
        slider_band_8->setObjectName(QString::fromUtf8("slider_band_8"));
        sizePolicy3.setHeightForWidth(slider_band_8->sizePolicy().hasHeightForWidth());
        slider_band_8->setSizePolicy(sizePolicy3);
        slider_band_8->setMinimum(-300);
        slider_band_8->setMaximum(300);
        slider_band_8->setSingleStep(1);
        slider_band_8->setPageStep(10);
        slider_band_8->setOrientation(Qt::Vertical);

        verticalLayout_9->addWidget(slider_band_8);

        spinBox_boost_8 = new QDoubleSpinBox(bandWgt_8);
        spinBox_boost_8->setObjectName(QString::fromUtf8("spinBox_boost_8"));
        spinBox_boost_8->setAlignment(Qt::AlignCenter);
        spinBox_boost_8->setDecimals(1);
        spinBox_boost_8->setMinimum(-30.000000000000000);
        spinBox_boost_8->setMaximum(30.000000000000000);
        spinBox_boost_8->setSingleStep(0.100000000000000);

        verticalLayout_9->addWidget(spinBox_boost_8);

        lab_Q_8 = new QLabel(bandWgt_8);
        lab_Q_8->setObjectName(QString::fromUtf8("lab_Q_8"));
        sizePolicy2.setHeightForWidth(lab_Q_8->sizePolicy().hasHeightForWidth());
        lab_Q_8->setSizePolicy(sizePolicy2);
        lab_Q_8->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_8->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(lab_Q_8);

        edt_Q_8 = new QLineEdit(bandWgt_8);
        edt_Q_8->setObjectName(QString::fromUtf8("edt_Q_8"));
        sizePolicy.setHeightForWidth(edt_Q_8->sizePolicy().hasHeightForWidth());
        edt_Q_8->setSizePolicy(sizePolicy);
        edt_Q_8->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(edt_Q_8);


        horizontalLayout->addWidget(bandWgt_8);

        bandWgt_9 = new QWidget(groupBox);
        bandWgt_9->setObjectName(QString::fromUtf8("bandWgt_9"));
        sizePolicy1.setHeightForWidth(bandWgt_9->sizePolicy().hasHeightForWidth());
        bandWgt_9->setSizePolicy(sizePolicy1);
        bandWgt_9->setMaximumSize(QSize(70, 16777215));
        verticalLayout_10 = new QVBoxLayout(bandWgt_9);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(6, 6, 6, 6);
        lab_freq_9 = new QLabel(bandWgt_9);
        lab_freq_9->setObjectName(QString::fromUtf8("lab_freq_9"));
        sizePolicy2.setHeightForWidth(lab_freq_9->sizePolicy().hasHeightForWidth());
        lab_freq_9->setSizePolicy(sizePolicy2);
        lab_freq_9->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_9->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(lab_freq_9);

        slider_band_9 = new QSlider(bandWgt_9);
        slider_band_9->setObjectName(QString::fromUtf8("slider_band_9"));
        sizePolicy3.setHeightForWidth(slider_band_9->sizePolicy().hasHeightForWidth());
        slider_band_9->setSizePolicy(sizePolicy3);
        slider_band_9->setMinimum(-300);
        slider_band_9->setMaximum(300);
        slider_band_9->setSingleStep(1);
        slider_band_9->setPageStep(10);
        slider_band_9->setOrientation(Qt::Vertical);

        verticalLayout_10->addWidget(slider_band_9);

        spinBox_boost_9 = new QDoubleSpinBox(bandWgt_9);
        spinBox_boost_9->setObjectName(QString::fromUtf8("spinBox_boost_9"));
        spinBox_boost_9->setAlignment(Qt::AlignCenter);
        spinBox_boost_9->setDecimals(1);
        spinBox_boost_9->setMinimum(-30.000000000000000);
        spinBox_boost_9->setMaximum(30.000000000000000);
        spinBox_boost_9->setSingleStep(0.100000000000000);

        verticalLayout_10->addWidget(spinBox_boost_9);

        lab_Q_9 = new QLabel(bandWgt_9);
        lab_Q_9->setObjectName(QString::fromUtf8("lab_Q_9"));
        sizePolicy2.setHeightForWidth(lab_Q_9->sizePolicy().hasHeightForWidth());
        lab_Q_9->setSizePolicy(sizePolicy2);
        lab_Q_9->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_9->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(lab_Q_9);

        edt_Q_9 = new QLineEdit(bandWgt_9);
        edt_Q_9->setObjectName(QString::fromUtf8("edt_Q_9"));
        sizePolicy.setHeightForWidth(edt_Q_9->sizePolicy().hasHeightForWidth());
        edt_Q_9->setSizePolicy(sizePolicy);
        edt_Q_9->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(edt_Q_9);


        horizontalLayout->addWidget(bandWgt_9);

        bandWgt_10 = new QWidget(groupBox);
        bandWgt_10->setObjectName(QString::fromUtf8("bandWgt_10"));
        sizePolicy1.setHeightForWidth(bandWgt_10->sizePolicy().hasHeightForWidth());
        bandWgt_10->setSizePolicy(sizePolicy1);
        bandWgt_10->setMaximumSize(QSize(70, 16777215));
        verticalLayout_11 = new QVBoxLayout(bandWgt_10);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(6, 6, 6, 6);
        lab_freq_10 = new QLabel(bandWgt_10);
        lab_freq_10->setObjectName(QString::fromUtf8("lab_freq_10"));
        sizePolicy2.setHeightForWidth(lab_freq_10->sizePolicy().hasHeightForWidth());
        lab_freq_10->setSizePolicy(sizePolicy2);
        lab_freq_10->setContextMenuPolicy(Qt::NoContextMenu);
        lab_freq_10->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(lab_freq_10);

        slider_band_10 = new QSlider(bandWgt_10);
        slider_band_10->setObjectName(QString::fromUtf8("slider_band_10"));
        sizePolicy3.setHeightForWidth(slider_band_10->sizePolicy().hasHeightForWidth());
        slider_band_10->setSizePolicy(sizePolicy3);
        slider_band_10->setMinimum(-300);
        slider_band_10->setMaximum(300);
        slider_band_10->setSingleStep(1);
        slider_band_10->setPageStep(10);
        slider_band_10->setSliderPosition(0);
        slider_band_10->setOrientation(Qt::Vertical);

        verticalLayout_11->addWidget(slider_band_10);

        spinBox_boost_10 = new QDoubleSpinBox(bandWgt_10);
        spinBox_boost_10->setObjectName(QString::fromUtf8("spinBox_boost_10"));
        spinBox_boost_10->setAlignment(Qt::AlignCenter);
        spinBox_boost_10->setDecimals(1);
        spinBox_boost_10->setMinimum(-30.000000000000000);
        spinBox_boost_10->setMaximum(30.000000000000000);
        spinBox_boost_10->setSingleStep(0.100000000000000);

        verticalLayout_11->addWidget(spinBox_boost_10);

        lab_Q_10 = new QLabel(bandWgt_10);
        lab_Q_10->setObjectName(QString::fromUtf8("lab_Q_10"));
        sizePolicy2.setHeightForWidth(lab_Q_10->sizePolicy().hasHeightForWidth());
        lab_Q_10->setSizePolicy(sizePolicy2);
        lab_Q_10->setContextMenuPolicy(Qt::NoContextMenu);
        lab_Q_10->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(lab_Q_10);

        edt_Q_10 = new QLineEdit(bandWgt_10);
        edt_Q_10->setObjectName(QString::fromUtf8("edt_Q_10"));
        sizePolicy.setHeightForWidth(edt_Q_10->sizePolicy().hasHeightForWidth());
        edt_Q_10->setSizePolicy(sizePolicy);
        edt_Q_10->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(edt_Q_10);


        horizontalLayout->addWidget(bandWgt_10);


        horizontalLayout_5->addWidget(groupBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(ctrlWgt);


        retranslateUi(EQTools);

        QMetaObject::connectSlotsByName(EQTools);
    } // setupUi

    void retranslateUi(QWidget *EQTools)
    {
        EQTools->setWindowTitle(QCoreApplication::translate("EQTools", "EQ\350\260\203\350\257\225\345\267\245\345\205\267", nullptr));
        pushButton->setText(QCoreApplication::translate("EQTools", "\346\211\223\345\274\200", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EQTools", "\344\277\235\345\255\230", nullptr));
        label_2->setText(QCoreApplication::translate("EQTools", "\351\207\207\346\240\267\351\242\221\347\216\207:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("EQTools", "44100", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("EQTools", "48000", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("EQTools", "64000", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("EQTools", "88200", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("EQTools", "96000", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("EQTools", "176400", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("EQTools", "192000", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("EQTools", "384000", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("EQTools", "768000", nullptr));

        label_3->setText(QCoreApplication::translate("EQTools", "\345\263\260\345\200\274\350\256\276\347\275\256:", nullptr));
        btn_setting->setText(QCoreApplication::translate("EQTools", "\350\256\276\347\275\256", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("EQTools", "\350\260\203\350\257\225\345\212\251\346\211\213", nullptr));
        label->setText(QCoreApplication::translate("EQTools", "\344\270\262\345\217\243:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("EQTools", "\350\277\236\346\216\245", nullptr));
        pushButton_4->setText(QCoreApplication::translate("EQTools", "\345\206\231\345\205\245\347\241\254\344\273\266", nullptr));
        label_4->setText(QCoreApplication::translate("EQTools", "\350\260\203\350\257\225\344\277\241\346\201\257", nullptr));
        pushButton_5->setText(QCoreApplication::translate("EQTools", "\346\270\205\347\251\272", nullptr));
        groupBox->setTitle(QCoreApplication::translate("EQTools", "\351\242\221\347\202\271\350\256\276\347\275\256", nullptr));
        lab_voice->setText(QCoreApplication::translate("EQTools", "\346\200\273\351\237\263\351\207\217", nullptr));
        edt_voice->setText(QCoreApplication::translate("EQTools", "0", nullptr));
        lab_freq->setText(QCoreApplication::translate("EQTools", "31Hz", nullptr));
        lab_Q->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_2->setText(QCoreApplication::translate("EQTools", "63Hz", nullptr));
        lab_Q_2->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_2->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_3->setText(QCoreApplication::translate("EQTools", "125Hz", nullptr));
        lab_Q_3->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_3->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_4->setText(QCoreApplication::translate("EQTools", "250Hz", nullptr));
        lab_Q_4->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_4->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_5->setText(QCoreApplication::translate("EQTools", "500Hz", nullptr));
        lab_Q_5->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_5->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_6->setText(QCoreApplication::translate("EQTools", "1KHz", nullptr));
        lab_Q_6->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_6->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_7->setText(QCoreApplication::translate("EQTools", "2KHz", nullptr));
        lab_Q_7->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_7->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_8->setText(QCoreApplication::translate("EQTools", "4KHz", nullptr));
        lab_Q_8->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_8->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_9->setText(QCoreApplication::translate("EQTools", "8KHz", nullptr));
        lab_Q_9->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_9->setText(QCoreApplication::translate("EQTools", "1", nullptr));
        lab_freq_10->setText(QCoreApplication::translate("EQTools", "16KHz", nullptr));
        lab_Q_10->setText(QCoreApplication::translate("EQTools", "Q\345\200\274", nullptr));
        edt_Q_10->setText(QCoreApplication::translate("EQTools", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EQTools: public Ui_EQTools {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQTOOLS_H

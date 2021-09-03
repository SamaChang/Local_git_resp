/********************************************************************************
** Form generated from reading UI file 'QWaveFilterDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWAVEFILTERDLG_H
#define UI_QWAVEFILTERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../common/customplot/QFreqLinesChart.h"

QT_BEGIN_NAMESPACE

class Ui_QWaveFilterDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *titleWgt;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_title;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QComboBox *comboBox;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *lineEdit_4;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_6;
    QLabel *label_10;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_20;
    QLineEdit *lineEdit_7;
    QLabel *label_6;
    QLabel *label_8;
    QWidget *page_3;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_9;
    QLabel *label_13;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_12;
    QLabel *label_11;
    QLineEdit *lineEdit_8;
    QLabel *label_9;
    QLineEdit *lineEdit_10;
    QWidget *page_4;
    QPushButton *pushButton_6;
    QWidget *page_5;
    QGridLayout *gridLayout_5;
    QLabel *label_21;
    QLineEdit *lineEdit_18;
    QLabel *label_22;
    QLineEdit *lineEdit_19;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *widget_3;
    QGridLayout *gridLayout_4;
    QLineEdit *lineEdit_15;
    QLabel *label_17;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_13;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_19;
    QLineEdit *lineEdit_12;
    QLabel *label_14;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_16;
    QLabel *label_18;
    QSpacerItem *verticalSpacer_6;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QFreqLinesChart *frChartWgt;
    QFreqLinesChart *phaseChartWgt;

    void setupUi(QDialog *QWaveFilterDlg)
    {
        if (QWaveFilterDlg->objectName().isEmpty())
            QWaveFilterDlg->setObjectName(QString::fromUtf8("QWaveFilterDlg"));
        QWaveFilterDlg->resize(1224, 872);
        QWaveFilterDlg->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(QWaveFilterDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleWgt = new QWidget(QWaveFilterDlg);
        titleWgt->setObjectName(QString::fromUtf8("titleWgt"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWgt->sizePolicy().hasHeightForWidth());
        titleWgt->setSizePolicy(sizePolicy);
        titleWgt->setMinimumSize(QSize(0, 70));
        horizontalLayout = new QHBoxLayout(titleWgt);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lab_title = new QLabel(titleWgt);
        lab_title->setObjectName(QString::fromUtf8("lab_title"));
        lab_title->setIndent(5);

        horizontalLayout->addWidget(lab_title);


        verticalLayout_2->addWidget(titleWgt);

        widget_5 = new QWidget(QWaveFilterDlg);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget = new QWidget(widget_5);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(comboBox);

        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, -1, 2, -1);
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 2);

        lineEdit_2 = new QLineEdit(page);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_2, 3, 1, 1, 1);

        lineEdit_3 = new QLineEdit(page);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_3, 4, 1, 1, 1);

        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(label, 1, 0, 1, 2);

        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(page);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_4, 5, 1, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, -1, 2, -1);
        lineEdit_6 = new QLineEdit(page_2);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(lineEdit_6, 3, 1, 1, 1);

        label_10 = new QLabel(page_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(label_10, 6, 0, 1, 1);

        lineEdit_17 = new QLineEdit(page_2);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        lineEdit_17->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(lineEdit_17, 7, 1, 1, 1);

        lineEdit_5 = new QLineEdit(page_2);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(lineEdit_5, 4, 1, 1, 1);

        label_7 = new QLabel(page_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 2);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_4, 1, 0, 1, 2);

        label_20 = new QLabel(page_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(label_20, 7, 0, 1, 1);

        lineEdit_7 = new QLineEdit(page_2);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(lineEdit_7, 6, 1, 1, 1);

        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        label_8 = new QLabel(page_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(label_8, 4, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_3 = new QGridLayout(page_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, -1, 0, -1);
        lineEdit_9 = new QLineEdit(page_3);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setMinimumSize(QSize(0, 25));

        gridLayout_3->addWidget(lineEdit_9, 3, 1, 1, 1);

        label_13 = new QLabel(page_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(label_13, 3, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_5, 0, 0, 1, 2);

        label_12 = new QLabel(page_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(label_12, 4, 0, 1, 1);

        label_11 = new QLabel(page_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(0, 30));

        gridLayout_3->addWidget(label_11, 1, 0, 1, 2);

        lineEdit_8 = new QLineEdit(page_3);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setMinimumSize(QSize(0, 25));

        gridLayout_3->addWidget(lineEdit_8, 2, 1, 1, 1);

        label_9 = new QLabel(page_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(label_9, 2, 0, 1, 1);

        lineEdit_10 = new QLineEdit(page_3);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setMinimumSize(QSize(0, 25));

        gridLayout_3->addWidget(lineEdit_10, 4, 1, 1, 1);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        pushButton_6 = new QPushButton(page_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(20, 80, 121, 30));
        pushButton_6->setMinimumSize(QSize(0, 30));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        gridLayout_5 = new QGridLayout(page_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_21 = new QLabel(page_5);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_5->addWidget(label_21, 0, 0, 1, 1);

        lineEdit_18 = new QLineEdit(page_5);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));
        lineEdit_18->setMinimumSize(QSize(0, 25));
        lineEdit_18->setReadOnly(false);

        gridLayout_5->addWidget(lineEdit_18, 0, 1, 1, 1);

        label_22 = new QLabel(page_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_5->addWidget(label_22, 2, 0, 1, 1);

        lineEdit_19 = new QLineEdit(page_5);
        lineEdit_19->setObjectName(QString::fromUtf8("lineEdit_19"));
        lineEdit_19->setMinimumSize(QSize(0, 25));
        lineEdit_19->setReadOnly(false);

        gridLayout_5->addWidget(lineEdit_19, 2, 1, 1, 1);

        pushButton_2 = new QPushButton(page_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 30));

        gridLayout_5->addWidget(pushButton_2, 1, 0, 1, 2);

        pushButton_3 = new QPushButton(page_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 30));

        gridLayout_5->addWidget(pushButton_3, 3, 0, 1, 2);

        stackedWidget->addWidget(page_5);

        verticalLayout_3->addWidget(stackedWidget);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(pushButton);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 30));

        verticalLayout_3->addWidget(pushButton_5);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_4 = new QGridLayout(widget_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lineEdit_15 = new QLineEdit(widget_3);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        lineEdit_15->setMinimumSize(QSize(0, 25));
        lineEdit_15->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_15, 4, 1, 1, 1);

        label_17 = new QLabel(widget_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_4->addWidget(label_17, 3, 0, 1, 1);

        lineEdit_14 = new QLineEdit(widget_3);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setMinimumSize(QSize(0, 25));
        lineEdit_14->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_14, 3, 1, 1, 1);

        lineEdit_13 = new QLineEdit(widget_3);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setMinimumSize(QSize(0, 25));
        lineEdit_13->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_13, 2, 1, 1, 1);

        label_15 = new QLabel(widget_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_4->addWidget(label_15, 1, 0, 1, 1);

        label_16 = new QLabel(widget_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_4->addWidget(label_16, 2, 0, 1, 1);

        label_19 = new QLabel(widget_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_4->addWidget(label_19, 5, 0, 1, 1);

        lineEdit_12 = new QLineEdit(widget_3);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setMinimumSize(QSize(0, 25));
        lineEdit_12->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_12, 1, 1, 1, 1);

        label_14 = new QLabel(widget_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_4->addWidget(label_14, 0, 0, 1, 1);

        lineEdit_11 = new QLineEdit(widget_3);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setMinimumSize(QSize(0, 25));
        lineEdit_11->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_11, 0, 1, 1, 1);

        lineEdit_16 = new QLineEdit(widget_3);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        lineEdit_16->setMinimumSize(QSize(0, 25));
        lineEdit_16->setReadOnly(true);

        gridLayout_4->addWidget(lineEdit_16, 5, 1, 1, 1);

        label_18 = new QLabel(widget_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_4->addWidget(label_18, 4, 0, 1, 1);


        verticalLayout_3->addWidget(widget_3);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);


        horizontalLayout_2->addWidget(widget);

        widget_2 = new QWidget(widget_5);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frChartWgt = new QFreqLinesChart(widget_2);
        frChartWgt->setObjectName(QString::fromUtf8("frChartWgt"));

        verticalLayout->addWidget(frChartWgt);

        phaseChartWgt = new QFreqLinesChart(widget_2);
        phaseChartWgt->setObjectName(QString::fromUtf8("phaseChartWgt"));

        verticalLayout->addWidget(phaseChartWgt);


        horizontalLayout_2->addWidget(widget_2);


        verticalLayout_2->addWidget(widget_5);


        retranslateUi(QWaveFilterDlg);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(QWaveFilterDlg);
    } // setupUi

    void retranslateUi(QDialog *QWaveFilterDlg)
    {
        QWaveFilterDlg->setWindowTitle(QCoreApplication::translate("QWaveFilterDlg", "QWaveFilterDlg", nullptr));
        lab_title->setText(QCoreApplication::translate("QWaveFilterDlg", "\346\273\244\346\263\242\345\231\250\347\244\272\346\204\217\345\233\276", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("QWaveFilterDlg", "BYPASS", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("QWaveFilterDlg", "PEAK", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("QWaveFilterDlg", "LOW SHELF", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("QWaveFilterDlg", "HIGH SHELF", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("QWaveFilterDlg", "LOW PASS", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("QWaveFilterDlg", "HIGH PASS", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("QWaveFilterDlg", "IIR", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("QWaveFilterDlg", "GAIN", nullptr));

        label_5->setText(QCoreApplication::translate("QWaveFilterDlg", "Gain", nullptr));
        label->setText(QCoreApplication::translate("QWaveFilterDlg", "\350\260\203\350\257\225\345\214\272", nullptr));
        label_3->setText(QCoreApplication::translate("QWaveFilterDlg", "Boost", nullptr));
        label_4->setText(QCoreApplication::translate("QWaveFilterDlg", "Q", nullptr));
        label_2->setText(QCoreApplication::translate("QWaveFilterDlg", "FreQ", nullptr));
        label_10->setText(QCoreApplication::translate("QWaveFilterDlg", "Slope", nullptr));
        label_7->setText(QCoreApplication::translate("QWaveFilterDlg", "\350\260\203\350\257\225\345\214\272", nullptr));
        label_20->setText(QCoreApplication::translate("QWaveFilterDlg", "Gain", nullptr));
        label_6->setText(QCoreApplication::translate("QWaveFilterDlg", "FreQ", nullptr));
        label_8->setText(QCoreApplication::translate("QWaveFilterDlg", "Boost", nullptr));
        label_13->setText(QCoreApplication::translate("QWaveFilterDlg", "Q", nullptr));
        label_12->setText(QCoreApplication::translate("QWaveFilterDlg", "Gain", nullptr));
        label_11->setText(QCoreApplication::translate("QWaveFilterDlg", "\350\260\203\350\257\225\345\214\272", nullptr));
        label_9->setText(QCoreApplication::translate("QWaveFilterDlg", "freq", nullptr));
        pushButton_6->setText(QCoreApplication::translate("QWaveFilterDlg", "\345\212\240\350\275\275IIR", nullptr));
        label_21->setText(QCoreApplication::translate("QWaveFilterDlg", "Gain_dB", nullptr));
        label_22->setText(QCoreApplication::translate("QWaveFilterDlg", "Gain_\347\272\277\346\200\247", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QWaveFilterDlg", "\350\256\276\347\275\256dB\345\200\274", nullptr));
        pushButton_3->setText(QCoreApplication::translate("QWaveFilterDlg", "\350\256\276\347\275\256\347\272\277\346\200\247\345\200\274", nullptr));
        pushButton->setText(QCoreApplication::translate("QWaveFilterDlg", "\346\230\276\347\244\272\346\263\242\345\275\242", nullptr));
        pushButton_4->setText(QCoreApplication::translate("QWaveFilterDlg", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
        pushButton_5->setText(QCoreApplication::translate("QWaveFilterDlg", "\346\225\260\346\215\256\345\217\246\345\255\230\344\270\272", nullptr));
        label_17->setText(QCoreApplication::translate("QWaveFilterDlg", "a0", nullptr));
        label_15->setText(QCoreApplication::translate("QWaveFilterDlg", "b1", nullptr));
        label_16->setText(QCoreApplication::translate("QWaveFilterDlg", "b2", nullptr));
        label_19->setText(QCoreApplication::translate("QWaveFilterDlg", "a2", nullptr));
        label_14->setText(QCoreApplication::translate("QWaveFilterDlg", "b0", nullptr));
        label_18->setText(QCoreApplication::translate("QWaveFilterDlg", "a1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWaveFilterDlg: public Ui_QWaveFilterDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWAVEFILTERDLG_H

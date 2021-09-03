/********************************************************************************
** Form generated from reading UI file 'QConfigAxisDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCONFIGAXISDLG_H
#define UI_QCONFIGAXISDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QConfigAxisDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *fr_doubleSpinBox_min_x;
    QDoubleSpinBox *fr_doubleSpinBox_min_y;
    QLabel *label;
    QDoubleSpinBox *fr_doubleSpinBox_max_x;
    QLabel *label_2;
    QDoubleSpinBox *fr_doubleSpinBox_max_y;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QDoubleSpinBox *phase_doubleSpinBox_min_y;
    QLabel *label_7;
    QDoubleSpinBox *phase_doubleSpinBox_min_x;
    QLabel *label_8;
    QLabel *label_3;
    QDoubleSpinBox *phase_doubleSpinBox_max_x;
    QLabel *label_4;
    QDoubleSpinBox *phase_doubleSpinBox_max_y;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *QConfigAxisDlg)
    {
        if (QConfigAxisDlg->objectName().isEmpty())
            QConfigAxisDlg->setObjectName(QString::fromUtf8("QConfigAxisDlg"));
        QConfigAxisDlg->resize(356, 252);
        verticalLayout = new QVBoxLayout(QConfigAxisDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(QConfigAxisDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        fr_doubleSpinBox_min_x = new QDoubleSpinBox(groupBox);
        fr_doubleSpinBox_min_x->setObjectName(QString::fromUtf8("fr_doubleSpinBox_min_x"));
        fr_doubleSpinBox_min_x->setMinimumSize(QSize(0, 25));
        fr_doubleSpinBox_min_x->setMaximum(20000.000000000000000);

        gridLayout->addWidget(fr_doubleSpinBox_min_x, 0, 1, 1, 1);

        fr_doubleSpinBox_min_y = new QDoubleSpinBox(groupBox);
        fr_doubleSpinBox_min_y->setObjectName(QString::fromUtf8("fr_doubleSpinBox_min_y"));
        fr_doubleSpinBox_min_y->setMinimumSize(QSize(0, 25));
        fr_doubleSpinBox_min_y->setMinimum(-100.000000000000000);
        fr_doubleSpinBox_min_y->setMaximum(20000.000000000000000);

        gridLayout->addWidget(fr_doubleSpinBox_min_y, 3, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 2, 1, 1);

        fr_doubleSpinBox_max_x = new QDoubleSpinBox(groupBox);
        fr_doubleSpinBox_max_x->setObjectName(QString::fromUtf8("fr_doubleSpinBox_max_x"));
        fr_doubleSpinBox_max_x->setMinimumSize(QSize(0, 25));
        fr_doubleSpinBox_max_x->setMaximum(10000000.000000000000000);

        gridLayout->addWidget(fr_doubleSpinBox_max_x, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 2, 1, 1);

        fr_doubleSpinBox_max_y = new QDoubleSpinBox(groupBox);
        fr_doubleSpinBox_max_y->setObjectName(QString::fromUtf8("fr_doubleSpinBox_max_y"));
        fr_doubleSpinBox_max_y->setMinimumSize(QSize(0, 25));
        fr_doubleSpinBox_max_y->setMaximum(10000000.000000000000000);

        gridLayout->addWidget(fr_doubleSpinBox_max_y, 3, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(QConfigAxisDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        phase_doubleSpinBox_min_y = new QDoubleSpinBox(groupBox_2);
        phase_doubleSpinBox_min_y->setObjectName(QString::fromUtf8("phase_doubleSpinBox_min_y"));
        phase_doubleSpinBox_min_y->setMinimumSize(QSize(0, 25));
        phase_doubleSpinBox_min_y->setMinimum(-180.000000000000000);
        phase_doubleSpinBox_min_y->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(phase_doubleSpinBox_min_y, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        phase_doubleSpinBox_min_x = new QDoubleSpinBox(groupBox_2);
        phase_doubleSpinBox_min_x->setObjectName(QString::fromUtf8("phase_doubleSpinBox_min_x"));
        phase_doubleSpinBox_min_x->setMinimumSize(QSize(0, 25));
        phase_doubleSpinBox_min_x->setMaximum(20000.000000000000000);

        gridLayout_2->addWidget(phase_doubleSpinBox_min_x, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        phase_doubleSpinBox_max_x = new QDoubleSpinBox(groupBox_2);
        phase_doubleSpinBox_max_x->setObjectName(QString::fromUtf8("phase_doubleSpinBox_max_x"));
        phase_doubleSpinBox_max_x->setMinimumSize(QSize(0, 25));
        phase_doubleSpinBox_max_x->setMaximum(10000000.000000000000000);

        gridLayout_2->addWidget(phase_doubleSpinBox_max_x, 0, 3, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 2, 1, 1);

        phase_doubleSpinBox_max_y = new QDoubleSpinBox(groupBox_2);
        phase_doubleSpinBox_max_y->setObjectName(QString::fromUtf8("phase_doubleSpinBox_max_y"));
        phase_doubleSpinBox_max_y->setMinimumSize(QSize(0, 25));
        phase_doubleSpinBox_max_y->setMinimum(-180.000000000000000);
        phase_doubleSpinBox_max_y->setMaximum(180.000000000000000);

        gridLayout_2->addWidget(phase_doubleSpinBox_max_y, 3, 3, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        widget = new QWidget(QConfigAxisDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(widget);


        retranslateUi(QConfigAxisDlg);

        QMetaObject::connectSlotsByName(QConfigAxisDlg);
    } // setupUi

    void retranslateUi(QDialog *QConfigAxisDlg)
    {
        QConfigAxisDlg->setWindowTitle(QCoreApplication::translate("QConfigAxisDlg", "\345\235\220\346\240\207\347\263\273\351\205\215\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("QConfigAxisDlg", "FR\345\235\220\346\240\207\347\263\273\351\205\215\347\275\256", nullptr));
        label_5->setText(QCoreApplication::translate("QConfigAxisDlg", "x\350\275\264\346\234\200\345\260\217\345\200\274", nullptr));
        label_6->setText(QCoreApplication::translate("QConfigAxisDlg", "y\350\275\264\346\234\200\345\260\217\345\200\274", nullptr));
        label->setText(QCoreApplication::translate("QConfigAxisDlg", "x\350\275\264\346\234\200\345\244\247\345\200\274", nullptr));
        label_2->setText(QCoreApplication::translate("QConfigAxisDlg", "y\350\275\264\346\234\200\345\244\247\345\200\274", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("QConfigAxisDlg", "PHASE\345\235\220\346\240\207\347\263\273\351\205\215\347\275\256", nullptr));
        label_7->setText(QCoreApplication::translate("QConfigAxisDlg", "x\350\275\264\346\234\200\345\260\217\345\200\274", nullptr));
        label_8->setText(QCoreApplication::translate("QConfigAxisDlg", "y\350\275\264\346\234\200\345\260\217\345\200\274", nullptr));
        label_3->setText(QCoreApplication::translate("QConfigAxisDlg", "x\350\275\264\346\234\200\345\244\247\345\200\274", nullptr));
        label_4->setText(QCoreApplication::translate("QConfigAxisDlg", "y\350\275\264\346\234\200\345\244\247\345\200\274", nullptr));
        pushButton->setText(QCoreApplication::translate("QConfigAxisDlg", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QConfigAxisDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QConfigAxisDlg: public Ui_QConfigAxisDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCONFIGAXISDLG_H

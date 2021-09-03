/********************************************************************************
** Form generated from reading UI file 'QConfAudioDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCONFAUDIODLG_H
#define UI_QCONFAUDIODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QConfAudioDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QComboBox *comboBox_3;
    QComboBox *comboBox_2;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *QConfAudioDlg)
    {
        if (QConfAudioDlg->objectName().isEmpty())
            QConfAudioDlg->setObjectName(QString::fromUtf8("QConfAudioDlg"));
        QConfAudioDlg->resize(381, 242);
        verticalLayout = new QVBoxLayout(QConfAudioDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(QConfAudioDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox_3 = new QComboBox(widget);
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox_3, 2, 1, 1, 2);

        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 2);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
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
        comboBox->setMinimumSize(QSize(0, 25));
        comboBox->setEditable(true);

        gridLayout->addWidget(comboBox, 0, 1, 1, 2);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 4, 2, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(31);
        spinBox->setValue(27);

        gridLayout->addWidget(spinBox, 3, 1, 1, 2);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMinimum(-30);
        spinBox_2->setMaximum(0);

        gridLayout->addWidget(spinBox_2, 4, 1, 1, 1);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(QConfAudioDlg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(widget_2);


        retranslateUi(QConfAudioDlg);

        comboBox_2->setCurrentIndex(1);
        comboBox->setCurrentIndex(10);


        QMetaObject::connectSlotsByName(QConfAudioDlg);
    } // setupUi

    void retranslateUi(QDialog *QConfAudioDlg)
    {
        QConfAudioDlg->setWindowTitle(QCoreApplication::translate("QConfAudioDlg", "\351\237\263\351\242\221\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("QConfAudioDlg", "16", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("QConfAudioDlg", "\345\215\225\345\243\260\351\201\223", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("QConfAudioDlg", "\347\253\213\344\275\223\345\243\260", nullptr));

        label_2->setText(QCoreApplication::translate("QConfAudioDlg", "\345\243\260\351\201\223:", nullptr));
        label_4->setText(QCoreApplication::translate("QConfAudioDlg", "\347\263\273\347\273\237\351\237\263\351\207\217", nullptr));
        label_3->setText(QCoreApplication::translate("QConfAudioDlg", "\344\275\215\346\267\261\345\272\246:", nullptr));
        label->setText(QCoreApplication::translate("QConfAudioDlg", "\351\207\207\346\240\267\347\216\207:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("QConfAudioDlg", "8000", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("QConfAudioDlg", "11025", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("QConfAudioDlg", "16000", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("QConfAudioDlg", "22050", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("QConfAudioDlg", "32000", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("QConfAudioDlg", "44100", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("QConfAudioDlg", "48000", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("QConfAudioDlg", "88200", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("QConfAudioDlg", "96000", nullptr));
        comboBox->setItemText(9, QCoreApplication::translate("QConfAudioDlg", "192000", nullptr));
        comboBox->setItemText(10, QCoreApplication::translate("QConfAudioDlg", "384000", nullptr));
        comboBox->setItemText(11, QCoreApplication::translate("QConfAudioDlg", "768000", nullptr));

        label_5->setText(QCoreApplication::translate("QConfAudioDlg", "dB", nullptr));
        label_6->setText(QCoreApplication::translate("QConfAudioDlg", "\347\263\273\347\273\237\347\263\273\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("QConfAudioDlg", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QConfAudioDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QConfAudioDlg: public Ui_QConfAudioDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCONFAUDIODLG_H

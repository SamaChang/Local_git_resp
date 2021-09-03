/********************************************************************************
** Form generated from reading UI file 'QConfLineColorDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCONFLINECOLORDLG_H
#define UI_QCONFLINECOLORDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QConfLineColorDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *labSerial;
    QLineEdit *edt_path_line_4;
    QToolButton *tbtn_save_line;
    QToolButton *tbtn_load_line_3;
    QToolButton *tbtn_color_line;
    QLabel *labSerial_6;
    QToolButton *tbtn_load_line_6;
    QToolButton *tbtn_color_line_2;
    QLineEdit *edt_name_line_2;
    QLabel *label_3;
    QToolButton *tbtn_color_line_6;
    QToolButton *tbtn_save_line_7;
    QLabel *labSerial_2;
    QToolButton *tbtn_load_line_4;
    QLineEdit *edt_name_line_6;
    QToolButton *tbtn_save_line_3;
    QLineEdit *edt_name_line_7;
    QLineEdit *edt_name_line_5;
    QToolButton *tbtn_save_line_5;
    QToolButton *tbtn_color_line_5;
    QLabel *labSerial_7;
    QToolButton *tbtn_color_line_4;
    QToolButton *tbtn_save_line_6;
    QLineEdit *edt_name_line_4;
    QToolButton *tbtn_load_line_5;
    QLineEdit *edt_name_line;
    QLabel *labSerial_5;
    QToolButton *tbtn_color_line_7;
    QLineEdit *edt_path_line_2;
    QLineEdit *edt_name_line_3;
    QToolButton *tbtn_load_line;
    QToolButton *tbtn_save_line_4;
    QLabel *label;
    QLineEdit *edt_path_line_6;
    QToolButton *tbtn_load_line_7;
    QToolButton *tbtn_color_line_3;
    QLabel *labSerial_3;
    QLineEdit *edt_path_line_3;
    QLineEdit *edt_path_line;
    QToolButton *tbtn_save_line_2;
    QLabel *label_4;
    QLabel *labSerial_4;
    QLineEdit *edt_path_line_7;
    QToolButton *tbtn_load_line_2;
    QLabel *label_2;
    QLineEdit *edt_path_line_5;
    QLabel *labSerial_8;
    QLineEdit *edt_name_line_8;
    QLineEdit *edt_path_line_8;
    QToolButton *tbtn_load_line_8;
    QToolButton *tbtn_save_line_8;
    QToolButton *tbtn_color_line_8;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *QConfLineColorDlg)
    {
        if (QConfLineColorDlg->objectName().isEmpty())
            QConfLineColorDlg->setObjectName(QString::fromUtf8("QConfLineColorDlg"));
        QConfLineColorDlg->resize(665, 348);
        verticalLayout = new QVBoxLayout(QConfLineColorDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(QConfLineColorDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labSerial = new QLabel(widget);
        labSerial->setObjectName(QString::fromUtf8("labSerial"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labSerial->sizePolicy().hasHeightForWidth());
        labSerial->setSizePolicy(sizePolicy);
        labSerial->setMinimumSize(QSize(30, 0));
        labSerial->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial, 1, 0, 1, 1);

        edt_path_line_4 = new QLineEdit(widget);
        edt_path_line_4->setObjectName(QString::fromUtf8("edt_path_line_4"));
        edt_path_line_4->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_4, 4, 2, 1, 1);

        tbtn_save_line = new QToolButton(widget);
        tbtn_save_line->setObjectName(QString::fromUtf8("tbtn_save_line"));
        tbtn_save_line->setEnabled(false);
        tbtn_save_line->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line, 1, 4, 1, 1);

        tbtn_load_line_3 = new QToolButton(widget);
        tbtn_load_line_3->setObjectName(QString::fromUtf8("tbtn_load_line_3"));
        tbtn_load_line_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_3, 3, 3, 1, 1);

        tbtn_color_line = new QToolButton(widget);
        tbtn_color_line->setObjectName(QString::fromUtf8("tbtn_color_line"));
        tbtn_color_line->setMinimumSize(QSize(0, 25));
        tbtn_color_line->setFocusPolicy(Qt::WheelFocus);
        tbtn_color_line->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line, 1, 5, 1, 1);

        labSerial_6 = new QLabel(widget);
        labSerial_6->setObjectName(QString::fromUtf8("labSerial_6"));
        sizePolicy.setHeightForWidth(labSerial_6->sizePolicy().hasHeightForWidth());
        labSerial_6->setSizePolicy(sizePolicy);
        labSerial_6->setMinimumSize(QSize(30, 0));
        labSerial_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_6, 6, 0, 1, 1);

        tbtn_load_line_6 = new QToolButton(widget);
        tbtn_load_line_6->setObjectName(QString::fromUtf8("tbtn_load_line_6"));
        tbtn_load_line_6->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_6, 6, 3, 1, 1);

        tbtn_color_line_2 = new QToolButton(widget);
        tbtn_color_line_2->setObjectName(QString::fromUtf8("tbtn_color_line_2"));
        tbtn_color_line_2->setMinimumSize(QSize(0, 25));
        tbtn_color_line_2->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_2, 2, 5, 1, 1);

        edt_name_line_2 = new QLineEdit(widget);
        edt_name_line_2->setObjectName(QString::fromUtf8("edt_name_line_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(edt_name_line_2->sizePolicy().hasHeightForWidth());
        edt_name_line_2->setSizePolicy(sizePolicy1);
        edt_name_line_2->setMinimumSize(QSize(80, 25));
        edt_name_line_2->setMaximumSize(QSize(80, 16777215));
        edt_name_line_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_2, 2, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        tbtn_color_line_6 = new QToolButton(widget);
        tbtn_color_line_6->setObjectName(QString::fromUtf8("tbtn_color_line_6"));
        tbtn_color_line_6->setMinimumSize(QSize(0, 25));
        tbtn_color_line_6->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_6, 6, 5, 1, 1);

        tbtn_save_line_7 = new QToolButton(widget);
        tbtn_save_line_7->setObjectName(QString::fromUtf8("tbtn_save_line_7"));
        tbtn_save_line_7->setEnabled(false);
        tbtn_save_line_7->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_7, 7, 4, 1, 1);

        labSerial_2 = new QLabel(widget);
        labSerial_2->setObjectName(QString::fromUtf8("labSerial_2"));
        sizePolicy.setHeightForWidth(labSerial_2->sizePolicy().hasHeightForWidth());
        labSerial_2->setSizePolicy(sizePolicy);
        labSerial_2->setMinimumSize(QSize(30, 0));
        labSerial_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_2, 2, 0, 1, 1);

        tbtn_load_line_4 = new QToolButton(widget);
        tbtn_load_line_4->setObjectName(QString::fromUtf8("tbtn_load_line_4"));
        tbtn_load_line_4->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_4, 4, 3, 1, 1);

        edt_name_line_6 = new QLineEdit(widget);
        edt_name_line_6->setObjectName(QString::fromUtf8("edt_name_line_6"));
        sizePolicy1.setHeightForWidth(edt_name_line_6->sizePolicy().hasHeightForWidth());
        edt_name_line_6->setSizePolicy(sizePolicy1);
        edt_name_line_6->setMinimumSize(QSize(80, 25));
        edt_name_line_6->setMaximumSize(QSize(80, 16777215));
        edt_name_line_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_6, 6, 1, 1, 1);

        tbtn_save_line_3 = new QToolButton(widget);
        tbtn_save_line_3->setObjectName(QString::fromUtf8("tbtn_save_line_3"));
        tbtn_save_line_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_3, 3, 4, 1, 1);

        edt_name_line_7 = new QLineEdit(widget);
        edt_name_line_7->setObjectName(QString::fromUtf8("edt_name_line_7"));
        sizePolicy1.setHeightForWidth(edt_name_line_7->sizePolicy().hasHeightForWidth());
        edt_name_line_7->setSizePolicy(sizePolicy1);
        edt_name_line_7->setMinimumSize(QSize(80, 25));
        edt_name_line_7->setMaximumSize(QSize(80, 16777215));
        edt_name_line_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_7, 7, 1, 1, 1);

        edt_name_line_5 = new QLineEdit(widget);
        edt_name_line_5->setObjectName(QString::fromUtf8("edt_name_line_5"));
        sizePolicy1.setHeightForWidth(edt_name_line_5->sizePolicy().hasHeightForWidth());
        edt_name_line_5->setSizePolicy(sizePolicy1);
        edt_name_line_5->setMinimumSize(QSize(80, 25));
        edt_name_line_5->setMaximumSize(QSize(80, 16777215));
        edt_name_line_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_5, 5, 1, 1, 1);

        tbtn_save_line_5 = new QToolButton(widget);
        tbtn_save_line_5->setObjectName(QString::fromUtf8("tbtn_save_line_5"));
        tbtn_save_line_5->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_5, 5, 4, 1, 1);

        tbtn_color_line_5 = new QToolButton(widget);
        tbtn_color_line_5->setObjectName(QString::fromUtf8("tbtn_color_line_5"));
        tbtn_color_line_5->setMinimumSize(QSize(0, 25));
        tbtn_color_line_5->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_5, 5, 5, 1, 1);

        labSerial_7 = new QLabel(widget);
        labSerial_7->setObjectName(QString::fromUtf8("labSerial_7"));
        sizePolicy.setHeightForWidth(labSerial_7->sizePolicy().hasHeightForWidth());
        labSerial_7->setSizePolicy(sizePolicy);
        labSerial_7->setMinimumSize(QSize(30, 0));
        labSerial_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_7, 7, 0, 1, 1);

        tbtn_color_line_4 = new QToolButton(widget);
        tbtn_color_line_4->setObjectName(QString::fromUtf8("tbtn_color_line_4"));
        tbtn_color_line_4->setMinimumSize(QSize(0, 25));
        tbtn_color_line_4->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_4, 4, 5, 1, 1);

        tbtn_save_line_6 = new QToolButton(widget);
        tbtn_save_line_6->setObjectName(QString::fromUtf8("tbtn_save_line_6"));
        tbtn_save_line_6->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_6, 6, 4, 1, 1);

        edt_name_line_4 = new QLineEdit(widget);
        edt_name_line_4->setObjectName(QString::fromUtf8("edt_name_line_4"));
        sizePolicy1.setHeightForWidth(edt_name_line_4->sizePolicy().hasHeightForWidth());
        edt_name_line_4->setSizePolicy(sizePolicy1);
        edt_name_line_4->setMinimumSize(QSize(80, 25));
        edt_name_line_4->setMaximumSize(QSize(80, 16777215));
        edt_name_line_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_4, 4, 1, 1, 1);

        tbtn_load_line_5 = new QToolButton(widget);
        tbtn_load_line_5->setObjectName(QString::fromUtf8("tbtn_load_line_5"));
        tbtn_load_line_5->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_5, 5, 3, 1, 1);

        edt_name_line = new QLineEdit(widget);
        edt_name_line->setObjectName(QString::fromUtf8("edt_name_line"));
        sizePolicy1.setHeightForWidth(edt_name_line->sizePolicy().hasHeightForWidth());
        edt_name_line->setSizePolicy(sizePolicy1);
        edt_name_line->setMinimumSize(QSize(80, 25));
        edt_name_line->setMaximumSize(QSize(80, 16777215));
        edt_name_line->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line, 1, 1, 1, 1);

        labSerial_5 = new QLabel(widget);
        labSerial_5->setObjectName(QString::fromUtf8("labSerial_5"));
        sizePolicy.setHeightForWidth(labSerial_5->sizePolicy().hasHeightForWidth());
        labSerial_5->setSizePolicy(sizePolicy);
        labSerial_5->setMinimumSize(QSize(30, 0));
        labSerial_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_5, 5, 0, 1, 1);

        tbtn_color_line_7 = new QToolButton(widget);
        tbtn_color_line_7->setObjectName(QString::fromUtf8("tbtn_color_line_7"));
        tbtn_color_line_7->setMinimumSize(QSize(0, 25));
        tbtn_color_line_7->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_7, 7, 5, 1, 1);

        edt_path_line_2 = new QLineEdit(widget);
        edt_path_line_2->setObjectName(QString::fromUtf8("edt_path_line_2"));
        edt_path_line_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_2, 2, 2, 1, 1);

        edt_name_line_3 = new QLineEdit(widget);
        edt_name_line_3->setObjectName(QString::fromUtf8("edt_name_line_3"));
        sizePolicy1.setHeightForWidth(edt_name_line_3->sizePolicy().hasHeightForWidth());
        edt_name_line_3->setSizePolicy(sizePolicy1);
        edt_name_line_3->setMinimumSize(QSize(80, 25));
        edt_name_line_3->setMaximumSize(QSize(80, 16777215));
        edt_name_line_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_3, 3, 1, 1, 1);

        tbtn_load_line = new QToolButton(widget);
        tbtn_load_line->setObjectName(QString::fromUtf8("tbtn_load_line"));
        tbtn_load_line->setEnabled(false);
        tbtn_load_line->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line, 1, 3, 1, 1);

        tbtn_save_line_4 = new QToolButton(widget);
        tbtn_save_line_4->setObjectName(QString::fromUtf8("tbtn_save_line_4"));
        tbtn_save_line_4->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_4, 4, 4, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        edt_path_line_6 = new QLineEdit(widget);
        edt_path_line_6->setObjectName(QString::fromUtf8("edt_path_line_6"));
        edt_path_line_6->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_6, 6, 2, 1, 1);

        tbtn_load_line_7 = new QToolButton(widget);
        tbtn_load_line_7->setObjectName(QString::fromUtf8("tbtn_load_line_7"));
        tbtn_load_line_7->setEnabled(false);
        tbtn_load_line_7->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_7, 7, 3, 1, 1);

        tbtn_color_line_3 = new QToolButton(widget);
        tbtn_color_line_3->setObjectName(QString::fromUtf8("tbtn_color_line_3"));
        tbtn_color_line_3->setMinimumSize(QSize(0, 25));
        tbtn_color_line_3->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_3, 3, 5, 1, 1);

        labSerial_3 = new QLabel(widget);
        labSerial_3->setObjectName(QString::fromUtf8("labSerial_3"));
        sizePolicy.setHeightForWidth(labSerial_3->sizePolicy().hasHeightForWidth());
        labSerial_3->setSizePolicy(sizePolicy);
        labSerial_3->setMinimumSize(QSize(30, 0));
        labSerial_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_3, 3, 0, 1, 1);

        edt_path_line_3 = new QLineEdit(widget);
        edt_path_line_3->setObjectName(QString::fromUtf8("edt_path_line_3"));
        edt_path_line_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_3, 3, 2, 1, 1);

        edt_path_line = new QLineEdit(widget);
        edt_path_line->setObjectName(QString::fromUtf8("edt_path_line"));
        edt_path_line->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line, 1, 2, 1, 1);

        tbtn_save_line_2 = new QToolButton(widget);
        tbtn_save_line_2->setObjectName(QString::fromUtf8("tbtn_save_line_2"));
        tbtn_save_line_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_2, 2, 4, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 3, 1, 3);

        labSerial_4 = new QLabel(widget);
        labSerial_4->setObjectName(QString::fromUtf8("labSerial_4"));
        sizePolicy.setHeightForWidth(labSerial_4->sizePolicy().hasHeightForWidth());
        labSerial_4->setSizePolicy(sizePolicy);
        labSerial_4->setMinimumSize(QSize(30, 0));
        labSerial_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_4, 4, 0, 1, 1);

        edt_path_line_7 = new QLineEdit(widget);
        edt_path_line_7->setObjectName(QString::fromUtf8("edt_path_line_7"));
        edt_path_line_7->setEnabled(false);
        edt_path_line_7->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_7, 7, 2, 1, 1);

        tbtn_load_line_2 = new QToolButton(widget);
        tbtn_load_line_2->setObjectName(QString::fromUtf8("tbtn_load_line_2"));
        tbtn_load_line_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_2, 2, 3, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        edt_path_line_5 = new QLineEdit(widget);
        edt_path_line_5->setObjectName(QString::fromUtf8("edt_path_line_5"));
        edt_path_line_5->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_5, 5, 2, 1, 1);

        labSerial_8 = new QLabel(widget);
        labSerial_8->setObjectName(QString::fromUtf8("labSerial_8"));
        sizePolicy.setHeightForWidth(labSerial_8->sizePolicy().hasHeightForWidth());
        labSerial_8->setSizePolicy(sizePolicy);
        labSerial_8->setMinimumSize(QSize(30, 0));
        labSerial_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labSerial_8, 8, 0, 1, 1);

        edt_name_line_8 = new QLineEdit(widget);
        edt_name_line_8->setObjectName(QString::fromUtf8("edt_name_line_8"));
        sizePolicy1.setHeightForWidth(edt_name_line_8->sizePolicy().hasHeightForWidth());
        edt_name_line_8->setSizePolicy(sizePolicy1);
        edt_name_line_8->setMinimumSize(QSize(80, 25));
        edt_name_line_8->setMaximumSize(QSize(80, 16777215));
        edt_name_line_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(edt_name_line_8, 8, 1, 1, 1);

        edt_path_line_8 = new QLineEdit(widget);
        edt_path_line_8->setObjectName(QString::fromUtf8("edt_path_line_8"));
        edt_path_line_8->setEnabled(false);
        edt_path_line_8->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(edt_path_line_8, 8, 2, 1, 1);

        tbtn_load_line_8 = new QToolButton(widget);
        tbtn_load_line_8->setObjectName(QString::fromUtf8("tbtn_load_line_8"));
        tbtn_load_line_8->setEnabled(false);
        tbtn_load_line_8->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_load_line_8, 8, 3, 1, 1);

        tbtn_save_line_8 = new QToolButton(widget);
        tbtn_save_line_8->setObjectName(QString::fromUtf8("tbtn_save_line_8"));
        tbtn_save_line_8->setEnabled(false);
        tbtn_save_line_8->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(tbtn_save_line_8, 8, 4, 1, 1);

        tbtn_color_line_8 = new QToolButton(widget);
        tbtn_color_line_8->setObjectName(QString::fromUtf8("tbtn_color_line_8"));
        tbtn_color_line_8->setMinimumSize(QSize(0, 25));
        tbtn_color_line_8->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(tbtn_color_line_8, 8, 5, 1, 1);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(QConfLineColorDlg);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(75, 28));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 28));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(75, 28));

        horizontalLayout->addWidget(pushButton_3);


        verticalLayout->addWidget(widget_2);


        retranslateUi(QConfLineColorDlg);

        QMetaObject::connectSlotsByName(QConfLineColorDlg);
    } // setupUi

    void retranslateUi(QDialog *QConfLineColorDlg)
    {
        QConfLineColorDlg->setWindowTitle(QCoreApplication::translate("QConfLineColorDlg", "\347\272\277\346\256\265\346\230\276\347\244\272\350\256\276\347\275\256", nullptr));
        labSerial->setText(QCoreApplication::translate("QConfLineColorDlg", "1", nullptr));
        tbtn_save_line->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        tbtn_load_line_3->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        tbtn_color_line->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        labSerial_6->setText(QCoreApplication::translate("QConfLineColorDlg", "6", nullptr));
        tbtn_load_line_6->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        tbtn_color_line_2->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        label_3->setText(QCoreApplication::translate("QConfLineColorDlg", "\350\267\257\345\276\204", nullptr));
        tbtn_color_line_6->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        tbtn_save_line_7->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        labSerial_2->setText(QCoreApplication::translate("QConfLineColorDlg", "2", nullptr));
        tbtn_load_line_4->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        tbtn_save_line_3->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        edt_name_line_7->setText(QCoreApplication::translate("QConfLineColorDlg", "FF\347\272\277", nullptr));
        tbtn_save_line_5->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        tbtn_color_line_5->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        labSerial_7->setText(QCoreApplication::translate("QConfLineColorDlg", "7", nullptr));
        tbtn_color_line_4->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        tbtn_save_line_6->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        tbtn_load_line_5->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        labSerial_5->setText(QCoreApplication::translate("QConfLineColorDlg", "5", nullptr));
        tbtn_color_line_7->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        tbtn_load_line->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        tbtn_save_line_4->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        label->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\272\217\345\217\267", nullptr));
        tbtn_load_line_7->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        tbtn_color_line_3->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        labSerial_3->setText(QCoreApplication::translate("QConfLineColorDlg", "3", nullptr));
        tbtn_save_line_2->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        label_4->setText(QCoreApplication::translate("QConfLineColorDlg", "\346\223\215\344\275\234", nullptr));
        labSerial_4->setText(QCoreApplication::translate("QConfLineColorDlg", "4", nullptr));
        tbtn_load_line_2->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        label_2->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\220\215\347\247\260", nullptr));
        labSerial_8->setText(QCoreApplication::translate("QConfLineColorDlg", "8", nullptr));
        edt_name_line_8->setText(QCoreApplication::translate("QConfLineColorDlg", "FB\347\272\277", nullptr));
        tbtn_load_line_8->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\212\240\350\275\275", nullptr));
        tbtn_save_line_8->setText(QCoreApplication::translate("QConfLineColorDlg", "\344\277\235\345\255\230", nullptr));
        tbtn_color_line_8->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\242\234\350\211\262", nullptr));
        pushButton->setText(QCoreApplication::translate("QConfLineColorDlg", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("QConfLineColorDlg", "\345\217\226\346\266\210", nullptr));
        pushButton_3->setText(QCoreApplication::translate("QConfLineColorDlg", "\351\273\230\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QConfLineColorDlg: public Ui_QConfLineColorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCONFLINECOLORDLG_H

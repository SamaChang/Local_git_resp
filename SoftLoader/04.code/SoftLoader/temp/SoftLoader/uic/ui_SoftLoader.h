/********************************************************************************
** Form generated from reading UI file 'SoftLoader.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOFTLOADER_H
#define UI_SOFTLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoftLoader
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWgt;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_title_icon;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lab_title;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *tbtn_help;
    QToolButton *tbtn_min;
    QToolButton *tbtn_normal;
    QToolButton *tbtn_close;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *mainPage;
    QWidget *pluginPage;

    void setupUi(QWidget *SoftLoader)
    {
        if (SoftLoader->objectName().isEmpty())
            SoftLoader->setObjectName(QString::fromUtf8("SoftLoader"));
        SoftLoader->resize(884, 538);
        SoftLoader->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(SoftLoader);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWgt = new QWidget(SoftLoader);
        titleWgt->setObjectName(QString::fromUtf8("titleWgt"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWgt->sizePolicy().hasHeightForWidth());
        titleWgt->setSizePolicy(sizePolicy);
        titleWgt->setMinimumSize(QSize(0, 60));
        titleWgt->setMaximumSize(QSize(16777215, 60));
        horizontalLayout = new QHBoxLayout(titleWgt);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(3, 0, 3, 0);
        lab_title_icon = new QLabel(titleWgt);
        lab_title_icon->setObjectName(QString::fromUtf8("lab_title_icon"));
        lab_title_icon->setMinimumSize(QSize(48, 48));
        lab_title_icon->setMaximumSize(QSize(48, 48));

        horizontalLayout->addWidget(lab_title_icon);

        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lab_title = new QLabel(titleWgt);
        lab_title->setObjectName(QString::fromUtf8("lab_title"));
        lab_title->setMinimumSize(QSize(200, 48));
        lab_title->setMaximumSize(QSize(16777215, 48));

        horizontalLayout->addWidget(lab_title);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tbtn_help = new QToolButton(titleWgt);
        tbtn_help->setObjectName(QString::fromUtf8("tbtn_help"));
        tbtn_help->setMinimumSize(QSize(25, 25));
        tbtn_help->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(tbtn_help);

        tbtn_min = new QToolButton(titleWgt);
        tbtn_min->setObjectName(QString::fromUtf8("tbtn_min"));
        tbtn_min->setMinimumSize(QSize(25, 25));
        tbtn_min->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(tbtn_min);

        tbtn_normal = new QToolButton(titleWgt);
        tbtn_normal->setObjectName(QString::fromUtf8("tbtn_normal"));
        tbtn_normal->setMinimumSize(QSize(25, 25));
        tbtn_normal->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(tbtn_normal);

        tbtn_close = new QToolButton(titleWgt);
        tbtn_close->setObjectName(QString::fromUtf8("tbtn_close"));
        tbtn_close->setMinimumSize(QSize(25, 25));
        tbtn_close->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(tbtn_close);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addWidget(titleWgt);

        stackedWidget = new QStackedWidget(SoftLoader);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        stackedWidget->addWidget(mainPage);
        pluginPage = new QWidget();
        pluginPage->setObjectName(QString::fromUtf8("pluginPage"));
        stackedWidget->addWidget(pluginPage);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(SoftLoader);

        QMetaObject::connectSlotsByName(SoftLoader);
    } // setupUi

    void retranslateUi(QWidget *SoftLoader)
    {
        SoftLoader->setWindowTitle(QCoreApplication::translate("SoftLoader", "SoftLoader", nullptr));
        lab_title_icon->setText(QString());
        lab_title->setText(QCoreApplication::translate("SoftLoader", "TX231\350\260\203\350\257\225\350\275\257\344\273\266", nullptr));
        tbtn_help->setText(QString());
        tbtn_min->setText(QString());
        tbtn_normal->setText(QString());
        tbtn_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SoftLoader: public Ui_SoftLoader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOFTLOADER_H

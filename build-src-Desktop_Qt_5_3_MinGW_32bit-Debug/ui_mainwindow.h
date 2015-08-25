/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *statusText;
    QLabel *label;
    QLabel *SNText;
    QLabel *label_2;
    QLabel *SNText_2;
    QPlainTextEdit *plainTextEdit_notice;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(714, 440);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setFocusPolicy(Qt::StrongFocus);
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        statusText = new QLabel(centralWidget);
        statusText->setObjectName(QStringLiteral("statusText"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusText->sizePolicy().hasHeightForWidth());
        statusText->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(72);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        statusText->setFont(font);
        statusText->setAutoFillBackground(false);
        statusText->setStyleSheet(QString::fromUtf8("font: 75 72pt \"\346\245\267\344\275\223\";"));
        statusText->setAlignment(Qt::AlignCenter);
        statusText->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout->addWidget(statusText, 0, 0, 2, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221,Microsoft Yahei,\351\273\221\344\275\223,STHeiti"));
        font1.setPointSize(48);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font-family:'\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft Yahei', '\351\273\221\344\275\223', STHeiti;\n"
"font-size:48pt;"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        SNText = new QLabel(centralWidget);
        SNText->setObjectName(QStringLiteral("SNText"));
        sizePolicy.setHeightForWidth(SNText->sizePolicy().hasHeightForWidth());
        SNText->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(60);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(9);
        SNText->setFont(font2);
        SNText->setStyleSheet(QString::fromUtf8("font: 75 60pt \"\351\273\221\344\275\223\";"));

        gridLayout->addWidget(SNText, 0, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("font-family:'\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft Yahei', '\351\273\221\344\275\223', STHeiti;\n"
"font-size:48pt;"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        SNText_2 = new QLabel(centralWidget);
        SNText_2->setObjectName(QStringLiteral("SNText_2"));
        sizePolicy.setHeightForWidth(SNText_2->sizePolicy().hasHeightForWidth());
        SNText_2->setSizePolicy(sizePolicy);
        SNText_2->setFont(font2);
        SNText_2->setStyleSheet(QString::fromUtf8("font: 75 60pt \"\351\273\221\344\275\223\";"));

        gridLayout->addWidget(SNText_2, 1, 2, 1, 1);

        plainTextEdit_notice = new QPlainTextEdit(centralWidget);
        plainTextEdit_notice->setObjectName(QStringLiteral("plainTextEdit_notice"));
        plainTextEdit_notice->setStyleSheet(QString::fromUtf8("font: 28pt \"\351\273\221\344\275\223\";"));
        plainTextEdit_notice->setReadOnly(true);

        gridLayout->addWidget(plainTextEdit_notice, 2, 0, 1, 3);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        statusText->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\346\235\241\347\240\201 1 :", 0));
        SNText->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "\346\235\241\347\240\201 2 :", 0));
        SNText_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

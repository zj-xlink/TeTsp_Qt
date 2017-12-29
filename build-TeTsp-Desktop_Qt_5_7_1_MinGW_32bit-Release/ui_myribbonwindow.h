/********************************************************************************
** Form generated from reading UI file 'myribbonwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYRIBBONWINDOW_H
#define UI_MYRIBBONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStatusBar>
#include "QtnRibbonBar.h"
#include "QtnRibbonGroup.h"
#include "QtnRibbonMainWindow.h"
#include "QtnRibbonPage.h"
#include "QtnRibbonStyle.h"

QT_BEGIN_NAMESPACE

class Ui_MyRibbonWindow
{
public:
    Qtitan::RibbonStyle *ribbonStyle;
    Qtitan::RibbonBar *ribbonBar;
    Qtitan::RibbonPage *homePage;
    Qtitan::RibbonGroup *ribbonGroupClipboard;
    QStatusBar *statusBar;

    void setupUi(Qtitan::RibbonMainWindow *MyRibbonWindow)
    {
        if (MyRibbonWindow->objectName().isEmpty())
            MyRibbonWindow->setObjectName(QStringLiteral("MyRibbonWindow"));
        MyRibbonWindow->resize(785, 509);
        ribbonStyle = new Qtitan::RibbonStyle(MyRibbonWindow);
        ribbonStyle->setObjectName(QStringLiteral("ribbonStyle"));
        MyRibbonWindow->setCentralWidget(ribbonStyle);
        ribbonBar = new Qtitan::RibbonBar(MyRibbonWindow);
        ribbonBar->setObjectName(QStringLiteral("ribbonBar"));
        ribbonBar->setGeometry(QRect(0, 0, 785, 26));
        homePage = new Qtitan::RibbonPage(ribbonBar);
        homePage->setObjectName(QStringLiteral("homePage"));
        homePage->setGeometry(QRect(0, 23, 785, 93));
        ribbonGroupClipboard = new Qtitan::RibbonGroup(homePage);
        ribbonGroupClipboard->setObjectName(QStringLiteral("ribbonGroupClipboard"));
        ribbonGroupClipboard->setGeometry(QRect(10, 0, 181, 91));
        MyRibbonWindow->setMenuBar(ribbonBar);
        statusBar = new QStatusBar(MyRibbonWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyRibbonWindow->setStatusBar(statusBar);

        retranslateUi(MyRibbonWindow);

        QMetaObject::connectSlotsByName(MyRibbonWindow);
    } // setupUi

    void retranslateUi(Qtitan::RibbonMainWindow *MyRibbonWindow)
    {
        MyRibbonWindow->setWindowTitle(QApplication::translate("MyRibbonWindow", "MyRibbonWindow", Q_NULLPTR));
        homePage->setWindowTitle(QString());
        homePage->setProperty("title", QVariant(QApplication::translate("MyRibbonWindow", "&File", Q_NULLPTR)));
        ribbonGroupClipboard->setProperty("title", QVariant(QApplication::translate("MyRibbonWindow", "&Home", Q_NULLPTR)));
    } // retranslateUi

};

namespace Ui {
    class MyRibbonWindow: public Ui_MyRibbonWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYRIBBONWINDOW_H

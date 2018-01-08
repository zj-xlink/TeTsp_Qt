#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenuBar>

#include "datainput_preeditdialog.h"
#include "datainput_datainputdialog.h"

#include "mainwindow.h"
#include "seismicplotwidget.h"
#include "seismicdata.h"

#define Font_Default        "System Default"
#define Font_Normal         "Normal"
#define Font_Large          "Large"
#define Font_ExLarge        "Extra Large"
#define DPI_100_percent     "DPI 100%"


/* MainWindow */
MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent)
    //: Qtitan::RibbonMainWindow(parent)
{
    // 设置样式
    //m_ribbonStyle = qobject_cast<Qtitan::RibbonStyle*>(qApp->style());
    //m_ribbonStyle->setTheme(OfficeStyle::Office2016White);
    // 设置默认字号
    m_defaultFont = 8;
    // 设置标题
    setWindowTitle(tr("TeTsp"));

    // 初始化工作面板，地震数据绘制Widget
    seismicPlot = new SeismicPlotWidget(this);
    setCentralWidget(seismicPlot);
    seismicPlot->hide();


    // 使能ribbon主题
    //ribbonBar()->setFrameThemeEnabled();
    //ribbonBar()->setTitleBarVisible(false);
    // 创建系统菜单
    //createMenuFile();
    createNonRibbonMenu();
    // 创建快速按钮
    //createQuickAccessBar();
    // 创建Ribbon按钮
    //createRibbon();
    // 创建状态栏
    //statusBar();

    //QAction* actionAbout = ribbonBar()->addAction(QIcon(":/res/about.png"), "About", Qt::ToolButtonIconOnly);
    //actionAbout->setToolTip(tr("Display program<br />information, version number and copyright"));
    //connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    // 创建样式选项
    //createOptions();

    // 添加Ribbon隐藏功能
    //m_actionRibbonMinimize = ribbonBar()->addAction(QIcon(":/res/ribbonMinimize.png"), "Minimize the Ribbon", Qt::ToolButtonIconOnly);
    //m_actionRibbonMinimize->setStatusTip(tr("Show only the tab names on the Ribbon"));
    //m_actionRibbonMinimize->setShortcut(tr("Ctrl+F1"));
    //connect(m_actionRibbonMinimize, SIGNAL(triggered()), this, SLOT(maximizeToggle()));
    //connect(ribbonBar(), SIGNAL(minimizationChanged(bool)), this, SLOT(minimizationChanged(bool)));


    // 设置窗口位置与大小
    QRect geom = QApplication::desktop()->availableGeometry();
    move(QPoint(200, 200));
    resize(2 * geom.width() / 3, 2 * geom.height() / 3);

}

MainWindow::~MainWindow()
{
}

/*void MainWindow::createMenuFile()
{
    QIcon iconLogo;
    iconLogo.addPixmap(QPixmap(":/res/qtitan.png"));
    iconLogo.addPixmap(QPixmap(":/res/qtitanlogo32x32.png"));
    if (QAction* actionFile = ribbonBar()->addSystemButton(iconLogo, tr("文件")))
    {
        actionFile->setToolTip(tr("Click here to see everything<br />you can do with your<br />document"));

        if (Qtitan::RibbonSystemPopupBar* popupBar = qobject_cast<Qtitan::RibbonSystemPopupBar*>(actionFile->menu()))
        {
            QAction* newFile = popupBar->addAction(QIcon(":/res/new.png"), tr("新建"));
            newFile->setShortcut(tr("Ctrl+N"));
            newFile->setStatusTip(tr("新建文档"));
            newFile->setToolTip(tr("新建"));
            newFile->setEnabled(false);

            QAction* openFile = popupBar->addAction(QIcon(":/res/open.png"), tr("打开..."));
            openFile->setShortcut(tr("Ctrl+O"));
            openFile->setToolTip(tr("打开"));
            openFile->setStatusTip(tr("打开存在的文件"));
            connect(openFile, SIGNAL(triggered()), this, SLOT(open()));

            QAction* saveFile = popupBar->addAction(QIcon(":/res/save.png"), tr("保存"));
            saveFile->setShortcut(tr("Ctrl+S"));
            saveFile->setToolTip(tr("保存"));
            saveFile->setStatusTip(tr("保存活动文件"));
            connect(saveFile, SIGNAL(triggered()), this, SLOT(save()));

            QAction* saveAsFile = popupBar->addAction(tr("另存为..."));
            saveAsFile->setToolTip(tr("另存为"));
            saveAsFile->setStatusTip(tr("用新名称命名活动文件"));
            connect(saveAsFile, SIGNAL(triggered()), this, SLOT(save()));

            popupBar->addSeparator();

            QAction* actionPrint = new QAction(QIcon(":/res/print.png"), tr("打印..."), this);
            actionPrint->setToolTip(tr("选择打印机, 打印分数, 配置打印选项"));

            QAction* actionPagePrint = new QAction(actionPrint->icon(), actionPrint->text(), this);
            popupBar->addAction(actionPagePrint);
            if (RibbonPageSystemPopup* pageSystemPopup = popupBar->addPageSystemPopup(tr("打印预览"), actionPagePrint, true))
            {
                connect(actionPagePrint, SIGNAL(triggered()), actionPrint, SIGNAL(triggered()));
                pageSystemPopup->setMinimumWidth(296);
                pageSystemPopup->addAction(actionPrint);

                QAction* actionPrintSetup = new QAction(QIcon(":/res/printSetup.png"), tr("打印设置"), this);
                actionPrintSetup->setToolTip(tr("更换打印机，配置打印选项"));

                pageSystemPopup->addAction(actionPrintSetup);

                QAction* actionPrintPreview = new QAction(QIcon(":/res/printPreview.png"), tr("打印预览..."), this);
                actionPrintPreview->setToolTip(tr("预览与修改"));
                pageSystemPopup->addAction(actionPrintPreview);
            }

            QAction* actionPrepare = popupBar->addAction(QIcon(":/res/prepare.png"), tr("准备"));
            popupBar->addAction(actionPrepare);

            QAction* actionSend = popupBar->addAction(QIcon(":/res/send.png"), tr("发送"));
            popupBar->addAction(actionSend);
            if (RibbonPageSystemPopup* pageSystemPopup = popupBar->addPageSystemPopup(tr("发送文档"), actionSend, false))
            {
                pageSystemPopup->setMinimumWidth(296);
                QAction* actionMail = pageSystemPopup->addAction(QIcon(":/res/mail.png"), tr("邮件"));
                actionMail->setToolTip(tr("发送至邮件"));
                pageSystemPopup->addAction(actionMail);

                QAction* actionIntenetFax = pageSystemPopup->addAction(QIcon(":/res/internetfix.png"), tr("网络传真"));
                actionIntenetFax->setToolTip(tr("发送传真"));
                pageSystemPopup->addAction(actionIntenetFax);
            }

            popupBar->addSeparator();

            QIcon iconClose;
            iconClose.addPixmap(QPixmap(":/res/close.png"));
            iconClose.addPixmap(QPixmap(":/res/smallclose.png"));
            QAction* actClose = popupBar->addAction(iconClose, tr("关闭"));
            actClose->setShortcut(tr("Ctrl+C"));
            actClose->setStatusTip(tr("退出"));
            connect(actClose, SIGNAL(triggered()), this, SLOT(close()));
            popupBar->addPopupBarAction(actClose, Qt::ToolButtonTextBesideIcon);

            QAction* option = new QAction(QPixmap(":/res/smalloption.png"), tr("选项"), this);
            popupBar->addPopupBarAction(option, Qt::ToolButtonTextBesideIcon);
            option->setEnabled(false);

            if (RibbonPageSystemRecentFileList* pageRecentFile = popupBar->addPageRecentFile(tr("最近文档")))
            {
                pageRecentFile->setSize(9);
                QStringList list;
                list.append("Document1.txt");
                list.append("Document2.txt");
                list.append("Document3.txt");
                list.append("Document4.txt");
                list.append("Document5.txt");
                list.append("Document6.txt");
                pageRecentFile->updateRecentFileActions(list);
            }
        }
    }
}

void MainWindow::createQuickAccessBar()
{
    if (Qtitan::RibbonQuickAccessBar* quickAccessBar = ribbonBar()->quickAccessBar())
    {
        QAction* action = quickAccessBar->actionCustomizeButton();
        action->setToolTip(tr("Customize Quick Access Bar"));

        QAction* smallButton = quickAccessBar->addAction(QIcon(":/res/smallNew.png"), tr("New"));
        smallButton->setToolTip(tr("Create a new document"));
        connect(smallButton, SIGNAL(triggered()), this, SLOT(pressButton()));
        quickAccessBar->setActionVisible(smallButton, false);

        smallButton = quickAccessBar->addAction(QIcon(":/res/smallOpen.png"), tr("Open"));
        smallButton->setToolTip(tr("Open an existing document"));
        connect(smallButton, SIGNAL(triggered()), this, SLOT(pressButton()));
        quickAccessBar->setActionVisible(smallButton, false);

        smallButton = quickAccessBar->addAction(QIcon(":/res/smallSave.png"), tr("Save"));
        smallButton->setToolTip(tr("Save the active document"));
        connect(smallButton, SIGNAL(triggered()), this, SLOT(pressButton()));

        smallButton = quickAccessBar->addAction(QIcon(":/res/smallUndo.png"), tr("&Undo"));
        smallButton->setShortcut(QKeySequence::Undo);
        smallButton->setEnabled(false);

        smallButton = quickAccessBar->addAction(QIcon(":/res/smallRedo.png"), tr("&Redo"));
        smallButton->setShortcut(QKeySequence::Redo);
        smallButton->setEnabled(false);

        ribbonBar()->showQuickAccess(true);
    }
}

void MainWindow::createRibbon()
{
    // 数据导入模块
    if (Qtitan::RibbonPage* pageDataInput = ribbonBar()->addPage(tr("数据导入")))
    {
        // 设置数据刷新组
        if (Qtitan::RibbonGroup* groupRefresh = pageDataInput->addGroup(tr("数据刷新")))
        {
            // 刷新数据
            QAction* actionRefresh = groupRefresh->addAction(QIcon(":/res/ribbon/datainput_refresh.png"), tr("刷新"),
                                                             Qt::ToolButtonFollowStyle);
            actionRefresh->setToolTip(tr(""));
            connect(actionRefresh,SIGNAL(triggered()), this, SLOT(dataInput_refresh()));

            groupRefresh->setEnabled(false);
        }

        // 设置数据管理
        if (Qtitan::RibbonGroup* groupDataManage = pageDataInput->addGroup(tr("数据管理")))
        {
            // 预编辑
            QAction* actionPreDeal = groupDataManage->addAction(QIcon(":/res/ribbon/datainput_preDeal.png"), tr("预编辑"),
                                                             Qt::ToolButtonFollowStyle);
            actionPreDeal->setToolTip(tr(""));
            connect(actionPreDeal,SIGNAL(triggered()),this,SLOT(dataInput_preDeal()));
            // 地震数据加载
            QAction* actionLoadData = groupDataManage->addAction(QIcon(":/res/ribbon/datainput_loadData.png"), tr("数据导入"),
                                                             Qt::ToolButtonFollowStyle);
            actionLoadData->setToolTip(tr(""));
            connect(actionLoadData,SIGNAL(triggered()),this,SLOT(dataInput_loadData()));

            groupDataManage->setEnabled(true);
        }

        // 设置观测系统
        if (Qtitan::RibbonGroup* groupObserver = pageDataInput->addGroup(tr("设置观测系统")))
        {
            // 刷新数据
            QAction* actionloadObserver = groupObserver->addAction(QIcon(":/res/ribbon/datainput_observer.png"), tr("观测系统"),
                                                             Qt::ToolButtonFollowStyle);
            actionloadObserver->setToolTip(tr(""));
            connect(actionloadObserver,SIGNAL(triggered()), this, SLOT(dataInput_setObserver()));

            groupObserver->setEnabled(true);
        }
    }


    // 预处理模块
    if (Qtitan::RibbonPage* pagePreDeal = ribbonBar()->addPage(tr("预处理")))
    {
        // 设置初至拾取
        if (Qtitan::RibbonGroup* groupfirstPickup = pagePreDeal->addGroup(tr("初至拾取")))
        {


            groupfirstPickup->setEnabled(false);
        }

        // 设置能量均衡
        if (Qtitan::RibbonGroup* groupPowerBalance = pagePreDeal->addGroup(tr("能量均衡")))
        {


            groupPowerBalance->setEnabled(true);
        }

        // 设置扩散补偿
        if (Qtitan::RibbonGroup* groupSpreadAmp = pagePreDeal->addGroup(tr("扩散补偿")))
        {


            groupSpreadAmp->setEnabled(true);
        }
    }


    m_defaultFont = ribbonBar()->font().pointSize();

    if (QToolButton* button = ribbonBar()->getSystemButton())
        button->setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void MainWindow::createOptions()
{
    Qtitan::RibbonStyle::Theme themeId = Qtitan::RibbonStyle::Office2007Blue;
    if (m_ribbonStyle)
        themeId = m_ribbonStyle->getTheme();

    QMenu* menu = ribbonBar()->addMenu(tr("Options"));
    QAction* actionStyle = menu->addAction(tr("Style"));

    QMenu* menuStyle = new QMenu(ribbonBar());
    QActionGroup* styleActions = new QActionGroup(this);

    QAction* actionBlue = menuStyle->addAction(tr("Office 2007 Blue"));
    actionBlue->setCheckable(true);
    actionBlue->setChecked(themeId == Qtitan::RibbonStyle::Office2007Blue);
    actionBlue->setObjectName("Office2007Blue");

    QAction* actionBlack = menuStyle->addAction(tr("Office 2007 Black"));
    actionBlack->setObjectName("Office2007Black");
    actionBlack->setCheckable(true);
    actionBlack->setChecked(themeId == Qtitan::RibbonStyle::Office2007Black);

    QAction* actionSilver = menuStyle->addAction(tr("Office 2007 Silver"));
    actionSilver->setObjectName("Office2007Silver");
    actionSilver->setCheckable(true);
    actionSilver->setChecked(themeId == Qtitan::RibbonStyle::Office2007Silver);

    QAction* actionAqua = menuStyle->addAction(tr("Office 2007 Aqua"));
    actionAqua->setObjectName("Office2007Aqua");
    actionAqua->setCheckable(true);
    actionAqua->setChecked(themeId == Qtitan::RibbonStyle::Office2007Aqua);

    menuStyle->addSeparator();

    QAction* actionScenic = menuStyle->addAction(tr("Windows 7 Scenic"));
    actionScenic->setObjectName("Windows7Scenic");
    actionScenic->setCheckable(true);
    actionScenic->setChecked(themeId == Qtitan::RibbonStyle::Windows7Scenic);

    menuStyle->addSeparator();

    QAction* action2010Blue = menuStyle->addAction(tr("Office 2010 Blue"));
    action2010Blue->setObjectName("Office2010Blue");
    action2010Blue->setCheckable(true);
    action2010Blue->setChecked(themeId == Qtitan::RibbonStyle::Office2010Blue);

    QAction* action2010Silver = menuStyle->addAction(tr("Office 2010 Silver"));
    action2010Silver->setObjectName("Office2010Silver");
    action2010Silver->setCheckable(true);
    action2010Silver->setChecked(themeId == Qtitan::RibbonStyle::Office2010Silver);

    QAction* action2010Black = menuStyle->addAction(tr("Office 2010 Black"));
    action2010Black->setObjectName("Office2010Black");
    action2010Black->setCheckable(true);
    action2010Black->setChecked(themeId == Qtitan::RibbonStyle::Office2010Black);

    menuStyle->addSeparator();

    QAction* action2016Colorful = menuStyle->addAction(tr("Office 2016 Colorful"));
    action2016Colorful->setObjectName("Office2016Colorful");
    action2016Colorful->setCheckable(true);
    action2016Colorful->setChecked(themeId == Qtitan::RibbonStyle::Office2016Colorful);

    QAction* action2016White = menuStyle->addAction(tr("Office 2016 White"));
    action2016White->setObjectName("Office2016White");
    action2016White->setCheckable(true);
    action2016White->setChecked(themeId == Qtitan::RibbonStyle::Office2016White);

    QAction* action2016DarkGray = menuStyle->addAction(tr("Office 2016 Dark Gray"));
    action2016DarkGray->setObjectName("Office2016DarkGray");
    action2016DarkGray->setCheckable(true);
    action2016DarkGray->setChecked(themeId == Qtitan::RibbonStyle::Office2016DarkGray);

    QAction* action2016Black = menuStyle->addAction(tr("Office 2016 Black"));
    action2016Black->setObjectName("Office2016Black");
    action2016Black->setCheckable(true);
    action2016Black->setChecked(themeId == Qtitan::RibbonStyle::Office2016Black);

    styleActions->addAction(actionBlue);
    styleActions->addAction(actionBlack);
    styleActions->addAction(actionSilver);
    styleActions->addAction(actionAqua);
    styleActions->addAction(actionScenic);
    styleActions->addAction(action2010Blue);
    styleActions->addAction(action2010Silver);
    styleActions->addAction(action2010Black);
    styleActions->addAction(action2016Colorful);
    styleActions->addAction(action2016White);
    styleActions->addAction(action2016DarkGray);
    styleActions->addAction(action2016Black);

    actionStyle->setMenu(menuStyle);
    connect(styleActions, SIGNAL(triggered(QAction*)), this, SLOT(optionsTheme(QAction*)));


    QAction* actionMenu = menu->addAction(tr("Font"));

    QMenu* menuFont = new QMenu(ribbonBar());
    QActionGroup* fontActions = new QActionGroup(this);

    m_actionDefault = menuFont->addAction(Font_Default);
    m_actionDefault->setCheckable(true);
    m_actionDefault->setChecked(true);
    m_actionDefault->setObjectName(Font_Default);
    fontActions->addAction(m_actionDefault);

    menuFont->addSeparator();

    m_actionNormal = menuFont->addAction(Font_Normal);
    m_actionNormal->setCheckable(true);
    m_actionNormal->setObjectName(Font_Normal);
    fontActions->addAction(m_actionNormal);

    m_actionLarge = menuFont->addAction(Font_Large);
    m_actionLarge->setCheckable(true);
    m_actionLarge->setObjectName(Font_Large);
    fontActions->addAction(m_actionLarge);

    m_actionExLarge = menuFont->addAction(Font_ExLarge);
    m_actionExLarge->setCheckable(true);
    m_actionExLarge->setObjectName(Font_ExLarge);
    fontActions->addAction(m_actionExLarge);
    actionMenu->setMenu(menuFont);
    connect(fontActions, SIGNAL(triggered(QAction*)), this, SLOT(optionsFont(QAction*)));

    menuFont->addSeparator();
    QAction* actionDPI_100_percent = menuFont->addAction(tr("DPI Aware (new)"));
    actionDPI_100_percent->setObjectName(DPI_100_percent);
    actionDPI_100_percent->setCheckable(true);
    actionDPI_100_percent->setChecked(true);
    connect(actionDPI_100_percent, SIGNAL(toggled(bool)), this, SLOT(setDPIToggled(bool)));

    menu->addSeparator();
    QAction* actionCusomize = menu->addAction(tr("Cusomize..."));
    actionCusomize->setEnabled(false);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"));
    if (!fileName.isEmpty()) 
    {
        statusBar()->showMessage(tr("File loaded"), 2000);
    }
}

bool MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),tr("Document"), QLatin1Char('*') + QLatin1String(".txt"));
    if (!fileName.isEmpty())
    {
        statusBar()->showMessage(tr("File saved"), 2000);
        return true;
    }
    return false;
}

void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted)
    {
    }
}

void MainWindow::printSetup()
{
}

void MainWindow::about()
{
    Qtitan::AboutDialog::show(this, tr("About Qtitan Ribbon System Menu Sample"), tr("QtitanRibbon"), QLatin1String(QTN_VERSION_RIBBON_STR));
}

void MainWindow::optionsTheme(QAction* action)
{
    if (m_ribbonStyle)
    {
        Qtitan::RibbonStyle::Theme themeId = Qtitan::RibbonStyle::Office2007Blue;
        if (action->objectName() == "Office2007Black")
            themeId = Qtitan::RibbonStyle::Office2007Black;
        else if (action->objectName() == "Office2007Silver")
            themeId = Qtitan::RibbonStyle::Office2007Silver;
        else if (action->objectName() == "Office2007Aqua")
            themeId = Qtitan::RibbonStyle::Office2007Aqua;
        else if (action->objectName() == "Windows7Scenic")
            themeId = Qtitan::OfficeStyle::Windows7Scenic;
        else if (action->objectName() == "Office2010Blue")
            themeId = Qtitan::OfficeStyle::Office2010Blue;
        else if (action->objectName() == "Office2010Silver")
            themeId = Qtitan::OfficeStyle::Office2010Silver;
        else if (action->objectName() == "Office2010Black")
            themeId = Qtitan::OfficeStyle::Office2010Black;
        else if (action->objectName() == "Office2016Colorful")
            themeId = Qtitan::OfficeStyle::Office2016White;
        else if (action->objectName() == "Office2016White")
            themeId = Qtitan::OfficeStyle::Office2016White;
        else if (action->objectName() == "Office2016DarkGray")
            themeId = Qtitan::OfficeStyle::Office2016DarkGray;
        else if (action->objectName() == "Office2016Black")
            themeId = Qtitan::OfficeStyle::Office2016Black;

        if (QToolButton* button = ribbonBar()->getSystemButton())
        {
            if (themeId == Qtitan::OfficeStyle::Windows7Scenic     || 
                themeId == Qtitan::OfficeStyle::Office2010Blue     ||
                themeId == Qtitan::OfficeStyle::Office2010Silver   ||
                themeId == Qtitan::OfficeStyle::Office2010Black    ||
                themeId == Qtitan::OfficeStyle::Office2016Colorful ||
                themeId == Qtitan::OfficeStyle::Office2016White    ||
                themeId == Qtitan::OfficeStyle::Office2016DarkGray ||
                themeId == Qtitan::OfficeStyle::Office2016Black)
                button->setToolButtonStyle(Qt::ToolButtonTextOnly);
            else
                button->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        }

        m_ribbonStyle->setTheme(themeId);
        m_actionDefault->setChecked(true);
    }
    // 设置绘图主窗口背景色
    seismicPlot->setBgColor(this);

}

void MainWindow::pressButton()
{
    QMessageBox messageBox(QMessageBox::Information, windowTitle(), 
        QLatin1String(""), QMessageBox::Ok, this);
    messageBox.setInformativeText(QLatin1String("Press button."));
    messageBox.exec();
}

void MainWindow::maximizeToggle()
{
    ribbonBar()->setMinimized(!ribbonBar()->isMinimized());
}

void MainWindow::minimizationChanged(bool minimized)
{
    m_actionRibbonMinimize->setChecked(minimized);
    m_actionRibbonMinimize->setIcon(minimized ? QIcon(":/res/ribbonMaximize.png") :  QIcon(":/res/ribbonMinimize.png"));
}

void MainWindow::optionsFont(QAction* act)
{
    QFont fnt = ribbonBar()->font();

    if (Font_Default == act->objectName())
        fnt.setPointSize(m_defaultFont);
    else if (Font_Normal == act->objectName())
        fnt.setPointSize(8);
    else if (Font_Large == act->objectName())
        fnt.setPointSize(11);
    else if (Font_ExLarge == act->objectName())
        fnt.setPointSize(13);

    ribbonBar()->setFont(fnt);
}

void MainWindow::setDPIToggled(bool on)
{
    m_actionDefault->setEnabled(on);
    m_actionNormal->setEnabled(on);
    m_actionLarge->setEnabled(on);
    m_actionExLarge->setEnabled(on);
    m_ribbonStyle->setDPIAware(on);
}
*/

/*** 数据导入槽函数 ***/
void MainWindow::dataInput_refresh()  // 数据刷新
{

}
void MainWindow::dataInput_preDeal()  // 数据预处理
{
    DataInput_PreEditDialog dlg;
    if(dlg.exec() == QDialog::Accepted){

    }
}
void MainWindow::dataInput_loadData() // 导入数据
{
    DataInput_DataInputDialog dlg;
    if(dlg.exec() == QDialog::Rejected){
        if(dlg.isLoadFlag){
            m_data_SX = new SeismicData(this,dlg.segyFileMain.at(0));
            m_data_SY = new SeismicData(this,dlg.segyFileMain.at(1));
            m_data_SZ = new SeismicData(this,dlg.segyFileMain.at(2));
            seismicPlot->initialSeismicData(m_data_SX,m_data_SY,m_data_SZ);
            seismicPlot->plotAllCustomPlot();
            seismicPlot->setBgColor(this);
            seismicPlot->show();
        }
    }


}
void MainWindow::dataInput_setObserver() // 设置观测系统
{

}

void MainWindow::createNonRibbonMenu()
{
    QMenu* dataInput = menuBar()->addMenu(tr("  预处理  "));

    QAction* dataInput_preDeal =  dataInput->addAction(QIcon(":/res/ribbon/datainput_preDeal.png"), tr("数据转换"));
    dataInput_preDeal->setShortcut(tr("Ctrl+N"));
    connect(dataInput_preDeal,SIGNAL(triggered()),this,SLOT(dataInput_preDeal()));

    QAction* dataInput_loadData =  dataInput->addAction(QIcon(":/res/ribbon/datainput_loadData.png"), tr("数据转换"));
    dataInput_loadData->setShortcut(tr("Ctrl+N"));
    connect(dataInput_loadData,SIGNAL(triggered()),this,SLOT(dataInput_loadData()));

    QAction* dataInput_observer =  dataInput->addAction(QIcon(":/res/ribbon/datainput_observer.png"), tr("数据转换"));
    dataInput_observer->setShortcut(tr("Ctrl+N"));
    connect(dataInput_observer,SIGNAL(triggered()),this,SLOT(dataInput_setObserver()));
}

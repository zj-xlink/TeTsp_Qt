#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QtitanRibbon.h>
#include "tetsp.h"


namespace Qtitan 
{ 
    class WidgetGalleryItems; 
    class OfficeWidgetGallery;
}

class SeismicPlotWidget;
class SeismicData;

/* MainWindow */
class MainWindow : public Qtitan::RibbonMainWindow
{
  Q_OBJECT
public:
    MainWindow(QWidget* parent = Q_NULL);
    virtual ~MainWindow();



private:
    void createMenuFile();
    void createQuickAccessBar();
    void createRibbon();
    void createStatusBar();
    void createOptions();

protected Q_SLOTS:
    void open();
    bool save();

    void print();
    void printSetup();
    void about();
    void optionsTheme(QAction*);
    void pressButton();
    void maximizeToggle();
    void minimizationChanged(bool minimized);
    void optionsFont(QAction* act);
    void setDPIToggled(bool);
    //数据导入
    void dataInput_refresh();  // 数据刷新
    void dataInput_preDeal();  // 数据预处理
    void dataInput_loadData(); // 导入数据
    void dataInput_setObserver(); // 设置观测系统

private:
    QAction* m_actionRibbonMinimize;
    QAction* m_actionDefault;
    QAction* m_actionNormal;
    QAction* m_actionLarge;
    QAction* m_actionExLarge;

    int m_defaultFont;

    Qtitan::RibbonStyle* m_ribbonStyle;

public:
    // 绘制地震数据主界面
    SeismicPlotWidget *seismicPlot;

    // 地震原始数据
    SeismicData *m_data_SX;
    SeismicData *m_data_SY;
    SeismicData *m_data_SZ;

};

#endif // MAINWINDOW_H

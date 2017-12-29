#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "datainput_preeditdialog.h"
#include "datainput_datainputdialog.h"
#include "datainput_setobserverdialog.h"
#include "segyfile.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *main = new QWidget(this);

    // 数据预编辑
    QPushButton *button_predeal = new QPushButton(tr("数据预编辑"),this);
    connect(button_predeal,SIGNAL(clicked()),this,SLOT(openRead()));
    // 导入数据
    QPushButton *button_datainput = new QPushButton(tr("导入数据"),this);
    connect(button_datainput,SIGNAL(clicked()),this,SLOT(loadData()));
    // 观测系统
    QPushButton *button_observer = new QPushButton(tr("设置观测系统"),this);
    connect(button_observer,SIGNAL(clicked()),this,SLOT(setObserver()));

    setCentralWidget(main);

    QVBoxLayout *layout = new QVBoxLayout(main);
    layout->addWidget(button_predeal);
    layout->addWidget(button_datainput);
    layout->addWidget(button_observer);

}

MainWindow::~MainWindow()
{

}

void MainWindow::openRead()
{
    DataInput_PreEditDialog dlg;
    if(dlg.exec() == QDialog::Accepted){
    }
}

void MainWindow::loadData()
{
    DataInput_DataInputDialog dlg;
    if(dlg.exec() == QDialog::Rejected){

    }
}

void MainWindow::setObserver()
{
    DataInput_SetObserverDialog dlg;
    if(dlg.exec()){

    }
}

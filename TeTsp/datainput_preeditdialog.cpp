#include <QMessageBox>
#include <QFileDialog>

#include "datainput_preeditdialog.h"
#include "ui_datainput_preeditdialog.h"
#include "seg2stosegys.h"

DataInput_PreEditDialog::DataInput_PreEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataInput_PreEditDialog)
{
    ui->setupUi(this);
    // 隐藏标题栏
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

}

DataInput_PreEditDialog::~DataInput_PreEditDialog()
{
    delete ui;
}

// 加载Seg2文件，渲染显示信息
void DataInput_PreEditDialog::on_pB_loadData_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Select Seg2 File"),tr("."),
                                 tr("Segy(*.segy *.sgy *.dat)"));

    if(!fileNames.isEmpty()){
        // 获取Seg2文件
        seg2FileNames = fileNames;

        // 设置Table显示
        setTableWidget();

        // 显示输出文件夹
        ui->tE_outputDir->clear();
        outputDir = seg2FileNames.at(0);
        outputDir = outputDir.mid(0,outputDir.lastIndexOf(tr("/")));
        ui->tE_outputDir->setText(outputDir);

        // 显示炮点个数
        ui->lE_spotNums->clear();
        spotNums = seg2FileNames.size();
        ui->lE_spotNums->setText(tr("%1").arg(spotNums));

        // 显示检波点数

        // 显示是否翻转
        isReversed = false;

    }
}

// 设置文件显示表
void DataInput_PreEditDialog::setTableWidget()
{
    //清空配置头
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(seg2FileNames.size());
    // 禁止编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置头显示模式
    QStringList list;
    list << "序号" << "文件名";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->hide();

    // 插入条目
    QString name;
    int index;
    int i=0;
    foreach(QString dir, seg2FileNames){
        index = dir.lastIndexOf(tr("/"));
        name = dir.mid(index+1);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString("%1").arg(i+1)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(name));
        i++;
    }
    ui->tableWidget->show();

    ui->tableWidget->setStyleSheet(QString("QTableView{  \
                                           border:none; \
                                           background:white; \
                                   } \
                                   QTableView::item:selected{ \
                                           color:white; \
                                           background:rgb(130, 130, 130);    \
                                   }"));
}

// OK按钮事件，执行格式转换
void DataInput_PreEditDialog::on_buttonBox_accepted()
{
    if(!seg2FileNames.isEmpty()){
        sts = new Seg2sToSegys(this);

        sts->setSeg2FileNames(seg2FileNames);

        sts->loadSeg2Files();
        sts->saveAsSegys(tr("XYZ"));
        QMessageBox::information(this,tr("数据导入"),tr("加载数据完成"));
    }
}

// 设置是否翻转
void DataInput_PreEditDialog::on_cB_isReversed_clicked(bool checked)
{
    isReversed = checked;

    QStringList temp;
    foreach(QString str, seg2FileNames){
        temp.push_front(str);
    }

    seg2FileNames = temp;
    setTableWidget();

}

// 置顶按钮事件
void DataInput_PreEditDialog::on_pB_top_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row >=0){
        QString temp = seg2FileNames.at(row);
        seg2FileNames.removeAt(row);
        seg2FileNames.insert(0,temp);
        setTableWidget();
        ui->tableWidget->setCurrentCell(0,1);
    }

}

// 置底按钮事件
void DataInput_PreEditDialog::on_pB_bottom_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row >=0){
        QString temp = seg2FileNames.at(row);
        seg2FileNames.removeAt(row);
        seg2FileNames.append(temp);
        setTableWidget();
        ui->tableWidget->setCurrentCell(seg2FileNames.size()-1,1);
    }
}

// 上移按钮事件
void DataInput_PreEditDialog::on_pB_up_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row > 0){
        QString temp = seg2FileNames.at(row);
        seg2FileNames.removeAt(row);
        seg2FileNames.insert(row-1,temp);
        setTableWidget();
        ui->tableWidget->setCurrentCell(row-1,1);
    }
}

// 下移按钮事件
void DataInput_PreEditDialog::on_pb_down_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row >= 0 && row < seg2FileNames.size()-1){
        QString temp = seg2FileNames.at(row);
        seg2FileNames.removeAt(row);
        seg2FileNames.insert(row+1,temp);
        setTableWidget();
        ui->tableWidget->setCurrentCell(row+1,1);

    }
}

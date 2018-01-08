#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

#include "datainput_datainputdialog.h"
#include "ui_datainput_datainputdialog.h"
#include "segyfile.h"

DataInput_DataInputDialog::DataInput_DataInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataInput_DataInputDialog),
    isLoadFlag(0)
{
    ui->setupUi(this);
}

DataInput_DataInputDialog::~DataInput_DataInputDialog()
{
    delete ui;
}

// 主侧X分量数据导入
void DataInput_DataInputDialog::on_pb_main_x_clicked()
{
    fileName_MainX = QFileDialog::getOpenFileName(this,tr("数据导入"),tr(""),tr("Segy (*.segy *.sgy);;All (*.*)"));
    ui->lE_main_x->setText(fileName_MainX);
    if(segyFileMain.size()<1){
        segyFileMain.insert(0,new SegyFile(fileName_MainX,this));
    }else{
        segyFileMain.at(0)->setFileName(fileName_MainX);
    }

}

// 主侧Y分量数据导入
void DataInput_DataInputDialog::on_pb_main_y_clicked()
{
    fileName_MainY = QFileDialog::getOpenFileName(this,tr("数据导入"),tr(""),tr("Segy (*.segy *.sgy);;All (*.*)"));
    ui->lE_main_y->setText(fileName_MainY);
    if(segyFileMain.size()<2){
        segyFileMain.insert(1,new SegyFile(fileName_MainY,this));
    }else{
        segyFileMain.at(1)->setFileName(fileName_MainY);
    }
}

// 主侧Z分量数据导入
void DataInput_DataInputDialog::on_pb_main_z_clicked()
{
    fileName_MainZ = QFileDialog::getOpenFileName(this,tr("数据导入"),tr(""),tr("Segy (*.segy *.sgy);;All (*.*)"));
    ui->lE_main_z->setText(fileName_MainZ);
    if(segyFileMain.size()<3){
        segyFileMain.insert(2,new SegyFile(fileName_MainZ,this));
    }else{
        segyFileMain.at(2)->setFileName(fileName_MainZ);
    }
}

void DataInput_DataInputDialog::on_buttonBox_accepted()
{
    QDialog::accept();
}

void DataInput_DataInputDialog::on_buttonBox_rejected()
{
    QDialog::reject();
}

// 导入数据
void DataInput_DataInputDialog::on_pB_ok_clicked()
{
    // 判断是否选择文件
    if(segyFileMain.size()<3){
        QMessageBox::information(this,tr("导入数据"),tr("请选择个分量数据"));
        return;
    }

    // 主侧数据
    if(!segyFileMain.at(0)->readAll()){
        QMessageBox::information(this,tr("导入数据"),tr("主侧X分量数据错误"));
        return;
    }
    if(!segyFileMain.at(1)->readAll()){
        QMessageBox::information(this,tr("导入数据"),tr("主侧Y分量数据错误"));
        return;
    }
    if(!segyFileMain.at(2)->readAll()){
        QMessageBox::information(this,tr("导入数据"),tr("主侧Z分量数据错误"));
        return;
    }
    QMessageBox::information(this,tr("导入数据"),tr("导入数据成功"));


    // 设置数据信息
    ui->lE_origin_spotnums->setText(tr("%1").arg(segyFileMain.at(0)->tapehead.tChannelNums));
    ui->lE_origin_samplenums->setText(tr("%1").arg(segyFileMain.at(0)->tapehead.tSampleNums));

    ui->lE_origin_sampletime->setText((tr("%1us").arg(segyFileMain.at(0)->tapehead.tSampleTime)));

    ui->lE_extract_sampletime->setText((tr("%1us").arg(segyFileMain.at(0)->tapehead.tSampleTime)));
    ui->lE_extract_samplenums->setText(tr("%1").arg(segyFileMain.at(0)->tapehead.tSampleNums));
    ui->lE_extract_sumtime->setText(tr("%1s").arg(segyFileMain.at(0)->tapehead.tSampleTime*
                                                 segyFileMain.at(0)->tapehead.tSampleNums/1000000.0,0,'g',4));


    isLoadFlag = true;
}

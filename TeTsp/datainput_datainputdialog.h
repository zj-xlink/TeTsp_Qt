#ifndef DATAINPUT_DATAINPUTDIALOG_H
#define DATAINPUT_DATAINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class DataInput_DataInputDialog;
}

class SegyFile;

class DataInput_DataInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataInput_DataInputDialog(QWidget *parent = 0);
    ~DataInput_DataInputDialog();

private slots:
    void on_pb_main_x_clicked();

    void on_pb_main_y_clicked();

    void on_pb_main_z_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pB_ok_clicked();

private:
    Ui::DataInput_DataInputDialog *ui;

    // 各分量数据文件名
    QString fileName_MainX;
    QString fileName_MainY;
    QString fileName_MainZ;
    QString fileName_SideX;
    QString fileName_SideY;
    QString fileName_SideZ;

public:
    // 数据文件
    bool isLoadFlag;
    QList<SegyFile*> segyFileMain;
    QList<SegyFile*> segyFileSide;

};

#endif // DATAINPUT_DATAINPUTDIALOG_H

#ifndef DATAINPUT_PREEDITDIALOG_H
#define DATAINPUT_PREEDITDIALOG_H

#include <QDialog>

namespace Ui {
class DataInput_PreEditDialog;
}

class Seg2sToSegys;

class DataInput_PreEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataInput_PreEditDialog(QWidget *parent = 0);
    ~DataInput_PreEditDialog();

private slots:
    void on_pB_loadData_clicked();

    void on_buttonBox_accepted();

    void on_cB_isReversed_clicked(bool checked);

    void on_pB_top_clicked();

    void on_pB_bottom_clicked();

    void on_pB_up_clicked();

    void on_pb_down_clicked();

private:
    void setTableWidget();

    Ui::DataInput_PreEditDialog *ui;

    Seg2sToSegys *sts; // seg2转segy对象指针
    QStringList seg2FileNames; // seg2文件名
    QString outputDir; // 输出文件夹
    qint32 spotNums; // 炮点个数
    qint32 observerNums; // 检波点数
    bool isReversed; // 是否翻转
};

#endif // DATAINPUT_PREEDITDIALOG_H

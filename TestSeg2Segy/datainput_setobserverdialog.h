#ifndef DATAINPUT_SETOBSERVERDIALOG_H
#define DATAINPUT_SETOBSERVERDIALOG_H

#include <QDialog>

namespace Ui {
class DataInput_SetObserverDialog;
}

class DataInput_SetObserverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataInput_SetObserverDialog(QWidget *parent = 0);
    ~DataInput_SetObserverDialog();

private:
    Ui::DataInput_SetObserverDialog *ui;
};

#endif // DATAINPUT_SETOBSERVERDIALOG_H

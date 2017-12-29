#include "datainput_setobserverdialog.h"
#include "ui_datainput_setobserverdialog.h"

DataInput_SetObserverDialog::DataInput_SetObserverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataInput_SetObserverDialog)
{
    ui->setupUi(this);
}

DataInput_SetObserverDialog::~DataInput_SetObserverDialog()
{
    delete ui;
}

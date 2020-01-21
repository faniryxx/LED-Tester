#include "saverefdialog.h"
#include "ui_saverefdialog.h"
#include "referencewindow.h"

saveRefDialog::saveRefDialog(referenceWindow *parent) :
    QDialog(parent),
    ui(new Ui::saveRefDialog)
{
    ui->setupUi(this);
    ui->efficaciteRefLineEdit->setText(QString::number(parent->getEfficaciteRef()));
    ui->stabiliteRefLineEdit->setText(QString::number(parent->getStabiliteRef()));
    ui->temperatureRefLineEdit->setText(QString::number(parent->getTemperatureRef()));
}

saveRefDialog::~saveRefDialog()
{
    delete ui;
}

#include "saverefdialog.h"
#include "ui_saverefdialog.h"
#include "referencewindow.h"

saveRefDialog::saveRefDialog(referenceWindow *parent) :
    QDialog(parent),
    ui(new Ui::saveRefDialog)
{
    ui->setupUi(this);
    ui->efficaciteRefLineEdit->setText(QString::number(parent->getEfficaciteRef()));
    ui->temperatureRefLineEdit->setText(QString::number(parent->getTemperatureRef()));
    ui->refLineEdit->setText(parent->getRefLineEdit());
    papa = parent;
}

saveRefDialog::~saveRefDialog()
{
    delete ui;
}

void saveRefDialog::on_annulerRef_clicked()
{
    close();
}

void saveRefDialog::on_confirmerRef_clicked()
{
    papa->setReferenceParent();
    close();
}

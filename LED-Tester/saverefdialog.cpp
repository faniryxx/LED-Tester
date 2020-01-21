#include "saverefdialog.h"
#include "ui_saverefdialog.h"

saveRefDialog::saveRefDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveRefDialog)
{
    ui->setupUi(this);
}

saveRefDialog::~saveRefDialog()
{
    delete ui;
}

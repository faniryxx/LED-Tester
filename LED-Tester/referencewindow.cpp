#include "referencewindow.h"
#include "ui_referencewindow.h"
#include <qcustomplot.h>

referenceWindow::referenceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::referenceWindow)
{
    ui->setupUi(this);
}

referenceWindow::~referenceWindow()
{
    delete ui;
}

void referenceWindow::on_mesurerRef_clicked()
{

}

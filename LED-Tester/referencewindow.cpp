#include "referencewindow.h"
#include "ui_referencewindow.h"

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

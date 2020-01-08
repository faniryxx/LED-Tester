#include "fenetre.h"
#include "ui_fenetre.h"

fenetre::fenetre(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fenetre)
{
    ui->setupUi(this);
}

fenetre::~fenetre()
{
    delete ui;
}


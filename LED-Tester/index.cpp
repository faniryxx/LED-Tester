#include "index.h"
#include "ui_index.h"
#include <QPainter>
#include <QPdfWriter>

Index::Index(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Index)
{
    ui->setupUi(this);
}

Index::~Index()
{
    delete ui;
}

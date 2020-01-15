#include "index.h"
#include "ui_index.h"

Index::Index(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Index)
{
    ui->setupUi(this);
    ui->plotEfficacite->addGraph();
    ui->plotEfficacite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotEfficacite->graph(0)->setLineStyle(QCPGraph::lsLine);
}

Index::~Index()
{
    delete ui;
}

void Index::ajouterPoint(double x, double y)
{
    efficacite_x.append(x);
    efficacite_y.append(y);
}

void Index::effacerEfficacite()
{
    efficacite_x.clear();
    efficacite_y.clear();
}

void Index::dessiner()
{
    ui->plotEfficacite->graph(0)->setData(efficacite_x,efficacite_y);
    ui->plotEfficacite->replot();
    ui->plotEfficacite->update();
}

void Index::on_ajoutEfficacite_clicked()
{
    ajouterPoint(ui->xEff->value(),ui->yEff->value());
    dessiner();
}

void Index::on_clearEfficacite_clicked()
{
    effacerEfficacite();
    dessiner();
}

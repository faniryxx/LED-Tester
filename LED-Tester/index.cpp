#include "index.h"
#include "ui_index.h"
#include <random>

Index::Index(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Index)
{
    ui->setupUi(this);
    ui->plotEfficacite->addGraph();
    ui->plotEfficacite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotEfficacite->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plotStabilite->addGraph();
    ui->plotStabilite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotStabilite->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plotTemperature->addGraph();
    ui->plotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotTemperature->graph(0)->setLineStyle(QCPGraph::lsLine);
}

Index::~Index()
{
    delete ui;
}

void Index::ajouterPoint(double x, double y, QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.append(x);
        efficacite_y.append(y);
    }
    else if(param == "Stabilité")
    {
        stabilite_x.append(x);
        stabilite_y.append(y);
    }
    else if(param == "Température")
    {
        temperature_x.append(x);
        temperature_y.append(y);
    }
}

void Index::effacer(QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.clear();
        efficacite_y.clear();
    }
    else if(param == "Stabilité")
    {
        stabilite_x.clear();
        stabilite_y.clear();
    }
    else if(param == "Température")
    {
        temperature_x.clear();
        temperature_y.clear();
    }
}

void Index::dessiner(QString param)
{
    if(param == "Efficacité")
    {
        ui->plotEfficacite->graph(0)->setData(efficacite_x,efficacite_y);
        ui->plotEfficacite->rescaleAxes();
        ui->plotEfficacite->replot();
        ui->plotEfficacite->update();
    }

    else if(param == "Stabilité")
    {
        ui->plotStabilite->graph(0)->setData(stabilite_x,stabilite_y);
        ui->plotStabilite->rescaleAxes();
        ui->plotStabilite->replot();
        ui->plotStabilite->update();
    }

    else if(param == "Température")
    {
        ui->plotTemperature->graph(0)->setData(temperature_x,temperature_y);
        ui->plotTemperature->rescaleAxes();
        ui->plotTemperature->replot();
        ui->plotTemperature->update();
    }
}

void Index::on_ajoutEfficacite_clicked()
{
    ajouterPoint(ui->xEff->value(),ui->yEff->value(),"Efficacité");
    ui->plotEfficacite->rescaleAxes();
    dessiner("Efficacité");
}

void Index::on_clearEfficacite_clicked()
{
    effacer("Efficacité");
    dessiner("Efficacité");
}

void Index::on_ajoutStabilite_clicked()
{
    ajouterPoint(ui->xSta->value(),ui->ySta->value(),"Stabilité");
    ui->plotStabilite->rescaleAxes();
    dessiner("Stabilité");
}

void Index::on_ClearStabilite_clicked()
{
    effacer("Stabilité");
    dessiner("Stabilité");
}

void Index::on_ajoutTemperature_clicked()
{
    ajouterPoint(ui->xTemp->value(),ui->yTemp->value(),"Température");
    ui->plotTemperature->rescaleAxes();
    dessiner("Température");
}

void Index::on_clearTemperature_clicked()
{
    effacer("Température");
    dessiner("Température");
}

int Index::genererRandom(int min, int max)
{
    return (qrand() % ((max + 1) - min) + min);
}

void Index::on_boutonMesure_clicked()
{
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        for(int x=0;x<(ui->duree->value())+1;)
        {
            ajouterPoint(x,genererRandom(0,10),"Efficacité");
            dessiner("Efficacité");
            x=x+(ui->intervalle->value());
        }
        break;
    case 1:
        for(int x=0;x<(ui->duree->value())+1;)
        {
            ajouterPoint(x,genererRandom(0,10),"Stabilité");
            dessiner("Stabilité");
            x=x+(ui->intervalle->value());
        }
        break;
    case 3:
        for(int x=0;x<(ui->duree->value())+1;)
        {
            ajouterPoint(x,genererRandom(0,10),"Température");
            dessiner("Température");
            x=x+(ui->intervalle->value());
        }
        break;
    default:
        break;
    }
}

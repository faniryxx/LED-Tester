#include "referencewindow.h"
#include "saverefdialog.h"
#include "ui_referencewindow.h"
#include <random>
#include <qcustomplot.h>
#include <QTimer>
#include <index.h>

referenceWindow::referenceWindow(Index *parent) :
    QDialog(parent),
    ui(new Ui::referenceWindow)
{
    ui->setupUi(this);
    ui->plotEfficacite->addGraph();
    ui->plotEfficacite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotEfficacite->graph(0)->setLineStyle(QCPGraph::lsLine);

    ui->plotTemperature->addGraph();
    ui->plotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotTemperature->graph(0)->setLineStyle(QCPGraph::lsLine);

    ui->plotCouleurs->addGraph(); //rouge
    ui->plotCouleurs->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotCouleurs->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plotCouleurs->graph(0)->setPen(QPen(QColor(250, 0, 0)));

    ui->plotCouleurs->addGraph(); //vert
    ui->plotCouleurs->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotCouleurs->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->plotCouleurs->graph(1)->setPen(QPen(QColor(0, 200, 0)));

    ui->plotCouleurs->addGraph(); //bleu
    ui->plotCouleurs->graph(2)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotCouleurs->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->plotCouleurs->graph(2)->setPen(QPen(QColor(0, 0, 209)));

    timerMesure = new QTimer(this);
    timerTempsRestant = new QTimer(this);
    connect(timerMesure,SIGNAL(timeout()),this,SLOT(updateGraph()));
    connect(timerTempsRestant,SIGNAL(timeout()),this,SLOT(arreterTimer()));

    papa=parent;
}

void referenceWindow::ajouterPoint(double x, double y, QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.append(x);
        efficacite_y.append(y);
    }
    else if(param == "Température")
    {
        temperature_x.append(x);
        temperature_y.append(y);
    }
    else if(param == "Rouge")
    {
        couleurs_x_R.append(x);
        couleurs_rouge.append(y);
    }
    else if(param == "Vert")
    {
        couleurs_x_V.append(x);
        couleurs_vert.append(y);
    }
    else if(param == "Bleu")
    {
        couleurs_x_B.append(x);
        couleurs_bleu.append(y);
    }
}

referenceWindow::~referenceWindow()
{
    delete ui;
}

void referenceWindow::on_mesurerRef_clicked()
{
    if(ui->intervalle->value()<=ui->duree->value() && !getRefLineEdit().isEmpty())
    {
        nettoyerTout();
        demarrerTimer();
    }
    else if(ui->intervalle->value()>ui->duree->value())
    {
        QMessageBox::critical(this, "Valeurs incorrectes", "Veuillez vérifier les valeurs et relancez la mesure.");
    }
    else if(getRefLineEdit().isEmpty())
    {
        QMessageBox::critical(this, "Référence vide", "La référence du tube doit être spécifiée.");
    }
}

void referenceWindow::updateGraph()
{
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(120,130),"Efficacité");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(90,100),"Température");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,255),"Rouge");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,255),"Vert");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,255),"Bleu");
    dessiner("All");
}

void referenceWindow::arreterTimer()
{
    timerMesure->stop();
    timerTempsRestant->stop();
    setValeursMoyennes();
    saveRefDialog *dialog = new saveRefDialog(this);
    dialog->show();
}

void referenceWindow::effacer(QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.clear();
        efficacite_y.clear();
    }
    else if(param == "Température")
    {
        temperature_x.clear();
        temperature_y.clear();
    }
    else if(param == "Couleurs")
    {
        couleurs_x_R.clear();
        couleurs_x_V.clear();
        couleurs_x_B.clear();
        couleurs_rouge.clear();
        couleurs_vert.clear();
        couleurs_bleu.clear();
    }
}

void referenceWindow::dessiner(QString param)
{
    if(param == "Efficacité")
    {
        ui->plotEfficacite->graph(0)->setData(efficacite_x,efficacite_y);
        ui->plotEfficacite->rescaleAxes();
        ui->plotEfficacite->replot();
        ui->plotEfficacite->update();
    }

    else if(param == "Température")
    {
        ui->plotTemperature->graph(0)->setData(temperature_x,temperature_y);
        ui->plotTemperature->rescaleAxes();
        ui->plotTemperature->replot();
        ui->plotTemperature->update();
    }

    else if(param == "Couleurs")
    {
        ui->plotCouleurs->graph(0)->setData(couleurs_x_R,couleurs_rouge);
        ui->plotCouleurs->graph(1)->setData(couleurs_x_V,couleurs_vert);
        ui->plotCouleurs->graph(2)->setData(couleurs_x_B,couleurs_bleu);
        ui->plotCouleurs->rescaleAxes();
        ui->plotCouleurs->replot();
        ui->plotCouleurs->update();
    }

    else if(param == "All")
    {
        dessiner("Efficacité");
        dessiner("Température");
        dessiner("Couleurs");
    }
}

int referenceWindow::genererRandom(int min, int max)
{
    return (qrand() % ((max + 1) - min) + min);
}

void referenceWindow::demarrerTimer()
{
    timerMesure->start((ui->intervalle->value())*1000);
    timerTempsRestant->start((ui->duree->value())*1000);
}

void referenceWindow::nettoyerTout()
{
    effacer("Efficacité");
    dessiner("Efficacité");
    effacer("Température");
    dessiner("Température");
    effacer("Couleurs");
    dessiner("Couleurs");
}

double referenceWindow::calculerMoyenne(QVector<double> parametre)
{
    double somme=0;
    for(int x=0;x<parametre.count();x++)
    {
        somme = somme + parametre.at(x);
    }
    double moyenne = somme/parametre.count();
    return moyenne;
}

void referenceWindow::setValeursMoyennes()
{
    efficaciteRef = calculerMoyenne(efficacite_y);
    rougeRef = calculerMoyenne(couleurs_rouge);
    vertRef = calculerMoyenne(couleurs_vert);
    bleuRef = calculerMoyenne(couleurs_bleu);
    temperatureRef = calculerMoyenne(temperature_y);
}

double referenceWindow::getEfficaciteRef()
{
    return efficaciteRef;
}

double referenceWindow::getTemperatureRef()
{
    return temperatureRef;
}

QString referenceWindow::getRefLineEdit()
{
    return ui->refLineEdit->text();
}

void referenceWindow::setReferenceParent()
{
    papa->setReference(efficaciteRef,temperatureRef,ui->refLineEdit->text());
    papa->updateReference();
    close();
}


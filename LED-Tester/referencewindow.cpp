/***************************************************************************
**                          LED-TESTER                                    **
****************************************************************************
**           Author: Nathan RANAIVO                                       **
**             Date: 04/02/2020                                           **
**          Version: 1.0                                                  **
****************************************************************************/

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

    if(papa->getBlueModeState()) setBlueMode();
    //else setLightMode();
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

void referenceWindow::setLightMode()
{
    ui->plotEfficacite->xAxis->setBasePen(QPen(Qt::black));
    ui->plotEfficacite->yAxis->setBasePen(QPen(Qt::black));
    ui->plotEfficacite->xAxis->setTickPen(QPen(Qt::black));
    ui->plotEfficacite->yAxis->setTickPen(QPen(Qt::black));
    ui->plotEfficacite->xAxis->setLabelColor(Qt::black);
    ui->plotEfficacite->yAxis->setLabelColor(Qt::black);
    ui->plotEfficacite->xAxis->setTickLabelColor(Qt::black);
    ui->plotEfficacite->yAxis->setTickLabelColor(Qt::black);
    ui->plotEfficacite->xAxis->grid()->setPen(QPen(Qt::black, 1, Qt::DotLine));
    ui->plotEfficacite->yAxis->grid()->setPen(QPen(Qt::black, 1, Qt::DotLine));
    ui->plotEfficacite->setBackground(*new QBrush(Qt::white));
    ui->plotEfficacite->axisRect()->setBackground(*new QBrush(Qt::white));

    ui->plotTemperature->xAxis->setBasePen(QPen(Qt::black));
    ui->plotTemperature->yAxis->setBasePen(QPen(Qt::black));
    ui->plotTemperature->xAxis->setTickPen(QPen(Qt::black));
    ui->plotTemperature->yAxis->setTickPen(QPen(Qt::black));
    ui->plotTemperature->xAxis->setLabelColor(Qt::black);
    ui->plotTemperature->yAxis->setLabelColor(Qt::black);
    ui->plotTemperature->xAxis->setTickLabelColor(Qt::black);
    ui->plotTemperature->yAxis->setTickLabelColor(Qt::black);
    ui->plotTemperature->xAxis->grid()->setPen(QPen(Qt::black, 1, Qt::DotLine));
    ui->plotTemperature->yAxis->grid()->setPen(QPen(Qt::black, 1, Qt::DotLine));
    ui->plotTemperature->setBackground(*new QBrush(Qt::white));
    ui->plotTemperature->axisRect()->setBackground(*new QBrush(Qt::white));

    ui->plotCouleurs->xAxis->setBasePen(QPen(Qt::black));
    ui->plotCouleurs->yAxis->setBasePen(QPen(Qt::black));
    ui->plotCouleurs->xAxis->setTickPen(QPen(Qt::black));
    ui->plotCouleurs->yAxis->setTickPen(QPen(Qt::black));
    ui->plotCouleurs->xAxis->setLabelColor(Qt::black);
    ui->plotCouleurs->yAxis->setLabelColor(Qt::black);
    ui->plotCouleurs->xAxis->setTickLabelColor(Qt::black);
    ui->plotCouleurs->yAxis->setTickLabelColor(Qt::black);
    ui->plotCouleurs->xAxis->grid()->setPen(QPen(Qt::black, 1, Qt::DotLine));
    ui->plotCouleurs->yAxis->grid()->setPen(QPen(Qt::black, 1, Qt::DotLine));
    ui->plotCouleurs->setBackground(*new QBrush(Qt::white));
    ui->plotCouleurs->axisRect()->setBackground(*new QBrush(Qt::white));

    ui->plotEfficacite->rescaleAxes();
    ui->plotEfficacite->replot();
    ui->plotEfficacite->update();
    ui->plotCouleurs->rescaleAxes();
    ui->plotCouleurs->replot();
    ui->plotCouleurs->update();
    ui->plotTemperature->rescaleAxes();
    ui->plotTemperature->replot();
    ui->plotTemperature->update();
}

void referenceWindow::setBlueMode()
{
    ui->plotEfficacite->xAxis->setBasePen(QPen(Qt::white));
    ui->plotEfficacite->yAxis->setBasePen(QPen(Qt::white));
    ui->plotEfficacite->xAxis->setTickPen(QPen(Qt::white));
    ui->plotEfficacite->yAxis->setTickPen(QPen(Qt::white));
    ui->plotEfficacite->xAxis->setLabelColor(Qt::white);
    ui->plotEfficacite->yAxis->setLabelColor(Qt::white);
    ui->plotEfficacite->xAxis->setTickLabelColor(Qt::white);
    ui->plotEfficacite->yAxis->setTickLabelColor(Qt::white);
    ui->plotEfficacite->xAxis->grid()->setPen(QPen(Qt::white, 1, Qt::DotLine));
    ui->plotEfficacite->yAxis->grid()->setPen(QPen(Qt::white, 1, Qt::DotLine));
    QLinearGradient plotGradient; //dégradé fond
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(45,55,65));
    plotGradient.setColorAt(0.5, QColor(40,50,60));
    plotGradient.setColorAt(1, QColor(25,35,45));
    ui->plotEfficacite->setBackground(plotGradient);
    QLinearGradient axisRectGradient; //dégradé surface du plot
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(35,45,55));
    //axisRectGradient.setColorAt(0.75,QColor(40,50,60));
    axisRectGradient.setColorAt(1, QColor(15,25,35));
    ui->plotEfficacite->axisRect()->setBackground(axisRectGradient);

    ui->plotTemperature->xAxis->setBasePen(QPen(Qt::white));
    ui->plotTemperature->yAxis->setBasePen(QPen(Qt::white));
    ui->plotTemperature->xAxis->setTickPen(QPen(Qt::white));
    ui->plotTemperature->yAxis->setTickPen(QPen(Qt::white));
    ui->plotTemperature->xAxis->setLabelColor(Qt::white);
    ui->plotTemperature->yAxis->setLabelColor(Qt::white);
    ui->plotTemperature->xAxis->setTickLabelColor(Qt::white);
    ui->plotTemperature->yAxis->setTickLabelColor(Qt::white);
    ui->plotTemperature->xAxis->grid()->setPen(QPen(Qt::white, 1, Qt::DotLine));
    ui->plotTemperature->yAxis->grid()->setPen(QPen(Qt::white, 1, Qt::DotLine));
    ui->plotTemperature->setBackground(plotGradient);
    ui->plotTemperature->axisRect()->setBackground(axisRectGradient);

    ui->plotCouleurs->xAxis->setBasePen(QPen(Qt::white));
    ui->plotCouleurs->yAxis->setBasePen(QPen(Qt::white));
    ui->plotCouleurs->xAxis->setTickPen(QPen(Qt::white));
    ui->plotCouleurs->yAxis->setTickPen(QPen(Qt::white));
    ui->plotCouleurs->xAxis->setLabelColor(Qt::white);
    ui->plotCouleurs->yAxis->setLabelColor(Qt::white);
    ui->plotCouleurs->xAxis->setTickLabelColor(Qt::white);
    ui->plotCouleurs->yAxis->setTickLabelColor(Qt::white);
    ui->plotCouleurs->xAxis->grid()->setPen(QPen(Qt::white, 1, Qt::DotLine));
    ui->plotCouleurs->yAxis->grid()->setPen(QPen(Qt::white, 1, Qt::DotLine));
    ui->plotCouleurs->setBackground(plotGradient);
    ui->plotCouleurs->axisRect()->setBackground(axisRectGradient);

    ui->plotEfficacite->rescaleAxes();
    ui->plotEfficacite->replot();
    ui->plotEfficacite->update();
    ui->plotCouleurs->rescaleAxes();
    ui->plotCouleurs->replot();
    ui->plotCouleurs->update();
    ui->plotTemperature->rescaleAxes();
    ui->plotTemperature->replot();
    ui->plotTemperature->update();
}


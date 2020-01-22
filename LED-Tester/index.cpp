#include "index.h"
#include "ui_index.h"
#include <random>
#include <QTimer>
#include <QFileDialog>
#include <qcustomplot.h>
#include "referencewindow.h"
#include <QAction>

Index::Index(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Index)
{
    ui->setupUi(this);
    ui->plotEfficacite->addGraph();
    ui->plotEfficacite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotEfficacite->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plotEfficacite->graph(0)->removeFromLegend();
    ui->plotEfficacite->legend->setVisible(false);

    ui->plotEfficacite->addGraph();
    ui->plotEfficacite->graph(1)->setScatterStyle(QCPScatterStyle::ssDot);
    ui->plotEfficacite->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->plotEfficacite->graph(1)->setPen(QPen(QColor(190, 190, 190)));
    ui->plotEfficacite->graph(1)->removeFromLegend();

    ui->plotTemperature->addGraph();
    ui->plotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotTemperature->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plotTemperature->graph(0)->removeFromLegend();
    ui->plotTemperature->legend->setVisible(false);

    ui->plotTemperature->addGraph();
    ui->plotTemperature->graph(1)->setScatterStyle(QCPScatterStyle::ssDot);
    ui->plotTemperature->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->plotTemperature->graph(1)->setPen(QPen(QColor(190, 190, 190)));
    ui->plotTemperature->graph(1)->removeFromLegend();

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

    connect(ui->ajoutRef, SIGNAL(triggered()), this, SLOT(ouvrirReferenceWindow()));

    ref = "";

    ui->tableView->setMo
}

Index::~Index()
{
    delete ui;
}

void Index::dessiner(QString param)
{
    if(param == "Efficacité")
    {
        ui->plotEfficacite->graph(0)->setData(efficacite_x,efficacite_y);
        ui->plotEfficacite->graph(1)->setData(efficacite_ref_x,efficacite_ref_y);
        ui->plotEfficacite->rescaleAxes();
        ui->plotEfficacite->replot();
        ui->plotEfficacite->update();
    }

    else if(param == "Température")
    {
        ui->plotTemperature->graph(0)->setData(temperature_x,temperature_y);
        ui->plotTemperature->graph(1)->setData(temperature_ref_x,temperature_ref_y);
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

void Index::on_boutonMesure_clicked()
{
    if(ui->intervalle->value()<=ui->duree->value() && !ref.isEmpty() && !ui->ref->text().isEmpty())
    {
        nettoyerTout();
        demarrerTimer();
    }
    else if(ui->intervalle->value()>ui->duree->value())
    {
        QMessageBox::critical(this, "Valeurs incorrectes", "Veuillez vérifier les valeurs et relancez la mesure.");
    }
    else if(ref.isEmpty())
    {
        QMessageBox::critical(this, "Absence de référence", "Veuillez enregistrer un tube de référence avant de lancer la mesure.");
    }
    else if(ui->ref->text().isEmpty())
    {
        QMessageBox::critical(this, "Référence du tube manquant", "Veuillez entrer la référence du tube à tester avant de lancer la mesure.");
    }
}

int Index::genererRandom(int min, int max)
{
    return (qrand() % ((max + 1) - min) + min);
}

void Index::demarrerTimer()
{
    showLegend();
    timerMesure->start((ui->intervalle->value())*1000);
    timerTempsRestant->start((ui->duree->value())*1000);
}

void Index::arreterTimer()
{
    timerMesure->stop();
    timerTempsRestant->stop();
    QMessageBox::information(this, "Fin de la mesure", "Les mesures ont été effectuées.");
}

void Index::updateGraph()
{
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(120,130),"Efficacité");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(90,100),"Température");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,255),"Rouge");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,255),"Vert");
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,255),"Bleu");
    dessiner("All");
}

void Index::on_saveButton_clicked()
{
    enregistrerSous();
}

void Index::ouvrirReferenceWindow()
{
    referenceWindow *ref = new referenceWindow(this);
    ref->show();
}

void Index::enregistrerSous()
{
    //getSaveFileName ==> Boîte de dialogue 'Enregistrer sous'
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Enregistrer sous ..."), "",
    tr("Fichier CSV (*.csv);;All Files (*)"));
    if (fileName.isEmpty()) return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),file.errorString());
            return;
        }
        QTextStream stream(&file);
        stream << "Reference: " << ui->ref->text() << "\n\n";
        stream << "Temps;Efficacite;  Temperature; R-G-B\n";
        for(int x=0;x<efficacite_x.count();x++)
            stream << efficacite_x.at(x) << ";" << efficacite_y.at(x) << ";"
                  << temperature_y.at(x) << ";"
                     << couleurs_rouge.at(x) << "-" << couleurs_vert.at(x) << "-" << couleurs_bleu.at(x) << "\n";
        file.close();
    }
}

void Index::setReference(double efficacite, double temperature, QString reference)
{
    efficaciteRef = efficacite;
    temperatureRef = temperature;
    ref = reference;
}

void Index::updateReference()
{
    ui->refTubeReference->setText(ref);
}

void Index::showLegend()
{
    ui->plotEfficacite->graph(0)->setName(ui->ref->text());
    ui->plotEfficacite->graph(1)->setName(ref);
    ui->plotEfficacite->graph(0)->addToLegend();
    ui->plotEfficacite->graph(1)->addToLegend();
    ui->plotEfficacite->legend->setVisible(true);

    ui->plotTemperature->graph(0)->setName(ui->ref->text());
    ui->plotTemperature->graph(1)->setName(ref);
    ui->plotTemperature->graph(0)->addToLegend();
    ui->plotTemperature->graph(1)->addToLegend();
    ui->plotTemperature->legend->setVisible(true);
}

void Index::ajouterPoint(double x, double y, QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.append(x);
        efficacite_y.append(y);

        //TEST
        struct efficacite eff;
        eff.x = x;
        eff.y = y;
        tableauEfficacite.append(eff);
        //FINTEST

        efficacite_ref_x.append(x);
        efficacite_ref_y.append(efficaciteRef);
    }
    else if(param == "Température")
    {
        temperature_x.append(x);
        temperature_y.append(y);
        temperature_ref_x.append(x);
        temperature_ref_y.append(temperatureRef);
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

void Index::effacer(QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.clear();
        efficacite_y.clear();
        efficacite_ref_x.clear();
        efficacite_ref_y.clear();
    }
    else if(param == "Température")
    {
        temperature_x.clear();
        temperature_y.clear();
        temperature_ref_x.clear();
        temperature_ref_y.clear();
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

void Index::nettoyerTout()
{
    effacer("Efficacité");
    dessiner("Efficacité");
    effacer("Température");
    dessiner("Température");
    effacer("Couleurs");
    dessiner("Couleurs");
}

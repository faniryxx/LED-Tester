#include "index.h"
#include "ui_index.h"
#include <random>
#include <QTimer>
#include <QFileDialog>
#include <qcustomplot.h>

Index::Index(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Index)
{
    ui->setupUi(this);
    ui->plotEfficacite->addGraph();
    ui->plotEfficacite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotEfficacite->graph(0)->setLineStyle(QCPGraph::lsLine);
    //ui->plotEfficacite->setInteractions(QCP::Interaction::iRangeDrag | QCP::iRangeZoom);

    ui->plotStabilite->addGraph();
    ui->plotStabilite->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotStabilite->graph(0)->setLineStyle(QCPGraph::lsLine);
    //ui->plotStabilite->setInteractions(QCP::Interaction::iRangeDrag | QCP::iRangeZoom);

    ui->plotTemperature->addGraph();
    ui->plotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plotTemperature->graph(0)->setLineStyle(QCPGraph::lsLine);
    //ui->plotTemperature->setInteractions(QCP::Interaction::iRangeDrag | QCP::iRangeZoom);

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
    //ui->plotCouleurs->setInteractions(QCP::Interaction::iRangeDrag | QCP::iRangeZoom);

    timerMesure = new QTimer(this);
    timerTempsRestant = new QTimer(this);
    connect(timerMesure,SIGNAL(timeout()),this,SLOT(updateGraph()));
    connect(timerTempsRestant,SIGNAL(timeout()),this,SLOT(arreterTimer()));
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
        dessiner("Stabilité");
        dessiner("Température");
        dessiner("Couleurs");
    }
}

void Index::on_boutonMesure_clicked()
{
    if(ui->intervalle->value()<=ui->duree->value())
    {
        nettoyerTout();
        demarrerTimer();
    }
    else QMessageBox::critical(this, "Valeurs incorrectes", "Veuillez vérifier les valeurs et relancez la mesure.");
}

int Index::genererRandom(int min, int max)
{
    return (qrand() % ((max + 1) - min) + min);
}

void Index::demarrerTimer()
{
    timerMesure->start((ui->intervalle->value())*1000);
    timerTempsRestant->start((ui->duree->value())*1000);
}

void Index::nettoyerTout()
{
    effacer("Efficacité");
    dessiner("Efficacité");
    effacer("Stabilité");
    dessiner("Stabilité");
    effacer("Température");
    dessiner("Température");
    effacer("Couleurs");
    dessiner("Couleurs");
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
    ajouterPoint((((ui->duree->value()+1)*1000)-timerTempsRestant->remainingTime())/1000,genererRandom(0,50),"Stabilité");
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
        stream << "Temps;Efficacite; Stabilite; RGB; Temperature\n";
        for(int x=0;x<efficacite_x.count();x++)
            stream << efficacite_x.at(x) << ";" << efficacite_y.at(x) << ";" << stabilite_y.at(x) << ";"
                   << couleurs_rouge.at(x) << "-" << couleurs_vert.at(x) << "-" << couleurs_bleu.at(x) << ";"
                  << temperature_y.at(x) << "\n";
        file.close();
    }
}

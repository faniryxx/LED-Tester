#include "index.h"
#include <random>
#include <QTimer>
#include <qcustomplot.h>

void Index::ajouterPoint(double x, double y, QString param)
{
    if(param == "Efficacité")
    {
        efficacite_x.append(x);
        efficacite_y.append(y);
        efficacite_ref_x.append(x);
        efficacite_ref_y.append(efficaciteRef);
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
    else if(param == "Stabilité")
    {
        stabilite_x.clear();
        stabilite_y.clear();
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
    effacer("Stabilité");
    dessiner("Stabilité");
    effacer("Température");
    dessiner("Température");
    effacer("Couleurs");
    dessiner("Couleurs");
}

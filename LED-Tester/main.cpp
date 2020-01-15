#include "index.h"
#include "exemplesgraphiques.h"
#include <QApplication>
#include <QtCharts>
#include <QLineSeries>

using namespace QtCharts;

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion"); //fusion = theme
    QApplication a(argc, argv);
    Index principale;

    QTabWidget *tabWidget = principale.findChild<QTabWidget*>("tabWidget");

    QWidget *efficacite = tabWidget->findChild<QWidget*>("efficacite");
    QChartView *chartViewEfficacite = efficacite->findChild<QChartView*>("chartViewEfficacite"); 

    QWidget *stabilite = tabWidget->findChild<QWidget*>("stabilite");
    QChartView *chartViewStabilite = stabilite->findChild<QChartView*>("chartViewStabilite");

    QWidget *couleurs = tabWidget->findChild<QWidget*>("couleurs");
    QChartView *chartViewCouleurs = couleurs->findChild<QChartView*>("chartViewCouleurs");

    QWidget *temperature = tabWidget->findChild<QWidget*>("temperature");
    QChartView *chartViewTemperature = temperature->findChild<QChartView*>("chartViewTemperature");

    ExemplesGraphiques::GenererExemplesCharts(chartViewEfficacite,chartViewStabilite,chartViewCouleurs,chartViewTemperature);

    principale.show();
    return a.exec();
}


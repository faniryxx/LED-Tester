#include "index.h"

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

    //EFFICACITE
    QLineSeries *seriesEfficacite = new QLineSeries();
    seriesEfficacite->append(0, 125);
    seriesEfficacite->append(5, 124);
    seriesEfficacite->append(10, 124);
    seriesEfficacite->append(15, 125);
    seriesEfficacite->append(20, 126);
    seriesEfficacite->append(25, 126);
    seriesEfficacite->append(30, 125);
    seriesEfficacite->append(35, 124);
    seriesEfficacite->append(40, 125);
    seriesEfficacite->append(45, 124);
    seriesEfficacite->append(50, 124);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(seriesEfficacite);
    chart->createDefaultAxes();
    chart->setTitle("Exemple efficacité");
    //chart->setTheme(QChart::ChartThemeDark);
    chart->layout()->setContentsMargins(0,0,0,0);
    chart->setBackgroundRoundness(0);

    chartViewEfficacite->setChart(chart);
    chartViewEfficacite->setRenderHint(QPainter::Antialiasing);
    //FIN EFFICACITE

    QWidget *stabilite = tabWidget->findChild<QWidget*>("stabilite");
    QChartView *chartViewStabilite = stabilite->findChild<QChartView*>("chartViewStabilite");

    //STABILITE
    QLineSeries *seriesStabilite = new QLineSeries();
    seriesStabilite->append(0, 35);
    seriesStabilite->append(5, 45);
    seriesStabilite->append(10, 23);
    seriesStabilite->append(15, 53);
    seriesStabilite->append(20, 45);
    seriesStabilite->append(25, 45);
    seriesStabilite->append(30, 54);
    seriesStabilite->append(35, 60);
    seriesStabilite->append(40, 54);
    seriesStabilite->append(45, 54);
    seriesStabilite->append(50, 51);

    QChart *chart2 = new QChart();
    chart2->legend()->hide();
    chart2->addSeries(seriesStabilite);
    chart2->createDefaultAxes();
    chart2->setTitle("Exemple stabilite");
    //chart2->setTheme(QChart::ChartThemeDark);
    chart2->layout()->setContentsMargins(0,0,0,0);
    chart2->setBackgroundRoundness(0);

    chartViewStabilite->setChart(chart2);
    chartViewStabilite->setRenderHint(QPainter::Antialiasing);
    //FIN STABILITE

    //COULEURS
    QWidget *couleurs = tabWidget->findChild<QWidget*>("couleurs");
    QChartView *chartViewCouleurs = couleurs->findChild<QChartView*>("chartViewCouleurs");

    QBarSet *rouge = new QBarSet("Rouge");
    QBarSet *vert = new QBarSet("Vert");
    QBarSet *bleu = new QBarSet("Bleu");

    *rouge << 255;
    *vert << 253;
    *bleu << 200;

    rouge->setColor(Qt::red);
    vert->setColor(Qt::green);
    bleu->setColor(Qt::blue);

    QBarSeries *seriesCouleurs = new QBarSeries();
    seriesCouleurs->append(rouge);
    seriesCouleurs->append(vert);
    seriesCouleurs->append(bleu);

    QChart *chartCouleurs = new QChart();
    chartCouleurs->addSeries(seriesCouleurs);
    chartCouleurs->setTitle("Couleurs");
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    chartCouleurs->layout()->setContentsMargins(0,0,0,0);
    chartCouleurs->setBackgroundRoundness(0);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,255);
    chartCouleurs->addAxis(axisY,Qt::AlignLeft);

    chartViewCouleurs->setChart(chartCouleurs);
    chartViewCouleurs->setRenderHint(QPainter::Antialiasing);
    //FIN COULEURS

    //TEMPERATURE
    QWidget *temperature = tabWidget->findChild<QWidget*>("temperature");
    QChartView *chartViewTemperature = temperature->findChild<QChartView*>("chartViewTemperature");

    QSplineSeries *seriesTemperature = new QSplineSeries();
    seriesTemperature->append(0, 100);
    seriesTemperature->append(5, 100);
    seriesTemperature->append(10, 98);
    seriesTemperature->append(15, 95);
    seriesTemperature->append(20, 80);
    seriesTemperature->append(25, 65);
    seriesTemperature->append(30, 50);
    seriesTemperature->append(35, 45);
    seriesTemperature->append(40, 40);
    seriesTemperature->append(45, 35);
    seriesTemperature->append(50, 30);

    QChart *chartTemperature = new QChart();
    chartTemperature->legend()->hide();
    chartTemperature->addSeries(seriesTemperature);
    chartTemperature->createDefaultAxes();
    chartTemperature->setTitle("Exemple courbe de température");
    chartTemperature->layout()->setContentsMargins(0,0,0,0);
    chartTemperature->setBackgroundRoundness(0);

    chartViewTemperature->setChart(chartTemperature);
    chartViewTemperature->setRenderHint(QPainter::Antialiasing);
    //FIN TEMPERATURE

    principale.show();
    return a.exec();
}

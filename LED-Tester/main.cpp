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

    QTabWidget *tabWidget = principale.findChild<QTabWidget*>("tabWidget");
    QWidget *efficacite = tabWidget->findChild<QWidget*>("efficacite");
    QChartView *chartViewEfficacite = efficacite->findChild<QChartView*>("chartViewEfficacite");

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

    principale.show();
    return a.exec();
}

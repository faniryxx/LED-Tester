#ifndef EXEMPLESGRAPHIQUES_H
#define EXEMPLESGRAPHIQUES_H
#include <QtCharts>

class ExemplesGraphiques
{
public:
    ExemplesGraphiques();
    static void creerGraphEfficacite(QChartView *chartViewEfficacite);
    static void creerGraphStabilite(QChartView *chartViewStabilite);
    static void creerGraphCouleurs(QChartView *chartViewCouleurs);
    static void creerGraphTemperature(QChartView *chartViewTemperature);
    static void GenererExemplesCharts(QChartView *chartViewEfficacite, QChartView *chartViewStabilite, QChartView *chartViewCouleurs, QChartView *chartViewTemperature);
};

#endif // EXEMPLESGRAPHIQUES_H

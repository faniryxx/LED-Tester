#ifndef REFERENCEWINDOW_H
#define REFERENCEWINDOW_H

#include <QWidget>

namespace Ui {
class referenceWindow;
}

class referenceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit referenceWindow(QWidget *parent = nullptr);
    void ajouterPoint(double x, double y, QString param);
    void effacer(QString param);
    void dessiner(QString param);
    int genererRandom(int min, int max);
    void demarrerTimer();
    void nettoyerTout();
    double calculerMoyenne(QVector<double> parametre);
    ~referenceWindow();

private slots:
    void on_mesurerRef_clicked();
    void updateGraph();
    void arreterTimer();

private:
    Ui::referenceWindow *ui;
    QVector<double> efficacite_x, efficacite_y;
    QVector<double> stabilite_x, stabilite_y;
    QVector<double> temperature_x, temperature_y;
    QVector<double> couleurs_x_R, couleurs_x_V, couleurs_x_B, couleurs_rouge, couleurs_vert, couleurs_bleu;
    QTimer *timerMesure;
    QTimer *timerTempsRestant;
    double efficacite, stabilite, temperature, rouge, vert, bleu;
};

#endif // REFERENCEWINDOW_H

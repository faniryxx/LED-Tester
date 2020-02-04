/***************************************************************************
**                          LED-TESTER                                    **
****************************************************************************
**           Author: Nathan RANAIVO                                       **
**             Date: 04/02/2020                                           **
**          Version: 1.0                                                  **
****************************************************************************/

#ifndef REFERENCEWINDOW_H
#define REFERENCEWINDOW_H
#include <index.h>
#include <QDialog>

namespace Ui {
class referenceWindow;
}

class referenceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit referenceWindow(Index *parent = nullptr);
    void ajouterPoint(double x, double y, QString param);
    void effacer(QString param);
    void dessiner(QString param);
    int genererRandom(int min, int max);
    void demarrerTimer();
    void nettoyerTout();
    double calculerMoyenne(QVector<double> parametre);
    void setValeursMoyennes();
    double getEfficaciteRef();
    double getTemperatureRef();
    QString getRefLineEdit();
    void setReferenceParent();
    ~referenceWindow();

private slots:
    void on_mesurerRef_clicked();
    void updateGraph();
    void arreterTimer();

private:
    Ui::referenceWindow *ui;
    QVector<double> efficacite_x, efficacite_y;
    QVector<double> temperature_x, temperature_y;
    QVector<double> couleurs_x_R, couleurs_x_V, couleurs_x_B, couleurs_rouge, couleurs_vert, couleurs_bleu;
    QTimer *timerMesure;
    QTimer *timerTempsRestant;
    double efficaciteRef, temperatureRef, rougeRef, vertRef, bleuRef;
    QString ref;
    Index *papa;
};

#endif // REFERENCEWINDOW_H

/***************************************************************************
**                          LED-TESTER                                    **
****************************************************************************
**           Author: Nathan RANAIVO                                       **
**             Date: 04/02/2020                                           **
**          Version: 1.0                                                  **
****************************************************************************/

#ifndef INDEX_H
#define INDEX_H
#include <QMainWindow>
#include <QSerialPort>
#include <QPrinter>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Index; }
QT_END_NAMESPACE

struct efficacite
{
    double x;
    double y;
};

class Index : public QMainWindow
{
    Q_OBJECT

public:
    Index(QWidget *parent = nullptr);
    void ajouterPoint(double x, double y, QString param);
    void effacer(QString param);
    void dessiner(QString param);
    int genererRandom(int min, int max);
    void demarrerTimer();
    void nettoyerTout();
    void enregistrerSous();
    void setReference(double efficacite, double temperature, QString reference);
    void updateReference();
    void showLegend();
    void getSelectPortName(QString portName);
    bool getBlueModeState(){return blueMode;}
    QRgb EstimerCouleur(int rouge,int vert, int bleu);
    QVector<double> getValeursCapteur();
    ~Index();

private slots:
    void on_boutonMesure_clicked();
    void updateGraph();
    void arreterTimer();
    void on_saveButton_clicked();
    void ouvrirReferenceWindow();
    void ouvrirMenuPorts();
    void enregistrement();
    void impression();
    void printPreview(QPrinter *);
    void setBlueMode();
    void setLightMode();
    void ouvrirDebug();

private:
    Ui::Index *ui;
    QVector<double> efficacite_x, efficacite_y, efficacite_ref_x, efficacite_ref_y;
    QVector<double> temperature_x, temperature_y, temperature_ref_x, temperature_ref_y;
    QVector<double> couleurs_x_R, couleurs_x_V, couleurs_x_B, couleurs_rouge, couleurs_vert, couleurs_bleu;
    QTimer *timerMesure;
    QTimer *timerTempsRestant;
    QString ref;
    double efficaciteRef, temperatureRef;//, rougeRef, vertRef, bleuRef;
    QList<efficacite> tableauEfficacite;
    QSerialPort *portUtilise;
    bool blueMode;
    QCPBars *rouge;
    QCPBars *vert;
    QCPBars *bleu;
    QCPBars *teinte;
};
#endif // INDEX_H

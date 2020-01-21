#ifndef INDEX_H
#define INDEX_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Index; }
QT_END_NAMESPACE

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
    ~Index();

private slots:
    void on_boutonMesure_clicked();
    void updateGraph();
    void arreterTimer();
    void on_saveButton_clicked();
    void ouvrirReferenceWindow();

private:
    Ui::Index *ui;
    QVector<double> efficacite_x, efficacite_y;
    QVector<double> stabilite_x, stabilite_y;
    QVector<double> temperature_x, temperature_y;
    QVector<double> couleurs_x_R, couleurs_x_V, couleurs_x_B, couleurs_rouge, couleurs_vert, couleurs_bleu;
    QTimer *timerMesure;
    QTimer *timerTempsRestant;
    double efficaciteRef, stabiliteRef, temperatureRef, rougeRef, vertRef, bleuRef;
};
#endif // INDEX_H

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
    ~Index();

private slots:
    void on_ajoutEfficacite_clicked();
    void on_clearEfficacite_clicked();

    void on_ajoutStabilite_clicked();

    void on_ClearStabilite_clicked();

    void on_ajoutTemperature_clicked();

    void on_clearTemperature_clicked();

private:
    Ui::Index *ui;
    QVector<double> efficacite_x, efficacite_y;
    QVector<double> stabilite_x, stabilite_y;
    QVector<double> temperature_x, temperature_y;
};
#endif // INDEX_H

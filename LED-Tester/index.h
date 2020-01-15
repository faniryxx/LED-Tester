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
    void ajouterPoint(double x, double y);
    void effacerEfficacite();
    void dessiner();
    ~Index();

private slots:
    void on_ajoutEfficacite_clicked();
    void on_clearEfficacite_clicked();

private:
    Ui::Index *ui;
    QVector<double> efficacite_x, efficacite_y;
};
#endif // INDEX_H

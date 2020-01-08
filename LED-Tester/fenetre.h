#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class fenetre; }
QT_END_NAMESPACE

class fenetre : public QMainWindow
{
    Q_OBJECT

public:
    fenetre(QWidget *parent = nullptr);
    ~fenetre();

private:
    Ui::fenetre *ui;
};
#endif // FENETRE_H

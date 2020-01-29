#ifndef MENUPORTS_H
#define MENUPORTS_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDialog>
#include <index.h>

namespace Ui {
class MenuPorts;
}

class MenuPorts : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPorts(Index *parent = nullptr);
    ~MenuPorts();

private slots:
    void ok();
    void annuler();

private:
    Ui::MenuPorts *ui;
    Index *papa;
};

#endif // MENUPORTS_H

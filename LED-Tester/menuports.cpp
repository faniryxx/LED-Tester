/***************************************************************************
**                          LED-TESTER                                    **
****************************************************************************
**           Author: Nathan RANAIVO                                       **
**             Date: 04/02/2020                                           **
**          Version: 1.0                                                  **
****************************************************************************/

#include "menuports.h"
#include "ui_menuports.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MenuPorts::MenuPorts(Index *parent) :
    QDialog(parent),
    ui(new Ui::MenuPorts)
{
    ui->setupUi(this);
    papa = parent;
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        ui->listePorts->addItem(port.portName());
    }
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(ok()));
    connect(ui->buttonBox, SIGNAL(rejected()),this, SLOT(annuler()));
}

MenuPorts::~MenuPorts()
{
    delete ui;
}

void MenuPorts::ok()
{
    papa->getSelectPortName(ui->listePorts->currentText());
    accept();
}

void MenuPorts::annuler()
{
    reject();
}

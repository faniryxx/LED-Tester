/***************************************************************************
**                          LED-TESTER                                    **
****************************************************************************
**           Author: Nathan RANAIVO                                       **
**             Date: 04/02/2020                                           **
**          Version: 1.0                                                  **
****************************************************************************/

#include "index.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion"); //fusion = theme
    QApplication a(argc, argv);

    QFile f(":qdarkstyle/style.qss");

    Index principale;
    principale.show();
    return a.exec();
}

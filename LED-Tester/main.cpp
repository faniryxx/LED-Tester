#include "index.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Index principale;
    principale.show();
    return a.exec();
}

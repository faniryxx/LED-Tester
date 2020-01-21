#ifndef SAVEREFDIALOG_H
#define SAVEREFDIALOG_H

#include <QDialog>
#include <referencewindow.h>

namespace Ui {
class saveRefDialog;
}

class saveRefDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveRefDialog(referenceWindow *parent = nullptr);
    ~saveRefDialog();

private:
    Ui::saveRefDialog *ui;
    double efficaciteRef, stabiliteRef, temperatureRef, rougeRef, vertRef, bleuRef;
};

#endif // SAVEREFDIALOG_H

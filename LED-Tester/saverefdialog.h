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

private slots:
    void on_annulerRef_clicked();

    void on_confirmerRef_clicked();

private:
    Ui::saveRefDialog *ui;
    double efficaciteRef, temperatureRef, rougeRef, vertRef, bleuRef;
    referenceWindow *papa;
};

#endif // SAVEREFDIALOG_H

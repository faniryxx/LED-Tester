#ifndef SAVEREFDIALOG_H
#define SAVEREFDIALOG_H

#include <QDialog>

namespace Ui {
class saveRefDialog;
}

class saveRefDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveRefDialog(QWidget *parent = nullptr);
    ~saveRefDialog();

private:
    Ui::saveRefDialog *ui;
};

#endif // SAVEREFDIALOG_H

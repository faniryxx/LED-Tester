#ifndef REFERENCEWINDOW_H
#define REFERENCEWINDOW_H

#include <QWidget>

namespace Ui {
class referenceWindow;
}

class referenceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit referenceWindow(QWidget *parent = nullptr);
    ~referenceWindow();

private slots:
    void on_mesurerRef_clicked();

private:
    Ui::referenceWindow *ui;
};

#endif // REFERENCEWINDOW_H

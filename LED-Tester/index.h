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
    ~Index();

private:
    Ui::Index *ui;
};
#endif // INDEX_H

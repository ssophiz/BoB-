#ifndef VENWIDGET_H
#define VENWIDGET_H

#include <QWidget>

namespace Ui {
class VenWidget;
}

class VenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VenWidget(QWidget *parent = 0);
    void MoneyChange(int number);
    ~VenWidget();
private:
    int number=0;
    bool flag=false;

private slots:
    void on_n10_clicked();

    void on_n50_clicked();

    void on_n100_clicked();

    void on_n500_clicked();

    void on_coke_clicked();

    void on_tea_clicked();

    void on_milk_clicked();

    void on_reset_clicked();

private:
    Ui::VenWidget *ui;
};

#endif // VENWIDGET_H

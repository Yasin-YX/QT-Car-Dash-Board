#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>
#include <carcongig.h>
namespace Ui {
class BottomBar;
}

class BottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = nullptr);
    ~BottomBar();
signals:
    void changeAir();
    void changeTheme();
    void changeHome();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();
//    void showTemp(int temp);
private:
    Ui::BottomBar *ui;
};

#endif // BOTTOMBAR_H

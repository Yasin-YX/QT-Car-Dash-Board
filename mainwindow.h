#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void dealAir();
    void dealTheme();
    void dealThemePage(QString path);
    void dealHome();
    void dealChart();
    void dealMap();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

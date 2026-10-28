#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->bottom,&BottomBar::changeAir,this,&MainWindow::dealAir);
    connect(ui->bottom,&BottomBar::changeTheme,this,&MainWindow::dealTheme);
    connect(ui->bottom,&BottomBar::changeHome,this,&MainWindow::dealHome);
    connect(ui->home,&HomeScreen::changeChart,this,&MainWindow::dealChart);
    connect(ui->home,&HomeScreen::changeMap,this,&MainWindow::dealMap);
    connect(ui->theme,&ThemeScreen::changeThemePage,this,&MainWindow::dealThemePage);

    ui->theme->randomSelectTheme();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealAir()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::dealTheme()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::dealThemePage(QString path)
{
    ui->home->setBackgroundImg(path);
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::dealHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::dealChart()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::dealMap()
{
    ui->stackedWidget->setCurrentIndex(4);
}


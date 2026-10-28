#ifndef THEMESCREEN_H
#define THEMESCREEN_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include <QRandomGenerator>
namespace Ui {
class ThemeScreen;
}

class ThemeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeScreen(QWidget *parent = nullptr);
    ~ThemeScreen();

    void randomSelectTheme();

     bool eventFilter(QObject* watched,QEvent* event)override;
private slots:
    void on_pushButton_clicked();

signals:
    void changeThemePage(QString path);

private:
    Ui::ThemeScreen *ui;
    QList<QString> imgPaths;

    QList<QLabel*> list_labels;
    int imgIndex = 0;
};

#endif // THEMESCREEN_H

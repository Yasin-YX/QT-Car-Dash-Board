#ifndef MYLABEL_H
#define MYLABEL_H

#include <QTimer>
#include <QLabel>
class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget* parent = nullptr);
    void toastLabel(QString str);
private:
    QTimer* timer;
};

#endif // MYLABEL_H

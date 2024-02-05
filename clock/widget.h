#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    virtual void paintEvent(QPaintEvent *event);

private:
    QTimer timer_;
    int hours_ {0};
    int minutes_ {0};
    int seconds_ {0};
};
#endif // WIDGET_H

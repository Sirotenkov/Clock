#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void clicked();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    virtual void paintEvent(QPaintEvent *event);

private slots:
    void onTimeout();

private:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    QTimer timer_;
    int hours_ {0};
    int minutes_ {0};
    int seconds_ {0};

    bool m_pressed = false;
    bool m_hovered = false;
};
#endif // WIDGET_H

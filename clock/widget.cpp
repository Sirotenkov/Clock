#include <QPainter>
#include <QtMath>
#include <QDateTime>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    auto const w = width(), h = height();
    auto const x0 = w / 2, y0 = h / 2;
    auto const d = qMin(w, h);
    auto const r = d / 2;
    auto const left = (w - d) / 2, top = (h - d) / 2;

    QPainter painter(this);
    painter.drawEllipse(left, top, d, d);


}

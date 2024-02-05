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

    // Засечки для часовых делений
    for (std::size_t i = 0; i < 12; ++i) {
        auto const degrees = (360.0 / 12) * i;
        auto const radians = qDegreesToRadians(degrees);
        auto x1 = x0 + r * qCos(radians), y1 = y0 + r *qSin(radians);
        auto x2 = x0 + (r * 0.9) * qCos(radians), y2 = y0 + (r * 0.9) * qSin(radians);
        painter.drawLine(x1, y1, x2, y2);
    }

}

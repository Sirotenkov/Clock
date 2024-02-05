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

void Widget::onTimeout()
{
    auto const dateTime = QDateTime::currentDateTime();

    hours_ = dateTime.time().hour();
    minutes_ = dateTime.time().minute();
    seconds_ = dateTime.time().second();
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

    // Засечки для минутных делений
    for (std::size_t i = 0; i < 60; ++i) {
        auto const degrees = (360.0 / 60) * i;
        auto const radians = qDegreesToRadians(degrees);
        auto x1 = x0 + r * qCos(radians), y1 = y0 + r *qSin(radians);
        auto x2 = x0 + (r * 0.95) * qCos(radians), y2 = y0 + (r * 0.95) * qSin(radians);
        painter.drawLine(x1, y1, x2, y2);
    }

    {   // Отрисовка часовой стрелки
        // -90 градусов - смещение относительно математического нуля,
        // чтобы ноль у стрелок соответствовал 12 часам
        auto const degrees = (360.0 / 12) * hours_;
        auto const radians = qDegreesToRadians(degrees - 90);
        auto x1 = x0, y1 = y0;
        auto x2 = x0 + (r * 0.5) * qCos(radians), y2 = y0 + (r * 0.5) * qSin(radians);
        painter.drawLine(x1, y1, x2, y2);
    }

    {   // Отрисовка минутной стрелки
        auto const degrees = (360.0 / 60) * minutes_;
        auto const radians = qDegreesToRadians(degrees - 90);
        auto x1 = x0, y1 = y0;
        auto x2 = x0 + (r * 0.7) * qCos(radians), y2 = y0 + (r * 0.7) * qSin(radians);
        painter.drawLine(x1, y1, x2, y2);
    }

    {   // Отрисовка секундной стрелки
        auto const degrees = (360.0 / 60) * seconds_;
        auto const radians = qDegreesToRadians(degrees - 90);
        auto x1 = x0, y1 = y0;
        auto x2 = x0 + (r * 0.8) * qCos(radians), y2 = y0 + (r * 0.8) * qSin(radians);
        painter.drawLine(x1, y1, x2, y2);
    }

}

#include <QPainter>
#include <QtMath>
#include <QDateTime>
#include <QMouseEvent>
#include <QColor>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    timer_.setInterval(1000);
    connect(&timer_, &QTimer::timeout, this, &Widget::onTimeout);

    timer_.start();
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

    update();
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

    QColor const active (Qt::gray);
    QColor const inactive (Qt::lightGray);

    painter.setPen(QPen(inactive, 5, Qt::SolidLine));

    if (m_pressed) {
    painter.setBrush(Qt::black); painter.drawEllipse(left, top, d, d);
    } else {
        painter.setBrush(Qt::white); painter.drawEllipse(left, top, d, d);
    }
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Засечки для минутных делений
    for (int i = 0; i < 60; ++i) {
        auto const degrees = (360.0 / 60) * i;
        auto const radians = qDegreesToRadians(degrees);
        auto x1 = x0 + r * qCos(radians), y1 = y0 + r *qSin(radians);
        auto x2 = x0 + (r * 0.95) * qCos(radians), y2 = y0 + (r * 0.95) * qSin(radians);

        if (m_pressed) {
            painter.setPen(QColor(active)); painter.drawLine(x1, y1, x2, y2);
        } else {
            painter.setPen(QColor(inactive)); painter.drawLine(x1, y1, x2, y2);
        }
    }

    // Засечки для часовых делений
    for (int i = 0; i < 12; ++i) {
        auto const degrees = (360.0 / 12) * i;
        auto const radians = qDegreesToRadians(degrees);
        auto x1 = x0 + r * qCos(radians), y1 = y0 + r *qSin(radians);
        auto x2 = x0 + (r * 0.9) * qCos(radians), y2 = y0 + (r * 0.9) * qSin(radians);
        painter.setPen(QColor(255, 0, 0));
        painter.drawLine(x1, y1, x2, y2);
    }

    {   // Отрисовка часовой стрелки
        // -90 градусов - смещение относительно математического нуля,
        // чтобы ноль у стрелок соответствовал 12 часам
        auto const degrees = (360.0 / 12) * hours_;
        auto const radians = qDegreesToRadians(degrees - 90);
        auto x1 = x0, y1 = y0;
        auto x2 = x0 + (r * 0.5) * qCos(radians), y2 = y0 + (r * 0.5) * qSin(radians);
        painter.setPen(QColor(71, 106, 125));
        painter.drawLine(x1, y1, x2, y2);
    }

    {   // Отрисовка минутной стрелки
        auto const degrees = (360.0 / 60) * minutes_;
        auto const radians = qDegreesToRadians(degrees - 90);
        auto x1 = x0, y1 = y0;
        auto x2 = x0 + (r * 0.7) * qCos(radians), y2 = y0 + (r * 0.7) * qSin(radians);
        painter.setPen(Qt::green);
        painter.drawLine(x1, y1, x2, y2);
    }

    {   // Отрисовка секундной стрелки
        auto const degrees = (360.0 / 60) * seconds_;
        auto const radians = qDegreesToRadians(degrees - 90);
        auto x1 = x0, y1 = y0;
        auto x2 = x0 + (r * 0.8) * qCos(radians), y2 = y0 + (r * 0.8) * qSin(radians);
        painter.setPen(Qt::yellow);
        painter.drawLine(x1, y1, x2, y2);
    }
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        m_pressed = true;
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        m_pressed = false;
        update();

        emit clicked();
    }
}

#include "Fullscreen.h"

#include <QPainter>

Fullscreen::Fullscreen(QWidget *parent)
    : QWidget(parent)
{}

Fullscreen::~Fullscreen() {}

void Fullscreen::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);
}

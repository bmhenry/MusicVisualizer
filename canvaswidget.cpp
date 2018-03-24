#include "canvaswidget.h"

#include <QDebug>
#include <QPainter>
#include <QRect>

#include <thread>
#include <vector>

CanvasWidget::CanvasWidget(int width, int height, QWidget* parent)
    : QOpenGLWidget(parent)
{
    this->resize(width, height);
    canvasWidth = width;
    canvasHeight = height;

    randomizeBarColor = false;
    barBackground = Qt::white;
    barColor = Qt::black;

    // init bar positions
    barNum = 10;
    updateBarPositions();
}

CanvasWidget::~CanvasWidget() {
}

void CanvasWidget::resizeCanvas() {
    // resize the canvas
    resize(canvasWidth, canvasHeight);

    updateBarPositions();
    redrawCanvas();
}

void CanvasWidget::updateBarPositions() {
    barSpace = (canvasWidth/barNum)/5;
    barWidth = (canvasWidth - barNum*2*barSpace)/barNum;

    barPos.clear();
    for (int i = 0; i < barNum; ++i) {
        barPos.push_back(QPoint(barSpace + i*(barWidth+barSpace*2), canvasHeight));
    }
}

void CanvasWidget::redrawCanvas() {
    // repaint so that drawing matches the new size
    repaint();
}

void CanvasWidget::paintEvent(QPaintEvent *e) {
    QOpenGLWidget::paintEvent(e);

    QPainter painter(this);
    // fill board with white (faster than drawing a all the white squares individually)
    painter.fillRect(0, 0, this->width(), this->height(), barBackground);

//    painter.fillRect(0, 0, canvasWidth/2, canvasHeight/2, Qt::green);
//    painter.fillRect(canvasWidth/2, canvasHeight/2, canvasWidth, canvasHeight, Qt::red);

    for (auto &i: barPos) {
        painter.fillRect(i.x(), i.y(), barWidth, -(qrand() % this->height()), randomizeBarColor ? QColor(qrand()%255,qrand()%255,qrand()%255) : barColor);
    }
}

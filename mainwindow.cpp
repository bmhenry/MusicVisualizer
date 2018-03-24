#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QTimer>

// TODO: put all drawing in a separate thread
// TODO: figure out how to display an image in the opengl widget

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // window setup
    this->setWindowTitle("Life");

    int x = 1200;
    int y = 800;
    this->resize(x, y);

    QWidget *w = new QWidget(this);
    this->setCentralWidget(w);

    fullscreenShortcut = new QShortcut(QKeySequence(Qt::Key_F11), this);
    fullscreenShortcut->setContext(Qt::ApplicationShortcut);
    connect(fullscreenShortcut, SIGNAL(activated()), this, SLOT(toggleFullscreen()));

    // widget setup
    QVBoxLayout *mainLayout = new QVBoxLayout(w);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    canvas = new CanvasWidget(x, y, w);
    mainLayout->addWidget(canvas);

    // initialize bar settings
    canvas->setBarNum(25);
    canvas->setBarBackground(Qt::black);
    canvas->setBarColor(QColor(100, 255, 200));
    canvas->setRandomizeBarColor(true);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), canvas, SLOT(redrawCanvas()));
    timer->start(1000/60); // 60 fps
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    canvas->setCanvasWidth(this->width());
    canvas->setCanvasHeight(this->height());
    canvas->resizeCanvas();
}


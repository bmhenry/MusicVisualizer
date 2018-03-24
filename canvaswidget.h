#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QOpenGLWidget>

#include <vector>

/*
 * CanvasWidget:
 *   Handles calls to GameLogic and drawing as a OpenGLWidget
 */
class CanvasWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(int width, int height ,QWidget* parent = 0);
    ~CanvasWidget();

    inline void setCanvasWidth(int w) {this->canvasWidth = w;}
    inline void setCanvasHeight(int h) {this->canvasHeight = h;}
    inline void setBarNum(int n) {this->barNum = n;}
    inline void setBarBackground(QColor col) {this->barBackground = col;}
    inline void setBarColor(QColor col) {this->barColor = col;}
    inline void setRandomizeBarColor(bool r) {this->randomizeBarColor = r;}

protected:
    virtual void paintEvent(QPaintEvent *);

public slots:
    void resizeCanvas();
    void redrawCanvas();

private:
    // canvas settings
    int canvasWidth;
    int canvasHeight;

    // bar settings
    int barWidth;
    int barNum;
    int barSpace;
    bool randomizeBarColor;
    QColor barBackground;
    QColor barColor;

    std::vector<QPoint> barPos;

    void updateBarPositions();
};

#endif // CANVASWIDGET_H

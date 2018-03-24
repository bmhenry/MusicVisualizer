#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QShortcut>

#include "canvaswidget.h"


/*
 * MainWindow:
 *   Main display window for the Qt app
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();

private:
    CanvasWidget* canvas;
    QTimer* timer;
    QShortcut* fullscreenShortcut;

    virtual void resizeEvent(QResizeEvent *event);

private slots:
    inline void toggleFullscreen() { if (!isFullScreen()) showFullScreen(); else showNormal(); }
};

#endif // MAINWINDOW_H

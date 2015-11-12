#ifndef NATRON_HSL_COLOR_WHEEL
#define NATRON_HSL_COLOR_WHEEL

#include <cmath>

#include <QWidget>
#include <QColor>
#include <QMouseEvent>

#include "BaseColorWheel.h"

class HSLColorWheel : BaseColorWheel {

private:

public:
    explicit HSLColorWheel(QWidget *parent = 0, QColor color = Qt::white, int radius = 120);
    ~HSLColorWheel ();

protected:
    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent *mouse);
    void mouseButtonPressEvent(QMouseEvent *mouse);

    float pixHue(int x, int y);
    float pixSaturation(int x, int y);
    float pixValue(int x, int y);

};

#endif

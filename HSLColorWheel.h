#ifndef NATRON_HSL_COLOR_WHEEL
#define NATRON_HSL_COLOR_WHEEL

#include <cmath>

#include <QWidget>
#include <QColor>
#include <QMouseEvent>

#include "BaseColorWheel.h"

class HSLColorWheel : BaseColorWheel {

private:
    QImage hs_circle;

public:
    explicit HSLColorWheel(QWidget *parent = 0, QColor color = QColor::fromHslF(0, 0, 0.5), int radius = 120, int ring_size = 8);
    ~HSLColorWheel ();

protected:
    void paintEvent(QPaintEvent *);

    void renderHSCircle(int radius);

    void mouseMoveEvent(QMouseEvent *mouse);
    void mouseButtonPressEvent(QMouseEvent *mouse);

    float pixHue(int x, int y);
    float pixSaturation(int x, int y);
    float pixLightness(int x, int y);

};

#endif

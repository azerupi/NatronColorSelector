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
    virtual ~HSLColorWheel ();

};

#endif

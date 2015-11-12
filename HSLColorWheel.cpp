#include "HSLColorWheel.h"

HSLColorWheel::HSLColorWheel(QWidget *parent, QColor color, int radius)
        : BaseColorWheel(parent, color, radius) {

}

HSLColorWheel::~HSLColorWheel() {}


/*
        PAINTING
*/

void HSLColorWheel::paintEvent(QPaintEvent *e) {

}


/*
        MOUSE EVENTS
*/

void HSLColorWheel::mouseMoveEvent(QMouseEvent *mouse) {

}

void HSLColorWheel::mouseButtonPressEvent(QMouseEvent *mouse) {

}

/*
    Conversion from pixel position to color values
*/

float HSLColorWheel::pixHue(int x, int y) {

}

float HSLColorWheel::pixSaturation(int x, int y) {

}

float HSLColorWheel::pixValue(int x, int y) {

}

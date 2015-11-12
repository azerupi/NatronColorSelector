#include "BaseBaseColorWheel.h"

#include "QPainter"
#include "QRectF"

BaseColorWheel::BaseColorWheel(QWidget *parent): QWidget(parent),
        inner_radius(100),
        outer_radius(120),
        n_outer_dots(9),
        hue(0),
        saturation(0),
        lightness(0.5), {

    setMinimumSize(outer_radius * 2, outer_radius * 2);
}

BaseColorWheel::~BaseColorWheel() {}

/*
        HELPER FUNCTIONS
*/

// Calculates the distance between two points
float BaseColorWheel::distanceBetweenPoints(x1, y1, x2, y2) {
    return std::sqrt( std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2) );
}

//  Checks if a point is in a given radius ()
bool BaseColorWheel::bool inRadius(int x, int y, int c_x, int c_y, int radius) {
    return std::round(distanceBetweenPoints(x , y, c_x, c_y)) <= radius;
}



/*
        GETTERS & SETTERS
*/

QColor BaseColorWheel::getColor() const {
    return QColor::fromHslF(hue, saturation, lightness);
}

float BaseColorWheel::getHue() const {
    return hue;
}

float BaseColorWheel::getSaturation() const {
    return saturation;
}

float BaseColorWheel::getLightness() const {
    return lightness;
}


void BaseColorWheel::setColor(QColor c) {
    setHue(c.hslHue());
    setSaturation(c.hslSaturation());
    setLightness(c.lightness());
    update();
}

void BaseColorWheel::setHue(float h) {
    if (h >= 0 && h <= 1) {
        hue = h;
        update();
    }
}

void BaseColorWheel::setSaturation(float s) {
    if (s >= 0 && s <= 1) {
        saturation = s;
        update();
    }
}

void BaseColorWheel::setLightness(float l) {
    if (l >= 0 && l <= 1) {
        lightness = l;
        update();
    }
}

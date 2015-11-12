#include "HSLColorWheel.h"

#include "QPainter"
#include "QRectF"

HSLColorWheel::HSLColorWheel(QWidget *parent, QColor color, int radius)
        : BaseColorWheel(parent, color, radius) {

    renderHSCircle(inner_radius);
}

HSLColorWheel::~HSLColorWheel() {}


/*
        PAINTING
*/

void HSLColorWheel::paintEvent(QPaintEvent *e) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;

    // Draw HS circle
    path.addEllipse(QRectF(0, 0, inner_radius * 2, inner_radius * 2));
    path.translate( center - inner_radius, center - inner_radius );
    painter.setClipPath(path);

    path = QPainterPath();
    painter.drawImage(center - inner_radius, center - inner_radius, hs_circle);

}

void HSLColorWheel::renderHSCircle(int radius) {
    hs_circle = QImage(radius * 2, radius * 2, QImage::Format_ARGB32_Premultiplied);

    // Correction offset, because the circle can have a smaller radius than the outer_radius and thus not be centered
    int center_offset = center - radius;

    for (int x = 0; x < radius * 2; x++) {
        for (int y = 0; y < radius * 2; y++) {
            hs_circle.setPixel(x, y, QColor::fromHslF(
                pixHue(x + center_offset, y + center_offset),
                pixSaturation(x + center_offset, y + center_offset),
                pixLightness(x + center_offset, y + center_offset)
            ).rgb());
        }
    }
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
    x -= center;
    y = -y + center;

    // To display red at the top, whe have to rotate 90° clockwise from the normal atan2(y, x) + PI
    // Imagine a axis system like this (Qt uses such axis system):
    //      +-------->
    //      |        x      When rotated 90° clockwise, the y value is on the -x axis and the x value on the y axis
    //      |               So we can write atan2(x, -y)
    //      v y             The PI constant is added because atan2 returns a value between -PI and PI but we need a value
    //                      between 0 and 2*PI
    float angle = std::atan2(x, -y) + PI;

    float h = angle / (2 * PI);

    return h;
}

float HSLColorWheel::pixSaturation(int x, int y) {
    float s = distanceBetweenPoints(center, center, x, y) / inner_radius;

    if(s > 1) { s = 1.0; }

    return s;
}

float HSLColorWheel::pixLightness(int x, int y) {
    // TODO: implement
    return 0.5;
}

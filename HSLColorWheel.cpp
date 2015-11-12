#include "HSLColorWheel.h"

#include "QPainter"
#include "QRectF"

#include <iostream>

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

    // Draw Lightness ring
    QConicalGradient gradient_lightness(center, center, -90);
    gradient_lightness.setColorAt(0, Qt::white);
    gradient_lightness.setColorAt(1, Qt::black);
    path.addEllipse(QRectF(0, 0, (inner_radius + ring_size * 2) * 2 , (inner_radius + ring_size * 2) * 2 ));
    path.translate(center - (inner_radius + ring_size * 2), center - (inner_radius + ring_size * 2));
    painter.setPen(QPen(QColor(75, 75, 75), 1.2));
    painter.fillPath(path, gradient_lightness);
    painter.drawPath(path);

    // Draw Hue ring
    path = QPainterPath();
    QConicalGradient gradient_hue(center, center, 0);
    for ( float a = 0; a < 1.0; a += 1.0 / float(24 - 1) ) {
        float c = a + 0.75;
        if ( c >= 1 ) { c -= 1; }
        gradient_hue.setColorAt(a, QColor::fromHslF(c, 1.0, 0.5));
    }
    gradient_hue.setColorAt(1,QColor::fromHslF(0, 1, 0.5).rgb());

    path.addEllipse(QRectF(0, 0, (inner_radius + ring_size) * 2 , (inner_radius + ring_size) * 2 ));
    path.translate(center - (inner_radius + ring_size), center - (inner_radius + ring_size));
    painter.setPen(Qt::NoPen);
    painter.fillPath(path, gradient_hue);
    painter.drawPath(path);

    // Draw HS circle
    path = QPainterPath();
    path.addEllipse(QRectF(0, 0, inner_radius * 2, inner_radius * 2));
    path.translate( center - inner_radius, center - inner_radius );
    painter.setClipPath(path);

    path = QPainterPath();
    painter.setPen(QPen(QColor(75, 75, 75), 1));
    painter.drawImage(center - inner_radius, center - inner_radius, hs_circle);

    painter.setClipping(false);



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
    return 0.3;
}

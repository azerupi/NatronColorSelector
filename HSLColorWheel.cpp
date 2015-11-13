#include "HSLColorWheel.h"

#include "QPainter"
#include "QRectF"
#include "QMatrix"

#include <iostream>

HSLColorWheel::HSLColorWheel(QWidget *parent, QColor color, int radius, int ring_size)
        : BaseColorWheel(parent, color, radius, ring_size),
        mouse_state(None) {

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
    QConicalGradient gradient_hue(center, center, 104);
    for ( float a = 0; a < 1.0; a += 1.0 / float(24 - 1) ) {
        gradient_hue.setColorAt(a, QColor::fromHslF(a, 1.0, 0.5));
    }
    gradient_hue.setColorAt(1, QColor::fromHslF(0, 1, 0.5).rgb());

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
    // Draw skin tone reference
    painter.setPen(QPen(QColor(75, 75, 75), 1));
    // 123° for skin tones
    painter.drawLine(QLine(center, center, inner_radius * std::cos(123.0 * PI / 180), inner_radius * std::sin(-123.0 * PI / 180) ));

    painter.setClipping(false);

    // Draw circle selector
    path = QPainterPath();
    path.addEllipse(QRectF(0, 0, 8, 8));
    int x = saturation * inner_radius * std::sin(hue * 2 * PI + (14 * PI) / 180);
    int y = saturation * inner_radius * std::cos(hue * 2 * PI + (14 * PI) / 180);
    path.translate(center - 4 - x, center - 4 - y);
    painter.fillPath(path, QColor(200, 200, 200));
    painter.setPen(QPen(QColor(25, 25, 25), 1));
    painter.drawPath(path);

    // Draw hue selector
    path = QPainterPath();
    QPolygonF triangle;
    triangle << QPoint(0,0) << QPoint(ring_size * 1.5, 0) << QPoint(ring_size * 0.75, ring_size + 2) << QPoint(0,0);
    triangle = QMatrix().translate(center, center)
                        .rotate(-360 * hue)
                        .rotate(-14)
                        .translate(-ring_size * 0.75, -inner_radius - ring_size)
                        .map(triangle);

    path.addPolygon(triangle);
    painter.fillPath(path, QColor(200, 200, 200));
    painter.drawPath(path);

    // Draw lightness selector
    path = QPainterPath();
    triangle = QPolygonF();
    triangle << QPoint(0,0) << QPoint(ring_size * 1.5, 0) << QPoint(ring_size * 0.75, ring_size + 2) << QPoint(0,0);
    triangle = QMatrix().translate(center, center)
                        .rotate(360 * lightness)
                        .rotate(-180)
                        .translate(-ring_size * 0.75, -inner_radius - ring_size)
                        .scale(1, -1)
                        .map(triangle);

    path.addPolygon(triangle);
    painter.fillPath(path, QColor(200, 200, 200));
    painter.drawPath(path);

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
                lightness
            ).rgb());
        }
    }
}


/*
        MOUSE EVENTS
*/

void HSLColorWheel::mouseMoveEvent(QMouseEvent *mouse) {
    if( mouse_state == HSCircle ) {
        setHue(pixHue(mouse->x(), mouse->y()));
        setSaturation(pixSaturation(mouse->x(), mouse->y()));
    }
    else if( mouse_state == HRing ) {
        setHue(pixHue(mouse->x(), mouse->y()));
    }
    else if( mouse_state == LRing ) {
        setLightness(pixLightness(mouse->x(), mouse->y()));
    }
}

void HSLColorWheel::mousePressEvent(QMouseEvent *mouse) {
    if( inRadius(mouse->x(), mouse->y(), center, center, inner_radius ) ){
        mouse_state = HSCircle;
        setHue(pixHue(mouse->x(), mouse->y()));
        setSaturation(pixSaturation(mouse->x(), mouse->y()));
    }
    else if( inRadius(mouse->x(), mouse->y(), center, center, inner_radius + ring_size)) {
        mouse_state = HRing;
        setHue(pixHue(mouse->x(), mouse->y()));
    }
    else if( inRadius(mouse->x(), mouse->y(), center, center, inner_radius + ring_size * 2)) {
        mouse_state = LRing;
        setLightness(pixLightness(mouse->x(), mouse->y()));
    }
}

void HSLColorWheel::mouseReleaseEvent(QMouseEvent *mouse) {
    mouse_state = None;
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
    float angle = std::atan2(x, -y) + PI - (14 * PI) / 180;
    if(angle < 0) { angle += 2 * PI; }
    float h = angle / (2 * PI);

    return h;
}

float HSLColorWheel::pixSaturation(int x, int y) {
    float s = distanceBetweenPoints(center, center, x, y) / inner_radius;

    if(s > 1) { s = 1.0; }

    return s;
}

float HSLColorWheel::pixLightness(int x, int y) {
    x -= center;
    y = -y + center;
    float angle = std::atan2(x, y) + PI;
    float l = angle / (2 * PI);
    return l;
}


void HSLColorWheel::setLightness(float l) {
    if (l >= 0 && l <= 1) {
        lightness = l;
        renderHSCircle(inner_radius);
        update();
    }
}

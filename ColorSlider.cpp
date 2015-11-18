#include "ColorSlider.h"

#include "QPainter"
#include "QRectF"

ColorSlider::ColorSlider(QWidget *parent, Orientation orientation, Type type)
        : QWidget(parent),
        value(0.5),
        orientation(orientation),
        type(type),
        gradient(QLinearGradient()) {

    int width, height = 0;

    if (orientation == Horizontal) {
        width = 50;
        height = 20;
        setFixedHeight(height);
    }
    else {
        width = 20;
        height = 50;
        setFixedWidth(width);
    }

    setMinimumSize(width, height);

    switch(type) {
        case BW:
            gradient.setColorAt(0, Qt::black);
            gradient.setColorAt(1, Qt::white);
            break;
        default:
            break;
    }
}

ColorSlider::~ColorSlider() {}


/*
        PAINTING
*/

void ColorSlider::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    int width = geometry().width();
    int height = geometry().height();
    int border_radius = (orientation == Horizontal)? height / 2 : width / 2;
    float border_tickness = 1.2;
    int selector_size;

    if(orientation == Horizontal) {
        height -= 4;
        selector_size = height;
        gradient.setStart(border_tickness, 0);
        gradient.setFinalStop(width - 2 * border_tickness, 0);
    } else {
        width -= 4;
        selector_size = width;
        gradient.setStart(0, border_tickness);
        gradient.setFinalStop(0, height - 2 * border_tickness);
    }

    QPainterPath path = QPainterPath();

    // slider
    // TODO: Correct the displacememet in function of orientation...
    path.addRoundedRect(QRectF(border_tickness + 2, border_tickness + 2, width - 2 * border_tickness, height - 2 * border_tickness),
                        border_radius, border_radius );

    painter.fillPath(path, gradient);
    painter.setPen(QPen(QColor(75, 75, 75), border_tickness));
    painter.drawPath(path);

    // Draw selector
    path = QPainterPath();
    QPainterPath negative_path = QPainterPath();

    path.addEllipse(QRectF(0, 0, selector_size, selector_size));
    negative_path.addEllipse(QRectF(5, 5, selector_size - 2 * 5, selector_size - 2 * 5));
    path -= negative_path;

    //path.translate()

    painter.fillPath(path, Qt::white);
    painter.setPen(QPen(QColor(75, 75, 75), 1.0));
    painter.drawPath(path);
}

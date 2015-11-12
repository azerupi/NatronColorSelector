#ifndef NATRON_ABSTRACT_COLOR_WHEEL
#define NATRON_ABSTRACT_COLOR_WHEEL


#include <cmath>

#include <QWidget>
#include <QColor>
#include <QMouseEvent>

// Pi constant
const float PI = std::acos(float(-1));

class BaseColorWheel: public QWidget {

    Q_OBJECT

protected:
    int outer_radius;
    int inner_radius;

    int n_outer_dots;

    float hue;
    float saturation;
    float lightness;

public:
    explicit BaseColorWheel(QWidget *parent = 0, QColor color = Qt::white, int radius = 120);
    virtual ~BaseColorWheel() = 0;

    QColor getColor() const;           // Get current color
    float getHue() const;              // Get current hue          between 0 and 1
    float getSaturation() const;       // Get current saturation   between 0 and 1
    float getLightness() const;            // Get current value        between 0 and 1

public slots:
    void setColor(QColor c);        // Set current color
    void setHue(float h);           // Set current hue
    void setSaturation(float s);    // Set current saturation
    void setLightness(float l);         // Set current value

signals:
    // Emitted when the user sets a color or the color is changed with setColor
    void colorChanged(QColor);

    // Emitted when the users sets a color
    void colorSelected(QColor);

protected:
    virtual void paintEvent(QPaintEvent *) = 0;

    virtual void mouseMoveEvent(QMouseEvent *mouse) = 0;
    virtual void mouseButtonPressEvent(QMouseEvent *mouse) = 0;

    void resizeEvent(QResizeEvent *resize);

    virtual float pixHue(int x, int y) = 0;
    virtual float pixSaturation(int x, int y) = 0;
    virtual float pixValue(int x, int y) = 0;

    // Calculates the distance between two points
    float distanceBetweenPoints(int x1, int y1, int x2, int y2);

    // Calculates if a point is in a given radius
    bool inRadius(int x, int y, int c_x, int c_y, int radius);

};

#endif

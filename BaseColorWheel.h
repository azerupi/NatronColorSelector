#ifndef NATRON_ABSTRACT_COLOR_WHEEL
#define NATRON_ABSTRACT_COLOR_WHEEL


#include <cmath>

#include <QWidget>
#include <QColor>
#include <QMouseEvent>

// Pi constant
const float pi = std::acos(float(-1));

class BaseColorWheel: QWidget {

    Q_OBJECT

private:
    int outer_radius;
    int inner_radius;

    int n_outer_dots;

    float hue;
    float saturation;
    float lightness;

public:
    explicit BaseColorWheel(QWidget *parent = 0);
    ~BaseColorWheel();

    QColor getColor() const;           // Get current color
    float getHue() const;              // Get current hue          between 0 and 1
    float getSaturation() const;       // Get current saturation   between 0 and 1
    float getValue() const;            // Get current value        between 0 and 1

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
    virtual void paintEvent(QPaintEvent *);

    virtual void mouseMoveEvent(QMouseEvent *mouse);
    virtual void mouseButtonPressEvent(QMouseEvent *mouse);

    void resizeEvent(QResizeEvent *resize);

    virtual float pixHue(int x, int y);
    virtual float pixSaturation(int x, int y);
    virtual float pixValue(int x, int y);

    // Calculates the distance between two points
    float distanceBetweenPoints(x1, y1, x2, y2);

    // Calculates if a point is in a given radius
    bool inRadius(int x, int y, int c_x, int c_y, int radius);

};

#endif

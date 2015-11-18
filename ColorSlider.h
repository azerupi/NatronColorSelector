#ifndef NATRON_COLOR_SLIDER
#define NATRON_COLOR_SLIDER

#include <cmath>

#include <QWidget>
#include <QColor>
#include <QMouseEvent>


class ColorSlider : public QWidget {

public:
    enum Orientation { Horizontal, Vertical };
    enum Type { Red, Green, Blue, Hue, BW, Alpha, Custom };

    explicit ColorSlider(QWidget *parent = 0, Orientation orientation = Horizontal, Type type = BW);
    ~ColorSlider ();

    //void setBGGradient(QLinearGradient g);

private:
    float value;
    Orientation orientation;
    Type type;
    QLinearGradient gradient;


protected:
    void paintEvent(QPaintEvent *);

    //void mouseMoveEvent(QMouseEvent *mouse);
    //void mousePressEvent(QMouseEvent *mouse);
    //void mouseReleaseEvent(QMouseEvent *mouse);

};

#endif

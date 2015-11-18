#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

#include "HSLColorWheel.h"
#include "ColorSlider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    QVBoxLayout vl1(&window);

    HSLColorWheel wheel(&window);
    ColorSlider slider(&window);

    vl1.addWidget(&wheel);
    vl1.addWidget(&slider);

    window.setLayout(&vl1);
    window.show();
    return app.exec();
}

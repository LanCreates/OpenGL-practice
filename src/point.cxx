#include "point.h"

const float DEG_TO_RAD = 0.01745;

float Point2D::locate(int radius, int screen_size, float degree, char axis) {
    float relative_position = (float)radius/screen_size;
    return axis == 'x'? std::cos(degree*DEG_TO_RAD)*relative_position: 
                        std::sin(degree*DEG_TO_RAD)*relative_position;
}

#include "Camera.hpp"

Camera::Camera(shared_ptr<Logger> logger, double _real_width, double _real_height, double _height, double _pos_x, double _pos_y)
{
    log = logger;
    real_width = _real_width;
    real_height = _real_height;
    height = _height;
    pos_x = _pos_x;
    pos_y = _pos_y;
    width = height * real_width / real_height;
}

double Camera::getWidth()
{
    return width;
}

double Camera::getHeight()
{
    return height;
}

pair<double, double> Camera::getPoint(double x, double y)
{
    pair<double, double> tmp;
    x -= pos_x;
    y -= pos_y;
    tmp.first = 2.0 * x / width;
    tmp.second = 2.0 * y / height;
    return tmp;
}

#pragma once

#include "global.hpp"

#include "Logger.hpp"

class Camera
{
protected:
    shared_ptr<Logger> log;
    double real_width;
    double real_height;
    double height;
    double width;
    double pos_x;
    double pos_y;

public:
    Camera(shared_ptr<Logger> logger, double _real_width, double _real_height, double _height, double _pos_x, double _pos_y);
    pair<double, double> getPoint(double x, double y);
    double getWidth();
    double getHeight();
};

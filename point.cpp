#include "point.h"

point::point()

{

}

point::point(float x, float y)
:_x(x), _y(y)
{

}

float point::x()
{
    return _x;
}

float point::y()
{
    return _y;
}

void point::setX(float x)
{
    _x = x;
}

void point::setY(float y)
{
    _y = y;
}

float point::distance(point end)
{
    float x_distance = end.x() - _x;
    float y_distance = end.y() - _y;

    float distance = sqrt(x_distance*x_distance + y_distance*y_distance);

    return distance;

}

#include "util.h"
#include <math.h>
#define PI 3.14159
void Util::movePointXY(double x0, double y0, double &x1, double &y1, double xDist, double yDist)
{
    x1 = x0 - xDist;
    y1 = y0 - yDist;
}


void Util::scalePointXY(double x0, double y0, double &x1, double &y1,double xFactor, double yFactor)
{
    x1 = x0 * xFactor;
    y1 = y0 * yFactor;
}

void Util::rotatePointXY(double x0, double y0, double &x1, double &y1, double angle, double rxCenter, double ryCenter)
{
    double a = PI * angle / 180;
//    x1 = (x0 - rxCenter) *cos(a) + (y0 - ryCenter) *sin(a);
//    y1 = -(x0 - rxCenter) *sin(a) + (y0 - ryCenter) * cos(a);

    movePointXY(x0,y0,x1,y1,rxCenter,ryCenter);
    x1 = x0 *cos(a) + y0 *sin(a);
    y1 = -x0 *sin(a) + y0 * cos(a);
    movePointXY(x1,y1,x1,y1,-rxCenter,-ryCenter);
}

void Util::transPointRTheta(double x, double y, double &r, double &theta)
{
//    double x1,y1;
//    scalePointXY(x,y,x1,y1);

//    theta = atan(y1/x1);
//    double r_ = sqrt(x1*x1+y1*y1);
//    r = r_*200.0;//映射
}


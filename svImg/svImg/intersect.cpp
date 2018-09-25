#include "intersect.h"
#include <cmath>

bool inShape(double x, double y, Shape shape, bool flag){
    //！定义坐标系
    //! XY轴坐标长度
    const double xLength = 200.0;
    const double yLength = 200.0;
    //! 当前像素点映射到坐标轴上
    double xPos = x * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
    double yPos = y * yLength - yLength/2;


    switch(shape){
        case Circle:
        {
            //! (椭)圆：x^2+y^2-r^2<0
            const double r = 100.0;
            const double a = 1.0;
            const double b = 1.0;
            double value = xPos * xPos / (a*a) + yPos * yPos / (b*b) - r * r;

            if(flag){//是否在内部？
                return value < 0;
            }
            else{//是否在边界？
                return fabs(value) < 100.0;
            }
            break;
        }
        case Parabola:
        {
            //! 抛物线：ax^2+bx+c-y>0
            const double a = -0.01;
            const double b = 0.0;
            const double c = 40;
            double value = a * xPos * xPos + b * xPos + c - yPos;

            if(flag){//是否在内部一侧？
                return value > 0;
            }
            else{//是否在边界？
                return fabs(value) < 5.0;
            }
            break;
        }
    }



    return false;

}

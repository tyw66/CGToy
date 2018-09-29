/** **************************************
 * @brief 2D图形类
 * @author tyw
 * @date 2018/09/29
 ****************************************/
#ifndef SHAPE_H
#define SHAPE_H

#include <math.h>
#include "color.h"

#define PI 3.1415926
namespace tyw {

//! 基类
class Shape
{
public:
    //! 图形位置
    double xPos, yPos;

    //! 填充颜色，边界颜色
    Color color_fill, color_border;

    //! 图形面积
    virtual double getArea(){
        return 0;
    }
    //! 一个点是否在形状内部
    virtual bool isContain(double x, double y){
        return false;
    }

    //! 一个点到该图形的带符号距离场
    virtual double getSDF(double x, double y){
        return sqrt(x * x + y * y);
    }

};

//! 圆
class Circle : public Shape
{
public:
    double r;             /**< 半径*/

    double getArea(){
        return PI * r *r;
    }

    bool isContain(double x, double y){
        return (x - xPos) * (x - xPos) + (y - yPos) * (y - yPos) - r * r < 0;
    }

    double getSDF(double x, double y){
        return  sqrt(x * x  + y * y) - r;
    }

};

//! 椭圆
class Ellipse : public Shape
{
public:
    double a, b;        /**< 椭圆因子*/

    double getArea(){
        return PI * a *b;
    }


    bool isContain(double x, double y){
        return  (x - xPos) *  (x - xPos) / (a * a) + (y - yPos) * (y - yPos) / (b * b) - 1 < 0;
    }
};

}


#endif // SHAPE_H

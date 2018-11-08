/** **************************************
 * @brief 2D图形类
 * @author tyw
 * @date 2018/09/29
 ****************************************/
#ifndef SHAPE_H
#define SHAPE_H

//#include<iostream>
#include <math.h>
#include "color.h"
#include "vec.h"


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

    //! 构造函数
    Shape(){ xPos = 0; yPos = 0; color_fill = Color(0,0,0); }
    Shape(double x, double y, Color color):xPos(x),yPos(y),color_fill(color){}

    //! 颜色
    Color getColor(){
        return color_fill;
    }

    void setColor(const Color& c){
        color_fill = c;
    }


    //! 图形面积
    virtual double getArea(){
        return 0;
    }
    //! 一个点是否在形状内部
    virtual bool isContain(double x, double y) = 0;

    //! 一个点到该图形的带符号距离场
    virtual double getSDF(double x, double y){
        return sqrt(x * x + y * y);
    }


};

//! 三角形
class Triangle3D : public Shape
{
public:
    Vec3 va, vb, vc; /**< 三个顶点*/
    int z_index; /**< */

    Triangle3D(){}
    Triangle3D(const Vec3& v1,const Vec3& v2,const Vec3& v3,const Color& c){
        va = v1; vb = v2; vc = v3;
        xPos = (v1.x+v2.x+v3.y)/3; yPos = (v1.y+v2.y+v3.y)/3;
        color_fill = c;
    }

    bool isContain(double x, double y, double z){
        //叉乘判断法
        Vec3 p(x,y,z);
        Vec3 pa = va - p;
        Vec3 pb = vb - p;
        Vec3 pc = vc - p;

        Vec3 t1 = crossProduct(pa, pb);
        Vec3 t2 = crossProduct(pb, pc);
        Vec3 t3 = crossProduct(pc, pa);

        //如果t1 t2 t3同向，则点在三角形内
        double f1 = t1 * t2;
        double f2 = t1 * t3;

        return f1>0 && f2 >0;
    }

    bool isContain(double x, double y){
        //叉乘判断法
        Vec3 p(x,y,0);
        Vec3 pa = va - p;
        Vec3 pb = vb - p;
        Vec3 pc = vc - p;

        Vec3 t1 = crossProduct(pa, pb);
        Vec3 t2 = crossProduct(pb, pc);
        Vec3 t3 = crossProduct(pc, pa);

        //如果t1 t2 t3同向，则点在三角形内
        double f1 = t1 * t2;
        double f2 = t1 * t3;

        return f1>0 && f2 >0;
    }

    //    Triangle3D projectTo2D(double d){
    //        Vec3 pva, pvb, pvc;

    //        //        d = (va.z + vb.z + vc.z)/3;

    //        pva.x = va.x * d / va.z;
    //        pva.y = va.y * d / va.z;
    //        pva.z = d;

    //        pvb.x = vb.x * d / vb.z;
    //        pvb.y = vb.y * d / vb.z;
    //        pvb.z = d;

    //        pvc.x = vc.x * d / vc.z;
    //        pvc.y = vc.y * d / vc.z;
    //        pvc.z = d;

    //        return tyw::Triangle3D(pva, pvb, pvc, color_fill);
    //    }

    Triangle3D projectTo2D(Vec3 eye, double d){
        Vec3 vva, vvb, vvc;//va在眼坐标下的坐标
        vva = -eye + va;
        vvb = -eye + vb;
        vvc = -eye + vc;

        z_index =  fabs((vva.z + vvb.z + vvc.z)/3 - d);

        Vec3 pva, pvb, pvc;

        pva.x = vva.x * d / vva.z;
        pva.y = vva.y * d / vva.z;
        pva.z = d;

        pvb.x = vvb.x * d / vvb.z;
        pvb.y = vvb.y * d / vvb.z;
        pvb.z = d;

        pvc.x = vvc.x * d / vvc.z;
        pvc.y = vvc.y * d / vvc.z;
        pvc.z = d;

        return tyw::Triangle3D(pva, pvb, pvc, color_fill);
    }

    void rotate(double xAngle, double yAngle, double zAngle){
        va.rotateXAxis(xAngle);
        va.rotateYAxis(yAngle);
        va.rotateZAxis(zAngle);

        vb.rotateXAxis(xAngle);
        vb.rotateYAxis(yAngle);
        vb.rotateZAxis(zAngle);

        vc.rotateXAxis(xAngle);
        vc.rotateYAxis(yAngle);
        vc.rotateZAxis(zAngle);
    }

};


//! 圆
class Circle : public Shape
{
public:
    double r;             /**< 半径*/

    //! 构造函数
    Circle(){r = 1;}

    Circle(double x, double y, Color c, double r_) : Shape(x, y, c)
      ,r(r_){}

    double getArea(){
        return PI * r *r;
    }

    bool isContain(double x, double y){
        return (x - xPos) * (x - xPos) + (y - yPos) * (y - yPos) - r * r < 0;
    }

    double getSDF(const double x, const double y){
        return  sqrt((x - xPos) * (x - xPos)  + (y - yPos) * (y - yPos)) - r;
    }

};

//! 椭圆
class Ellipse : public Shape
{
public:
    double a, b;        /**< 椭圆因子*/

    //! 构造函数
    Ellipse(){a = b = 1;}

    Ellipse(double x, double y, Color c, double a_, double b_) : Shape(x, y, c){a = a_; b = b_;}


    double getArea(){
        return PI * a *b;
    }


    bool isContain(double x, double y){
        return  (x - xPos) *  (x - xPos) / (a * a) + (y - yPos) * (y - yPos) / (b * b) - 1 < 0;
    }
};

//! 扇形
class Fan : public Circle
{
public:
    double start, end;        /**< 起始、终止角度*/

    //! 构造函数
    Fan(){start = 0; end = 2 * PI;}

    Fan(double x, double y, Color c, double r, double start_, double end_) : Circle(x, y, c, r){start = start_; end = end_;}


    double getArea(){
        return PI * r *r * (end - start)/(2*PI);
    }


    bool isContain(double x, double y){
        if( (x - xPos) * (x - xPos) + (y - yPos) * (y - yPos) - r * r > 0){
            return false;
        }

        //! 不对 啊
        if( acos(x / r) > start && acos(x / r) < end && asin(y/r) > start && asin(y/r) > end){
            return true;
        }
        return false;
    }
};


//! 矩形
class Rect : public Shape{
public:
    double x,y,width,height;

    Rect(){}

    Rect(double x, double y, Color c, double width_, double height_):Shape(x, y, c)
      ,width(width_),height(height_)
    {}

    bool isContain(double x, double y){
        return x > xPos && x < xPos + width && y > yPos && y < yPos +height;
    }

};

//! 心形线
//! x^2+(y-x^(2/3))^2=1
class Heart : public Shape{
public:
    double size;

    Heart(){}
    Heart(double x, double y, Color c, double size_) : Shape(x, y, c)
      ,size(size_){}

    bool isContain(double x, double y){
        double n = -(y-yPos) - pow((x-xPos),2.0/3);
        return  x*x + n * n -size < 0;
        //        return size*(1-sin(theta)) < r;

    }


};



}




#endif // SHAPE_H

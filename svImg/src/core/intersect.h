#ifndef INTERSECT_H
#define INTERSECT_H

enum ShapeType{
    Circle = 0, //(椭)圆
    Parabola   //抛物线
};

/**
 * @brief  判断点是否在形状内，输入是
 * @param x: 归一化后的坐标
 * @param y: 归一化后的坐标
 * @param shape: 哪种形状
 * @param flag: true-内部 false-边缘
 * @return
 */
bool inShape(double x, double y, ShapeType shape, bool flag=true);

/**
 * @brief circleSDF   (椭)圆：x^2+y^2-r^2<0
 * @param x 当前点
 * @param y
 * @param ox 圆心
 * @param oy
 * @param r 半径
 * @param a 椭圆参数a
 * @param b 椭圆参数b
 * @param flag 在图形上
 * @return
 */
bool inCircle(double x, double y, double ox, double oy, double r, double a, double b, bool flag = false);
/**
 * @brief inParabola   抛物线：ax^2+bx+c-y>0
 * @param x 当前点
 * @param y
 * @param a
 * @param b
 * @param c
 * @param flag 在图形上
 * @return
 */
bool inParabola(double x, double y, double a, double b, double c, bool flag = false);


#endif // INTERSECT_H

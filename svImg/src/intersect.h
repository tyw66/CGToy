#ifndef INTERSECT_H
#define INTERSECT_H

enum Shape{
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
bool inShape(double x, double y, Shape shape, bool flag=true);


#endif // INTERSECT_H

#ifndef CASE_H
#define CASE_H

#include "color.h"
#include "shape.h"
#include "muti_shape.h"
#include <math.h>

/**
 * @brief 当前像素点映射到坐标轴上,xy直角坐标系
 * Detail. 定义坐标系
 * @param x0 变换前X : 0-1
 * @param y0
 * @param x1 变换后X
 * @param y1
 */
void transPointXY(double x0, double y0, double &x1, double &y1);
/**
 * @brief 旋转坐标点
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param angle 旋转角度
 */
void rotatePointXY(double x0, double y0, double& x1, double& y1, double angle);
/**
 * @brief 当前像素点映射到坐标轴上，极坐标系
 * Detail. 定义坐标系
 * @param x0 变换前X: 0-1
 * @param y0
 * @param r 变换后
 * @param theta
 * @return
 */
void transPointRTheta(double x, double y, double& r, double& theta);

/**
 * @brief 参数图形。位置随鼠标移动,半径随时间变化
 * @param x 当前绘制的像素归一化位置
 * @param y
 * @param mx 鼠标归一化位置
 * @param my
 * @param time 时间，动画用
 * @return 该像素的颜色
 */
Color case000(double x, double y, double mx, double my, int time = 0);

/**
 * @brief 图案
 */
Color case001(double x, double y, double mx, double my, int time = 0);

/**
 * @brief 滑稽表情
 */
Color case002(double x, double y, double mx, double my, int time = 0);

/**
 * @brief  画三角形
 */
Color case003(double x, double y, double mx, double my, int time = 0);

/**
 * @brief  画光
 */
Color case004(double x, double y, double mx, double my, int time = 0);

double trace(double x, double y, double dx, double dy, tyw::Circle &circle);



#endif

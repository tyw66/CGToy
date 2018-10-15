#ifndef CASE_H
#define CASE_H

#include "color.h"

/**
 * @brief 当前像素点映射到坐标轴上
 * Detail. 定义坐标系
 * @param x0 变换前X
 * @param y0
 * @param x1 变换后X
 * @param y1
 * @return
 */
bool transPoint(double x0, double y0, double& x1, double& y1);

/**
 * @brief 圆。位置随鼠标移动,半径随时间变化
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




#endif

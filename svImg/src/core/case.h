#ifndef CASE_H
#define CASE_H

#include "color.h"
#include "shape.h"
#include "muti_shape.h"
#include <math.h>


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
 * @brief  画三角形
 */
int case03(double x, double y, double mx, double my, int time = 0);
/**
 * @brief  画光
 */
Color case004(double x, double y, double mx, double my, int time = 0);

double trace(double x, double y, double dx, double dy, tyw::Circle &circle);

/**
 * @brief  画时锺
 */
Color case005(double x, double y, double mx, double my, int time = 0);

#endif

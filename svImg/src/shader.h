#ifndef SHADER_H
#define SHADER_H

#include "../common/color.h"

/**
 * @brief 画棋盘格复合图形
 * @param x 归一化后的x坐标
 * @param y 归一化后的y坐标
 * @return 该点的颜色
 */
Color3 shader01(double x, double y);

/**
 * @brief 画人脸
 * @param x 归一化后的x坐标
 * @param y 归一化后的y坐标
 * @param time
 * @return 该点的颜色
 */
Color3 shader02(double x, double y, int time=1);



#endif // SHADER_H

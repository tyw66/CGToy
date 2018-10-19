#ifndef UTIL_H
#define UTIL_H

namespace Util
{
/**
 * @brief 平移坐标点
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param xDist
 * @param yDist
 */
void movePointXY(double x0, double y0, double &x1, double &y1,double xDist, double yDist);
/**
     * @brief 当前像素点映射到坐标轴上,xy直角坐标系
     * @param x0 变换前X : 0-1
     * @param y0
     * @param x1 变换后X
     * @param y1
     */
void scalePointXY(double x0, double y0, double &x1, double &y1,double xFactor, double yFactor);
/**
     * @brief 旋转坐标点
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param angle 旋转角度
     */
void rotatePointXY(double x0, double y0, double& x1, double& y1, double angle, double rxCenter, double ryCenter);

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


}
#endif // UTIL_H

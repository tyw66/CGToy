#include "testtime.h"



TestTime::TestTime()
{

}

Color TestTime::draw(double x, double y, int time)
{
    //! 背景滑稽黄
    color.set(250, 211, 94);

    //! 定义坐标系
    //! XY轴坐标长度
    const double xLength = 200.0;
    const double yLength = 200.0;
    //! 当前像素点映射到坐标轴上
    double xPos = x * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
    double yPos = y * yLength - yLength/2;

    //! 加入对象构建场景
//    tyw::Circle circle001;
    circle001.xPos = 50;
    circle001.yPos = 50;
    circle001.r = 10;

//    tyw::Circle circle002;
    circle002.xPos = -30;
    circle002.yPos = -50;
    circle002.r = 30;

//    tyw::Circle circle003;
    circle003.xPos = 0;
    circle003.yPos = 0;
    circle003.r = 80;

    //! 构造实体几何
    if(circle003.isContain(xPos,yPos) && !circle001.isContain(xPos,yPos) && !circle002.isContain(xPos,yPos)){
        color.set(255,0,0);

//        tyw::Circle circle004;
        circle004.xPos = 0;
        circle004.yPos = 0;
        circle004.r = 60;

//        tyw::Circle circle005;
        circle005.xPos = 0;
        circle005.yPos = 0;
        circle005.r = 50;

        if(circle004.isContain(xPos,yPos) && !circle005.isContain(xPos,yPos)){
            color.set(255,255,255);
        }
    }
    return color;
}

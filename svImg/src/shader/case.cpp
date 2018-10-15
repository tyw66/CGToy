#include "shape.h"
#include "muti_shape.h"

bool transPoint(double x0, double y0, double &x1, double &y1)
{
    //! XY轴坐标长度
    const double xLength = 200.0;
    const double yLength = 200.0;
    //! 当前像素点映射到坐标轴上
    x1 = x0 * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
    y1 = y0 * yLength - yLength/2;

    return true;
}

Color case000(double x, double y, double mx, double my, int time)
{
    Color color(250, 211, 94);    //背景填充

    //! 坐标转换
    double xPos, yPos;
    transPoint(x,y,xPos,yPos);
    double xCircle,yCircle;//圆心
    transPoint(mx,my,xCircle,yCircle);

//    double r = 30;
    double r = 30+10*sin(time/2);//半径随时间变化
    tyw::Circle circle(xCircle,yCircle,Color(255,0,0),r);
    if(circle.isContain(xPos,yPos)){
        return circle.getColor();
    }
    return color;
}


Color case001(double x, double y, double mx, double my, int time = 0)
{
    //! 背景滑稽黄
    Color color(250, 211, 94);

    //! 坐标转换
    double xPos, yPos;
    transPoint(x,y,xPos,yPos);

    //! 加入对象构建场景
    tyw::Circle circle001;
    circle001.xPos = 50;
    circle001.yPos = 50;
    circle001.r = 10;

    tyw::Circle circle002;
    circle002.xPos = -30;
    circle002.yPos = -50;
    circle002.r = 30;

    tyw::Circle circle003;
    circle003.xPos = 0;
    circle003.yPos = 0;
    circle003.r = 80;

    //! 构造实体几何
    if(circle003.isContain(xPos,yPos) && !circle001.isContain(xPos,yPos) && !circle002.isContain(xPos,yPos)){
        color = Color(255,0,0);

        tyw::Circle circle004;
        circle004.xPos = 0;
        circle004.yPos = 0;
        circle004.r = 60;

        tyw::Circle circle005;
        circle005.xPos = 0;
        circle005.yPos = 0;
        circle005.r = 50;

        if(circle004.isContain(xPos,yPos) && !circle005.isContain(xPos,yPos)){
            color = Color(255,255,255);
        }
    }
    return color;
}



Color case002(double x, double y, double mx, double my, int time = 0)
{
    //t变化范围：0～1
    double t = sin(time)*0.5+0.5;

    //! 背景色
    Color color(225,225,225);

    //! 定义坐标系
    //! XY轴坐标长度
    const double xLength = 200.0;
    const double yLength = 200.0;
    //! 当前像素点映射到坐标轴上
    double xPos = x * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
    double yPos = (y * yLength - yLength/2);

    //! 加入对象构建场景
    //脸
    tyw::Circle face(0,0, Color(250,211,94), 90);
    if(face.isContain(xPos,yPos)){
        color.set(face.color_fill.r,face.color_fill.g,face.color_fill.b);
    }
    //    else {
    //        return color;
    //    }

    //嘴巴
    tyw::Circle mouth_top(0,-10, Color(20,20,20), 82);
    tyw::Circle mouth_buttom(0,0, Color(124,64,12), 80);
    Ring r(mouth_buttom,mouth_top);
    if(r.isContain(xPos,yPos)){
        color.set(mouth_buttom.color_fill.r,mouth_buttom.color_fill.g,mouth_buttom.color_fill.b);
    }

    //眉毛
    tyw::Circle c0(0,-300, Color(124,64,12), 240);
    tyw::Circle c1(-55,-60, Color(20, 20, 20), 15);
    tyw::Circle c2(-55,-60, Color(20,20,20), 10);
    tyw::Circle c3(55,-60, Color(20, 20, 20), 15);
    tyw::Circle c4(55,-60, Color(20,20,20), 10);
    BendShape eyebrow1(c1,c2,c0);
    BendShape eyebrow2(c3,c4,c0);
    if(eyebrow1.isContain(xPos,yPos) || eyebrow2.isContain(xPos,yPos)){
        color.set(c0.color_fill.r,c0.color_fill.g,c0.color_fill.b);
    }

    //脸颊
    tyw::Ellipse e1(-70,-10, Color(250,190,130),20,10);
    tyw::Ellipse e2(70,-10, Color(250,190,130),20,10);
    if(e1.isContain(xPos, yPos) || e2.isContain(xPos, yPos)){
        color.set(e1.color_fill.r,e1.color_fill.g,e1.color_fill.b);
    }

    //左眼睛
    tyw::Rect rect1(-80,-45,Color(255, 255, 255),50,16);
    tyw::Circle cLeft(-80,-37, Color(20, 20, 20), 8);
    tyw::Circle cRight(-30,-37, Color(20,20,20), 8);
    Capsule eye1(rect1, cLeft,cRight);
    if(eye1.isContain(xPos, yPos)){
        color.set(rect1.color_fill.r,rect1.color_fill.g,rect1.color_fill.b);
    }

    //右眼睛
    tyw::Rect rect2(30,-45,Color(255, 255, 255),50,16);
    tyw::Circle cLeft2(80,-37, Color(20, 20, 20), 8);
    tyw::Circle cRight2(30,-37, Color(20,20,20), 8);
    Capsule eye2(rect2, cLeft2,cRight2);
    if(eye2.isContain(xPos, yPos)){
        color.set(rect2.color_fill.r,rect1.color_fill.g,rect1.color_fill.b);
    }

    //左眼珠（变化范围 -80~-30）
//    tyw::Circle ball1(-79,-37, Color(20,20,20), 8);//无动画
    tyw::Circle ball1(-80+t*50,-37, Color(20,20,20), 8);
    if(ball1.isContain(xPos, yPos)){
        color.set(ball1.color_fill.r,ball1.color_fill.g,ball1.color_fill.b);
    }

    //右眼珠（变化范围 30~80）
//    tyw::Circle ball2(31,-37, Color(20,20,20), 8);//无动画
    tyw::Circle ball2(30+t*50,-37, Color(20,20,20), 8);
    if(ball2.isContain(xPos, yPos)){
        color.set(ball2.color_fill.r,ball1.color_fill.g,ball1.color_fill.b);
    }

    return color;
}



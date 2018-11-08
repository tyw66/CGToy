#include "case.h"
#include "stdlib.h"
#include <iostream>

#include "util.h"

Color case000(double x, double y, double mx, double my, int time)
{
    //    Color color(250, 211, 94);    //背景填充
    Color color(0,0,0);    //背景填充

    //! 坐标转换
    double xPos, yPos;
    Util::scalePointXY(x,y,xPos,yPos,200,200);
    double xCenter,yCenter;//圆心
    Util::scalePointXY(mx,my,xCenter,yCenter,200,200);

    //圆
    double r = 30;//+10*sin(time/2);//半径随时间变化
    tyw::Circle circle(xCenter,yCenter,Color(255,0,0),r);
    if(circle.isContain(xPos,yPos)){
        return circle.getColor();
    }

    //心形
    //    double size = 100+5*sin(time/2);//半径随时间变化
    //    tyw::Heart heart(xCenter,yCenter,Color(255,0,0),size);
    //    if(heart.isContain(xPos,yPos)){
    //        return heart.getColor();
    //    }
    return color;
}

void case001(Scene *scene)
{
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

    scene->m_objs.push_back(&circle001);
    scene->m_objs.push_back(&circle002);
    scene->m_objs.push_back(&circle003);
}
Color shader001(Scene* scene,double x, double y, double mx, double my, int time)
{
    //! 背景滑稽黄
    Color color(250, 211, 94);

    //! 坐标转换
    double xPos, yPos;
    Util::scalePointXY(x,y,xPos,yPos,200,200);
    Util::movePointXY(xPos, yPos, xPos, yPos, 100, 100);

    //! 构造实体几何
    //    if(circle003.isContain(xPos,yPos) && !circle001.isContain(xPos,yPos) && !circle002.isContain(xPos,yPos)){
    if(scene->m_objs[2]->isContain(xPos,yPos) &&
            !scene->m_objs[0]->isContain(xPos,yPos) &&
            !scene->m_objs[1]->isContain(xPos,yPos)){
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



Color shader002(double x, double y, double mx, double my, int time)
{
    //t变化范围：0～1
    double t = sin(time)*0.5+0.5;

    //! 背景色
    Color color(225,225,225);

    //! 定义坐标系
    double xPos, yPos;
    Util::scalePointXY(x,y,xPos,yPos,200,200);
    Util::movePointXY(xPos, yPos, xPos, yPos, 100, 100);

    double angle = my * 180.0 - 90;
    Util::rotatePointXY(xPos, yPos,xPos, yPos, angle, 0, 0);

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
    tyw::Ellipse e1(-70,-10, Color(255,190,130),20,10);
    tyw::Ellipse e2(70,-10, Color(255,190,130),20,10);
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
    Capsule eye2(rect2, cLeft2, cRight2);
    if(eye2.isContain(xPos, yPos)){
        color.set(rect2.color_fill.r,rect1.color_fill.g,rect1.color_fill.b);
    }

    //左眼珠（变化范围 -80~-30）
    //        tyw::Circle ball1(-79,-37, Color(20,20,20), 8);//无动画
    //    tyw::Circle ball1(-80+t*50,-37, Color(20,20,20), 8);//随时间动
    tyw::Circle ball1(-80+mx*50,-37, Color(20,20,20), 8);//随鼠标动
    if(ball1.isContain(xPos, yPos)){
        color.set(ball1.color_fill.r,ball1.color_fill.g,ball1.color_fill.b);
    }

    //右眼珠（变化范围 30~80）
    //        tyw::Circle ball2(31,-37, Color(20,20,20), 8);//无动画
    //    tyw::Circle ball2(30+t*50,-37, Color(20,20,20), 8); //随时间动
    tyw::Circle ball2(30+mx*50,-37, Color(20,20,20), 8); //随鼠标动
    if(ball2.isContain(xPos, yPos)){
        color.set(ball2.color_fill.r,ball1.color_fill.g,ball1.color_fill.b);
    }

    return color;
}


int case03(double x, double y, double mx, double my, int time)
{
    //! 背景色
    int value = 0;

    //! 坐标变换
    double xPos, yPos;
    Util::scalePointXY(x,y,xPos,yPos,200,200);
    Util::movePointXY(xPos, yPos, xPos, yPos, 100, 100);
    double xMouse, yMouse;//鼠标
    Util::scalePointXY(mx,my,xMouse,yMouse,200,200);
    Util::movePointXY(xMouse, yMouse, xMouse, yMouse, 100, 100);

    //画两个三角形
    Vec3 vtMouse(xMouse,yMouse,0);
    Vec3 vt1(-60,0,0);
    Vec3 vt2(60,0,0);
    tyw::Triangle3D triangle(vt1,vt2,vtMouse,Color(255,125,0));
    tyw::Triangle3D triangle2(vt1,vt2,-vtMouse,Color(255,255,0));

    if(triangle.isContain(xPos,yPos)){
        value = 4;
    }
    //    else if(triangle2.isContain(xPos,yPos)){
    //        value = 2;
    //    }

    return value;
}

Color case004(double x, double y, double mx, double my, int time)
{
    //! 背景色
    Color color(255, 255, 200);
    double factor = 0;

    //! 坐标转换
    double xPos, yPos;
    Util::scalePointXY(x,y,xPos,yPos,200,200);
    Util::movePointXY(xPos, yPos, xPos, yPos, 100, 100);
    double xCenter,yCenter;//圆心
    Util::scalePointXY(mx,my,xCenter,yCenter,200,200);
    Util::movePointXY(xCenter, yCenter, xCenter, yCenter, 100, 100);

    //! 光源
    double r = 20;
    tyw::Circle lightSource(0,0,Color(255,0,0),r);

    //    //! 物体
    //    double ri = 30;
    //    tyw::Circle item(xCenter,yCenter,Color(255,0,0),ri);

    //    if(item.isContain(xPos,yPos)){
    //        return item.getColor();
    //    }

    //! 不用积分
    //    double sdf = lightSource.getSDF(xPos,yPos) ;
    //    factor = 1 - sdf/500;

    //!  用MC积分计算当前像素点处的光线强度
    const int N = 8;

    for(int i = 0; i < N; ++i){
        //        double a = 6.28 *i / N; //分层采样
        //        double a =  6.28*  rand()/RAND_MAX;//均匀采样
        double a = 6.28 * (i + (double)rand()/RAND_MAX) / N; //抖动采样
        double dx = cos(a);
        double dy = sin(a);
        factor += trace(xPos,yPos,dx,dy,lightSource);
    }
    factor = (double)factor / N;
    return color*factor;
}

double trace(double x, double y, double dx, double dy, tyw::Circle &circle)
{
    double t = 0.0;
    for(int j = 0; j < 10 && t < 200; ++j){
        double sdf = circle.getSDF(x + dx * t, y + dy * t) ;
        if(sdf < 1e-6 ) {
            return 2.0;
        }
        t += sdf;
    }
    return 0;
}


Color case005(double x, double y, double mx, double my, int time)
{

}



Color case006(double x, double y, double mx, double my, int time)
{
    //! 背景色
    int value = 0;
    Color c(64,64,64);

    //! 坐标变换
    double xPos, yPos;
    Util::scalePointXY(x,y,xPos,yPos,200,200);
    Util::movePointXY(xPos, yPos, xPos, yPos, 100, 100);
    double xMouse, yMouse;//鼠标
    Util::scalePointXY(mx,my,xMouse,yMouse,180,180);
    Util::movePointXY(xMouse, yMouse, xMouse, yMouse, 90, 90);


    //画立方体
    Vec3 vtMouse(0,-60,10);

    Vec3 vt1(-30, -30, 30);
    Vec3 vt2(30, -30, 30);
    Vec3 vt3(30, -30, -30);
    Vec3 vt4(-30, -30, -30);
    Vec3 vt5(-30, 30, 30);
    Vec3 vt6(30, 30, 30);
    Vec3 vt7(30, 30, -30);
    Vec3 vt8(-30, 30, -30);

    tyw::Triangle3D triangle1(vt1,vt2,vt3,Color(255,125,0));
    tyw::Triangle3D triangle2(vt1,vt3,vt4,Color(125,125,0));

    tyw::Triangle3D triangle3(vt2,vt3,vt6,Color(0,255,0));
    tyw::Triangle3D triangle4(vt3,vt6,vt7,Color(255,0,255));

    tyw::Triangle3D triangle5(vt1,vt2,vt5,Color(0,0,255));
    tyw::Triangle3D triangle6(vt2,vt5,vt6,Color(255,0,0));

    tyw::Triangle3D triangle7(vt5,vt6,vt7,Color(255,125,255));
    tyw::Triangle3D triangle8(vt5,vt7,vt8,Color(125,0,0));

    tyw::Triangle3D triangle9(vt3,vt4,vt8,Color(255,125,0));
    tyw::Triangle3D triangle10(vt3,vt7,vt8,Color(125,0,255));

    tyw::Triangle3D triangle11(vt1,vt4,vt8,Color(255,255,125));
    tyw::Triangle3D triangle12(vt1,vt5,vt8,Color(125,125,255));

    ///绕轴旋转
    triangle1.rotate(-yMouse,xMouse,0);
    triangle2.rotate(-yMouse,xMouse,0);
    triangle3.rotate(-yMouse,xMouse,0);
    triangle4.rotate(-yMouse,xMouse,0);
    triangle5.rotate(-yMouse,xMouse,0);
    triangle6.rotate(-yMouse,xMouse,0);
    triangle7.rotate(-yMouse,xMouse,0);
    triangle8.rotate(-yMouse,xMouse,0);
    triangle9.rotate(-yMouse,xMouse,0);
    triangle10.rotate(-yMouse,xMouse,0);
    triangle11.rotate(-yMouse,xMouse,0);
    triangle12.rotate(-yMouse,xMouse,0);

    ///投影变换
    double d = 100;//投影面 坐标
    Vec3 eye(0,0,100);
    tyw::Triangle3D projTr1 = triangle1.projectTo2D(eye,d);
    tyw::Triangle3D projTr2 = triangle2.projectTo2D(eye,d);
    tyw::Triangle3D projTr3 = triangle3.projectTo2D(eye,d);
    tyw::Triangle3D projTr4 = triangle4.projectTo2D(eye,d);
    tyw::Triangle3D projTr5 = triangle5.projectTo2D(eye,d);
    tyw::Triangle3D projTr6 = triangle6.projectTo2D(eye,d);
    tyw::Triangle3D projTr7 = triangle7.projectTo2D(eye,d);
    tyw::Triangle3D projTr8 = triangle8.projectTo2D(eye,d);
    tyw::Triangle3D projTr9 = triangle9.projectTo2D(eye,d);
    tyw::Triangle3D projTr10 = triangle10.projectTo2D(eye,d);
    tyw::Triangle3D projTr11 = triangle11.projectTo2D(eye,d);
    tyw::Triangle3D projTr12 = triangle12.projectTo2D(eye,d);

    ///光栅化前后遮挡剔除还存在问题。projectTo2D不能这样写
    double index = 10e9;
    if(projTr1.isContain(xPos,yPos, d)){
        if(projTr1.z_index < index){
            c = projTr1.color_fill;
            index = projTr1.z_index;
        }
    }
    if(projTr2.isContain(xPos,yPos, d)){
        if(projTr2.z_index < index){
            c = projTr2.color_fill;
            index = projTr2.z_index;
        }
    }
    if(projTr3.isContain(xPos,yPos, d)){
        if(projTr3.z_index < index){
            c = projTr3.color_fill;
            index = projTr3.z_index;
        }
    }
    if(projTr4.isContain(xPos,yPos, d)){
        if(projTr4.z_index < index){
            c = projTr4.color_fill;
            index = projTr4.z_index;
        }
    }
    if(projTr5.isContain(xPos,yPos, d)){
        if(projTr5.z_index < index){
            c = projTr5.color_fill;
            index = projTr5.z_index;
        }
    }
    if(projTr6.isContain(xPos,yPos, d)){
        if(projTr6.z_index < index){
            c = projTr6.color_fill;
            index = projTr6.z_index;
        }
    }
    if(projTr7.isContain(xPos,yPos, d)){
        if(projTr7.z_index < index){
            c = projTr7.color_fill;
            index = projTr7.z_index;
        }
    }
    if(projTr8.isContain(xPos,yPos, d)){
        if(projTr8.z_index < index){
            c = projTr8.color_fill;
            index = projTr8.z_index;
        }
    }
    if(projTr9.isContain(xPos,yPos, d)){
        if(projTr9.z_index < index){
            c = projTr9.color_fill;
            index = projTr9.z_index;
        }
    }
    if(projTr10.isContain(xPos,yPos, d)){
        if(projTr10.z_index < index){
            c = projTr10.color_fill;
            index = projTr10.z_index;
        }
    }
    if(projTr11.isContain(xPos,yPos, d)){
        if(projTr11.z_index < index){
            c = projTr11.color_fill;
            index = projTr11.z_index;
        }
    }
    if(projTr12.isContain(xPos,yPos, d)){
        if(projTr12.z_index < index){
            c = projTr12.color_fill;
            index = projTr12.z_index;
        }
    }
    return c;
}

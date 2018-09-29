#include "shader.h"
#include "intersect.h"


const int ss = 32*4;
const int s = 16*4;	//棋盘格的边长
Color3 shader01(double x, double y, int time){
    Color3 color;
    int row = 512*y;
    int col = 512*x;

    double f = 0.1;//默认黑格

    //变换xy坐标 到当前的方格
    double x1 = (double)((col % s)/ (double)s);
    double y1 = (double)((row % s)/ (double)s);

    if(row % ss < s){
        if(col % ss < s){//白格
            f = 1.0;
            //当前方格绘制灰色图形
            if(inShape(x1,y1,Circle))
                f = 0.4;
        }
        else {//黑格
            //当前方格绘制灰色图形
            if(inShape(x1,y1,Circle))
                f = 0.8;
        }
    }
    else{
        if(col % ss > s){//白格
            f = 1.0;

            //当前方格绘制图形
            if(inShape(x1,y1,Circle))
                f = 0.4;
        }
        else {//黑格
            //当前方格绘制灰色图形
            if(inShape(x1,y1,Circle))
                f = 0.8;
        }
    }

    color.set(f*255);
    return color;
}


Color3 shader02(double x, double y, int time){
    Color3 color;
    double f = 0.7;//灰色背景
    color.set(f*255);

    int r, g, b; //颜色三分量

    int num_x = 9;// 水平方向上划分的格数
    int num_y = 10;// 竖直方向上划分的格数
    double factor_x1=0.0, factor_x2=0.0; //水平方向的定位因子
    double factor_y1=0.0, factor_y2=0.0; //竖直方向的定位因子

    //! 脸
    factor_x1 = 1.0, factor_x2 = 8.0;
    factor_y1 = 1.0, factor_y2 = 9.0;
    if(y>factor_y1/num_y && y<factor_y2/num_y){
        if(x>factor_x1/num_x && x<factor_x2/num_x){
            double xx = (num_x*x-factor_x1)/(factor_x2-factor_x1);
            double yy = (num_y*y-factor_y1)/(factor_y2-factor_y1);
            //填充
            if(inShape(xx,yy,Circle,true)){
                r = 250, g = 211, b = 94;//滑稽黄
                color.set(r, g, b);
            }
            //描边
            if(inShape(xx,yy,Circle,false)){
                f = 0.0f;
                color.set(f*255);
            }
        }
    }
    //! 左眼
    if(time == 1){
        factor_x1 = 3.0, factor_x2 = 4.0;
        factor_y1 = 3.0, factor_y2 = 4.0;
    }
    else{
        factor_x1 = 2.0, factor_x2 = 4.0;
        factor_y1 = 3.2, factor_y2 = 4.0;
    }
    if(y>factor_y1/num_y && y<factor_y2/num_y){
        if(x>factor_x1/num_x && x<factor_x2/num_x){
            double xx = (num_x*x-factor_x1)/(factor_x2-factor_x1);
            double yy = (num_y*y-factor_y1)/(factor_y2-factor_y1);
            if(inShape(xx,yy,Circle)){
                f = 1.0f;
                color.set(f*255);
                return color;
            }
        }
    }
    //! 右眼
    if(time == 1){
        factor_x1 = 5.0, factor_x2 = 6.0;
        factor_y1 = 3.0, factor_y2 = 4.0;
    }
    else{
        factor_x1 = 5.0, factor_x2 = 7.0;
        factor_y1 = 3.2, factor_y2 = 4.0;
    }
    if(y>factor_y1/num_y && y<factor_y2/num_y){
        if(x>factor_x1/num_x && x<factor_x2/num_x){
            double xx = (num_x*x-factor_x1)/(factor_x2-factor_x1);
            double yy = (num_y*y-factor_y1)/(factor_y2-factor_y1);
            if(inShape(xx,yy,Circle)){
                f = 1.0f;
                color.set(f*255);
                return color;
            }
        }
    }


    //! 鼻子
    if(time == 1){
        factor_x1 = 4.0, factor_x2 = 5.0;
        factor_y1 = 4.0, factor_y2 = 5.5;
    }
    else{
        factor_x1 = 4.0, factor_x2 = 5.0;
        factor_y1 = 4.0, factor_y2 = 5.0;
    }
    if(y>factor_y1/num_y && y<factor_y2/num_y){
        if(x>factor_x1/num_x && x<factor_x2/num_x){
            double xx = (num_x*x-factor_x1)/(factor_x2-factor_x1);
            double yy = (num_y*y-factor_y1)/(factor_y2-factor_y1);
            if(inShape(xx,yy,Circle)){
                f = 1.0f;
                color.set(f*255);
                return color;
            }
        }
    }


    //! 嘴巴
    if(time == 1){
        factor_x1 = 3.5, factor_x2 = 5.5;
        factor_y1 = 6.5, factor_y2 = 8.5;
    }
    else{
        factor_x1 = 1.5, factor_x2 = 7.5;
        factor_y1 = 5.5, factor_y2 = 9.5;
    }
    if(y>factor_y1/num_y && y<factor_y2/num_y){
        if(x>factor_x1/num_x && x<factor_x2/num_x){
            double xx = (num_x*x-factor_x1)/(factor_x2-factor_x1);
            double yy = (num_y*y-factor_y1)/(factor_y2-factor_y1);
            //填充
            if(inShape(xx,yy,Parabola,true)){
                r = 250, g = 100, b = 94;//
                color.set(r, g, b);
            }
            //描边
            if(inShape(xx,yy,Parabola,false)){
                r = 240, g = 200, b = 90;//
                color.set(r, g, b);
            }
            return color;
        }
    }

    return color;
}


#include "shape.h"
Color shader003(double x, double y, int time)
{
    Color color(250, 211, 94); //背景滑稽黄

    //！定义坐标系
    //! XY轴坐标长度
    const double xLength = 200.0;
    const double yLength = 200.0;
    //! 当前像素点映射到坐标轴上
    double xPos = x * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
    double yPos = y * yLength - yLength/2;


    //! 加入对象
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


    //
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

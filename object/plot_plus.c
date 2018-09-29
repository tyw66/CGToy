/** **********************************************************
 * 
 *  随便画画，用svpng库导出为图片
 * Created by tyw66 at 2018-09-20
 * 
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "svpng.inc"

//! 图像大小
const double PI = 3.141592;
const int W = 256;
const int H = 256;

//! 测试：随机色
void case00(char* img, double x, double y){
	int row = W*y;
	int col = H*x;

	int index = (W*row+col)*3;	
	int value = rand()%255;
	img[index] = value;
	img[index+1] = value;
	img[index+2] = value;
}

//! 绿色渐变  rgb(0,0,0)->(0,255,0)->(255,255,255)
void case01(char* img, double x, double y){
	int row = W*y;
	int col = H*x;

	int index = (W*row+col)*3;

	//double f = (double)(W*i+j)/(double)(W*H);//全部像素占比
	double f = (double)row/(double)H;//行占比

	if(row < H/2){
		img[index] = 0;
		img[index+1] = f*255*2;
		img[index+2] = 0;
	}
	else{
		img[index] = f*255*2-255;
		img[index+1] = 255;
		img[index+2] = f*255*2-255;
	}

}

//!  棋盘格
void case02(char* img, double x, double y){
	int row = W*y;
	int col = H*x;

	int index = (W*row+col)*3;
	double f = 0.0;//默认黑格
	//!  边长16
	if(row%32 < 16){
		if(col%32 < 16) f = 1.0;//白格
	}
	else{
		if(col%32 > 16) f = 1.0;//白格
	}

	img[index] = img[index+1] = img[index+2] = f*255;
	//printf("%f\n",f);
}

//! 圆形、抛物线
void case03(char* img, double x, double y){
	int row = W*y;
	int col = H*x;

	int index = (W*row+col)*3;
	double f = 1.0;

	//！定义坐标系
	//!XY轴坐标长度
	const double xLength = 200.0;
	const double yLength = 200.0;	
	//! 当前像素点映射到坐标轴上
	double xPos = (double)col/W * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
	double yPos = (double)row/H * yLength - yLength/2;

	//todo:画一个顺时针旋转30度的椭圆
	//xPos=xPos * cos(30*PI/180);
	//yPos=yPos * sin(30*PI/180);

	int flag = 0;
	switch(flag){
		case 0:
		{
			//! (椭)圆：x^2+y^2<r^2
			const double r = 36.0;
			const double a = 2.0;
			const double b = 1.0;
			//if(xPos * xPos + yPos * yPos < r * r)
			if(xPos * xPos / (a*a) + yPos * yPos / (b*b) < r * r)
				f = 0.0;

			break;
		}
		case 1:
		{
			//! 抛物线：y-ax^2-bx-c>0
			const double a = -0.01;
			const double b = 0.0;
			const double c = 0.0;
			if(yPos - a * xPos * xPos - b * xPos - c > 0)
				f = 0.0;

			break;
		}
	}

//	printf("%f\n",f);
	img[index] = img[index+1] = img[index+2] = f*255;
}

///////////////////////////////////////////////////////////////////////////////////


int inShape(double x, double y){
	//！定义坐标系
	//!XY轴坐标长度
	const double xLength = 200.0;
	const double yLength = 200.0;	
	//! 当前像素点映射到坐标轴上
	double xPos = x * xLength - xLength/2;//减去Length/2是把坐标中心从图像屏幕左上方移动到中心
	double yPos = y * yLength - yLength/2;

	int flag = 0;
	switch(flag){
		case 0:
		{
			//! (椭)圆：x^2+y^2<r^2
			const double r = 36.0;
			const double a = 2.0;
			const double b = 1.0;
			//if(xPos * xPos + yPos * yPos < r * r)
			if(xPos * xPos / (a*a) + yPos * yPos / (b*b) < r * r)
				return 1;
		}
		case 1:
		{
			//! 抛物线：y-ax^2-bx-c>0
			const double a = -0.01;
			const double b = 0.0;
			const double c = 0.0;
			if(yPos - a * xPos * xPos - b * xPos - c > 0)
				return 1;

		}
	}
	return 0;

}

//! 着色：将img[index]的颜色设置为f1f2f3确定的rgb色
void shader(char* img, int index, double f1, double f2, double f3){
	img[index] = f1*255;
	img[index+1] = f2*255;
	img[index+2] = f3*255;
}

//! 复合图形
void test(char* img, double x, double y){
	int row = W*y;
	int col = H*x;

	int index = (W*row+col)*3;
	double f = 0.0;//默认黑格
	//!  边长16
	if(row%32 < 16){
		if(col%32 < 16){//白格
			if(inShape(x,y))
				f = 1.0;
		}
	}
	else{
		if(col%32 > 16){//白格
			if(inShape(x,y))
				f = 1.0;
		}
	}

	shader(img, index, f, f, f);
	//printf("%f\n",f);


}



int main()
{
    char img[W*H*3];
    for(int i = 0; i < H; ++i){
		for(int j = 0; j < W; ++j){
			test(img,(double)i/H,(double)j/W);
		}
	}



    FILE *fp = fopen("demo.png", "wb");
    svpng(fp,W,H,img,0);


    //FILE *fp1 = fopen("debug", "wb");
	//fprintf(fp1,img);

    printf("finish!\n");
    return 0;
}

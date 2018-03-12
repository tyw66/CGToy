/** *****************
 * 画线 - 中点算法
 ********************/
#include "svpng.inc"
#include <stdlib.h> // abs()
#include <string.h> // memset()
#define PI 3.14159265359f
#define W 1024
#define H 1024
static unsigned char img[W * H * 3];

void setpixel(int x, int y) {
   unsigned char* p = img + (y * W + x) * 3;
   p[0] = p[1] = p[2] = 0;
}

//画从(x0,y0)到(x1,y1)的直线
void line(int x0, int y0, int x1, int y1) {
	//if((x0==x1)||(y0==y1))return;

	double k = (double)(y1-y0)/(double)(x1-x0);//斜率有四种情况：(-无穷,-1],(-1,0],(0,1],1,正无穷]

	int y=y0;
	for(int x=x0;x<x1;++x){
		setpixel(x,y);
		double f = (y0-y1)*x+(x1-x0)*(y+0.5)+x0*y1-x1*y0;
		if(k>0 && k<=1 && f<0){//(0,1]
			y++;
			if(y>H)y=H;
		}
		else if(k>-1 && k<=0 && f>0){//(-1,0]
			y--;
			if(y<0)y=0;
		}
	}
	//todo:另外2种情况
}

int main() {


   char* fileName="output.png";

   memset(img, 255, sizeof(img));//白色填充背景

    //line(0,0,900,400);
    line(0,400,900,0);

   svpng(fopen(fileName, "wb"), W, H, img, 0);


}



#include<stdio.h>
#include<math.h>
/*int main(){
	for(float y = 2; y>-2; y-=0.1){
		for(float x =-2; x<2; x+=0.05){
			float a = x*x+y*y-1;
			putchar(a*a*a-x*x*y*y*y < 0.0f ? '*':' ');
		}
		putchar('\n');
	}
	getchar();
}*/


/*
#define WIDTH 200
#define HEIGHT 200
#define X_BEGIN -1.5
#define Y_BEGIN -1.5
#define DELTA_X 1.5
#define DELTA_Y 1.5

char heart(int px, int py){
	int x = px;
	int y = py;
	float a = x*x+y*y-1;	
	return a*a*a-x*x*y*y*y < 0.0f ? '*':' ';
	
}
	

//milo的命令行画图框架
int main(){
	for(int y = Y_BEGIN; y<Y_BEGIN+HEIGHT; ++DELTA_Y){
		for(int x = X_BEGIN; x< X_BEGIN+WIDTH; ++Y_BEGIN){
			printf(heart(x,y));
		}		
		printf("\r\n");
	}
	return 0;
}*/
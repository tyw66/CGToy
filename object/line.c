/** *********************
 *  画根线
 *  方程：x+y=1
 ** **********************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h> 

//直线的隐式方程 
float f(float x, float y, float x1, float y1, float x2, float y2){
	return (y1-y2)*x+(x2-x1)*y+x1*y2-x2*y1;	
}

///1-画一条过(0,0)和(0.9,0.7) 的线 
// 直接用方程判断,存在的问题是线不连续 
void line0(){
	for(float sy=1.0f; sy>-1.0f; sy-=0.05f){
		for(float sx =-1.0f; sx<1.0f; sx+=0.025f){
			putchar(fabs(f(sx,sy,0,0,0.9,0.4))<0.01f?'*':'.');
		}
		putchar('\n');
	}
}

///2-画一条(0,0)到(90,70) 的线 
//使用中点算法 
char img[20][20];//[宽][高] 

void show_pic(){
	system("cls");
	for(int row =0; row<20; ++row){
		for(int col = 0; col<20; ++col){
			putchar(img[col][row]);
		}
		putchar('\n');		
	}	
	putchar('\n');
}

void line1(){	
	float x1 = 0.0f;
 	float y1 = 0.0f;
	float x2 = 90.0f;
	float y2 = 20.0f;
	
	int sy=y1;
	for(int sx =x1;sx<x2;++sx) {
		if(f(sx,sy+0.5,x1,y1,x2,y2)>0){
			sy++;
		}
		img[sx][sy] = '*';
		
	}		
 	show_pic();
	
	/*
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
	int row=0;
	int col=0;
	for(int sx = 0; sx<0.9;sx+=0.05)
		for(float sx =-1.0f; sx<1.0f; sx+=0.025f){
			
		}
	}
	
	
	
	COORD coord = {};
	SetConsoleCursorPosition(o, coord);
 	WriteConsole(o, buffer[sy], 79, NULL, 0);
	*/
} 

int main(){
	int caseID = 1;
	switch(caseID){
	case 0:
		line0();
		break;
	case 1:
		line1();
		break;
		
	default:
		break;	
	}
	return 0;
}
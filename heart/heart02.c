#include <stdio.h>
//0-基本版
void heart0(){
	for(float y=1.5f; y>-1.5f; y-=0.1f){
		for(float x=-1.5f; x<1.5f; x+=0.05f){
			float a=x*x+y*y-1;
			float f=a*a*a-x*x*y*y*y;
			putchar(f<=0.0f?'*':' ');
		}
		putchar('\n');
	}
}

//1-等值线花纹版
void heart1(){
	for(float y=1.5f; y>-1.5f; y-=0.1f){
		for(float x=-1.5f; x<1.5f; x+=0.05f){
			float a=x*x+y*y-1;
			float f=a*a*a-x*x*y*y*y;
			putchar(f<=0.0f?".:-=*%@"[(int)(f*-8.0f)]:' ');
		}
		putchar('\n');
	}
}

//2-3D版
#include<math.h>
float f(float x, float y, float z){
	float a=x*x+9.0f/4.0f*y*y+z*z-1;
	return a*a*a-x*x*z*z*z-9.0f/80.0f*y*y*z*z*z;	
}

float h(float x,float z){
	for(float y=1.0f; y>=0.0f; y-=0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

void heart2(){
	for (float z = 1.5f; z > -1.5f; z -= 0.05f){
		for (float x = -1.5f; x < 1.5f; x += 0.025f) {
			float v = f(x, 0.0f, z);
            if (v <= 0.0f) {
				float y0 = h(x, z);
                float ny = 0.01f;
				float nx = h(x + ny, z) - y0;
				float nz = h(x, z + ny) - y0;
				float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
				float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
				putchar(".:-=+*#%@"[(int)(d * 5.0f)]);		
			}
			else
				putchar(' ');
		}
		putchar('\n');
	}
}


//milo的命令行画图框架
int main(){
	int caseID = 2;
	
	switch(caseID){
	case 0:
		heart0();break;
	case 1:
		heart1();break;
	case 2:
		heart2();break;
	
	default:
		break;
	}
	
	return 0;
}
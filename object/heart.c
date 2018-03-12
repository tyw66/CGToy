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
			putchar(f<=0.0f?".:-=*%@GYL"[(int)(f*-9.0f)]:' ');
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
	//获取表面
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
				//Finite difference求法矢量
				float y0 = h(x, z);
                float ny = 0.01f;
				float nx = h(x + ny, z) - y0;
				float nz = h(x, z + ny) - y0;
				float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
				float d = (nx + ny - nz) * nd * 0.5f + 0.5f;
				//
				putchar(".:*-=+#%@"[(int)(d * 6.3f)]);
			}
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

//3-3D版PPM
void heart3(){
	FILE* fp = fopen("heart.ppm", "w");
	int sw = 512, sh = 512;
	fprintf(fp, "P3\n%d %d\n255\n", sw, sh);



}

//4-
#include <windows.h>
#include <tchar.h>
void heart4(){
    HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
    _TCHAR buffer[25][80] = { _T(' ') };
    _TCHAR ramp[] = _T(".:-=+*#%@");
    for (float t = 0.0f;; t += 0.1f) {
        int sy = 0;
         float s = sinf(t);
        float a = s * s * s * s * 0.2f;

	FILE* fp = fopen("heart.ppm", "w");
	int width=512, height = 512;
	fprintf(fp, "P3\n%d %d\n255\n", width, height);
	for(int sy = 0; sy<height;sy++){
		float z = 1.5f - sy * 3.0f / height;
		for(int sx = 0;sx <width; sx++){
			float x =sx *3.0f /width-1.5f;
			float v=f(x,0.0f,z);
			int r = 0;
			if (v <= 0.0f) {
				//Finite difference求法矢量
				float y0 = h(x, z);
                float ny = 0.01f;
				float nx = h(x + ny, z) - y0;
				float nz = h(x, z + ny) - y0;
				float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
				float d = (nx + ny - nz) /sqrtf(3)* nd * 0.5f + 0.5f;
				r = (int)(d*200.0f);
				//
				fprintf(fp,"%d %d 0 ",r,r);
			}
			else
				fprintf(fp,"200,200,200 ");
		}
		fputc('\n',fp);
	}
	fclose(fp);
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
	case 3:
		heart3();break;
    case 4:
		heart4();break;

	default:
		break;
	}

	return 0;
}

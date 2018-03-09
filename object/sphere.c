/** *********************
 * 画个球
 ************************/
#include <stdio.h>
//0-基本版
void sphere0(){
	for(float y=1.5f; y>-1.5f; y-=0.05f){
		for(float x=-1.5f; x<1.5f; x+=0.025f){
			float f=x*x+y*y-1;
			putchar(f<=0.0f?'@':' ');
		}
		putchar('\n');
	}
}

//1-等值线花纹版
void sphere1(){
	for(float y=1.2f; y>-1.2f; y-=0.05f){
		for(float x=-1.2f; x<1.2f; x+=0.025f){
			float f=x*x+y*y-1;
			putchar(f<=0.0f?".-=#%@"[(int)(f*-5.0f)]:' ');
			//putchar(f<=0.0f?"0123456"[(int)(f*-6.0f)]:' ');
		}
		putchar('\n');
	}
}

//2-3D版
#include<math.h>
float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

float h(float x,float z){
	//获取表面(解方程的过程)
	for(float y=1.0f; y>=0.0f; y-=0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

void sphere2(){
	for (float z = 1.2f; z > -1.2f; z -= 0.05f){
		for (float x = -1.2f; x < 1.2f; x += 0.025f) {
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
				putchar(".-=#%@"[(int)(d * 4.0f)]);		
			}
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

//3-3D版PPM
void sphere3(){
	FILE* fp = fopen("sphere.ppm", "w");
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

//4-3D版PPM-图像序列动画
#include<string.h>
void sphere4(){
	const int frame_number = 3;
	for(int index=0;index<frame_number;++index){
		char* fileName ;
		sprintf(fileName,"sphere_%d.ppm",index);
		FILE* fp = fopen(fileName,"w");
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
					//float d = (nx + ny - nz) /sqrtf(3)* nd * 0.5f + 0.5f;
					float d = ((index*2/frame_number-1) * nx + ny - nz) /sqrtf(3)* nd * 0.5f + 0.5f;
					
					r = (int)(d*200.0f);
					//	
					fprintf(fp,"%d %d 0 ",r);
				}
				else
					fprintf(fp,"230,230,230 ");	
			}
			fputc('\n',fp);
		}			
		fclose(fp);
	}

}



//milo的命令行画图框架
int main(){
	int caseID = 3;
	
	switch(caseID){
	case 0:
		sphere0();break;
	case 1:
		sphere1();break;
	case 2:
		sphere2();break;
	case 3:
		sphere3();break;
	case 4:
		sphere4();break;
	
	default:
		break;
	}
	
	return 0;
}
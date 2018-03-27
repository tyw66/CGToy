/** *********************
 *  画个球
 *  与光照模型一起玩耍 
 *  坐标轴朝向： x右 z上 y里 
 ** **********************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//~~~~~~~~~公用定义~~~~~~~~~~~~~~~~~~~~

float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

float h(float x,float z){
	//获取表面(解方程的过程)
	//这个函数规定了 Y轴 垂直纸面向里 右手坐标系
	for(float y = -1.0f; y <= 0.0f; y += 0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

struct color3{
	int r;
	int g;
	int b;

};

struct vec3{
	float x;
	float y;
	float z;
	//float normalize()const{return sqrtf(x*x+y*y+z*z);}
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 


///8-球体图像输出-加入高光、边缘
//
void sphere8(){
	FILE* fp = fopen("sphere_shader.ppm", "w");
	int width=512, height = 512;
	fprintf(fp, "P3\n%d %d\n255\n", width, height);

	for(int sy = 0; sy < height; sy++){
		for(int sx = 0; sx < width; sx++){
			//按比例从屏幕像素转到模型大小的尺度
			float z = 1.5f - sy * 3.0f / height; 
			float x = sx * 3.0f /width - 1.5f;
			//属于球体
			if (f(x,0.0f,z) <= 0.0f) {
				float y = h(x, z);
				
				//// 求当前点光栅化后的颜色 //// 
				struct vec3 L = {-1, -1, 1};
				struct vec3 N = {x, y, z};
				struct color3 Cr
				
                //光线向量L：[-1,-1,1]
                float norm = sqrtf(L.x*L.x+L.y*L.y+L.z*L.z);
               	float cosNL = (L.x * N.x +  L.y * N.y +  L.z * N.z) /norm /sqrtf(3);
               	// float cosNL = (- x - y + z) / sqrtf(x * x + y * y + z * z) / sqrtf(3);
				
				//漫反射，wrapped diffuse处理
                float diffuse = cosNL*0.5f+0.5f;

				//高光
				float specular = pow(cosNL,64.0);
				
				//边缘
				float cosB = y / sqrtf(x*x+y*y+z*z) / sqrtf(3);//(光线向量：[0,1,0])
				float rim =  1 - pow(cosB,64.0);
				

/* 				int r = (int)(diffuse * 255.0f + specular * 200.0f);
                int g = (int) (specular * 200.0f );
                int b = (int) (specular * 200.0f);
                r=r>255?255:r;
                g=g>255?255:g;
                b=b>255?255:b;*/
                
               	int r = (int)(diffuse * 255.0f);
				fprintf(fp,"%d 0 0 ",r);
			}
			else
				fprintf(fp,"255,255,255 ");
		}
		fputc('\n',fp);
	}
	fclose(fp);
	printf("sphere.ppm has been generated.\n");
}





int main(){
	int caseID = 8; //See different effect by change the number.
	//system("cls");
	
	switch(caseID){
	case 8:
		sphere8();break;
	default:
		break;
	}

	return 0;
}

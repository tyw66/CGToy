/** ***********************************
 *
 *  画个球plus 
 *  与光照模型一起玩耍 
 *  坐标轴朝向： x右 z上 y里 
 * 
 ***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../common/basic_type.hpp"  //一些公用定义 

const int WIDTH = 512;
const int HIGHT = 512;
const bool IsCartoon = true;

//////////////////////////////////////////////////////
//曲线,曲面方程 
float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

//获取表面(解方程的过程)
float h(float x,float z){
	//这个函数规定了 Y轴 垂直纸面向里 右手坐标系
	for(float y = -1.0f; y <= 0.0f; y += 0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

//画个球输出图片 
void sphere(){
	FILE* fp = fopen("sphere_plus.ppm", "w");
	fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HIGHT);

	for(int sy = 0; sy < HIGHT; sy++){
		for(int sx = 0; sx < WIDTH; sx++){
			//按比例从屏幕像素转到模型大小的尺度
			float z = 1.5f - sy * 3.0f / HIGHT; 
			float x = sx * 3.0f /WIDTH - 1.5f;
			//像素点属于球体
			if (f(x,0.0f,z) <= 0.0f) {				
				float y = h(x, z);
				
				////  一些向量   ////
				Vec L = {-1, -1, 1};	//光线向量L
				Vec Coord = {x, y, z};	//坐标Coord
				Vec N = {x, y, z};		//法向量N 	
               	
				//// 光照模型  //// 
   				double cosNL = dot(L,N)/N.norm()/L.norm();
   				
				//漫反射部分 
                double diffuse = cosNL;
				diffuse = cosNL*0.5f+0.5f;//wrapped diffuse处理 

				//高光部分 
				double specular = cosNL;
				specular = pow(cosNL,64.0); //phong 
				
				//边缘部分 
				double cosNY = -y / N.norm() / sqrtf(3);
				double pCosNY = pow(cosNY,64.0);
				bool rim =  (cosNY<0.1&&cosNY>0) ? true : false;
				
				//// 像素着色 //// 
				// 参考的公式：C = Cr(Ca+Cl*max(0,N·L))+ClCp*(N·H)^p 
				//
				Color color ;
				if(rim){
					color = {0,0,0};
				}
				else{
					Color Cr = { 255,0,0 }; 
					float a = 0.05; 			//环境光补偿 
					float p = 1.00;			//光强度系数 
					Color Cp = { 255,255,255 }; 	//高光颜色 
					
					//卡通渲染效果，根据不同区间，给diffuse不同值 
					if(IsCartoon){
						//卡通漫反射 
						if(cosNL>0.8){diffuse = 0.9*0.5f+0.5f;}
						else if(cosNL>0.6){diffuse = 0.7*0.5f+0.5f;}
						else if(cosNL>0.4){diffuse = 0.5*0.5f+0.5f;}
						else if(cosNL>0.2){diffuse = 0.3*0.5f+0.5f;}
						else {diffuse = 0.1*0.5f+0.5f;}
								
						//卡通高光 
						if(cosNL>0.995f){specular = 1;} 
						else if(cosNL>0.99f){specular = 0.95;} 
						else{specular = 0.0;}
					}
					color =  Cr*(a+p*diffuse)+Cp*p*specular;	
				}              
				fprintf(fp,"%d %d %d ",color.r,color.g,color.b);
			}
			//像素点不属于球体
			else
				fprintf(fp,"255,200,100 ",100+sin((x+z)/10));
		}
		fputc('\n',fp);
	}
	fclose(fp);
	printf("sphere.ppm has been generated.\n");
}





int main(){
	sphere();
	return 0;
}

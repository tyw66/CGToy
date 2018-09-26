/** ***********************************
 *
 *  ������plus 
 *  �����ģ��һ����ˣ 
 *  �����ᳯ�� x�� z�� y�� 
 * 
 ***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../common/basic_type.hpp"  //һЩ���ö��� 

const int WIDTH = 512;
const int HIGHT = 512;
const bool IsCartoon = true;

//////////////////////////////////////////////////////
//����,���淽�� 
float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

//��ȡ����(�ⷽ�̵Ĺ���)
float h(float x,float z){
	//��������涨�� Y�� ��ֱֽ������ ��������ϵ
	for(float y = -1.0f; y <= 0.0f; y += 0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

//���������ͼƬ 
void sphere(){
	FILE* fp = fopen("sphere_plus.ppm", "w");
	fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HIGHT);

	for(int sy = 0; sy < HIGHT; sy++){
		for(int sx = 0; sx < WIDTH; sx++){
			//����������Ļ����ת��ģ�ʹ�С�ĳ߶�
			float z = 1.5f - sy * 3.0f / HIGHT; 
			float x = sx * 3.0f /WIDTH - 1.5f;
			//���ص���������
			if (f(x,0.0f,z) <= 0.0f) {				
				float y = h(x, z);
				
				////  һЩ����   ////
				Vec L = {-1, -1, 1};	//��������L
				Vec Coord = {x, y, z};	//����Coord
				Vec N = {x, y, z};		//������N 	
               	
				//// ����ģ��  //// 
   				double cosNL = dot(L,N)/N.norm()/L.norm();
   				
				//�����䲿�� 
                double diffuse = cosNL;
				diffuse = cosNL*0.5f+0.5f;//wrapped diffuse���� 

				//�߹ⲿ�� 
				double specular = cosNL;
				specular = pow(cosNL,64.0); //phong 
				
				//��Ե���� 
				double cosNY = -y / N.norm() / sqrtf(3);
				double pCosNY = pow(cosNY,64.0);
				bool rim =  (cosNY<0.1&&cosNY>0) ? true : false;
				
				//// ������ɫ //// 
				// �ο��Ĺ�ʽ��C = Cr(Ca+Cl*max(0,N��L))+ClCp*(N��H)^p 
				//
				Color color ;
				if(rim){
					color = {0,0,0};
				}
				else{
					Color Cr = { 255,0,0 }; 
					float a = 0.05; 			//�����ⲹ�� 
					float p = 1.00;			//��ǿ��ϵ�� 
					Color Cp = { 255,255,255 }; 	//�߹���ɫ 
					
					//��ͨ��ȾЧ�������ݲ�ͬ���䣬��diffuse��ֵͬ 
					if(IsCartoon){
						//��ͨ������ 
						if(cosNL>0.8){diffuse = 0.9*0.5f+0.5f;}
						else if(cosNL>0.6){diffuse = 0.7*0.5f+0.5f;}
						else if(cosNL>0.4){diffuse = 0.5*0.5f+0.5f;}
						else if(cosNL>0.2){diffuse = 0.3*0.5f+0.5f;}
						else {diffuse = 0.1*0.5f+0.5f;}
								
						//��ͨ�߹� 
						if(cosNL>0.995f){specular = 1;} 
						else if(cosNL>0.99f){specular = 0.95;} 
						else{specular = 0.0;}
					}
					color =  Cr*(a+p*diffuse)+Cp*p*specular;	
				}              
				fprintf(fp,"%d %d %d ",color.r,color.g,color.b);
			}
			//���ص㲻��������
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

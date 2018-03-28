/** *********************
 *  ������
 *  �����ģ��һ����ˣ 
 *  �����ᳯ�� x�� z�� y�� 
 * 
 ** **********************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//~~~~~~~~~���ö���~~~~~~~~~~~~~~~~~~~~
struct Color3{
	int r, g, b;
	//���캯�� 
	Color3(unsigned int r_=0,unsigned int g_=0 ,unsigned int b_=0) { 
		r=r_>255?255:r_; g=g_>255?255:g_;b=b_>255?255:b_;
	}
	//��������todo
		
	//��ɫ�ӷ� 
	Color3 operator+(const Color3& c)const{return Color3(r+c.r, g+c.g, b+c.b);}
	//��ɫ���� 
	Color3 operator-(const Color3& c)const{return Color3(r-c.r, g-c.g, b-c.b);}
	//��ɫ���� 
	Color3 operator*(const double factor)const{return Color3(factor*r, factor*g, factor*b);}

};

struct Vec3{
	double x, y, z;
	//���캯��
	Vec3(double x_=0, double y_=0, double z_=0){x=x_; y=y_; z=z_;} 
	//��������todo
	//Vec3 operator=(const Vec3& v){x=v.x; y=v.y+233; z=v.z;}
	//�����ӷ�
	Vec3 operator+(const Vec3& v)const{return Vec3(x+v.x, y+v.y, z+v.z);}
	//��������
	Vec3 operator-(const Vec3& v)const{return Vec3(x-v.x, y-v.y, z-v.z);}
	//������ģ 
	double norm()const{return sqrtf(x*x+y*y+z*z);}
};

//�������
double dot(const Vec3& lhs, const Vec3& rhs){
	return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z;
}


typedef struct Color3 Color;
typedef struct Vec3 Pos;
typedef struct Vec3 Vec;



/////////////
//����,���淽�� 
float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

float h(float x,float z){
	//��ȡ����(�ⷽ�̵Ĺ���)
	//��������涨�� Y�� ��ֱֽ������ ��������ϵ
	for(float y = -1.0f; y <= 0.0f; y += 0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 


void sphere(){
	bool cartoon = true;
	FILE* fp = fopen("sphere_plus.ppm", "w");
	int width=512, height = 512;
	fprintf(fp, "P3\n%d %d\n255\n", width, height);

	for(int sy = 0; sy < height; sy++){
		for(int sx = 0; sx < width; sx++){
			//����������Ļ����ת��ģ�ʹ�С�ĳ߶�
			float z = 1.5f - sy * 3.0f / height; 
			float x = sx * 3.0f /width - 1.5f;
			//���ص���������
			if (f(x,0.0f,z) <= 0.0f) {				
				float y = h(x, z);
				
				////  һЩ����   ////
				Vec L = {-1, -1, 1};	//��������L
				Vec Coord = {x, y, z};	//����Coord
				Vec N = {x, y, z};		//������N 
				
				//// ����ģ��  //// 
               	double cosNL = dot(L,N)/N.norm()/L.norm();
               	// float cosNL = (- x - y + z) / sqrtf(x * x + y * y + z * z) / sqrtf(3);
				
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
					if(cartoon){
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
				fprintf(fp,"255,200,100 ",255*sin((x+z)/10));
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

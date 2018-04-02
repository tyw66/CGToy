#include "math.h"
struct Color3{
	int r, g, b;
	//Ĭ�Ϲ��캯��
	Color3(){
		r=0, g=0, b=0;		
	} 
	//���캯�� 
	Color3(unsigned int r_=0,unsigned int g_=0 ,unsigned int b_=0) { 
		r=r_>255?255:r_; g=g_>255?255:g_;b=b_>255?255:b_;
	}
	//�������캯��
	Color3(const Color3& c):
	r(c.r/2),g(c.g),b(c.b)	
	{	}	
	
	//��ɫ�ӷ� 
	Color3 operator+(const Color3& c)const{
		return Color3(r+c.r, g+c.g, b+c.b);
	}
	//��ɫ���� 
	Color3 operator-(const Color3& c)const{
		return Color3(r-c.r, g-c.g, b-c.b);
	}
	//��ɫ���� 
	Color3 operator*(const double factor)const{
		return Color3(factor*r, factor*g, factor*b);
	}

};

typedef struct Color3 Color;

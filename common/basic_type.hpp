#include "math.h"
struct Color3{
	int r, g, b;
	//构造函数 
	Color3(unsigned int r_=0,unsigned int g_=0 ,unsigned int b_=0) { 
		r=r_>255?255:r_; g=g_>255?255:g_;b=b_>255?255:b_;
	}
	//拷贝函数todo
		
	//颜色加法 
	Color3 operator+(const Color3& c)const{return Color3(r+c.r, g+c.g, b+c.b);}
	//颜色减法 
	Color3 operator-(const Color3& c)const{return Color3(r-c.r, g-c.g, b-c.b);}
	//颜色数乘 
	Color3 operator*(const double factor)const{return Color3(factor*r, factor*g, factor*b);}

};

struct Vec3{
	double x, y, z;
	//构造函数
	Vec3(double x_=0, double y_=0, double z_=0){x=x_; y=y_; z=z_;} 
	//拷贝函数todo
	//Vec3 operator=(const Vec3& v){x=v.x; y=v.y+233; z=v.z;}
	//向量加法
	Vec3 operator+(const Vec3& v)const{return Vec3(x+v.x, y+v.y, z+v.z);}
	//向量减法
	Vec3 operator-(const Vec3& v)const{return Vec3(x-v.x, y-v.y, z-v.z);}
	//向量的模 
	double norm()const{return sqrtf(x*x+y*y+z*z);}
};

//向量点乘
double dot(const Vec3& lhs, const Vec3& rhs){
	return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z;
}

//向量叉乘	



typedef struct Color3 Color;
typedef struct Vec3 Pos;
typedef struct Vec3 Vec;
/** ***********************************
* @brief: 向量类
* @note : 
* @update : 2018-4-2
***************************************/
#include "math.h"
struct Vec3{
	///成员变量  
	double x, y, z;
 	
	///构造函数（返回新对象） 
 	//默认构造函数,不执行任何操作
    Vec3(){}
	//复制构造函数
	Vec3(double nx=0, double ny=0, double nz=0):x(nx),y(ny),z(nz){} 
	Vec3(const Vec3& v):x(v.x),y(v.y),z(v.z){} 
	//Vec3 operator=(const Vec3& v)x(v.x),y(v.y),z(v.z){} 
	
	///标准对象操作（返回新对象） 
	//向量取反
	Vec3 operator-()const{return Vec3(-x,-y,-z);}
	//向量加法
	Vec3 operator+(const Vec3& v)const{return Vec3(x+v.x, y+v.y, z+v.z);}
	//向量减法
	Vec3 operator-(const Vec3& v)const{return Vec3(x-v.x, y-v.y, z-v.z);}
	//向量标量乘法 （标量右乘） 
	Vec3 operator*(const double num)const{return Vec3(x*num, y*num, z*num);}
	//向量标量除法 
	Vec3 operator*(const double num)const{return Vec3(x*num, y*num, z*num);}
	
	///自反操作符(原对象上修改)
	//todo 返回值改成void会怎样 
	Vec3& operator+=(const Vec3& v){
		x+=v.x; y+=v.y; z+=v.z;
		return *this; 
	} 
	Vec3& operator-=(const Vec3& v){
		x-=v.x; y-=v.y; z-=v.z;
		return *this; 
	}
	Vec3& operator*=(const double num){
		x*=num; y*=num; z*=num;
		return *this; 
	}
	Vec3& operator/=(const double num){
		float oneOverN =1.0f/num; //不对除0进行检查
		x*=oneOverN; y*=oneOverN; z*=oneOverN;
		return *this; 
	}
	
    ///常用运算
    //置为零向量
    void zero(){x=y=z=0.0;}     
    //向量标准化
    void normalize(){
        float magSq=x*x+y*y+z*z;
        if(magSq>0.0f){//检查除0
            float oneOverMag=1.0f/sqrt(magSq);
            x*=oneOverMag; y*=oneOverMag; z*=oneOverMag;
        }
    }    
   	//求模 
	double norm()const{return sqrtf(x*x+y*y+z*z);}
	//点乘 
 	double dotWith(const Vec3& v){return x*v.x+y*v.y+z*v.z;}
 	
};

//******************************************************************************
///非成员函数
//向量的模
inline double vec3norm(const Vec3 &v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}


//两向量点乘
inline double vec3dot(const Vec3& a, const Vec3& b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

//两向量叉乘
inline Vec3 vec3crossProduct(const Vec3 &a,const Vec3 &b){
    return Vec3(a.y*b.z-a.z*b.y,
                a.z*b.x-a.x*b.z,
                a.x*b.y-a.y*b.x);
}
//两点距离
inline double distance(const Vec3 &a,const Vec3 &b){
    double dx=a.x-b.x;
    double dy=a.y-b.y;
    double dz=a.z-b.z;
    return sqrt(dx*dx+dy*dy+dz*dz);
}

//标量左乘 todo待研究 
inline Vec3 operator *(float k, const Vec3 &v){
    return Vec3(k*v.x,k*v.y,k*v.z);
}

//******************************************************************************
//提供一个全局零向量
extern const Vec3 kZeroVec;


typedef struct Vec3 Pos;
typedef struct Vec3 Vec;
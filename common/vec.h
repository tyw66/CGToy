/** **************************************
 * @brief 3D向量类
 * @author tyw
 * @date 2018/09/26
 ****************************************/
#ifndef VEC3_H
#define VEC3_H


#include<math.h>
class Vec3{
public:
    float x,y,z;

    //! 默认构造函数,不执行任何操作
    Vec3(){}
    //! 复制构造函数
    Vec3(const Vec3 &a):x(a.x),y(a.y),z(a.z){}
    Vec3(float nx,float ny,float nz):x(nx),y(ny),z(nz){}

    ///标准对象操作
    //! 重载赋值运算符，返回引用实现左值。
    Vec3 &operator=(const Vec3&a){
        x=a.x;y=a.y;z=a.z;
        return *this;
    }
    //! 重载逻辑运算符
    bool operator == (const Vec3&a) const{
        return x==a.x && y==a.y	 && z==a.z;
    }
    bool operator != (const Vec3&a) const{
        return x!=a.x || y!=a.y	 || z!=a.z;
    }

    ///向量运算（符）
    //重载一元"-"运算符
    Vec3 operator - ()const{
        return Vec3(-x,-y,-z);
    }
    //重载二元"+"和"-"运算符
    Vec3 operator + (const Vec3 &a)const{
        return Vec3(x+a.x,y+a.y,z+a.z);
    }
    Vec3 operator - (const Vec3 &a)const{
        return Vec3(x-a.x,y-a.y,z-a.z);
    }
    //与标量的乘除法
    Vec3 operator * (float a)const{
        return Vec3(x*a,y*a,z*a);
    }
    Vec3 operator / (float a)const{
        float oneOverA =1.0f/a; //不对除0进行检查
        return Vec3(x*oneOverA,y*oneOverA,z*oneOverA);
    }
    //重载自反运算符
    Vec3 &operator +=(const Vec3&a){
        x +=a.x; y+=a.y; z+=a.z;
        return *this;
    }
    Vec3 &operator -=(const Vec3&a){
        x -=a.x; y-=a.y; z-=a.z;
        return *this;
    }
    Vec3 &operator *=(float a){
        x*=a;y*=a;z*=a;
        return *this;
    }
    Vec3 &operator /=(float a){
        float oneOverA =1.0f/a; //不对除0进行检查
        x*=oneOverA; y*=oneOverA; z*=oneOverA;
        return *this;
    }
    ///常用运算
    //置为零向量
    void zero(){
        x=y=z=0.0f;
    }
    //向量标准化
    void normalize(){
        float magSq=x*x+y*y+z*z;
        if(magSq>0.0f){//检查除0
            float oneOverMag=1.0f/sqrt(magSq);
            x*=oneOverMag;
            y*=oneOverMag;
            z*=oneOverMag;
        }
    }
    //向量点乘，重载标准乘法运算符
    float operator *(const Vec3 &a)const{
        return x*a.x+y*a.y+z*a.z;
    }

    ///成员函数版本
    //向量的模
    float mag(){
        return sqrt(x*x+y*y+z*z);
    }

};

///vector3非成员函数
//! 求向量模，非成员函数版本
inline float vectorMag(const Vec3 &a){
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}
//! 计算两向量叉乘
inline Vec3 crossProduct(const Vec3 &a,const Vec3 &b){
    return Vec3(
                a.y*b.z-a.z*b.y,
                a.z*b.x-a.x*b.z,
                a.x*b.y-a.y*b.x
                );
}
//! 实现标量左乘
inline Vec3 operator *(float k, const Vec3 &v){
    return Vec3(k*v.x,k*v.y,k*v.z);
}
//! 计算两点间距离
inline float distance(const Vec3 &a,const Vec3 &b){
    float dx=a.x-b.x;
    float dy=a.y-b.y;
    float dz=a.z-b.z;
    return sqrt(dx*dx+dy*dy+dz*dz);
}

//提供一个全局零向量
extern const Vec3 kZeroVector;

#endif


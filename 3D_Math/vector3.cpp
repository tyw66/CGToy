/** ***********************************
* @brief: Vector3类：简单的3D向量类
* @note : 是一个严格要求速度的类
* @date : 2018-02-11
***************************************/
#include<math.h>
class Vector3{
public:
    float x,y,z;
    ///构造函数
    //默认构造函数,不执行任何操作
    Vector3(){}
    //复制构造函数
    Vector3(const Vector3 &a):x(a.x),y(a.y),z(a.z){}
    Vector3(float nx,float ny,float nz):x(nx),y(ny),z(nz){}

    ///标准对象操作
    //重载赋值运算符，返回引用实现左值。
    Vector3 &operator=(const Vector3&a){
        x=a.x;y=a.y;z=a.z;
        return *this;
    }
    //重载逻辑运算符
    bool operator == (const Vector3&a) const{
        return x==a.x && y==a.y	 && z==a.z;
    }
    bool operator != (const Vector3&a) const{
        return x!=a.x || y!=a.y	 || z!=a.z;
    }

    ///向量运算（符）
    //重载一元"-"运算符
    Vector3 operator - ()const{
        return Vector3(-x,-y,-z);
    }
    //重载二元"+"和"-"运算符
    Vector3 operator + (const Vector3 &a)const{
        return Vector3(x+a.x,y+a.y,z+a.z);
    }
    Vector3 operator - (const Vector3 &a)const{
        return Vector3(x-a.x,y-a.y,z-a.z);
    }
    //与标量的乘除法
    Vector3 operator * (float a)const{
        return Vector3(x*a,y*a,z*a);
    }
    Vector3 operator / (float a)const{
        float oneOverA =1.0f/a; //不对除0进行检查
        return Vector3(x*oneOverA,y*oneOverA,z*oneOverA);
    }
    //重载自反运算符
    Vector3 &operator +=(const Vector3&a){
        x +=a.x; y+=a.y; z+=a.z;
        return *this;
    }
    Vector3 &operator -=(const Vector3&a){
        x -=a.x; y-=a.y; z-=a.z;
        return *this;
    }
    Vector3 &operator *=(float a){
        x*=a;y*=a;z*=a;
        return *this;
    }
    Vector3 &operator /=(float a){
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
    float operator *(const Vector3 &a)const{
        return x*a.x+y*a.y+z*a.z;
    }

    ///成员函数版本
    //向量的模
    float mag(){
        return sqrt(x*x+y*y+z*z);
    }

};

//////////////////////////////////////////
//vector3非成员函数
//////////////////////////////////////////
//求向量模，非成员函数版本
inline float vectorMag(const Vector3 &a){
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}
//计算两向量叉乘
inline Vector3 crossProduct(const Vector3 &a,const Vector3 &b){
    return Vector3(
                a.y*b.z-a.z*b.y,
                a.z*b.x-a.x*b.z,
                a.x*b.y-a.y*b.x
                );
}
//实现标量左乘
inline Vector3 operator *(float k, const Vector3 &v){
    return Vector3(k*v.x,k*v.y,k*v.z);
}
//计算两点间距离
inline float distance(const Vector3 &a,const Vector3 &b){
    float dx=a.x-b.x;
    float dy=a.y-b.y;
    float dz=a.z-b.z;
    return sqrt(dx*dx+dy*dy+dz*dz);
}

/////////////////////////////////
//全局变量
/////////////////////////////////
//提供一个全局零向量
extern const Vector3 kZeroVector;


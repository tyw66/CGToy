/** ***********************************
* @brief: ������
* @note : 
* @update : 2018-4-2
***************************************/
#include "math.h"
struct Vec3{
	///��Ա����  
	double x, y, z;
 	
	///���캯���������¶��� 
 	//Ĭ�Ϲ��캯��,��ִ���κβ���
    Vec3(){}
	//���ƹ��캯��
	Vec3(double nx=0, double ny=0, double nz=0):x(nx),y(ny),z(nz){} 
	Vec3(const Vec3& v):x(v.x),y(v.y),z(v.z){} 
	//Vec3 operator=(const Vec3& v)x(v.x),y(v.y),z(v.z){} 
	
	///��׼��������������¶��� 
	//����ȡ��
	Vec3 operator-()const{return Vec3(-x,-y,-z);}
	//�����ӷ�
	Vec3 operator+(const Vec3& v)const{return Vec3(x+v.x, y+v.y, z+v.z);}
	//��������
	Vec3 operator-(const Vec3& v)const{return Vec3(x-v.x, y-v.y, z-v.z);}
	//���������˷� �������ҳˣ� 
	Vec3 operator*(const double num)const{return Vec3(x*num, y*num, z*num);}
	//������������ 
	Vec3 operator*(const double num)const{return Vec3(x*num, y*num, z*num);}
	
	///�Է�������(ԭ�������޸�)
	//todo ����ֵ�ĳ�void������ 
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
		float oneOverN =1.0f/num; //���Գ�0���м��
		x*=oneOverN; y*=oneOverN; z*=oneOverN;
		return *this; 
	}
	
    ///��������
    //��Ϊ������
    void zero(){x=y=z=0.0;}     
    //������׼��
    void normalize(){
        float magSq=x*x+y*y+z*z;
        if(magSq>0.0f){//����0
            float oneOverMag=1.0f/sqrt(magSq);
            x*=oneOverMag; y*=oneOverMag; z*=oneOverMag;
        }
    }    
   	//��ģ 
	double norm()const{return sqrtf(x*x+y*y+z*z);}
	//��� 
 	double dotWith(const Vec3& v){return x*v.x+y*v.y+z*v.z;}
 	
};

//******************************************************************************
///�ǳ�Ա����
//������ģ
inline double vec3norm(const Vec3 &v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}


//���������
inline double vec3dot(const Vec3& a, const Vec3& b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

//���������
inline Vec3 vec3crossProduct(const Vec3 &a,const Vec3 &b){
    return Vec3(a.y*b.z-a.z*b.y,
                a.z*b.x-a.x*b.z,
                a.x*b.y-a.y*b.x);
}
//�������
inline double distance(const Vec3 &a,const Vec3 &b){
    double dx=a.x-b.x;
    double dy=a.y-b.y;
    double dz=a.z-b.z;
    return sqrt(dx*dx+dy*dy+dz*dz);
}

//������� todo���о� 
inline Vec3 operator *(float k, const Vec3 &v){
    return Vec3(k*v.x,k*v.y,k*v.z);
}

//******************************************************************************
//�ṩһ��ȫ��������
extern const Vec3 kZeroVec;


typedef struct Vec3 Pos;
typedef struct Vec3 Vec;
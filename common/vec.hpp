#include "math.h"
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
	//��������
	Vec3 operator*(const double number){return Vec3(x*number, y*number, z*number);}
};

//�������
double dot(const Vec3& lhs, const Vec3& rhs){
	return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z;
}

//�������	


typedef struct Vec3 Pos;
typedef struct Vec3 Vec;
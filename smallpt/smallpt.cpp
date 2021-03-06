/**
* 
*
*
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//#define M_PI 3.1415

//产生0-1随机数 
double erand48(unsigned short xsubi[3]) {
    return (double)rand() / (double)RAND_MAX;
}

//向量 
struct Vec{
    double x, y, z; // position, also color (r,g,b)
    Vec(double x_ = 0, double y_ = 0, double z_ = 0){
        x = x_;
        y = y_;
        z = z_;
    }
    Vec operator+(const Vec &b) const{
        return Vec(x + b.x, y + b.y, z + b.z);
    }
    Vec operator-(const Vec &b) const{
        return Vec(x - b.x, y - b.y, z - b.z);
    }
    //数乘
    Vec operator*(double b) const {
        return Vec(x * b, y * b, z * b);
    }
    //直接乘
    Vec mult(const Vec &b) const {
        return Vec(x * b.x, y * b.y, z * b.z);
    }
    //归一化
    Vec &norm() {
        return *this = *this * (1 / sqrt(x * x + y * y + z * z));
    }
    //内积
    double dot(const Vec &b) const{
        return x * b.x + y * b.y + z * b.z;
    }
    //外积
    Vec operator%(Vec &b){
        return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};

//射线 
struct Ray{
    Vec o, d;
    Ray(Vec o_, Vec d_) : o(o_), d(d_) {}
};

//表面类型 
enum Refl_t{
    DIFF,
    SPEC,
    REFR
}; // material types, used in radiance()

//球体 
struct Sphere{
    double rad;  // radius
    Vec p, e, c; // position, emission, color
    Refl_t refl; // reflection type (DIFFuse, SPECular, REFRactive)
    Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_) : rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {}

    // returns distance, 0 if nohit
    double intersect(const Ray &r) const
    {
        // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        Vec op = p - r.o;
        double t, eps = 1e-4;
        double b = op.dot(r.d);
        double det = b * b - op.dot(op) + rad * rad;
        if (det < 0)
            return 0;
        else
            det = sqrt(det);
        return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    }
};

Sphere spheres[] = {
    //Scene: radius, position, emission, color, material
    Sphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(), Vec(.75, .25, .25), DIFF),   //Left
    Sphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(), Vec(.25, .25, .75), DIFF), //Rght
    Sphere(1e5, Vec(50, 40.8, 1e5), Vec(), Vec(.75, .75, .75), DIFF),         //Back
    Sphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), Vec(), DIFF),               //Frnt
    Sphere(1e5, Vec(50, 1e5, 81.6), Vec(), Vec(.75, .75, .75), DIFF),         //Botm
    Sphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(), Vec(.75, .75, .75), DIFF), //Top

    Sphere(16.5, Vec(27, 16.5, 47), Vec(), Vec(1, 1, 1) * .999, SPEC),        //Mirr
    Sphere(16.5, Vec(73, 16.5, 78), Vec(), Vec(1, 1, 1) * .999, REFR),        //Glas
    Sphere(600, Vec(50, 681.6 - .27, 81.6), Vec(12, 12, 12), Vec(), DIFF)     //Lite
};

inline double clamp(double x){
    return x < 0 ? 0 : x > 1 ? 1 : x;
}
inline int toInt(double x){
    return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
}
inline bool intersect(const Ray &r, double &t, int &id){
    double n = sizeof(spheres) / sizeof(Sphere), d, inf = t = 1e20;
    for (int i = int(n); i--;){
        if ((d = spheres[i].intersect(r)) && d < t)
        {
            t = d;
            id = i;
        }
    }
    return t < inf;
}

Vec radiance(const Ray &r, int depth, unsigned short *Xi){
    //相交性检测 交点距离与相交对象 
    double t;	// distance to intersection    
    int id = 0; 	// id of intersected object
    if (!intersect(r, t, id)){
        return Vec();                  // if miss, return black
    }
    const Sphere &obj = spheres[id]; // the hit object
    
    
    Vec x = r.o + r.d * t;
	//交点处法向量 
	Vec n = (x - obj.p).norm();
	//法向量与光线方向向量夹角判断，determine if it is entering or exiting glass to ray. 
	Vec nl = n.dot(r.d) < 0 ? n : n * -1;
	//相交物体颜色 
	Vec f = obj.c;
	//颜色的最大分量 
    double p = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z; // max refl
    //Russian Roulette:Stop the recursion randomly based on the surface reflectivity.
    if (++depth > 5){
    	if (erand48(Xi) < p)
			f = f * (1 / p);
		else 
			return obj.e; //R.R.	
    }
	
    
    // 理想漫反射表面 
    if (obj.refl == DIFF){
        double r1 = 2 * M_PI * erand48(Xi);//随机角度 
		double r2 = erand48(Xi);
		double r2s = sqrt(r2);//random distance from center  
        Vec w = nl;
		Vec u = ((fabs(w.x) > 0.1 ? Vec(0, 1) : Vec(1)) % w).norm();
		Vec v = w % u;
        Vec d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();
        return obj.e + f.mult(radiance(Ray(x, d), depth, Xi));
    }
  
	// 理想镜面反射表面 
    else if (obj.refl == SPEC){
        return obj.e + f.mult(radiance(Ray(x, r.d - n * 2 * n.dot(r.d)), depth, Xi));
    }
    
    
    // 理想折射表面 
    Ray reflRay(x, r.d - n * 2 * n.dot(r.d));
     // Ray from outside going in?
    bool into = n.dot(nl) > 0;
    double nc = 1, nt = 1.5;
	double nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;
	 // Total internal reflection
    if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) < 0){
         return obj.e + f.mult(radiance(reflRay, depth, Xi));
    }   
    
    Vec tdir = (r.d * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t)))).norm();
    double a = nt - nc;
	double b = nt + nc;
	double R0 = a * a / (b * b);
	double c = 1 - (into ? -ddn : tdir.dot(n));
    double Re = R0 + (1 - R0) * c * c * c * c * c;
	double Tr = 1 - Re;
	double P = .25 + .5 * Re;
	double RP = Re / P;
	double TP = Tr / (1 - P);
	// Russian roulette
    return obj.e + f.mult(depth > 2 ? 
						(erand48(Xi) < P ? 	radiance(reflRay, depth, Xi) * RP : radiance(Ray(x, tdir), depth, Xi) * TP)
                                    : radiance(reflRay, depth, Xi) * Re + radiance(Ray(x, tdir), depth, Xi) * Tr);

}


int main(int argc, char *argv[]){
    //采样数
    int samps = argc == 2 ? atoi(argv[1]) / 4 : 1;
    //渲染的图像
    int w = 1024, h = 768;
    Vec *c = new Vec[w * h];
    //摄像机 位置方向
    Ray cam(Vec(50, 52, 295.6), Vec(0, -0.1, -1).norm());
    //摄影机目标X方向的增量
    Vec cx = Vec(w * 0.5135 / h);//0.5135是视角
    //摄影机目标Y方向的增量
    Vec cy = (cx % cam.d).norm() * 0.5135;

#pragma omp parallel for schedule(dynamic, 1) private(r) // OpenMP
    // 行循环
    for (int y = 0; y < h; y++){
        //进度输出
        printf("\rRendering (%d spp) %5.2f%%", samps * 4, 100. * y / (h - 1));
        //
        unsigned short Xi[3] = {0, 0, y * y * y};
        // 列循环
        for (unsigned short x = 0; x < w; x++){

            //从下到上“扫描”？
            int i = (h - y - 1) * w + x;
            // 2x2 subpixel rows
            for (int sy = 0; sy < 2; sy++){
                // 2x2 subpixel cols
                for (int sx = 0; sx < 2; sx++){
                    // Camera rays are pushed ^^^^^ forward to start in interior
                    Vec r;
                    for (int s = 0; s < samps; s++){
                        //构造subpixel的光线
                        double r1 = 2 * erand48(Xi), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
                        double r2 = 2 * erand48(Xi), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
                        Vec d = cx * (((sx + 0.5 + dx) / 2 + x) / w - 0.5) + cy * (((sy + 0.5 + dy) / 2 + y) / h - 0.5) + cam.d;
                        //追踪subpixel颜色，
                        r = r + radiance(Ray(cam.o + d * 140, d.norm()), 0, Xi) * (1.0 / samps);
                    }
                    //各subpixel的颜色混合,各占0.25 
                    c[i] = c[i] + Vec(clamp(r.x), clamp(r.y), clamp(r.z)) * 0.25;
                }
            }


        }
    }
    // Write image to PPM file.
    FILE *f = fopen("image.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    for (int i = 0; i < w * h; i++){
        fprintf(f, "%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
    }

}

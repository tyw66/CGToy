/** *********************
 *  画个圆/球
 *  半径为1
 ** **********************/
#include <stdio.h>
///0-基本版
// 画个平面圆，内部填充统一符号
void sphere0(){
	for(float y=1.5f; y>-1.5f; y-=0.05f){
		for(float x=-1.5f; x<1.5f; x+=0.025f){
			float f=x*x+y*y-1;
			putchar(f<=0.0f?'@':' ');
		}
		putchar('\n');
	}
}

///1-等值线版
// 画个平面圆，根据隐式方程的值填充不同符号
void sphere1(){
	for(float y=1.2f; y>-1.2f; y-=0.05f){
		for(float x=-1.2f; x<1.2f; x+=0.025f){
			float f=x*x+y*y-1;
			putchar(f<=0.0f?".-=#%@"[(int)(f*-5.0f)]:' ');
			//putchar(f<=0.0f?"0123456"[(int)(f*-6.0f)]:' ');
		}
		putchar('\n');
	}
}

///2-球体
// 根据法线与光线夹角余弦值填充不同符号
#include<math.h>
float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

float h(float x,float z){
	//获取表面(解方程的过程)
	//这个函数说明 Y轴 垂直纸面向外 右手坐标系
	for(float y=1.0f; y>=0.0f; y-=0.001f){
		if(f(x,y,z)<=0.0f)
			return y;
	}
	return 0.0f;
}

void sphere2(){
	for (float z = 1.2f; z > -1.2f; z -= 0.05f){
		for (float x = -1.2f; x < 1.2f; x += 0.025f) {
            if (f(x, 0.0f, z) <= 0.0f) {
				//球体法向量d=[x,y,z]
				float y = h(x, z);
				float cosA = (-x+y+z)/ sqrtf(x*x+y*y+z*z) / sqrtf(3);
				//wrapped diffuse修正，增大值，使其值在背面到正面的范围是 [0, 1]，而不是[-1,1];
				//避免法向量与光夹角大于90°时不显示的情况，负值的话就看不到了...
				float d = cosA*0.5f+0.5f;
				putchar(".-+#%@"[(int)(d * 6.0f)]);//.-+#%@
			}
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

///3-球体PPM图像输出
// 
void sphere3(){
	FILE* fp = fopen("sphere.ppm", "w");
	int width=512, height = 512;
	fprintf(fp, "P3\n%d %d\n255\n", width, height);

	for(int sy = 0; sy < height; sy++){
		float z = 1.5f - sy * 3.0f / height;//按比例从屏幕像素转到模型大小的尺度
		for(int sx = 0; sx <width; sx++){
			float x =sx *3.0f /width-1.5f;//按比例从屏幕像素转到模型大小的尺度

			if (f(x,0.0f,z) <= 0.0f) {//属于球体
                //球面法向量公式d=[x,y,z]
                float y = h(x, z);
                float cosA = (- x + y + z) / sqrtf(x*x+y*y+z*z) /sqrtf(3);//(光线向量：[1,-1,-1])
                float d = cosA*0.5f+0.5f;//wrapped diffuse处理
                //float d = cosA+0.2f>1.0f?1.0f:cosA+0.2f;//加入全局光处理

                int r = (int)(d*255.0f);
				fprintf(fp,"%d %d %d ",r,r,r);
			}
			else
				fprintf(fp,"255,255,255 ");
		}
		fputc('\n',fp);
	}
	fclose(fp);
	printf("sphere.ppm has been generated.\n");
}

///4-改变光照方向，球体PPM图像序列输出
//
#include<string.h>
void sphere4(){
	const int FRAME_NUMBER = 36;
	for(int index=0;index<FRAME_NUMBER;++index){
		//新建这一帧
		char fileName[200] ;
		sprintf(fileName,"sphere_%d.ppm",index);
		FILE* fp = fopen(fileName,"w");
		int width=512, height = 512;
		fprintf(fp, "P3\n%d %d\n255\n", width, height);

		//计算光照向量，从(-1,1,1)到(1,1,1)
		float theta = 10.0*(index+1)*3.14/180;
		float l_x = cos(theta);
		float l_y = sin(theta);
		
		float l_z = 1; 
		//float l_z = cos(theta);
		
		//绘制
		for(int sy = 0; sy<height;sy++){
			float z = 1.5f - sy * 3.0f / height;
			for(int sx = 0;sx <width; sx++){
				float x =sx *3.0f /width-1.5f;			
				if (f(x,0.0f,z) <= 0.0f) {
					//球面法向量公式d=[x,y,z]					
					float y = h(x,z);
					float cosA = (l_x*x+l_y*y+l_z*z)/sqrtf(x*x+y*y+z*z)/sqrtf(3);
					float d = cosA * 0.5f + 0.5f;
					
					//d
					int r = (int)(d*241.0f);	
					int g = (int)(d*124.0f);	
					int b = (int)(d*103.0f);				
					 
					fprintf(fp,"%d %d %d ",r,g,b);
				}
				else
					fprintf(fp,"185 136 125 ");//
			}
			fputc('\n',fp);
		}
		fclose(fp);
		printf("frame_%d has been generated.\n",index);
	}

}

///5 - ASCII 动画 - 心跳状动画 
//
#include <windows.h>
#include <tchar.h>
void sphere5(){
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
    _TCHAR buffer[25][80] = { _T(' ') };
    _TCHAR ramp[] = _T(".:-=+*#%@");
	
    for (float t = 0.0f;; t += 0.1f) {
        int sy = 0;
        float s = sinf(t);
        float a = s * s * s * s * 0.2f;
	
		for (float z = 1.3f; z > -1.2f; z -= 0.1f){
			_TCHAR* p = &buffer[sy++][0];
			float tz = z * (1.2f - a);//？？？ 
			
			for (float x = -1.5f; x < 1.5f; x += 0.05f) {
				float tx = x * (1.2f + a);//？？？ 
				if (f(tx, 0.0f, tz) <= 0.0f) {
					//球体法向量d=[x,y,z]
					float ty = h(tx, tz);
					float cosA = (-tx+ty+tz)/ sqrtf(tx*tx+ty*ty+tz*tz) / sqrtf(3);
					float d = cosA*0.5f+0.5f;
					*p++ = ramp[(int)(d * 5.0f)];
					//putchar(".-+#%@"[(int)(d * 6.0f)]);//.-+#%@
				}
				else
					*p++ = ' ';
					//putchar(' ');
			}
			//putchar('\n');
		}
		 for (sy = 0; sy < 25; sy++) {
			 COORD coord = { 0, sy };
			 SetConsoleCursorPosition(o, coord);
			 WriteConsole(o, buffer[sy], 79, NULL, 0);
		 }
		 Sleep(33);
	}

}

///6 - ASCII 动画 - 光照角度变化 
//
void sphere6(){
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
    _TCHAR buffer[60][100] = { _T(' ') };
    _TCHAR ramp[] = _T(".-+#%@");
   	

	int index = 0;
    for (float t = 0.0f;; t += 0.1f) {
        int sy = 0;
       	//计算光照向量，从(-1,1,1)到(1,1,1)       	
        float theta = 10.0*(index+1);
  		float tx = cosf(theta*3.14/180);
		float ty = sinf(theta*3.14/180);
		float tz = 1;
		//float tz = cosf(theta*3.14/180);
			
		for (float z = 1.2f; z > -1.2f; z -= 0.05f){	
			_TCHAR* p = &buffer[sy++][0];
			for (float x = -1.2f; x < 1.2f; x += 0.025f) {
				if (f(x, 0.0f, z) <= 0.0f) {
					//球体法向量d=[x,y,z]
					float y = h(x, z);
					float cosA = (tx*x+ty*y+tz*z)/ sqrtf(x*x+y*y+z*z) / sqrtf(tx*tx+ty*ty+tz*tz);
					float d = cosA*0.5f+0.5f;
					*p++ = ramp[(int)(d * 6.0f)];					
				}
				else
					*p++ = ' ';
			}
		}
		 for (sy = 0; sy < 60; sy++) {
			 COORD coord = { 0, sy };
			 SetConsoleCursorPosition(o, coord);
			 WriteConsole(o, buffer[sy], 100, NULL, 0);
		 }
		 //
		 index++;
		 if(index>35)index=0;
		 printf("DEBUG:theta=%f",theta);
		 Sleep(33);
	}

}


#include<stdlib.h>
int main(){
	int caseID = 6;
	//system("cls");
	
	switch(caseID){
	case 0:
		sphere0();break;
	case 1:
		sphere1();break;
	case 2:
		sphere2();break;
	case 3:
		sphere3();break;
	case 4:
		sphere4();break;
	case 5:
		sphere5();break;
	case 6:
		sphere6();break;
	default:
		break;
	}

	return 0;
}

    ///Finite difference求法矢量
    /*
    float y0 = h(x, z);
    float ny = 0.01f;
    float nx = h(x + ny, z) - y0;
    float nz = h(x, z + ny) - y0;
    float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
    //(nx + ny - nz)* nd /sqrtf(3)表示单位长度的光线向量与单位长度的法向量求内积
    float d = (nx + ny - nz)* nd /sqrtf(3) ;//* 0.5f + 0.5f;
    */

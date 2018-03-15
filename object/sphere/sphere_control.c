/** *********************
 *  画个圆/球
 *  半径为1
 *  键盘上下左右控制光源方向
 ** **********************/
#include <stdio.h>

// 根据法线与光线夹角余弦值填充不同符号
#include<math.h>
static float l_x;
static float l_y;
static float l_z;

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

#include<stdlib.h>
void sphere_control(){
	//system("cls");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	for (float z = 1.2f; z > -1.2f; z -= 0.05f){
		for (float x = -1.2f; x < 1.2f; x += 0.025f) {
            if (f(x, 0.0f, z) <= 0.0f) {
				//球体法向量d=[x,y,z]
				float y = h(x, z);
				float cosA = (x*l_x+y*l_y+z*l_z)/ sqrtf(x*x+y*y+z*z) / sqrtf(3);
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
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}

int main(){
	
	int theta = 225;
	l_x = -1;
	l_y = 1;
	l_z = 1;
	sphere_control();
	
	char flag;
	while(flag = getchar()){
		printf("debug:loop head.");
		printf("please press key : wasd to move. q to quit\n");
		if(flag == 'q') break;
		if(flag == 'a'){
			theta++;			
			l_x = cos(theta*3.14/180);
			l_y = sin(theta*3.14/180);

		}
		else if(flag == 'd'){
			theta--;			
			l_x = cos(theta*3.14/180);
			l_y = sin(theta*3.14/180);
		}
		else if(flag == 'w'){
			l_z++;			
		}
		else if(flag == 's'){
			l_z--;			
		}
		
		if(theta >=360)theta=0;
		if(l_z >10) l_z=10;
		if(l_z <-10) l_z=-10;
		
		
		sphere_control();
		
		printf("debug:loop tail.");
	}


	return 0;
}


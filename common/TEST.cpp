#include <stdio.h>
#include "color.hpp"   
#include "vec.hpp"   

//½á¹¹Ìå - ²âÊÔ 
int main(){
	/*
	Color red = {255,0,0};
	Color green(0,255,0); 
	Color blue = {0,0,255};

	Color white = red + blue + green;
	printf("white-> r:%d,g:%d,b:%d\n",white.r,white.g,white.b);
	
	Color cyan =   (red - white)*0.5;
	printf("cyan-> r:%d,g:%d,b:%d\n\n",cyan.r,cyan.g,cyan.b);
	
	Color gray(100,100,100);
	Color gray_light = gray*2;
	printf("gray_light:%d,%d,%d\n",gray_light.r,gray_light.g,gray_light.b);
	
	Color gray_light2 (gray_light);
	printf("gray_light2-> r:%d,g:%d,b:%d\n\n",gray_light2.r,gray_light2.g,gray_light2.b);
	*/
		

	Vec v1(4,1,1);
	Vec v2(3,2,3);
	Vec v= v1-v2;
 	printf("x:%f,y:%f,z:%f\n",v.x,v.y,v.z);

	printf("dot:%f",vec3dot(v1,v2));

}

#include <stdio.h>
#include "basic_type.hpp"   

//½á¹¹Ìå - ²âÊÔ 
int main(){

	Color red = {255,0,0};
	Color green(0,255,0); 
	Color blue = {0,0,255};

	Color white = red + blue + green;
	printf("white-> r:%d,g:%d,b:%d\n",white.r,white.g,white.b);
	
	Color cyan =   (red - white)*0.5;
	printf("cyan-> r:%d,g:%d,b:%d\n\n",cyan.r,cyan.g,cyan.b);
	
	
	Vec v1(4,1,1);
	Vec v2(3,2,3);
	Vec v= v1-v2;
 	printf("x:%f,y:%f,z:%f\n",v.x,v.y,v.z);

	printf("dot:%f",dot(v1,v2));
	
}

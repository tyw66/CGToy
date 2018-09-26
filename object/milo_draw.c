#include<stdio.h>
#include<math.h>

#define WIDTH 20
#define HEIGHT 20

int f(int px, int py){
	int x = px;
	int y = py;
	
	return ((y>-x+WIDTH/2)&&(y>x-WIDTH/2)&&(y<HEIGHT/2)? 1:0);	
	
	//return (y>=abs(x-10) ? 1 : 0);
	
}
	

/*milo的命令行画图框架*/
int main(){
	int x,y;
	for(y = 0; y<HEIGHT; ++y){
		for(x = 0; x< WIDTH; ++x){
			printf(f(x,y)? "*":" ");
		}		
		printf("\r\n");
	}
	return 0;
}
#include "svpng.inc"
#include <math.h>   // fmaxf(), sinf(), cosf()
#include <stdlib.h> // abs()
#include <string.h> // memset()
#define PI 3.14159265359f
#define W 1024
#define H 1024
static unsigned char img[W * H * 3];

void setpixel(int x, int y) {
   unsigned char* p = img + (y * W + x) * 3;
   p[0] = p[1] = p[2] = 0;
}

// Modified from  https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
void bresenham(int x0, int y0, int x1, int y1) {
   int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
   int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
   int err = (dx > dy ? dx : -dy) / 2;

   while (setpixel(x0, y0), x0 != x1 || y0 != y1) {
       int e2 = err;
       if (e2 > -dx) { err -= dy; x0 += sx; }
       if (e2 <  dy) { err += dx; y0 += sy; }
   }
}

int main() {
//    memset(img, 255, sizeof(img));//白色填充背景
//    float cx = W * 0.5f - 0.5f, cy = H * 0.5f - 0.5f;
//    for (int j = 0; j < 5; j++) {
//        float r1 = fminf(W, H) * (j + 0.5f) * 0.085f;
//        float r2 = fminf(W, H) * (j + 1.5f) * 0.085f;
//        float t = j * PI / 64.0f;
//        for (int i = 1; i <= 64; i++, t += 2.0f * PI / 64.0f) {
//            float ct = cosf(t), st = sinf(t);
//            bresenham((int)(cx + r1 * ct), (int)(cy - r1 * st), (int)(cx + r2 * ct), (int)(cy - r2 * st));
//        }
//    }

//    int index=1;
//    char* fileName="demo.png";
for(int index=1 ; index < 100; ++index){
   char tmp[10];
   sprintf(tmp,"%d",index);

   char fileName[20];
   strcpy(fileName,"demo_");
   strcat(fileName,tmp);
   strcat(fileName,".png");

   memset(img, 255, sizeof(img));//白色填充背景
   float cx = W * 0.5f - 0.5f, cy = H * 0.5f - 0.5f;
   int out=360;
   for(int angle=0, j= index ;j<out+index && angle<out;){
       bresenham((int)(j*cos(angle)+cx),(int)(j*sin(angle)+cy),
                 (int)((j+1)*cos(angle+1)+cx),(int)((j+1)*sin(angle+1)+cy));

       j+=1;
       ++angle;

   }

   svpng(fopen(fileName, "wb"), W, H, img, 0);
}

}



/** **********************************************************
 *
 *  随便画画，用svpng库导出为图片
 * Created by tyw66 at 2018-09-20
 *
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "svpng.inc"
#include "shader.h"

//! 图像大小
const double PI = 3.141592;
const int W = 512;
const int H = 512;

int main()
{
    unsigned char img[W*H*3];
    //遍历像素点
    for(int i = 0; i < H; ++i){
        for(int j = 0; j < W; ++j){
            //像素点着色
            Color c = shader01((double)i/H,(double)j/W);
            //保存到数组
            int index = (W*j + i)*3;
            img[index] = c.r;
            img[index+1] = c.g;
            img[index+2] = c.b;
                     
					 }
    }

    //数组保存到PNG
    FILE *fp = fopen("./img/demo.png", "wb");
    svpng(fp,W,H,img,0);

    printf("finish!\n");
    return 0;
}

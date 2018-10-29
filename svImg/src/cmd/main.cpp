#include <iostream>
#include "case.h"

int main(){
    int W = 100;
    int H = 60;

    //    #pragma omp parallel for
    //遍历像素点
    for(int i = 0; i < H; ++i){
        for(int j = 0; j < W; ++j){
            //获取颜色
            Color color = case000((double)j/W, (double)i/H, 0.5,0.5, 0);
            //设置颜色
            int c = color.toLightness() * 5 /255;
            putchar(" -*=#@"[c]);
        }
        putchar('\n');
    }

//    printf("\033c");//清屏
    //    m_time++;


    return 0;
}

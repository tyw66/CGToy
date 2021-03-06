#  画一个球
## 简介
在知乎上看了[用C语言绘制心形](https://www.zhihu.com/question/20187195/answer/34873279)，理解了思路，我自己也试着做一个球体版的。(球体的法线很直观，不用像心形那样用有限差分法，因此要简单些。)

程序根据圆形和球体的方程，画个球输出到控制台；输出到ppm图像文件；输出球体光照角度变化时的动画等。

## 食用说明
- 更改main()中的caseID数值(0,1,2...)，可以得到不同效果。

- 确保安装了c编译器，如gcc，简单调用 `gcc -o sphere sphere.c` 即可编译，然后执行`./sphere.exe`。

- case5和case6调用了windows的API，需要windows环境下。

## 效果
- CASE0: 控制台绘制，输出一个圆形，内部填充统一符号

![ ](case0.png)  

- CASE1: 控制台绘制，输出一个圆形，内部等值线填充不同符号

![ ](case1.png)  

- CASE2: 控制台绘制，输出一个球体，根据法线与光线夹角余弦值填充不同符号

![ ](case2.png)  

- CASE3: PPM图像输出,输出一个球体，根据法线与光线夹角余弦值填充不同灰度值

![ ](case3.png)  

- CASE4: PPM图像序列输出,光照方向改变下的球体，另外这次是一个红色为固有色。
 （已经人工把图像序列合成了gif动图）

![ ](case4.gif)  

- CASE5: 控制台动画，球的心跳状动画
 
-![ ](case5.gif)  

- CASE6: 控制台动画，球的光照方向动画
 
-![ ](case6.gif)  

- CASE7: PPM图像输出,输出球体，加入高光

-![ ](case7.png)  

## 一些效果
- 卡通渲染
-![ ](casePlus_cartoon.png)  


## 更详细的介绍
请参见知乎：[链接](https://zhuanlan.zhihu.com/p/34525494)


## 附
[ppm图像格式](https://zh.wikipedia.org/zh-hk/PBM%E6%A0%BC%E5%BC%8F)确实挺方便的，没有经过压缩，很直观，能够直接控制到某一个像素的RGB值，适合用作图形学这种练习项目。





--created on 2018/3/14 

--updated on 2018/3/28 


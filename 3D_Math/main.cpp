/** **********************************************
* @brief 《3D数学基础：图形与游戏开发》相关代码练习
*
* @date  2018.02.11
* @author tyw66@qq.com
**************************************************/
#include<iostream>
#include "vector3.cpp"
///测试1
void testCase1(){
    Vector3 v(1,2,3);
    Vector3 vec(v);
    std::cout<<vec.x<<" "<<vec.y<<" "<<vec.z<<std::endl;

    vec.z = 10;
    if(vec == v){
        vec.zero();
    }
    else{
        vec += vec;
    }
    std::cout<<vec.x<<" "<<vec.y<<" "<<vec.z<<std::endl;
}



int main(){
    int caseID = 1;
    switch (caseID) {
    case 1:
        testCase1();
        break;
        \
    default:
        break;
    }

    return 0;
}

/** *********************
 *  ����Բ/��
 *  �뾶Ϊ1
 ** **********************/
#include <stdio.h>
///0-������
// ����ƽ��Բ���ڲ����ͳһ����
void sphere0(){
	for(float y=1.5f; y>-1.5f; y-=0.05f){
		for(float x=-1.5f; x<1.5f; x+=0.025f){
			float f=x*x+y*y-1;
			putchar(f<=0.0f?'@':' ');
		}
		putchar('\n');
	}
}

///1-��ֵ�߰�
// ����ƽ��Բ��������ʽ���̵�ֵ��䲻ͬ����
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

///2-����
// ���ݷ�������߼н�����ֵ��䲻ͬ����
#include<math.h>
float f(float x, float y, float z){
	return x*x+y*y+z*z-1;
}

float h(float x,float z){
	//��ȡ����(�ⷽ�̵Ĺ���)
	//�������˵�� Y�� ��ֱֽ������ ��������ϵ
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
				//���巨����d=[x,y,z]
				float y = h(x, z);
				float cosA = (-x+y+z)/ sqrtf(x*x+y*y+z*z) / sqrtf(3);
				//wrapped diffuse����������ֵ��ʹ��ֵ�ڱ��浽����ķ�Χ�� [0, 1]��������[-1,1];
				//���ⷨ�������нǴ���90��ʱ����ʾ���������ֵ�Ļ��Ϳ�������...
				float d = cosA*0.5f+0.5f;
				putchar(".-+#%@"[(int)(d * 6.0f)]);//.-+#%@
			}
			else
				putchar(' ');
		}
		putchar('\n');
	}
}

///3-����PPMͼ�����
// 
void sphere3(){
	FILE* fp = fopen("sphere.ppm", "w");
	int width=512, height = 512;
	fprintf(fp, "P3\n%d %d\n255\n", width, height);

	for(int sy = 0; sy < height; sy++){
		float z = 1.5f - sy * 3.0f / height;//����������Ļ����ת��ģ�ʹ�С�ĳ߶�
		for(int sx = 0; sx <width; sx++){
			float x =sx *3.0f /width-1.5f;//����������Ļ����ת��ģ�ʹ�С�ĳ߶�

			if (f(x,0.0f,z) <= 0.0f) {//��������
                //���淨������ʽd=[x,y,z]
                float y = h(x, z);
                float cosA = (- x + y + z) / sqrtf(x*x+y*y+z*z) /sqrtf(3);//(����������[1,-1,-1])
                float d = cosA*0.5f+0.5f;//wrapped diffuse����
                //float d = cosA+0.2f>1.0f?1.0f:cosA+0.2f;//����ȫ�ֹ⴦��

                int r = (int)(d*255.0f);
				fprintf(fp,"%d %d %d ",r,r,r);
			}
			else
				fprintf(fp,"255,255,255 ");
		}
		fputc('\n',fp);
	}
	fclose(fp);
}

///4-�ı���շ�������PPMͼ���������
//
#include<string.h>
void sphere4(){
	const int FRAME_NUMBER = 36;
	for(int index=0;index<FRAME_NUMBER;++index){
		//�½���һ֡
		char fileName[200] ;
		sprintf(fileName,"sphere_%d.ppm",index);
		FILE* fp = fopen(fileName,"w");
		int width=512, height = 512;
		fprintf(fp, "P3\n%d %d\n255\n", width, height);

		//���������������(-1,1,1)��(1,1,1)
		float theta = 10.0*(index+1)*3.14/180;
		float l_x = cos(theta);
		float l_y = sin(theta);
		
		float l_z = 1; 
		//float l_z = cos(theta);
		
		//����
		for(int sy = 0; sy<height;sy++){
			float z = 1.5f - sy * 3.0f / height;
			for(int sx = 0;sx <width; sx++){
				float x =sx *3.0f /width-1.5f;			
				if (f(x,0.0f,z) <= 0.0f) {
					//���淨������ʽd=[x,y,z]					
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
	}

}

#include<stdlib.h>
int main(){
	int caseID = 0;
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

	default:
		break;
	}

	return 0;
}

    ///Finite difference��ʸ��
    /*
    float y0 = h(x, z);
    float ny = 0.01f;
    float nx = h(x + ny, z) - y0;
    float nz = h(x, z + ny) - y0;
    float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
    //(nx + ny - nz)* nd /sqrtf(3)��ʾ��λ���ȵĹ��������뵥λ���ȵķ��������ڻ�
    float d = (nx + ny - nz)* nd /sqrtf(3) ;//* 0.5f + 0.5f;
    */

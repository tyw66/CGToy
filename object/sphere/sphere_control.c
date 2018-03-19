/** ****************************************** 
 *  ����Բ/�� - ������̨������ 
 *  �뾶Ϊ1
 *  �����������ҿ������λ�ã�wasd���ƹ�Դ����
 * 
 *  ���˿ӣ���δ����~~����
 *********************************/
#include <stdio.h>
#include"windows.h"
#include <tchar.h>
// ���ݷ�������߼н�����ֵ��䲻ͬ����
#include<math.h>
static float l_x;
static float l_y;
static float l_z;

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


void sphere_control(){
	system("cls");
	HANDLE o = GetStdHandle(STD_OUTPUT_HANDLE);
    _TCHAR buffer[60][100] = { _T(' ') };
    _TCHAR ramp[] = _T(".-+#%@");
   	

	int index = 0;
    for (float t = 0.0f;; t += 0.1f) {
        int sy = 0;
       	//���������������(-1,1,1)��(1,1,1)       	
        float theta = 10.0*(index+1);
  		float tx = cosf(theta*3.14/180);
		float ty = sinf(theta*3.14/180);
		float tz = 1;
		//float tz = cosf(theta*3.14/180);
			
		for (float z = 1.2f; z > -1.2f; z -= 0.05f){	
			_TCHAR* p = &buffer[sy++][0];
			for (float x = -1.2f; x < 1.2f; x += 0.025f) {
				if (f(x, 0.0f, z) <= 0.0f) {
					//���巨����d=[x,y,z]
					float y = h(x, z);
					float cosA = (tx*x+ty*y+tz*z)/ sqrtf(x*x+y*y+z*z) / sqrtf(tx*tx+ty*ty+tz*tz);
					float d = cosA*0.5f+0.5f;
					*p++ = ramp[(int)(d * 6.0f)];					
				}
				else
					*p++ = ' ';
			}
		}
		 for (sy = 0; sy < 60; sy++) {
			 COORD coord = { 0, sy };
			 SetConsoleCursorPosition(o, coord);
			 WriteConsole(o, buffer[sy], 100, NULL, 0);
		 }
		 //
		 index++;
		 if(index>35)index=0;
		 printf("DEBUG:theta=%f",theta);
		// Sleep(33);
	}
}
/*
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
}*/


BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
char mesg[128];

switch(CEvent)
{
case KEY_EVENT :
	//if()
break;
/*
case CTRL_C_EVENT:
MessageBox(NULL,
"CTRL+C received!","CEvent",MB_OK);
break;
case CTRL_BREAK_EVENT:
MessageBox(NULL,
"CTRL+BREAK received!","CEvent",MB_OK);
break;
case CTRL_CLOSE_EVENT:
MessageBox(NULL,
"Program being closed!","CEvent",MB_OK);
break;
case CTRL_LOGOFF_EVENT:
MessageBox(NULL,
"User is logging off!","CEvent",MB_OK);
break;
case CTRL_SHUTDOWN_EVENT:
MessageBox(NULL,
"User is logging off!","CEvent",MB_OK);
break;
*/
}
return TRUE;
}

int main(){
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler,TRUE)==FALSE)
	{
		// unable to install handler... 
		// display message to the user
		printf("Unable to install handler!\n");
		return -1;
	} 
	while(1){
		sphere_control();
		
	}
}
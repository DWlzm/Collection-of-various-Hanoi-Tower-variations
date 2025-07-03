#include<stdio.h>
#include<windows.h>

#include"render.h" 



/*������һЩ��ͼ��ʾ�� 
* @sleepTime: �ȴ�ʱ�� 
* @autoPlay���Ƿ��Զ����� 
* @wall: ǽ 
* @pillar������ 
* @hanoiLeft����ŵ��Բ�������ʾ 
* @hanoiRight����ŵ��Բ���ұ���ʾ 
* @hanoiAir����ŵ��Բ���м��οղ�����ʾ 
*/  
const int sleepTime = 50; 
int autoPlay; 
const char wall = '#';  
const char pillar = '|'; 
const char hanoiLeft = '['; 
const char hanoiRight = ']'; 
const char hanoiAir = '-'; 
const int up = 0,down = 1,left = 2,right = 3; 
/*�������ƶ��� 
* @next_go ��һ���ƶ����� //��0��1��2��3��
*/ 
int next_go[4][2] = {{0,-1},{0,1},{-1,0},{1,0}}; 

/*��ϵͳ������ 
* @abc_pillar[3][1000] ��ǰ���ӷ��õ�Բ����
[i][0]��ŵ�i�����ӵ�ǰ�߶� 
*                      [i][j]��ʾ��i�����ӵ�j���ŵ�Բ�̴�С 
* @abc_x[3] abc���ӵ����� 
* 		    �������ֱ��ͨ�� ABC - 'A' ֱ�ӻ�ȡ�±�ȡֵ 
*/  
int N;
int abc_pillar[3][1000] = {{0},{0},{0}};
int abc_x[3] = {0,0,0}; 
int mapHeight,mapWidth; 
int deep;


//��¼��С���� 
long long cnt1,cnt2,cnt3,cnt4,cnt5;

// ָ�������ת��x��y�����괦
// ˮƽx����ֱy 
void gotoxy(int x,int y)  
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
} 

void menu()
{
	system("CLS");
	printf("\t\t\t*******************************Hanoi������*******************************\n\n");
	printf("\t\t\t\t\t\t\t1.����Hanoi������\n\n");
	printf("\t\t\t\t\t\t\t2.�����ƶ�Hanoi��\n\n");
	printf("\t\t\t\t\t\t\t3.����˫ɫHanoi��\n\n");	
	printf("\t\t\t\t\t\t\t4.˫��Hanoi��\n\n");
	printf("\t\t\t\t\t\t\t5.˫ɫHanoi���ֽ�\n\n");
	printf("\t\t\t\t\t\t\t6.��ɫHanoi���ֽ�\n\n");
//	printf("\t\t\t\t\t\t\t6.��ŵ�����ܷ���\n\n");
	printf("\t\t\t\t\t\t\t0.�˳�����\n\n");
	
	printf("\t\t\t*******************************Hanoi������*******************************\n\n");
}
/********************************	���뺺ŵ��ͷ�ļ�		****************************/
#include"Hanoi.h" 
#include"Red-BlueHanoi.h"
#include"Adjacent-Move-Hanoi.h"
#include"Red-BlueHanoi-Layered.h" 
#include"comparison.h"
#include"Double.h"
#include"threecolorHanoi-Layered.h" 

int main()
{
	render();
	int op=100;
	do{
		for(int i=0;i<3;i++)
			for(int j=0;j<1000;j++)
				abc_pillar[i][j]=0;
		for(int i=0;i<3;i++)
			abc_x[i]=0; 
		menu();
		printf("��������Ҫ���еĲ�����");
		scanf("%d",&op);
	    printf("hanoi����Ҫ���Ĳ���");
	    scanf("%d",&N);
		if(N%2&&op==4)	{
			printf("\nNӦ��Ϊż������������");
			system("pause");
			continue;
		}
	    printf("1.�Զ����� 0.�ֶ�����\n");
	   	while(1)
	   	{
	   		scanf("%d",&autoPlay);
			if(autoPlay==1||autoPlay==0)
			{
				break;
			}	
			else 
			{
				printf("����������\n");
			}
		}
	    system("CLS");
	    
	    getchar(); 
	    HideCursor();
	    if(op==1){
	    	system("CLS"); 
	    	init();//
	    	printf("\n");
	    	Sleep(1700);
	    	//Sleep(100000); ��ͼ��ʼ���� 
	    	cnt1=0;
			hanoi(N,'A','B','C');
			gotoxy(0,mapHeight+2);
			printf("������С�ƶ�������%d\n",cnt1);	
		}
	    else if(op==2){
	    		init();
	    		printf("\n");
	    		system("pause"); 
	    		//Sleep(100000); // ��ͼ��ʼ����
	    		cnt2=0;
				hanoi_nex(N,'A','B','C');
				gotoxy(0,mapHeight+2);
				printf("������С�ƶ�������%d\n",cnt2);
		}
	    
	    else if(op==3){
	    		cnt1=0;
	    		init_red_blue();
	    		printf("\n");
	    		system("pause"); 
	    		//	Sleep(100000); // ��ͼ��ʼ����
	    		hanoi_red_blue(N,'A','B','C');
	    		SetColor(15,0);
	    		gotoxy(0,mapHeight+2);
				printf("������С�ƶ�������%d\n",cnt1);
		}		
		else if(op==4){
			cnt5=0;
			init_double();
			printf("\n");
			system("pause"); 
			hanoi_double(N,'A','B','C');
			gotoxy(0,mapHeight+2);
			printf("������С�ƶ�������%d\n",cnt5);
		}
		else if(op==5){
			cnt4=0;
			init_s();
			printf("\n");
	    	system("pause"); 
			//	Sleep(100000); // ��ͼ��ʼ����
			hanoi_c(N,'A','B','C');
			SetColor(15,0);
			gotoxy(0,mapHeight+2);
			printf("������С�ƶ�������%d\n",cnt4);
		}
		system("pause");
	}while(op!=0);

    
    getchar();
    getchar();
    return 0;
} 

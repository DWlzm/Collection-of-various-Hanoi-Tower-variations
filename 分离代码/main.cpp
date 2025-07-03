#include<stdio.h>
#include<windows.h>

#include"render.h" 



/*【定义一些地图显示】 
* @sleepTime: 等待时间 
* @autoPlay：是否自动播放 
* @wall: 墙 
* @pillar：柱子 
* @hanoiLeft：汉诺塔圆盘左边显示 
* @hanoiRight：汉诺塔圆盘右边显示 
* @hanoiAir：汉诺塔圆盘中间镂空部分显示 
*/  
const int sleepTime = 50; 
int autoPlay; 
const char wall = '#';  
const char pillar = '|'; 
const char hanoiLeft = '['; 
const char hanoiRight = ']'; 
const char hanoiAir = '-'; 
const int up = 0,down = 1,left = 2,right = 3; 
/*【控制移动】 
* @next_go 下一次移动方向 //上0下1左2右3；
*/ 
int next_go[4][2] = {{0,-1},{0,1},{-1,0},{1,0}}; 

/*【系统变量】 
* @abc_pillar[3][1000] 当前柱子放置的圆盘数
[i][0]存放第i个柱子当前高度 
*                      [i][j]表示第i个柱子第j层存放的圆盘大小 
* @abc_x[3] abc柱子的坐标 
* 		    数组可以直接通过 ABC - 'A' 直接获取下标取值 
*/  
int N;
int abc_pillar[3][1000] = {{0},{0},{0}};
int abc_x[3] = {0,0,0}; 
int mapHeight,mapWidth; 
int deep;


//记录最小步数 
long long cnt1,cnt2,cnt3,cnt4,cnt5;

// 指定光标跳转到x，y的坐标处
// 水平x，竖直y 
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
	printf("\t\t\t*******************************Hanoi塔程序*******************************\n\n");
	printf("\t\t\t\t\t\t\t1.经典Hanoi塔动画\n\n");
	printf("\t\t\t\t\t\t\t2.相邻移动Hanoi塔\n\n");
	printf("\t\t\t\t\t\t\t3.红蓝双色Hanoi塔\n\n");	
	printf("\t\t\t\t\t\t\t4.双层Hanoi塔\n\n");
	printf("\t\t\t\t\t\t\t5.双色Hanoi塔分解\n\n");
	printf("\t\t\t\t\t\t\t6.三色Hanoi塔分解\n\n");
//	printf("\t\t\t\t\t\t\t6.汉诺塔性能分析\n\n");
	printf("\t\t\t\t\t\t\t0.退出程序\n\n");
	
	printf("\t\t\t*******************************Hanoi塔程序*******************************\n\n");
}
/********************************	导入汉诺塔头文件		****************************/
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
		printf("请输入需要进行的操作：");
		scanf("%d",&op);
	    printf("hanoi塔需要叠的层数");
	    scanf("%d",&N);
		if(N%2&&op==4)	{
			printf("\nN应该为偶数，重新输入");
			system("pause");
			continue;
		}
	    printf("1.自动播放 0.手动播放\n");
	   	while(1)
	   	{
	   		scanf("%d",&autoPlay);
			if(autoPlay==1||autoPlay==0)
			{
				break;
			}	
			else 
			{
				printf("请重新输入\n");
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
	    	//Sleep(100000); 截图开始画面 
	    	cnt1=0;
			hanoi(N,'A','B','C');
			gotoxy(0,mapHeight+2);
			printf("最终最小移动步数：%d\n",cnt1);	
		}
	    else if(op==2){
	    		init();
	    		printf("\n");
	    		system("pause"); 
	    		//Sleep(100000); // 截图开始画面
	    		cnt2=0;
				hanoi_nex(N,'A','B','C');
				gotoxy(0,mapHeight+2);
				printf("最终最小移动步数：%d\n",cnt2);
		}
	    
	    else if(op==3){
	    		cnt1=0;
	    		init_red_blue();
	    		printf("\n");
	    		system("pause"); 
	    		//	Sleep(100000); // 截图开始画面
	    		hanoi_red_blue(N,'A','B','C');
	    		SetColor(15,0);
	    		gotoxy(0,mapHeight+2);
				printf("最终最小移动步数：%d\n",cnt1);
		}		
		else if(op==4){
			cnt5=0;
			init_double();
			printf("\n");
			system("pause"); 
			hanoi_double(N,'A','B','C');
			gotoxy(0,mapHeight+2);
			printf("最终最小移动步数：%d\n",cnt5);
		}
		else if(op==5){
			cnt4=0;
			init_s();
			printf("\n");
	    	system("pause"); 
			//	Sleep(100000); // 截图开始画面
			hanoi_c(N,'A','B','C');
			SetColor(15,0);
			gotoxy(0,mapHeight+2);
			printf("最终最小移动步数：%d\n",cnt4);
		}
		system("pause");
	}while(op!=0);

    
    getchar();
    getchar();
    return 0;
} 

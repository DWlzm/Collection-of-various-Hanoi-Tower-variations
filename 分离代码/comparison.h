#include <stdio.h>
#include <time.h>
long long step1=0;
void hanoi_control(int n,char from ,char temp,char to){
    if(n==1){           // from到to只有一个需要移动就直接移动 
        step1++;
    }
    else{
        hanoi_control(n-1,from ,to,temp); //移动from 上面的n-1 ==> temp 暂存 
        step1++;
        hanoi_control(n-1,temp,from,to);  //移动temp 暂存的n-1 ==> to   目的地 
    }
}


void control(){
	int n[]={20,25,30,31,32,33};
	int step[6],idx=0;
	printf("\t\t\t*******************************  性能对比  *******************************\n\n");
	printf("汉诺塔层数	"); 
	for(int i=0;i<6;i++){
		printf("%d\t\t",n[i]);
	}
	printf("\n");
	printf("\n经典汉诺塔	\n");
	printf("时间：\t\t");
	for(int i=0;i<6;i++){
		step1=0;
		clock_t start, end;
	
		
		start = clock();

		hanoi_control(n[i],'A','B','C');
		
		
		end = clock();
		
		int	cpu_time_used =end-start; 
		printf("%dms\t\t", cpu_time_used);
		step[idx++]=step1;
	}
	printf("\n");
	printf("步数：\t\t");
	for(int i=0;i<6;i++)	printf("%lld步\t",step[i]);
	printf("\n");
	
	idx=0;
	printf("汉诺塔层数	"); 
	for(int i=0;i<6;i++){
		printf("%d\t\t",n[i]);
	}
	printf("\n");
	printf("\n经典汉诺塔	\n");
	printf("时间：\t\t");
	for(int i=0;i<6;i++){
		step1=0;
		clock_t start, end;
	
		
		start = clock();

		hanoi_control(n[i],'A','B','C');
		
		
		end = clock();
		
		int	cpu_time_used =end-start; 
		printf("%dms\t\t", cpu_time_used);
		step[idx++]=step1;
	}
	printf("\n");
	printf("步数：\t\t");
	for(int i=0;i<6;i++)	printf("%lld步\t",step[i]);
	printf("\n");
	
	 
}





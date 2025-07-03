#include <stdio.h>
#include <time.h>
long long step1=0;
void hanoi_control(int n,char from ,char temp,char to){
    if(n==1){           // from��toֻ��һ����Ҫ�ƶ���ֱ���ƶ� 
        step1++;
    }
    else{
        hanoi_control(n-1,from ,to,temp); //�ƶ�from �����n-1 ==> temp �ݴ� 
        step1++;
        hanoi_control(n-1,temp,from,to);  //�ƶ�temp �ݴ��n-1 ==> to   Ŀ�ĵ� 
    }
}


void control(){
	int n[]={20,25,30,31,32,33};
	int step[6],idx=0;
	printf("\t\t\t*******************************  ���ܶԱ�  *******************************\n\n");
	printf("��ŵ������	"); 
	for(int i=0;i<6;i++){
		printf("%d\t\t",n[i]);
	}
	printf("\n");
	printf("\n���人ŵ��	\n");
	printf("ʱ�䣺\t\t");
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
	printf("������\t\t");
	for(int i=0;i<6;i++)	printf("%lld��\t",step[i]);
	printf("\n");
	
	idx=0;
	printf("��ŵ������	"); 
	for(int i=0;i<6;i++){
		printf("%d\t\t",n[i]);
	}
	printf("\n");
	printf("\n���人ŵ��	\n");
	printf("ʱ�䣺\t\t");
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
	printf("������\t\t");
	for(int i=0;i<6;i++)	printf("%lld��\t",step[i]);
	printf("\n");
	
	 
}





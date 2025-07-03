struct abc{
	int x=0,y;
}abc_pi[3][1000];

void drawHanoi_s(int &x,int &y,int n,int next,int se){
	// 清空原来的 
	if(se%2)	SetColor(12,0);
	else SetColor(11,0); 
	
	
	char replace[2*n+1] = ""; 
	for(int i = 0; i < 2*n + 1; i++){
		replace[i] = ' ';
		if(i == n && y != 1){
			replace[i] = pillar;
		}
		if(i == 2*n){
			replace[i+1] = '\0';
		}
	}
	gotoxy(x - n,y);
	for(int i=0;replace[i];i++)
	{
		if(replace[i]=='#'||replace[i]=='|')
			SetColor(15,0);
		else if(se%2)	SetColor(12,0);
		else SetColor(11,0); 
		printf("%c",replace[i]);
	}
	// printf("%s",replace); ***********************************************************************************
	// 绘制新的 
	if(next != -1){
		x += next_go[next][0];
		y += next_go[next][1];	
	}
	for(int i = 0; i < 2*n + 1; i++){
		if(i == n && y != 1){
			replace[i] = pillar;
		}else if(i == 0){
			replace[i] = hanoiLeft;
		}else if(i == 2*n){
			replace[i] = hanoiRight;
		}else{
			replace[i] = hanoiAir;
		}
		if(i == 2*n){
			replace[i+1] = '\0';
		}
	}
	gotoxy(x - n,y);
	printf("%s",replace); 
	Sleep(sleepTime);
}


void init_s(){
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<1000;j++)
		{
			abc_pi[i][j].x=0;
			abc_pi[i][j].y=0;
		}
	}
	// 初始化柱子信息 
	abc_pi[0][0].x= N;
	for(int i = 1; i <= N; i++ ){
		abc_pi[0][i].x= (N + 2 - i)>>1;
		abc_pi[0][i].y=N+1-i;
	}
	//高度 = 上下墙(2) + deep(4) + 上空行(1) 
	//宽度 = 左右墙(2) + 3个区块[3*(deep*2+1)] + 两个中间空行(2)
	mapHeight = 2 + N + 1;
	mapWidth = 2 + 3 * (N * 2 + 1) + 2;
	
	//柱子0(a)水平坐标 = 左边墙(1) + deep(4) 
	//柱子1(b)水平坐标 = 柱子1 + 2*deep + 2 
	//柱子2(c)水平坐标 = 柱子2 + 2*deep + 2 
	abc_x[0] = 1 + N;
	abc_x[1] = abc_x[0] + 2* N + 2;
	abc_x[2] = abc_x[1] + 2* N + 2;
	
	// 绘制地图
	for(int i = 0; i < mapHeight; i++){
		for(int j = 0; j < mapWidth; j++){
			//墙体绘制 
			if(i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1){
				gotoxy(j,i);
				printf("%c",wall);
			}
			//绘制柱子
			else if( i > 1 && i < mapHeight - 1){
				if(j == abc_x[0] || j == abc_x[1] || j == abc_x[2]){
					//初始化绘制圆盘
					int abc_x_index = 0;
					if(j == abc_x[0]) abc_x_index = 0;
					else if(j == abc_x[1]) abc_x_index = 1;
					else if(j == abc_x[2]) abc_x_index = 2;
					drawHanoi_s(j,i,abc_pi[abc_x_index][N - i + 2].x,-1,abc_pi[abc_x_index][N - i + 2].y);
				}
			}
		}
	} 
}
void move_s(char from,char to){
	cnt4++;
	gotoxy(0,mapHeight+1); 
	printf("%c--->%c\n",from,to); //***************************************************
	// 获取from的柱子有多少高定位从哪开始 
	int fromHeight = abc_pi[from-'A'][0].x;
	int n = abc_pi[from-'A'][fromHeight].x;
	
	int x = abc_x[from-'A'];
	int y = 2 + N - fromHeight;
	abc_pi[from-'A'][0].x--;
	// 获取to 的柱子有多高 定位到哪结束 
	abc_pi[to-'A'][0].x++;
	int toHeight = abc_pi[to-'A'][0].x;
	abc_pi[to-'A'][toHeight] = abc_pi[from-'A'][fromHeight];
	int toX = abc_x[to-'A'];//********************************************************************
	int toY = 2 + N - toHeight;
	// 取出盘 ==> 上升至顶部 
	while(y > 1){
		drawHanoi_s(x,y,n,up,abc_pi[from-'A'][fromHeight].y);
		Sleep(100);
	}
	// 移动盘 ==> 移动至指定盘 
	if(x < toX){
		while(x < toX){
			drawHanoi_s(x,y,n,right,abc_pi[from-'A'][fromHeight].y);
			Sleep(100);
		}
	}else if(x > toX){
		while(x > toX){
			drawHanoi_s(x,y,n,left,abc_pi[from-'A'][fromHeight].y);
			Sleep(100);
		}
	}
	// 放置盘 ==> 下降到上面 
	while(y < toY){
		drawHanoi_s(x,y,n,down,abc_pi[from-'A'][fromHeight].y);
		Sleep(200);
	}
	//手动播放 
	if(autoPlay == 0){
		gotoxy(0,mapHeight+2); 
		printf("回车进行下一步"); 
		getchar(); 
	} 
}

/*
  4.双色Hanoi塔分层
*/
void hanoi_s(int n,char from ,char temp,char to){
	if(n==1){           // from到to只有一个需要移动就直接移动 
		move_s(from, to); //递归截止条件
		move_s(from,to);
	}
	else{
		hanoi_s(n-1,from ,to,temp); //移动from 上面的n-1 ==> temp 暂存 
		hanoi_s(1,from,temp,to);
		hanoi_s(n-1,temp,from,to);  //移动temp 暂存的n-1 ==> to   目的地 
	}
}
void hanoi_c(int n,char from ,char temp,char to){
	for(int i=n/2;i>1;i--)
	{
		hanoi_s(i-1,from,temp,to);
		move_s(from,temp);
		move_s(from,temp);
		hanoi_s(i-1,to,temp,from);
		move_s(temp,to);
	}
	move_s(from,temp);//n==1 
	move_s(from,to);	
}




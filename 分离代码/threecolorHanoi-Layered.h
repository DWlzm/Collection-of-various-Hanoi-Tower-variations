
void drawHanoi_3colors(int &x,int &y,int n,int next,int se){
	// 清空原来的 
	if(se%3==1)	SetColor(12,0);
	else if(se%3==2) SetColor(11,0); 
	else SetColor(10,0); 
	
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
		if(replace[i]=='#'||replace[i]=='|')	SetColor(15,0);
		else if(se%3==1)	SetColor(12,0);
		else if(se%3==2) SetColor(11,0); 
		else SetColor(10,0);
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

void init_3colors(){
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

//递归思想实现递回
void Hanoi3colors_whole(int N, char from, char temp, char to){ 
    if (N == 1){
        move( from, to); 
        move(from, to); 
        move( from, to);
    }else{
        Hanoi3colors_whole(N-1, from, to, temp); 
        Hanoi3colors_whole(1, from, temp, to); 
        Hanoi3colors_whole(N-1, temp, from, to);
    }
}
 
//A、B、C分别表示三种颜色的盘
void Hanoi3colors_control(int N){
    char from = 'A';
    char temp = 'B'; 
    char to = 'C'; 
    
    //移动过程提示
    if(N == 1){
        move( from, temp); 
        move( from, temp); 
        move( from, to); 
        move( temp, to); 
        move( temp, from); 
        move( to, temp);;
    }
    else {
        Hanoi3colors_whole(N-1, from, temp, to);//移动、递回
        move( from, temp); 
        move( from, temp); 
        move( from, temp);
        Hanoi3colors_whole(N-1, to, temp, from);//移动、递回
        move( temp, to); 
        move( temp, to); 
        move( temp, to);
        Hanoi3colors_whole(N-1, from, to, temp);//移动、递回
        move( to, from); 
        move( to, from);
        Hanoi3colors_whole(N-1, temp, from, to);//移动、递回
        move( from, temp);
        for (int i =N - 1; i > 0; i--){
            if (i>1){
                Hanoi3colors_whole(i-1, to, from, temp);//移动、递回
            }
            move(to, from); 
            move(to, from); 
            if (i>1){
                Hanoi3colors_whole(i-1, temp, from, to);//移动、递回
            }
            move( from, temp);
        }
    }
}

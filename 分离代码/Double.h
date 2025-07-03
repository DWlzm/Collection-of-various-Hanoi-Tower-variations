
void init_double(){
    // 初始化柱子信息 
    abc_pillar[0][0] = N;
   for(int i = 1; i <= N; i++ ){
		abc_pillar[0][i] = (N + 2 - i)>>1;
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
                    drawHanoi(j,i,abc_pillar[abc_x_index][N - i + 2],-1);
                }
            }
        }
    } 
}

void hanoi_double(int n,char from ,char temp,char to){
	if(n==2){           // from到to只有一个需要移动就直接移动 
		move(from, to); //递归截止条件
		move(from,to);
		cnt5+=2;
	}
	else{
		hanoi_double(n-2,from ,to,temp); //移动from 上面的n-1 ==> temp 暂存 
		move(from,to);
		move(from,to);
		cnt5+=2;
		hanoi_double(n-2,temp,from,to);  //移动temp 暂存的n-1 ==> to   目的地 
	}
}


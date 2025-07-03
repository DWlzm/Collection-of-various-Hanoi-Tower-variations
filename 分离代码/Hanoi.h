

// 清空x，y地方的绘制
// 并且绘制下一处 长度为n 的汉诺塔 
void drawHanoi(int &x,int &y,int n,int next){
    // 清空原来的 
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
    printf("%s",replace); 
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


void init(){
    // 初始化柱子信息 
    abc_pillar[0][0] = N;
    for(int i = 1; i <= N; i++ ){
        abc_pillar[0][i] = N + 1 - i;
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

// a ==> c 
// startx starty == > toX toY
void move(char from,char to){
    gotoxy(0,mapHeight+1); 
    printf("%c--->%c\n",from,to); 
    // 获取from的柱子有多少高定位从哪开始 
    int fromHeight = abc_pillar[from-'A'][0];
    int n = abc_pillar[from-'A'][fromHeight];
    int x = abc_x[from-'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from-'A'][0]--;
    // 获取to 的柱子有多高 定位到哪结束 
    abc_pillar[to-'A'][0]++;
    int toHeight = abc_pillar[to-'A'][0];
    abc_pillar[to-'A'][toHeight] = n;
    int toX = abc_x[to-'A'];
    int toY = 2 + N - toHeight;
    // 取出盘 ==> 上升至顶部 
    while(y > 1){
        drawHanoi(x,y,n,up);
        Sleep(100);
    }
    // 移动盘 ==> 移动至指定盘 
    if(x < toX)
        while(x < toX)
           drawHanoi(x,y,n,right),Sleep(100);
	else if(x > toX)
        while(x > toX)
            drawHanoi(x,y,n,left),Sleep(100);
        
    // 放置盘 ==> 下降到上面 
    while(y < toY){
        drawHanoi(x,y,n,down);
        Sleep(200);
    }
    //手动播放 
    if(autoPlay == 0){
        gotoxy(0,mapHeight+2); 
        printf("回车进行下一步"); 
        getchar(); 
    } 
}


/**
* from 从哪开始 
* temp 暂时经过 
* to   移动到哪 
*/

void hanoi(int n,char from ,char temp,char to){
    if(n==1){           // from到to只有一个需要移动就直接移动 
        move(from, to); //递归截止条件
        cnt1++;
    }
    else{
        hanoi(n-1,from ,to,temp); //移动from 上面的n-1 ==> temp 暂存 
        move(from,to);            //移动from 剩下的1   ==> to   目的地 
        cnt1++;
        hanoi(n-1,temp,from,to);  //移动temp 暂存的n-1 ==> to   目的地 
    }
}


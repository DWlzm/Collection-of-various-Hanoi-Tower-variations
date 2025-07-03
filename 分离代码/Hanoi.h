

// ���x��y�ط��Ļ���
// ���һ�����һ�� ����Ϊn �ĺ�ŵ�� 
void drawHanoi(int &x,int &y,int n,int next){
    // ���ԭ���� 
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
    // �����µ� 
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
    // ��ʼ��������Ϣ 
    abc_pillar[0][0] = N;
    for(int i = 1; i <= N; i++ ){
        abc_pillar[0][i] = N + 1 - i;
    }
    //�߶� = ����ǽ(2) + deep(4) + �Ͽ���(1) 
    //��� = ����ǽ(2) + 3������[3*(deep*2+1)] + �����м����(2)
    mapHeight = 2 + N + 1;
    mapWidth = 2 + 3 * (N * 2 + 1) + 2;
    
    //����0(a)ˮƽ���� = ���ǽ(1) + deep(4) 
    //����1(b)ˮƽ���� = ����1 + 2*deep + 2 
    //����2(c)ˮƽ���� = ����2 + 2*deep + 2 
    abc_x[0] = 1 + N;
    abc_x[1] = abc_x[0] + 2* N + 2;
    abc_x[2] = abc_x[1] + 2* N + 2;
    
    // ���Ƶ�ͼ
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            //ǽ����� 
            if(i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1){
                gotoxy(j,i);
                printf("%c",wall);
            }
            //��������
            else if( i > 1 && i < mapHeight - 1){
                if(j == abc_x[0] || j == abc_x[1] || j == abc_x[2]){
                    //��ʼ������Բ��
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
    // ��ȡfrom�������ж��ٸ߶�λ���Ŀ�ʼ 
    int fromHeight = abc_pillar[from-'A'][0];
    int n = abc_pillar[from-'A'][fromHeight];
    int x = abc_x[from-'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from-'A'][0]--;
    // ��ȡto �������ж�� ��λ���Ľ��� 
    abc_pillar[to-'A'][0]++;
    int toHeight = abc_pillar[to-'A'][0];
    abc_pillar[to-'A'][toHeight] = n;
    int toX = abc_x[to-'A'];
    int toY = 2 + N - toHeight;
    // ȡ���� ==> ���������� 
    while(y > 1){
        drawHanoi(x,y,n,up);
        Sleep(100);
    }
    // �ƶ��� ==> �ƶ���ָ���� 
    if(x < toX)
        while(x < toX)
           drawHanoi(x,y,n,right),Sleep(100);
	else if(x > toX)
        while(x > toX)
            drawHanoi(x,y,n,left),Sleep(100);
        
    // ������ ==> �½������� 
    while(y < toY){
        drawHanoi(x,y,n,down);
        Sleep(200);
    }
    //�ֶ����� 
    if(autoPlay == 0){
        gotoxy(0,mapHeight+2); 
        printf("�س�������һ��"); 
        getchar(); 
    } 
}


/**
* from ���Ŀ�ʼ 
* temp ��ʱ���� 
* to   �ƶ����� 
*/

void hanoi(int n,char from ,char temp,char to){
    if(n==1){           // from��toֻ��һ����Ҫ�ƶ���ֱ���ƶ� 
        move(from, to); //�ݹ��ֹ����
        cnt1++;
    }
    else{
        hanoi(n-1,from ,to,temp); //�ƶ�from �����n-1 ==> temp �ݴ� 
        move(from,to);            //�ƶ�from ʣ�µ�1   ==> to   Ŀ�ĵ� 
        cnt1++;
        hanoi(n-1,temp,from,to);  //�ƶ�temp �ݴ��n-1 ==> to   Ŀ�ĵ� 
    }
}


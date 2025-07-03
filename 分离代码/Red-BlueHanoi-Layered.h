struct abc{
	int x=0,y;
}abc_pi[3][1000];

void drawHanoi_s(int &x,int &y,int n,int next,int se){
	// ���ԭ���� 
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


void init_s(){
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<1000;j++)
		{
			abc_pi[i][j].x=0;
			abc_pi[i][j].y=0;
		}
	}
	// ��ʼ��������Ϣ 
	abc_pi[0][0].x= N;
	for(int i = 1; i <= N; i++ ){
		abc_pi[0][i].x= (N + 2 - i)>>1;
		abc_pi[0][i].y=N+1-i;
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
	// ��ȡfrom�������ж��ٸ߶�λ���Ŀ�ʼ 
	int fromHeight = abc_pi[from-'A'][0].x;
	int n = abc_pi[from-'A'][fromHeight].x;
	
	int x = abc_x[from-'A'];
	int y = 2 + N - fromHeight;
	abc_pi[from-'A'][0].x--;
	// ��ȡto �������ж�� ��λ���Ľ��� 
	abc_pi[to-'A'][0].x++;
	int toHeight = abc_pi[to-'A'][0].x;
	abc_pi[to-'A'][toHeight] = abc_pi[from-'A'][fromHeight];
	int toX = abc_x[to-'A'];//********************************************************************
	int toY = 2 + N - toHeight;
	// ȡ���� ==> ���������� 
	while(y > 1){
		drawHanoi_s(x,y,n,up,abc_pi[from-'A'][fromHeight].y);
		Sleep(100);
	}
	// �ƶ��� ==> �ƶ���ָ���� 
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
	// ������ ==> �½������� 
	while(y < toY){
		drawHanoi_s(x,y,n,down,abc_pi[from-'A'][fromHeight].y);
		Sleep(200);
	}
	//�ֶ����� 
	if(autoPlay == 0){
		gotoxy(0,mapHeight+2); 
		printf("�س�������һ��"); 
		getchar(); 
	} 
}

/*
  4.˫ɫHanoi���ֲ�
*/
void hanoi_s(int n,char from ,char temp,char to){
	if(n==1){           // from��toֻ��һ����Ҫ�ƶ���ֱ���ƶ� 
		move_s(from, to); //�ݹ��ֹ����
		move_s(from,to);
	}
	else{
		hanoi_s(n-1,from ,to,temp); //�ƶ�from �����n-1 ==> temp �ݴ� 
		hanoi_s(1,from,temp,to);
		hanoi_s(n-1,temp,from,to);  //�ƶ�temp �ݴ��n-1 ==> to   Ŀ�ĵ� 
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




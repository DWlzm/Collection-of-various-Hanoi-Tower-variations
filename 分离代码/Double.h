
void init_double(){
    // ��ʼ��������Ϣ 
    abc_pillar[0][0] = N;
   for(int i = 1; i <= N; i++ ){
		abc_pillar[0][i] = (N + 2 - i)>>1;
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

void hanoi_double(int n,char from ,char temp,char to){
	if(n==2){           // from��toֻ��һ����Ҫ�ƶ���ֱ���ƶ� 
		move(from, to); //�ݹ��ֹ����
		move(from,to);
		cnt5+=2;
	}
	else{
		hanoi_double(n-2,from ,to,temp); //�ƶ�from �����n-1 ==> temp �ݴ� 
		move(from,to);
		move(from,to);
		cnt5+=2;
		hanoi_double(n-2,temp,from,to);  //�ƶ�temp �ݴ��n-1 ==> to   Ŀ�ĵ� 
	}
}


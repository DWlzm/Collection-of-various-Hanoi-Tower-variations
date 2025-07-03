#include<stdio.h>
#include<windows.h>

/* ����һЩͼ����ʾ�ĳ���
 * @sleepTime: �ȴ�ʱ�� 
 * @autoPlay: �Ƿ��Զ����� 
 * @wall: ǽ 
 * @pillar: ���� 
 * @hanoiLeft: ��ŵ��Բ�������ʾ 
 * @hanoiRight: ��ŵ��Բ���Ҳ���ʾ 
 * @hanoiAir: ��ŵ��Բ���м�հײ�����ʾ 
 */  
const int sleepTime = 200; 
int autoPlay; 
const char wall = '#';  
const char pillar = '|'; 
const char hanoiLeft = '['; 
const char hanoiRight = ']'; 
const char hanoiAir = '-'; 
const int up = 0, down = 1, left = 2, right = 3; 

/* �����ƶ�����
 * @next_go ��һ���ƶ����� //ȡֵ 0,1,2,3 
 */ 
int next_go[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; 

/* ϵͳ����
 * @abc_pillar[3][1000] ��ǰ�����Ϸ��õ�Բ�����
[i][0] ��ʾ�� i �����ӵĵ�ǰ�߶� 
 *                      [i][j] ��ʾ�� i �����ӵĵ� j ��Բ�̵Ĵ�С 
 * @abc_x[3] abc �������ӵĺ����� 
 *            ����ֱ��ͨ�� ABC - 'A' ֱ�ӻ�ȡ�±�ȡֵ 
 */  
int N;
int abc_pillar[3][1000] = {{0}, {0}, {0}};
int abc_x[3] = {0, 0, 0}; 
int mapHeight, mapWidth; 
int deep;

VOID SetColor(UINT uFore, UINT uBack) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, uFore + uBack * 0x10);
}

VOID SetTitle(LPCSTR lpTitle) {
    SetConsoleTitle(lpTitle);
}

void render()
{
    SetTitle("Hanoi ��ŵ����ʾ����");
}

// �ƶ���굽 x,y ����λ��
// ˮƽ x ��ֱ y 
void gotoxy(int x, int y)  
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
} 

// ���ع�꺯��
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor;    
    cursor.bVisible = FALSE;    
    cursor.dwSize = sizeof(cursor);    
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
    SetConsoleCursorInfo(handle, &cursor);
}

// ���ƺ�ŵ��Բ��
// ��һ������Ϊ x ���꣬�ڶ�������Ϊ y ���꣬����������ΪԲ�̴�С�����ĸ�����Ϊ��һ���ƶ�����
void drawHanoi(int &x, int &y, int n, int next) {
    // ���ԭλ�� 
    char replace[2 * n + 1] = ""; 
    for (int i = 0; i < 2 * n + 1; i++) {
        replace[i] = ' ';
        if (i == n && y != 1) {
            replace[i] = pillar;
        }
        if (i == 2 * n) {
            replace[i + 1] = '\0';
        }
    }
    gotoxy(x - n, y);
    printf("%s", replace); 
    // �ƶ�����λ�� 
    if (next != -1) {
        x += next_go[next][0];
        y += next_go[next][1];	
    }
    for (int i = 0; i < 2 * n + 1; i++) {
        if (i == n && y != 1) {
            replace[i] = pillar;
        } else if (i == 0) {
            replace[i] = hanoiLeft;
        } else if (i == 2 * n) {
            replace[i] = hanoiRight;
        } else {
            replace[i] = hanoiAir;
        }
        if (i == 2 * n) {
            replace[i + 1] = '\0';
        }
    }
    gotoxy(x - n, y);
    printf("%s", replace); 
    Sleep(sleepTime);
}

// ��ʼ����ŵ��״̬
void init() {
    // ��ʼ��������Ϣ 
    abc_pillar[0][0] = N;
    for (int i = 1; i <= N; i++) {
        abc_pillar[0][i] = N + 1 - i;
    }
    // �߶� = ����ǽ(2) + ����(N) + �Ͽհ�(1) 
    // ��� = ����ǽ(2) + 3 ������[3*(����*2+1)] + �����м���(2)
    mapHeight = 2 + N + 1;
    mapWidth = 2 + 3 * (N * 2 + 1) + 2;
    
    // ���� 0(a) ˮƽλ�� = ��ǽ(1) + ����(N) 
    // ���� 1(b) ˮƽλ�� = ���� 0 + 2*���� + 2 
    // ���� 2(c) ˮƽλ�� = ���� 1 + 2*���� + 2 
    abc_x[0] = 1 + N;
    abc_x[1] = abc_x[0] + 2 * N + 2;
    abc_x[2] = abc_x[1] + 2 * N + 2;
    
    // ���Ƴ�ʼͼ��
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            // ǽ�Ļ��� 
            if (i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1) {
                gotoxy(j, i);
                printf("%c", wall);
            }
            // ���ӵĻ���
            else if (i > 1 && i < mapHeight - 1) {
                if (j == abc_x[0] || j == abc_x[1] || j == abc_x[2]) {
                    // ��ʼ���������ϵ�Բ��
                    int abc_x_index = 0;
                    if (j == abc_x[0]) abc_x_index = 0;
                    else if (j == abc_x[1]) abc_x_index = 1;
                    else if (j == abc_x[2]) abc_x_index = 2;
                    drawHanoi(j, i, abc_pillar[abc_x_index][N - i + 2], -1);
                }
            }
        }
    } 
}

// �ƶ�Բ��
// �� from �����ƶ��� to ����
void move(char from, char to) {
    gotoxy(0, mapHeight + 1); 
    printf("%c--->%c\n", from, to); 
    // ��ȡ from ���ӵ�ǰ�߶�λ�õĿ�ʼ 
    int fromHeight = abc_pillar[from - 'A'][0];
    int n = abc_pillar[from - 'A'][fromHeight];
    int x = abc_x[from - 'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from - 'A'][0]--;
    // ��ȡ to ���ӵ�ǰ�߶�λ�õĽ��� 
    abc_pillar[to - 'A'][0]++;
    int toHeight = abc_pillar[to - 'A'][0];
    abc_pillar[to - 'A'][toHeight] = n;
    int toX = abc_x[to - 'A'];
    int toY = 2 + N - toHeight;
    // ����Բ�� ==> �ƶ������� 
    while (y > 1) {
        drawHanoi(x, y, n, up);
        Sleep(100);
    }
    // �ƶ�Բ�� ==> �ƶ���Ŀ�������Ϸ� 
    if (x < toX)
        while (x < toX)
            drawHanoi(x, y, n, right), Sleep(100);
    else if (x > toX)
        while (x > toX)
            drawHanoi(x, y, n, left), Sleep(100);
        
    // ����Բ�� ==> �ŵ��������� 
    while (y < toY) {
        drawHanoi(x, y, n, down);
        Sleep(200);
    }
    // �ֶ����� 
    if (autoPlay == 0) {
        gotoxy(0, mapHeight + 2); 
        printf("�������������һ��"); 
        getchar(); 
    } 
}

/**
 * from ��ʼ���� 
 * temp ��ʱ���� 
 * to   Ŀ������ 
 */
int cnt1;
void hanoi(int n, char from, char temp, char to) {
    if (n == 1) {           // from �� to ֻ��һ��Բ����Ҫ�ƶ���ֱ���ƶ� 
        move(from, to); // �ݹ���ֹ����
        cnt1++;
    }
    else {
        hanoi(n - 1, from, to, temp); // �ƶ� from �����ϵ� n - 1 ��Բ�̵� temp ���� 
        move(from, to);            // �ƶ� from ������ʣ�µ� 1 ��Բ�̵� to ���� 
        cnt1++;
        hanoi(n - 1, temp, from, to);  // �ƶ� temp �����ϵ� n - 1 ��Բ�̵� to ���� 
    }
}

int main() {
    render();
    printf("hanoi Բ����Ҫ�ƶ�������: ");
    scanf("%d", &N);
    printf("1.�Զ����� 0.�ֶ�����\n");
    while (1) {
        scanf("%d", &autoPlay);
        if (autoPlay == 1 || autoPlay == 0) {
            break;
        }	
        else {
            printf("�����������������\n");
        }
    }
    system("CLS");
    
    getchar(); 
    HideCursor();
    init();
    printf("\n");
    Sleep(1700);
    cnt1 = 0;
    hanoi(N, 'A', 'B', 'C');
    gotoxy(0, mapHeight + 2);
    printf("��С�ƶ�����Ϊ: %d\n", cnt1);	
    system("pause");

    getchar();
    getchar();
    return 0;
} 

#include<stdio.h> 
#include<windows.h>
#include<time.h>

// 全局变量定义
int N;  // 汉诺塔层数
int mapHeight, mapWidth;  // 地图尺寸
int abc_x[3];  // 三根柱子的x坐标
int abc_pillar[3][1000];  // 柱子上圆盘的信息
int autoPlay = 0;  // 是否自动播放
long long cnt1 = 0, cnt2 = 0, cnt4 = 0, cnt5 = 0;  // 不同算法的步数统计
long long step1 = 0; // 性能测试用步数计数器

// 常量定义
const char wall = '#';      // 墙壁字符
const char pillar = '|';    // 柱子字符
const char hanoiLeft = '['; // 圆盘左边界
const char hanoiRight = ']';// 圆盘右边界
const char hanoiAir = '=';  // 圆盘填充字符
const int sleepTime = 50;   // 动画延迟时间(ms)
const int next_go[4][2] = {{0,-1},{1,0},{0,1},{-1,0}}; // 上右下左移动方向
const int up = 0, right = 1, down = 2, left = 3;  // 方向常量

// 双色分层汉诺塔的数据结构
struct abc{
    int x=0,y;
}abc_pi[3][1000];

// 函数声明
void gotoxy(int x, int y);
VOID SetColor(UINT uFore, UINT uBack);
VOID SetTitle(LPCSTR lpTitle);
void render();
void HideCursor();
void hanoi_control(int n, char from, char temp, char to);

// 光标定位函数
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

// 设置颜色函数
VOID SetColor(UINT uFore, UINT uBack) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, uFore+uBack*0x10);
}

// 设置标题函数
VOID SetTitle(LPCSTR lpTitle) {
    SetConsoleTitle(lpTitle);
}

// 渲染函数
void render() {
    SetTitle("Hanoi塔可视化显示程序");
}

// 隐藏光标函数
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor;    
    cursor.bVisible = FALSE;    
    cursor.dwSize = sizeof(cursor);    
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
    SetConsoleCursorInfo(handle, &cursor);
}

// 性能测试用的控制函数
void hanoi_control(int n, char from, char temp, char to) {
    if(n==1) {
        step1++;
    } else {
        hanoi_control(n-1, from, to, temp);
        step1++;
        hanoi_control(n-1, temp, from, to);
    }
}

// ŵĻƺ
void drawHanoi(int &x, int &y, int n, int next) {
    // ���ԭλ��
    char replace[2*n+1] = ""; 
    for(int i = 0; i < 2*n + 1; i++) {
        replace[i] = ' ';
        if(i == n && y != 1) {
            replace[i] = pillar;
        }
        if(i == 2*n) {
            replace[i+1] = '\0';
        }
    }
    gotoxy(x - n, y);
    printf("%s", replace);

    // ����λ��
    if(next != -1) {
        x += next_go[next][0];
        y += next_go[next][1];	
    }

    // ������λ��
    for(int i = 0; i < 2*n + 1; i++) {
        if(i == n && y != 1) {
            replace[i] = pillar;
        } else if(i == 0) {
            replace[i] = hanoiLeft;
        } else if(i == 2*n) {
            replace[i] = hanoiRight;
        } else {
            replace[i] = hanoiAir;
        }
        if(i == 2*n) {
            replace[i+1] = '\0';
        }
    }
    gotoxy(x - n, y);
    printf("%s", replace);
    Sleep(sleepTime);
}

// ������ŵ����ʼ��
void init() {
    // ��ʼ��������Ϣ
    abc_pillar[0][0] = N;
    for(int i = 1; i <= N; i++) {
        abc_pillar[0][i] = N + 1 - i;
    }
    
    mapHeight = 2 + N + 1;
    mapWidth = 2 + 3 * (N * 2 + 1) + 2;
    
    abc_x[0] = 1 + N;
    abc_x[1] = abc_x[0] + 2* N + 2;
    abc_x[2] = abc_x[1] + 2* N + 2;
    
    // ���Ƶ�ͼ
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if(i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1) {
                gotoxy(j, i);
                printf("%c", wall);
            }
            else if(i > 1 && i < mapHeight - 1) {
                if(j == abc_x[0] || j == abc_x[1] || j == abc_x[2]) {
                    int abc_x_index = 0;
                    if(j == abc_x[0]) abc_x_index = 0;
                    else if(j == abc_x[1]) abc_x_index = 1;
                    else if(j == abc_x[2]) abc_x_index = 2;
                    drawHanoi(j, i, abc_pillar[abc_x_index][N - i + 2], -1);
                }
            }
        }
    }
}

// �ƶ�Բ��
void move(char from, char to) {
    gotoxy(0, mapHeight+1);
    printf("%c--->%c\n", from, to);
    
    int fromHeight = abc_pillar[from-'A'][0];
    int n = abc_pillar[from-'A'][fromHeight];
    int x = abc_x[from-'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from-'A'][0]--;
    
    abc_pillar[to-'A'][0]++;
    int toHeight = abc_pillar[to-'A'][0];
    abc_pillar[to-'A'][toHeight] = n;
    int toX = abc_x[to-'A'];
    int toY = 2 + N - toHeight;
    
    // ȡ����
    while(y > 1) {
        drawHanoi(x, y, n, up);
        Sleep(100);
    }
    
    // ˮƽ�ƶ�
    if(x < toX)
        while(x < toX)
           drawHanoi(x, y, n, right), Sleep(100);
    else if(x > toX)
        while(x > toX)
            drawHanoi(x, y, n, left), Sleep(100);
    
    // ����ȥ
    while(y < toY) {
        drawHanoi(x, y, n, down);
        Sleep(200);
    }
    
    if(autoPlay == 0) {
        gotoxy(0, mapHeight+2);
        printf("���س�������һ��");
        getchar();
    }
}

// ������ŵ���ݹ�ʵ��
void hanoi(int n, char from, char temp, char to) {
    if(n == 1) {
        move(from, to);
        cnt1++;
    } else {
        hanoi(n-1, from, to, temp);
        move(from, to);
        cnt1++;
        hanoi(n-1, temp, from, to);
    }
}

// �����ƶ���ŵ��ʵ��
void hanoi_nex(int n, int from, char temp, char to) {
    if(n == 1) {
        move(from, temp);
        cnt2++;
        move(temp, to);
        cnt2++;
    } else {
        hanoi_nex(n-1, from, temp, to);
        move(from, temp);
        cnt2++;
        hanoi_nex(n-1, to, temp, from);
        move(temp, to);
        cnt2++;
        hanoi_nex(n-1, from, temp, to);
    }
}

// ˫ɫ��ŵ�����ƺ���
void drawHanoi_red_blue(int &x, int &y, int n, int next) {
    if(n%2) SetColor(12,0);
    else SetColor(11,0);
    
    char replace[2*n+1] = "";
    for(int i = 0; i < 2*n + 1; i++) {
        replace[i] = ' ';
        if(i == n && y != 1) {
            replace[i] = pillar;
        }
        if(i == 2*n) {
            replace[i+1] = '\0';
        }
    }
    gotoxy(x - n, y);
    for(int i = 0; replace[i]; i++) {
        if(replace[i] == '#' || replace[i] == '|')
            SetColor(15,0);
        else if(n%2) SetColor(12,0);
        else SetColor(11,0);
        printf("%c", replace[i]);
    }

    if(next != -1) {
        x += next_go[next][0];
        y += next_go[next][1];	
    }
    
    for(int i = 0; i < 2*n + 1; i++) {
        if(i == n && y != 1) {
            replace[i] = pillar;
        } else if(i == 0) {
            replace[i] = hanoiLeft;
        } else if(i == 2*n) {
            replace[i] = hanoiRight;
        } else {
            replace[i] = hanoiAir;
        }
        if(i == 2*n) {
            replace[i+1] = '\0';
        }
    }
    gotoxy(x - n, y);
    printf("%s", replace);
    Sleep(sleepTime);
}

// ˫ɫ��ŵ����ʼ��
void init_red_blue() {
    abc_pillar[0][0] = N;
    for(int i = 1; i <= N; i++) {
        abc_pillar[0][i] = N + 1 - i;
    }
    
    mapHeight = 2 + N + 1;
    mapWidth = 2 + 3 * (N * 2 + 1) + 2;
    
    abc_x[0] = 1 + N;
    abc_x[1] = abc_x[0] + 2* N + 2;
    abc_x[2] = abc_x[1] + 2* N + 2;
    
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if(i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1) {
                gotoxy(j, i);
                printf("%c", wall);
            }
            else if(i > 1 && i < mapHeight - 1) {
                if(j == abc_x[0] || j == abc_x[1] || j == abc_x[2]) {
                    int abc_x_index = 0;
                    if(j == abc_x[0]) abc_x_index = 0;
                    else if(j == abc_x[1]) abc_x_index = 1;
                    else if(j == abc_x[2]) abc_x_index = 2;
                    drawHanoi_red_blue(j, i, abc_pillar[abc_x_index][N - i + 2], -1);
                }
            }
        }
    }
}

// ˫ɫ��ŵ���ƶ�����
void move_red_blue(char from, char to) {
    gotoxy(0, mapHeight+1);
    printf("%c--->%c\n", from, to);
    
    int fromHeight = abc_pillar[from-'A'][0];
    int n = abc_pillar[from-'A'][fromHeight];
    int x = abc_x[from-'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from-'A'][0]--;
    
    abc_pillar[to-'A'][0]++;
    int toHeight = abc_pillar[to-'A'][0];
    abc_pillar[to-'A'][toHeight] = n;
    int toX = abc_x[to-'A'];
    int toY = 2 + N - toHeight;
    
    while(y > 1) {
        drawHanoi_red_blue(x, y, n, up);
        Sleep(100);
    }
    
    if(x < toX)
        while(x < toX)
           drawHanoi_red_blue(x, y, n, right), Sleep(100);
    else if(x > toX)
        while(x > toX)
            drawHanoi_red_blue(x, y, n, left), Sleep(100);
    
    while(y < toY) {
        drawHanoi_red_blue(x, y, n, down);
        Sleep(200);
    }
    
    if(autoPlay == 0) {
        gotoxy(0, mapHeight+2);
        printf("���س�������һ��");
        getchar();
    }
}

// ˫ɫ��ŵ���ݹ�ʵ��
void hanoi_red_blue(int n, char from, char temp, char to) {
    if(n == 1) {
        move_red_blue(from, to);
        cnt1++;
    } else {
        hanoi_red_blue(n-1, from, to, temp);
        move_red_blue(from, to);
        cnt1++;
        hanoi_red_blue(n-1, temp, from, to);
    }
}

// ��ɫ��ŵ�����ƺ���
void drawHanoi_3colors(int &x, int &y, int n, int next, int se) {
    if(se%3==1) SetColor(12,0);
    else if(se%3==2) SetColor(11,0);
    else SetColor(10,0);
    
    char replace[2*n+1] = "";
    for(int i = 0; i < 2*n + 1; i++) {
        replace[i] = ' ';
        if(i == n && y != 1) {
            replace[i] = pillar;
        }
        if(i == 2*n) {
            replace[i+1] = '\0';
        }
    }
    gotoxy(x - n, y);
    for(int i = 0; replace[i]; i++) {
        if(replace[i]=='#' || replace[i]=='|') SetColor(15,0);
        else if(se%3==1) SetColor(12,0);
        else if(se%3==2) SetColor(11,0);
        else SetColor(10,0);
        printf("%c", replace[i]);
    }

    if(next != -1) {
        x += next_go[next][0];
        y += next_go[next][1];	
    }
    
    for(int i = 0; i < 2*n + 1; i++) {
        if(i == n && y != 1) {
            replace[i] = pillar;
        } else if(i == 0) {
            replace[i] = hanoiLeft;
        } else if(i == 2*n) {
            replace[i] = hanoiRight;
        } else {
            replace[i] = hanoiAir;
        }
        if(i == 2*n) {
            replace[i+1] = '\0';
        }
    }
    gotoxy(x - n, y);
    printf("%s", replace);
    Sleep(sleepTime);
}

// ��ɫ��ŵ���ݹ�ʵ��
void Hanoi3colors_whole(int N, char from, char temp, char to) {
    if (N == 1) {
        move(from, to);
        move(from, to);
        move(from, to);
    } else {
        Hanoi3colors_whole(N-1, from, to, temp);
        Hanoi3colors_whole(1, from, temp, to);
        Hanoi3colors_whole(N-1, temp, from, to);
    }
}

// ��ɫ��ŵ�����ƺ���
void Hanoi3colors_control(int N) {
    char from = 'A';
    char temp = 'B';
    char to = 'C';
    
    if(N == 1) {
        move(from, temp);
        move(from, temp);
        move(from, to);
        move(temp, to);
        move(temp, from);
        move(to, temp);
    } else {
        Hanoi3colors_whole(N-1, from, temp, to);
        move(from, temp);
        move(from, temp);
        move(from, temp);
        Hanoi3colors_whole(N-1, to, temp, from);
        move(temp, to);
        move(temp, to);
        move(temp, to);
        Hanoi3colors_whole(N-1, from, to, temp);
        move(to, from);
        move(to, from);
        Hanoi3colors_whole(N-1, temp, from, to);
        move(from, temp);
        for (int i = N - 1; i > 0; i--) {
            if (i > 1) {
                Hanoi3colors_whole(i-1, to, from, temp);
            }
            move(to, from);
            move(to, from);
            if (i > 1) {
                Hanoi3colors_whole(i-1, temp, from, to);
            }
            move(from, temp);
        }
    }
}

// ���ܶԱȺ���
void control() {
    int n[] = {20,25,30,31,32,33};
    int step[6], idx = 0;
    printf("\t\t\t*******************************  ���ܶԱ�  *******************************\n\n");
    printf("��ŵ������\t");
    for(int i = 0; i < 6; i++) {
        printf("%d\t\t", n[i]);
    }
    printf("\n");
    printf("\n���人ŵ��\t\n");
    printf("ʱ�䣺\t\t");
    for(int i = 0; i < 6; i++) {
        step1 = 0;
        clock_t start, end;
        
        start = clock();
        hanoi_control(n[i], 'A', 'B', 'C');
        end = clock();
        
        int cpu_time_used = end-start;
        printf("%dms\t\t", cpu_time_used);
        step[idx++] = step1;
    }
    printf("\n");
    printf("������\t\t");
    for(int i = 0; i < 6; i++) printf("%lld��\t", step[i]);
    printf("\n");
    
    idx = 0;
    printf("��ŵ������\t");
    for(int i = 0; i < 6; i++) {
        printf("%d\t\t", n[i]);
    }
    printf("\n");
    printf("\n���ں�ŵ��\t\n");
    printf("ʱ�䣺\t\t");
    for(int i = 0; i < 6; i++) {
        step1 = 0;
        clock_t start, end;
        
        start = clock();
        hanoi_control(n[i], 'A', 'B', 'C');
        end = clock();
        
        int cpu_time_used = end-start;
        printf("%dms\t\t", cpu_time_used);
        step[idx++] = step1;
    }
    printf("\n");
    printf("������\t\t");
    for(int i = 0; i < 6; i++) printf("%lld��\t", step[i]);
    printf("\n");
}

// ������
int main() {
    HideCursor();
    render();
    printf("�����뺺ŵ���Ĳ�����");
    scanf("%d", &N);
    printf("�Ƿ��Զ���ʾ(1��/0��)��");
    scanf("%d", &autoPlay);
    system("cls");
    
    // ������Ҫѡ��ͬ�ĺ�ŵ��ʵ��
    init(); // �� init_red_blue(); ��������ʼ������
    hanoi(N, 'A', 'B', 'C'); // ��������ŵ������
    
    gotoxy(0, mapHeight+3);
    printf("��ʾ��ɣ�\n");
    return 0;
} 

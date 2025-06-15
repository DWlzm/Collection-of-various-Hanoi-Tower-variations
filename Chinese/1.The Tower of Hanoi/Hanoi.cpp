#include<stdio.h>
#include<windows.h>

/* 定义一些图形显示的常量
 * @sleepTime: 等待时间 
 * @autoPlay: 是否自动播放 
 * @wall: 墙 
 * @pillar: 柱子 
 * @hanoiLeft: 汉诺塔圆盘左侧显示 
 * @hanoiRight: 汉诺塔圆盘右侧显示 
 * @hanoiAir: 汉诺塔圆盘中间空白部分显示 
 */  
const int sleepTime = 200; 
int autoPlay; 
const char wall = '#';  
const char pillar = '|'; 
const char hanoiLeft = '['; 
const char hanoiRight = ']'; 
const char hanoiAir = '-'; 
const int up = 0, down = 1, left = 2, right = 3; 

/* 定义移动方向
 * @next_go 下一步移动方向 //取值 0,1,2,3 
 */ 
int next_go[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; 

/* 系统变量
 * @abc_pillar[3][1000] 当前柱子上放置的圆盘情况
[i][0] 表示第 i 个柱子的当前高度 
 *                      [i][j] 表示第 i 个柱子的第 j 个圆盘的大小 
 * @abc_x[3] abc 三个柱子的横坐标 
 *            可以直接通过 ABC - 'A' 直接获取下标取值 
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
    SetTitle("Hanoi 汉诺塔演示程序");
}

// 移动光标到 x,y 坐标位置
// 水平 x 垂直 y 
void gotoxy(int x, int y)  
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
} 

// 隐藏光标函数
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor;    
    cursor.bVisible = FALSE;    
    cursor.dwSize = sizeof(cursor);    
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
    SetConsoleCursorInfo(handle, &cursor);
}

// 绘制汉诺塔圆盘
// 第一个参数为 x 坐标，第二个参数为 y 坐标，第三个参数为圆盘大小，第四个参数为下一步移动方向
void drawHanoi(int &x, int &y, int n, int next) {
    // 清除原位置 
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
    // 移动到新位置 
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

// 初始化汉诺塔状态
void init() {
    // 初始化柱子信息 
    abc_pillar[0][0] = N;
    for (int i = 1; i <= N; i++) {
        abc_pillar[0][i] = N + 1 - i;
    }
    // 高度 = 上下墙(2) + 层数(N) + 上空白(1) 
    // 宽度 = 左右墙(2) + 3 个柱子[3*(层数*2+1)] + 柱子中间间隔(2)
    mapHeight = 2 + N + 1;
    mapWidth = 2 + 3 * (N * 2 + 1) + 2;
    
    // 柱子 0(a) 水平位置 = 左墙(1) + 层数(N) 
    // 柱子 1(b) 水平位置 = 柱子 0 + 2*层数 + 2 
    // 柱子 2(c) 水平位置 = 柱子 1 + 2*层数 + 2 
    abc_x[0] = 1 + N;
    abc_x[1] = abc_x[0] + 2 * N + 2;
    abc_x[2] = abc_x[1] + 2 * N + 2;
    
    // 绘制初始图形
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            // 墙的绘制 
            if (i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1) {
                gotoxy(j, i);
                printf("%c", wall);
            }
            // 柱子的绘制
            else if (i > 1 && i < mapHeight - 1) {
                if (j == abc_x[0] || j == abc_x[1] || j == abc_x[2]) {
                    // 开始绘制柱子上的圆盘
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

// 移动圆盘
// 从 from 柱子移动到 to 柱子
void move(char from, char to) {
    gotoxy(0, mapHeight + 1); 
    printf("%c--->%c\n", from, to); 
    // 获取 from 柱子当前高度位置的开始 
    int fromHeight = abc_pillar[from - 'A'][0];
    int n = abc_pillar[from - 'A'][fromHeight];
    int x = abc_x[from - 'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from - 'A'][0]--;
    // 获取 to 柱子当前高度位置的结束 
    abc_pillar[to - 'A'][0]++;
    int toHeight = abc_pillar[to - 'A'][0];
    abc_pillar[to - 'A'][toHeight] = n;
    int toX = abc_x[to - 'A'];
    int toY = 2 + N - toHeight;
    // 拿起圆盘 ==> 移动到顶部 
    while (y > 1) {
        drawHanoi(x, y, n, up);
        Sleep(100);
    }
    // 移动圆盘 ==> 移动到目标柱子上方 
    if (x < toX)
        while (x < toX)
            drawHanoi(x, y, n, right), Sleep(100);
    else if (x > toX)
        while (x > toX)
            drawHanoi(x, y, n, left), Sleep(100);
        
    // 放下圆盘 ==> 放到新柱子上 
    while (y < toY) {
        drawHanoi(x, y, n, down);
        Sleep(200);
    }
    // 手动控制 
    if (autoPlay == 0) {
        gotoxy(0, mapHeight + 2); 
        printf("按任意键继续下一步"); 
        getchar(); 
    } 
}

/**
 * from 起始柱子 
 * temp 临时柱子 
 * to   目标柱子 
 */
int cnt1;
void hanoi(int n, char from, char temp, char to) {
    if (n == 1) {           // from 到 to 只有一个圆盘需要移动则直接移动 
        move(from, to); // 递归终止条件
        cnt1++;
    }
    else {
        hanoi(n - 1, from, to, temp); // 移动 from 柱子上的 n - 1 个圆盘到 temp 柱子 
        move(from, to);            // 移动 from 柱子上剩下的 1 个圆盘到 to 柱子 
        cnt1++;
        hanoi(n - 1, temp, from, to);  // 移动 temp 柱子上的 n - 1 个圆盘到 to 柱子 
    }
}

int main() {
    render();
    printf("hanoi 圆盘需要移动的数量: ");
    scanf("%d", &N);
    printf("1.自动播放 0.手动播放\n");
    while (1) {
        scanf("%d", &autoPlay);
        if (autoPlay == 1 || autoPlay == 0) {
            break;
        }	
        else {
            printf("输入错误，请重新输入\n");
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
    printf("最小移动次数为: %d\n", cnt1);	
    system("pause");

    getchar();
    getchar();
    return 0;
} 

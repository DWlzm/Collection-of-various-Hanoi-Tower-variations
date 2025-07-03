/*
 * Hanoi Tower Demonstration Program
 * 
 * Copyright (c) 2025 Zhongming Liu
 * 
 * This program is a demonstration of the classic Tower of Hanoi problem.
 * It uses a recursive algorithm to solve the problem and graphically displays
 * the movement of disks through the console interface.
 * 
 * This software is protected by copyright laws. Without the explicit permission
 * of the copyright holder, any reproduction, modification, distribution, 
 * publication, or other dissemination of all or part of this software is prohibited.
 * 
 * The use of this software is limited to personal learning and demonstration purposes.
 * Any commercial use or other use beyond the scope of permission requires 
 * written permission from the copyright holder.
 * 
 * Author: Zhongming Liu
 * Date: 2025
 */

#include <stdio.h>
#include <windows.h>

/* Define constants for graphical display
 * @sleepTime: Delay time between moves (milliseconds)
 * @autoPlay: Automatic play mode (1) or manual play mode (0)
 * @wall: Wall character
 * @pillar: Pillar character
 * @hanoiLeft: Left side character of the disk
 * @hanoiRight: Right side character of the disk
 * @hanoiAir: Middle character of the disk
 */
const int sleepTime = 300;
int autoPlay;
const char wall = '#';
const char pillar = '|';
const char hanoiLeft = '[';
const char hanoiRight = ']';
const char hanoiAir = '-';
const int up = 0, down = 1, left = 2, right = 3;

/* Define movement directions
 * @next_go: Direction array for movement (up, down, left, right)
 */
int next_go[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

/* System variables
 * @abc_pillar[3][1000]: Current state of disks on each pillar
 *                      [i][0] indicates the current height of pillar i
 *                      [i][j] indicates the size of the j-th disk on pillar i
 * @abc_x[3]: X-coordinates of the three pillars (A, B, C)
 */
int N;
int abc_pillar[3][1000] = {{0}, {0}, {0}};
int abc_x[3] = {0, 0, 0};
int mapHeight, mapWidth;
int deep;

// Function prototypes
VOID SetColor(UINT uFore, UINT uBack);
VOID SetTitle(LPCSTR lpTitle);
void render();
void gotoxy(int x, int y);
void HideCursor();
void drawHanoi(int &x, int &y, int n, int next);
void init();
void move(char from, char to);
void hanoi(int n, char from, char temp, char to);

// Set console text color
VOID SetColor(UINT uFore, UINT uBack) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, uFore + uBack * 0x10);
}

// Set console window title
VOID SetTitle(LPCSTR lpTitle) {
    SetConsoleTitle(lpTitle);
}

// Initialize the program display
void render() {
    SetTitle("Tower of Hanoi Demonstration");
}

// Move console cursor to specified coordinates
void gotoxy(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

// Hide the console cursor
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}

// Draw a disk on the console
void drawHanoi(int &x, int &y, int n, int next) {
    // Clear original position
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

    // Move to new position
    if (next != -1) {
        x += next_go[next][0];
        y += next_go[next][1];
    }

    // Draw the disk
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

// Initialize the Tower of Hanoi state
void init() {
    // Initialize disks on pillar A
    abc_pillar[0][0] = N;
    for (int i = 1; i <= N; i++) {
        abc_pillar[0][i] = N + 1 - i;
    }

    // Calculate console dimensions
    mapHeight = 2 + N + 1;
    mapWidth = 2 + 3 * (N * 2 + 1) + 2;

    // Calculate X-coordinates for pillars
    abc_x[0] = 1 + N;
    abc_x[1] = abc_x[0] + 2 * N + 2;
    abc_x[2] = abc_x[1] + 2 * N + 2;

    // Draw initial state
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            // Draw walls
            if (i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1) {
                gotoxy(j, i);
                printf("%c", wall);
            }
            // Draw pillars and disks
            else if (i > 1 && i < mapHeight - 1) {
                if (j == abc_x[0] || j == abc_x[1] || j == abc_x[2]) {
                    int pillarIndex = 0;
                    if (j == abc_x[0]) pillarIndex = 0;
                    else if (j == abc_x[1]) pillarIndex = 1;
                    else if (j == abc_x[2]) pillarIndex = 2;
                    drawHanoi(j, i, abc_pillar[pillarIndex][N - i + 2], -1);
                }
            }
        }
    }
}

// Move a disk from one pillar to another
void move(char from, char to) {
    gotoxy(0, mapHeight + 1);
    printf("%c --> %c\n", from, to);

    // Get current height of the source pillar
    int fromHeight = abc_pillar[from - 'A'][0];
    int n = abc_pillar[from - 'A'][fromHeight];
    int x = abc_x[from - 'A'];
    int y = 2 + N - fromHeight;
    abc_pillar[from - 'A'][0]--;

    // Get target height
    abc_pillar[to - 'A'][0]++;
    int toHeight = abc_pillar[to - 'A'][0];
    abc_pillar[to - 'A'][toHeight] = n;
    int toX = abc_x[to - 'A'];
    int toY = 2 + N - toHeight;

    // Lift the disk up
    while (y > 1) {
        drawHanoi(x, y, n, up);
        Sleep(100);
    }

    // Move horizontally to target pillar
    if (x < toX)
        while (x < toX)
            drawHanoi(x, y, n, right), Sleep(100);
    else if (x > toX)
        while (x > toX)
            drawHanoi(x, y, n, left), Sleep(100);

    // Lower the disk onto target pillar
    while (y < toY) {
        drawHanoi(x, y, n, down);
        Sleep(200);
    }

    // Manual control mode
    if (autoPlay == 0) {
        gotoxy(0, mapHeight + 2);
        printf("Press any key to continue...");
        getchar();
    }
}

// Recursive solution to the Tower of Hanoi problem
int moveCount;
void hanoi(int n, char from, char temp, char to) {
    if (n == 1) {
        move(from, to);
        moveCount++;
    } else {
        hanoi(n - 1, from, to, temp);
        move(from, to);
        moveCount++;
        hanoi(n - 1, temp, from, to);
    }
}

int main() {
    render();
    printf("Number of disks: ");
    scanf("%d", &N);
    printf("1. Automatic Play 0. Manual Play\n");
    
    while (1) {
        scanf("%d", &autoPlay);
        if (autoPlay == 1 || autoPlay == 0) {
            break;
        } else {
            printf("Invalid input. Please enter 1 or 0.\n");
        }
    }
    
    system("CLS");
    getchar(); // Consume the newline character
    HideCursor();
    init();
    printf("\n");
    Sleep(1700);
    
    moveCount = 0;
    hanoi(N, 'A', 'B', 'C');
    
    gotoxy(0, mapHeight + 2);
    printf("Minimum moves required: %d\n", moveCount);
    system("pause");

    getchar();
    getchar();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Windows equivalent for termios
#include <windows.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 60

// W->UP
// A->LEFT
// S->DOWN
// D->RIGHT
enum Direction { UP, DOWN, LEFT, RIGHT, STOP };
enum Direction dir;
int score;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_length;
int tail_x[100], tail_y[100];

void setup();
void clear_screen();
void draw();
void input();
void game_play();

void sleep_ms(int milliseconds) {
    Sleep(milliseconds);  // Windows-compatible sleep function
}

int main() {
    srand(time(NULL));
    setup();
    while (1) {
        draw();
        input();
        game_play();
        int sleep_time = 3000 / (score != 0 ? score : 10);
        sleep_ms(sleep_time);
    }
}

void input() {
    if (_kbhit()) {  // Check if a key is pressed
        char ch = _getch();  // Get the pressed key
        switch (ch) {
            case 'a': dir = LEFT; break;
            case 's': dir = DOWN; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 'x': exit(0);
        }
    }
}

void game_play() {
    for (int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    switch (dir) {
        case UP: head_y--; break;
        case DOWN: head_y++; break;
        case LEFT: head_x--; break;
        case RIGHT: head_x++; break;
        case STOP: break;
    }

    if (head_x < 0) head_x = WIDTH - 1;
    else if (head_x >= WIDTH) head_x = 0;

    if (head_y < 0) head_y = HEIGHT - 1;
    else if (head_y >= HEIGHT) head_y = 0;

    for (int i = 0; i < tail_length; i++) {
        if (tail_x[i] == head_x && tail_y[i] == head_y) {
            printf("\nYou have hit your tail. GAME OVER !!!\n");
            exit(0);
        }
    }

    if (head_x == fruit_x && head_y == fruit_y) {
        score += 10;
        tail_length++;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    }
}

void setup() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
    score = 0;
    tail_length = 0;
}

void draw() {
    clear_screen();
    printf("\t\tWelcome to The Snake Game!!!\n");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");

    for (int i = 0; i < HEIGHT; i++) {
        printf("\n#");
        for (int j = 0; j < WIDTH; j++) {
            if (i == head_y && j == head_x) {
                printf("O");
            } else if (i == fruit_y && j == fruit_x) {
                printf("F");
            } else {
                int tail_found = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found) printf(" ");
            }
        }
        printf("#");
    }

    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

void clear_screen() {
    system("cls");  // Windows clear screen command
}

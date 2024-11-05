#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int width = 20, height = 20, gameover, score;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];  // Arrays to hold snake body segments
int nTail = 0;               // Initial length of the snake tail

void setup() {
    gameover = 0;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
    nTail = 0;  // Reset snake length when game starts
}

void draw() {
    system("clear"); // Clear the screen

    // Print top wall
    for (int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    // Print left wall, snake, food, and right wall
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printf("#"); // Left wall

            if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruity && j == fruitx)
                printf("*"); // Food
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Snake body segment
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == width - 1)
                printf("#"); // Right wall
        }
        printf("\n");
    }

    // Print bottom wall
    for (int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void input() {
    system("/bin/stty raw");  // Set terminal to raw mode
    char c = getchar();
    system("/bin/stty cooked"); // Set terminal back to normal mode

    switch (c) {
        case 'a':
            flag = 1; // Left
            break;
        case 'd':
            flag = 2; // Right
            break;
        case 'w':
            flag = 3; // Up
            break;
        case 's':
            flag = 4; // Down
            break;
        case 'x':
            gameover = 1; // Exit
            break;
    }
}

void logic() {
    // Move tail positions forward
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Update snake head position based on direction
    switch (flag) {
        case 1:
            x--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y--;
            break;
        case 4:
            y++;
            break;
    }

    // Check for wall collisions
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameover = 1;

    // Check for collisions with tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    // Check if snake eats the food
    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;  // Increase the length of the snake
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        usleep(100000); // Delay to slow down the game
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}

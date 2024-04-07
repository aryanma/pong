#include <iostream>
#include "raylib/5.0/include/raylib.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 80;
const int BALL_SIZE = 10;
const int PADDLE_SPEED = 5;
const int BALL_SPEED = 4;

struct Paddle {
    Rectangle rect;
    int speed;

    Paddle(int x, int y) {
        rect.x = x;
        rect.y = y;
        rect.width = PADDLE_WIDTH;
        rect.height = PADDLE_HEIGHT;
        speed = PADDLE_SPEED;
    }

    void moveUp() {
        rect.y -= speed;
    }

    void moveDown() {
        rect.y += speed;
    }
};

struct Ball {
    Rectangle rect;
    Vector2 speed;

    Ball(int x, int y) {
        rect.x = x;
        rect.y = y;
        rect.width = BALL_SIZE;
        rect.height = BALL_SIZE;
        speed.x = BALL_SPEED;
        speed.y = BALL_SPEED;
    }

    void move() {
        rect.x += speed.x;
        rect.y += speed.y;
    }

    void changeDirectionX() {
        speed.x = -speed.x;
    }

    void changeDirectionY() {
        speed.y = -speed.y;
    }
};

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

    SetTargetFPS(60);

    Paddle leftPaddle(30, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2);
    Paddle rightPaddle(WINDOW_WIDTH - 30 - PADDLE_WIDTH, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2);
    Ball ball((WINDOW_WIDTH - BALL_SIZE) / 2, (WINDOW_HEIGHT - BALL_SIZE) / 2);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) {
            leftPaddle.moveUp();
        }
        if (IsKeyDown(KEY_S)) {
            leftPaddle.moveDown();
        }
        if (IsKeyDown(KEY_UP)) {
            rightPaddle.moveUp();
        }
        if (IsKeyDown(KEY_DOWN)) {
            rightPaddle.moveDown();
        }

        ball.move();

        if (CheckCollisionRecs(ball.rect, leftPaddle.rect) || CheckCollisionRecs(ball.rect, rightPaddle.rect)) {
            ball.changeDirectionX();
        }

        if (ball.rect.y <= 0 || ball.rect.y >= WINDOW_HEIGHT - BALL_SIZE) {
            ball.changeDirectionY();
        }

        if (ball.rect.x <= 0 || ball.rect.x >= WINDOW_WIDTH - BALL_SIZE) {
            // Reset ball position
            ball.rect.x = (WINDOW_WIDTH - BALL_SIZE) / 2;
            ball.rect.y = (WINDOW_HEIGHT - BALL_SIZE) / 2;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRec(leftPaddle.rect, WHITE);
        DrawRectangleRec(rightPaddle.rect, WHITE);
        DrawRectangleRec(ball.rect, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
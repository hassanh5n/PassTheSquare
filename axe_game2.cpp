#include <iostream>
#include "raylib.h"

using namespace std;

int main()
{
    int width = 800;
    int height = 450;
    InitWindow(width, height, "Hassan's Window");

    int circleX = width / 2;
    int circleY = height / 2;
    int radius = 25;

    // axe coordinates
    int axeX = 450;
    int axeY = 0;
    int length = 50;

    int direction = 10;

    bool collision = false;
    bool hasPassed = false;
    int score = 0;

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        // Update circle edges
        int leftcircleX = circleX - radius;
        int rightcircleX = circleX + radius;
        int upcircleY = circleY - radius;
        int downcircleY = circleY + radius;

        // Update axe edges
        int leftaxeX = axeX;
        int rightaxeX = axeX + length;
        int upaxeY = axeY;
        int downaxeY = axeY + length;

        // Collision detection
        collision = downaxeY >= upcircleY && upaxeY <= downcircleY && leftaxeX <= rightcircleX && rightaxeX >= leftcircleX;
        hasPassed = rightcircleX >= 450 && leftcircleX <= 500;

        BeginDrawing();
        ClearBackground(WHITE);

        if (collision)
        {
            DrawText("Game Over! Press X to Play Again", 200, 200, 20, RED);
            DrawText(TextFormat("\nFinal Score: %d", score), 200, 240, 20, RED);

            if (IsKeyDown(KEY_X))
            {
                // Reset positions
                circleX = width / 2;
                circleY = height / 2;
                axeX = 450;
                axeY = 0;
                score = 0;
                collision = false;
            }
        }
        else
        {
            DrawRectangle(450, 0, length, 450, WHITE);
            DrawCircle(circleX, circleY, radius, BLUE);
            DrawRectangle(axeX, axeY, length, length, RED);
            DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);


            // Update axe position
            axeY += direction;
            if (axeY > height || axeY < 0)
            {
                direction = -direction;
            }
            if(hasPassed){
                score++;
                hasPassed = false;
            }


            // Move circle
            if ((IsKeyDown(KEY_D)||IsKeyDown(KEY_RIGHT)) && circleX < width - radius)
            {
                circleX += 10;
            }
            if ((IsKeyDown(KEY_A)||IsKeyDown(KEY_LEFT)) && circleX > radius)
            {
                circleX -= 10;
            }
            if ((IsKeyDown(KEY_W)||IsKeyDown(KEY_UP)) && circleY > radius)
            {
                circleY -= 10;
            }
            if ((IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN)) && circleY < height - radius)
            {
                circleY += 10;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

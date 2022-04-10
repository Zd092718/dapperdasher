#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{500};
    const int windowHeight{500};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // accelaration due to gravity (pixels/frame)/frame
    const int gravity{1};
    const int jumpVel{-22};

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};
    bool isInAir{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // logic begins here
        // ground check
        if (posY >= windowHeight - height)
        {
            // rectangle is on ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in air
            isInAir = true;
            // apply gravity
            velocity += gravity;
        }
        // check for jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        // update y postion
        posY += velocity;
        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}

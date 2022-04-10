#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{500};
    const int windowHeight{500};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // logic begins here
        if (IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }
        posY += velocity;
        DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}

#include "raylib.h"

int main()
{

    InitWindow(500, 500, "Dapper Dasher");
    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}

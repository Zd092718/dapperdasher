#include "raylib.h"

int main()
{
    // window dimensions
    const int windowWidth{500};
    const int windowHeight{500};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // accelaration due to gravity (pixels/s)/s
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // pixels per second
    const int jumpVel{-600};
    int velocity{0};

    // is scarfy in air?

    bool isInAir{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dt{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);
        // logic begins here
        // ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
            velocity += gravity * dt;
        }
        // check for jumping
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        // update y postion
        scarfyPos.y += velocity * dt;
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}

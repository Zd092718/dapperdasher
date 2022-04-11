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

    // scarfy model
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;

    // nebula model
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula x velocity (pixels/second)
    int nebVel{-400};

    // nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0 / 12.0};
    float nebRunningTime{};

    // scarfy position
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // jump pixels per second
    const int jumpVel{-600};
    int velocity{0};

    // scarfy animation variables
    int frame{};
    const float updateTime{1.0 / 12.0};
    float runningTime{};

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
        // update nebula position
        nebPos.x += nebVel * dt;

        // update scarfy postion
        scarfyPos.y += velocity * dt;

        // update scarfy's animation frame
        if (!isInAir)
        {
            // update running time
            runningTime += dt;
            if (runningTime >= updateTime)
            {
                // update animation frame
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update nebula running time
        nebRunningTime += dt;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

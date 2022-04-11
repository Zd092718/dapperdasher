#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

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

    // scarfy variables
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // is scarfy in air?
    bool isInAir{};

    // jump pixels per second
    const int jumpVel{-600};
    int velocity{0};

    // Rectangle scarfyRec;
    // scarfyRec.x = 0;
    // scarfyRec.y = 0;
    // scarfyRec.width = scarfy.width / 6;
    // scarfyRec.height = scarfy.height;

    // // scarfy position
    // Vector2 scarfyPos;
    // scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    // scarfyPos.y = windowHeight - scarfyRec.height;

    // // scarfy animation variables
    // int frame{};
    // const float updateTime{1.0 / 12.0};
    // float runningTime{};

    // nebula model
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f}, // rectangle rec
        {windowWidth, windowHeight - nebula.height / 8.0f},    // Vector2 pos
        0,                                                     // int frame
        1.0 / 12.0,                                            // float updateTime
        0};                                                    // float runningTime

    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f},    // rectangle rec
        {windowWidth + 300, windowHeight - nebula.height / 8.0f}, // Vector2 pos
        0,                                                        // int frame
        1.0 / 12.0,                                               // float updateTime
        0};                                                       // float runningTime

    // Rectangle nebRec{0.0, 0.0, nebula.width / 8.0f, nebula.height / 8.0f};
    // Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // nebula x velocity (pixels/second)
    int nebVel{-400};

    // // nebula animation variables
    // int nebFrame{};
    // const float nebUpdateTime{1.0 / 12.0};
    // float nebRunningTime{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dt{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);
        // logic begins here
        // ground check
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
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
        nebData.pos.x += nebVel * dt;
        // update nebula 2 position
        neb2Data.pos.x += nebVel * dt;

        // update scarfy postion
        scarfyData.pos.y += velocity * dt;

        // update scarfy's animation frame
        if (!isInAir)
        {
            // update running time
            scarfyData.runningTime += dt;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                // update animation frame
                scarfyData.runningTime = 0.0;
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        // update nebula running time
        nebData.runningTime += dt;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }

        // update nebula 2 running time
        neb2Data.runningTime += dt;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        // draw nebula 2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

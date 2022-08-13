#include "raylib.h"

int main()
{
    //window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // acceleration due to gravity (pixels/second)/second
    const int gravity{1'000};

    // nebula variables

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //animation frame
    int frame{};
    //amount of time before animation update
    const float updateTime = 1.0 / 12.0;
    float runningTime{};

    // is the rectanlge in the air?
    bool isInAir{};
    // jump velocity
    const int jumpVel{-600};// (pixels per second) / second

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT = GetFrameTime();

        // perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            velocity += gravity * dT;
            isInAir = true;
        }

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update the position
        scarfyPos.y += velocity * dT;


        
        runningTime += dT;
        // update the animation frame
        if(runningTime >= updateTime)
        {
            runningTime = 0;
            // update the animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame > 5)
            {
                frame = 0;
            }
        }
 

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}
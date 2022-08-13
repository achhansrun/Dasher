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
    //window dimensions
    const int windowDimensions[2] {512, 380};
    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher!");

    // acceleration due to gravity (pixels/second)/second
    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData
    {
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Nebrec data
        {windowDimensions[0], windowDimensions[1] - nebula.height / 8}, // vector2 pos
        0, //int frame
        1.0/12.0, //float updateTime
        0.0 // float runningtime
    };

    // nebula 2 variables 
    Texture2D nebula2 = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula 2
    AnimData neb2Data
    {
        {0.0, 0.0, (double) nebula.width/8.0, (double) nebula.height/8},
        {windowDimensions[0] + 300, windowDimensions[1] - nebula.height/8},
        0,
        1.0/16,
        0
    };

    AnimData nebulae[2] {nebData, neb2Data};

    // nebula x velocity (pixels/second)
    int nebVel{-200};
 
    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0;

    // is the rectanlge in the air?
    bool isInAir{};
    // jump velocity
    const int jumpVel{-600};// (pixels per second) / second

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        const float dT = GetFrameTime();

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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

        // update nebula position
        nebulae[0].pos.x += nebVel * dT;

        // update nebula 2 position
        nebulae[1].pos.x += nebVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;
        
        //update scarfy animation
        if(!isInAir)
        {
            // update running time
            scarfyData.runningTime += dT;
            // update the animation frame
            if(scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0;
                // update the animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        // update nebula animation
        nebulae[0].runningTime += dT;
        if(nebulae[0].runningTime >= nebulae[0].updateTime)
        {   
            // update nebula animation frame
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        // update nebula 2 animation
        nebulae[1].runningTime += dT;
        if(nebulae[1].runningTime >= nebulae[1].updateTime)
        {   
            // update nebula animation frame
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }
 
        // draw nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        
        // draw nebula 2
        DrawTextureRec(nebula2, nebulae[1].rec, nebulae[1].pos, WHITE);

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
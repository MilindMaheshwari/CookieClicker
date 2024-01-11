#include <iostream>
#include <raylib.h>

using namespace std;









int main()
{   
    int shopBoxWidth = 125;
    int shopBoxHeight = 320;
    int dispBoxWidth = 925;
    int dispBoxHeight = 128;
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    

    Texture2D texture = LoadTexture("X:/My Drive/Smithmas 2/Unit Project/CookieClicker/AssetLibrary/Shane1.png");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(590, 161, dispBoxWidth, dispBoxHeight, RED);
        int shaneVar = 5;
        for (int i = 0; i < 20; i++)
        {
            shaneVar *=-1;
            DrawTexture(texture, 590 + i*40, 175 + shaneVar, WHITE);
        }
        // Draw the texture at the center of the screen
       



        

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(texture);
    return 0;
}

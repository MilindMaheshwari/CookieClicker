#include <iostream>
#include <unistd.h>
#include <raylib.h>
#include <thread> 
#include <vector>
#include "CookieGeneratorClass.hpp"

using namespace std;

int main()
{   
    int shopBoxWidth = 125;
    int shopBoxHeight = 320;
    int dispBoxWidth = 925;
    int dispBoxHeight = 128;
    const int screenWidth = 1920;
    const int screenHeight = 1080;



    long long money;


    Generator cursor("Cursor", 0.2, 10);
    Generator shane("Shane", 3, 100);

    vector<Generator> generators{cursor, shane};
    
    thread moneyGenerationThr([&]()     //Money and generators can be accesed by reference
    {
        while(WindowShouldClose() == false){

            for(Generator generator : generators){ 

                money += generator.getTotalCPS();   

            }
            cout << money;
            sleep(1000); //After it has increased money from all generators, pause for one second
        }
    }); //For generating money while other stuff is happening




    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    

    // Texture2D texture = LoadTexture("X:/My Drive/Smithmas 2/Unit Project/CookieClicker/AssetLibrary/Shane1.png");
    Texture2D texture = LoadTexture("AssetLibrary\\Shane1.png");


    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(590, 161, dispBoxWidth, dispBoxHeight, RED);
        int shaneVar = 5;
        for (int i = 0; i < 22; i++)
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

#include <iostream>
#include <unistd.h>
#include <raylib.h>
#include <thread> 
#include <vector>
#include "CookieGeneratorClass.hpp"

using namespace std;

int main()
{   
    int shopBoxWidth = 300;
    int shopBoxHeight = 128;
    int dispBoxWidth = 925;
    int dispBoxHeight = 128;
    const int screenWidth = 1920;
    const int screenHeight = 1080;



    long long money = 0;


    Generator cursor("Cursor", 0.2, 10);
    Generator shane("Shane", 3, 100);

    vector<Generator> generators{cursor, shane};
    





    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);



    thread moneyGenerationThr([&]()     //Money and generators can be accesed by reference
    {
        while(WindowShouldClose() == false){

            for(Generator generator : generators){ 

                money += generator.getTotalCPS();   

            }
            cout << money << endl;
            sleep(1); //After it has increased money from all generators, pause for one second
        }
    }); //For generating money while other stuff is happening




    cout << "Hello World" << endl;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    

    Texture2D texture = LoadTexture("AssetLibrary/Shane1.png");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw Display Boxes
        DrawRectangle(590, 161, dispBoxWidth, dispBoxHeight, RED);
        DrawRectangle(590, 161 + dispBoxHeight, dispBoxWidth, dispBoxHeight, BLUE);
        DrawRectangle(590, 161 + dispBoxHeight*2, dispBoxWidth, dispBoxHeight, YELLOW);
        DrawRectangle(590, 161 + dispBoxHeight*3, dispBoxWidth, dispBoxHeight, RED);
        DrawRectangle(590, 161 + dispBoxHeight*4, dispBoxWidth, dispBoxHeight, BLUE);

        //Draw Shop Boxes
        DrawRectangle(1545, 161, shopBoxWidth, shopBoxHeight, MAROON);
        DrawRectangle(1545, 161 + dispBoxHeight, shopBoxWidth, shopBoxHeight, DARKBLUE);
        DrawRectangle(1545, 161 + dispBoxHeight*2, shopBoxWidth, shopBoxHeight, GOLD);
        DrawRectangle(1545, 161 + dispBoxHeight*3, shopBoxWidth, shopBoxHeight, MAROON);
        DrawRectangle(1545, 161 + dispBoxHeight*4, shopBoxWidth, shopBoxHeight, DARKBLUE);

        int shaneVar = 5;
        for (int i = 0; i < 22; i++)
        {
            shaneVar *=-1;
            if (i < shane.getCounter())
            DrawTexture(texture, 590 + i*40, 175 + shaneVar, WHITE);
        }
        // Draw the texture at the center of the screen
       



        

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(texture);
    return 0;
}

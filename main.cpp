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
    

    Texture2D imageShane = LoadTexture("X:/My Drive/Smithmas 2/Unit Project/CookieClicker/AssetLibrary/Shane1.png");
    Texture2D imageOak = LoadTexture("AssetLibrary/oakridge.png");
    
    Rectangle clickBox = {10, GetScreenHeight()/2.0f - 50, 200, 100};
    Rectangle oakCollisionBox = {168, 329, static_cast<float>(imageOak.width), static_cast<float>(imageOak.height)};

    bool collision = false;

    while (WindowShouldClose() == false)
    {
        
        collision = CheckCollisionPointRec(GetMousePosition(), clickBox);






        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw Counters
        DrawText(to_string(money).c_str(), 150, 150, 40, BLUE);

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
        for (int i = 0; i < shane.getCounter(); i++)
        {
            shaneVar *=-1;
            
            DrawTexture(imageShane, 590 + i*40, 175 + shaneVar, WHITE);
        }   
        // Draw the texture at the center of the screen
        DrawTexture(imageOak, oakCollisionBox.x, oakCollisionBox.y, WHITE);
        

        
        if (CheckCollisionPointRec(GetMousePosition(), oakCollisionBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Handle collision behavior here (e.g., increase money, perform some action, etc.)
            money++; // Adjust this according to your requirements
        }



        

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(imageShane);
    UnloadTexture(imageOak);
    return 0;
}

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

    double money = 0;   //Should print with 2 decimals, like money usually is
    double totalCPS = 0;

    //COULD FIND OTHER SOLUTION FOR THIS

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    Rectangle cursorDispBox = {590, 161, dispBoxWidth, dispBoxHeight};
    Rectangle shaneDispBox = {590, 161 + dispBoxHeight, dispBoxWidth, dispBoxHeight};
    Rectangle thirdDispBox = {590, 161 + dispBoxHeight*2, dispBoxWidth, dispBoxHeight};
    Rectangle fourthDispBox = {590, 161 + dispBoxHeight*3, dispBoxWidth, dispBoxHeight};
    Rectangle fifthDispBox = {590, 161 + dispBoxHeight*4, dispBoxWidth, dispBoxHeight};

    Rectangle cursorBuyBox = {1545, 161, shopBoxWidth, shopBoxHeight};
    Rectangle shaneBuyBox = {1545, 161 + dispBoxHeight, shopBoxWidth, shopBoxHeight};
    Rectangle thirdBuyBox = {1545, 161 + dispBoxHeight*2, shopBoxWidth, shopBoxHeight};
    Rectangle fourthBuyBox = {1545, 161 + dispBoxHeight*3, shopBoxWidth, shopBoxHeight};
    Rectangle fifthBuyBox = {1545, 161 + dispBoxHeight*4, shopBoxWidth, shopBoxHeight};

    Generator cursor("Cursor", 0.2, 10, cursorDispBox, cursorBuyBox, BLUE, DARKBLUE);
    Generator shane("Shane", 3, 100, shaneDispBox, shaneBuyBox, RED, MAROON);    
    
    

    vector<Generator*> generators{&cursor, &shane}; //Has to be pointer so that changes to shane/cursor actually affect the vector

    thread moneyGenerationThr([&]()     //Money and generators can be accesed by reference
    {
        while(WindowShouldClose() == false){

            for(Generator* generator : generators){ 
                
                money += generator->getGeneratorTotalCPS();   

            }

            sleep(1); //After it has increased money from all generators, pause for one second
        }
    }); //For generating money while other stuff is happening




    cout << "Hello World" << endl;
    

    Texture2D imageShane = LoadTexture("AssetLibrary/Shane1.png");
    Texture2D imageOak = LoadTexture("AssetLibrary/oakridge.png");
    Texture2D imageCursor = LoadTexture("AssetLibrary/cursor.png");
    
    Rectangle clickBox = {10, GetScreenHeight()/2.0f - 50, 200, 100};
    Rectangle oakCollisionBox = {168, 329, static_cast<float>(imageOak.width), static_cast<float>(imageOak.height)};


    bool collision = false;
     
    Texture2D texture = LoadTexture("AssetLibrary/Shane1.png");

    double tempMoney = 8000;

    shane.buyNew(tempMoney);
    shane.buyNew(tempMoney);
    shane.buyNew(tempMoney); 

    while (WindowShouldClose() == false)
    {
        
        collision = CheckCollisionPointRec(GetMousePosition(), clickBox);


        totalCPS = 0;
        for(Generator* generator : generators){ 
            
            totalCPS += generator->getGeneratorTotalCPS();
        }

        DrawText(TextFormat("%.2f", totalCPS), 30, 30, 22, GREEN);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw Counters
        DrawText(TextFormat("%.2f", money), 150, 150, 40, BLUE);

        //Draw Display Boxes

        shane.displayBoxes(money);
        cursor.displayBoxes(money);

        //Draw Shop Boxes
       

        DrawText(TextFormat("%.2f", money), 50, 50, 34, RED);

        int shaneVar = 5;

        int dispVar = 5;
        for (int i = 0; i < cursor.getCounter(); i++)
        {
                dispVar *=-1;
                if (i < 23)
                {
                    DrawTexture(imageCursor, 590 + i*40, 175 + dispVar, WHITE);
                }
                else if (i < 46)
                {
                    DrawTexture(imageCursor, 590 + i*40 - 23*40, 205 + dispVar*-1, WHITE);
                }
        }   
        for (int j = 0; j < shane.getCounter(); j++)
        {
            dispVar *=-1;
            if (j < 22)
            {
                DrawTexture(imageShane, 590 + j*40, 175 + dispBoxHeight + dispVar, WHITE);
            }
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

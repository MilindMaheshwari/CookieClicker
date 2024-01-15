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

    unsigned long long money = 0;

    //COULD FIND OTHER SOLUTION FOR THIS

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    Rectangle shaneDispBox = {590, 161, dispBoxWidth, dispBoxHeight};
    Rectangle blueDispBox = {590, 161 + dispBoxHeight, dispBoxWidth, dispBoxHeight};
    Rectangle thirdDispBox = {590, 161 + dispBoxHeight*2, dispBoxWidth, dispBoxHeight};
    Rectangle fourthDispBox = {590, 161 + dispBoxHeight*3, dispBoxWidth, dispBoxHeight};
    Rectangle fifthDispBox = {590, 161 + dispBoxHeight*4, dispBoxWidth, dispBoxHeight};

    Rectangle shaneBuyBox = {1545, 161, shopBoxWidth, shopBoxHeight};
    Rectangle secondBuyBox = {1545, 161 + dispBoxHeight, shopBoxWidth, shopBoxHeight};
    Rectangle thirdBuyBox = {1545, 161 + dispBoxHeight*2, shopBoxWidth, shopBoxHeight};
    Rectangle fourthBuyBox = {1545, 161 + dispBoxHeight*3, shopBoxWidth, shopBoxHeight};
    Rectangle fifthBuyBox = {1545, 161 + dispBoxHeight*4, shopBoxWidth, shopBoxHeight};

    Generator cursor("Cursor", 0.2, 10, blueDispBox, secondBuyBox, BLUE, DARKBLUE);
    Generator shane("Shane", 3, 100, shaneDispBox, shaneBuyBox, RED, MAROON);    
    
    

    vector<Generator*> generators{&cursor, &shane}; //Has to be pointer so that changes to shane/cursor actually affect the vector

    thread moneyGenerationThr([&]()     //Money and generators can be accesed by reference
    {
        while(WindowShouldClose() == false){

            for(Generator* generator : generators){ 
                
                money += generator->getTotalCPS();   

            }
            cout << money << endl;

            sleep(1); //After it has increased money from all generators, pause for one second
        }
    }); //For generating money while other stuff is happening


    Texture2D texture = LoadTexture("AssetLibrary/Shane1.png");

    unsigned long long tempMoney = 8000;

    shane.buyNew(tempMoney);
    shane.buyNew(tempMoney);
    shane.buyNew(tempMoney); 

    while (WindowShouldClose() == false)
    {
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Draw Display Boxes

        shane.displayBoxes(money);
        cursor.displayBoxes(money);

        //Draw Shop Boxes
       

        DrawText(to_string(money).c_str(), 50, 50, 34, RED);

        int shaneVar = 5;
        // for (int i = 0; i < 22; i++)
        // {
        //     shaneVar *=-1;
        //     if (i < shane.getCounter())
        //     DrawTexture(texture, 590 + i*40, 175 + shaneVar, WHITE);
        // }
        // Draw the texture at the center of the screen
       
        for (int i = 0; i < shane.getCounter(); i++)
        {
            if(i < 22){
                shaneVar *=-1;
                DrawTexture(texture, 590 + i*40, 175 + shaneVar, WHITE);
            }

        }

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(texture);
    return 0;
}

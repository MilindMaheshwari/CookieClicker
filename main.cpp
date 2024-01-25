#include <iostream>
#include <unistd.h>
#include <raylib.h>
#include <thread> 
#include <vector>
#include "CookieGeneratorClass.hpp"
#include "AchievementClass.hpp"
#include <random>

using namespace std;

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(gen);
}

int main()
{   
    float shopBoxWidth = 300;
    float shopBoxHeight = 128;
    float dispBoxWidth = 925;
    float dispBoxHeight = 128;
    const float screenWidth = 1920;
    const float screenHeight = 1080;
    //Should print with 2 decimals, like money usually is
    double totalCPS = 0;
    double CPC = 1;
    double money = 00000000;
    Music music;
    //COULD FIND OTHER SOLUTION FOR THIS
    InitAudioDevice();
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    int randNum = generateRandomNumber(1, 3);
    if (randNum == 1)
    {
        music = LoadMusicStream("AssetLibrary/Chorus.wav");
    }
    else if (randNum == 2)
    {
        music = LoadMusicStream("AssetLibrary/Drake-Fair-Trade.wav");
    }
    else if(randNum == 3)
    {
        music = LoadMusicStream("AssetLibrary/Brass-Monkey.wav");
    }

    PlayMusicStream(music);
    
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

    Generator cursor("Cursor", 1, 10, cursorDispBox, cursorBuyBox, BLUE, DARKBLUE);
    Generator shane("Shane", 2, 100, shaneDispBox, shaneBuyBox, RED, MAROON);    
    Generator sweater("Offbrand Merch", 20, 500, thirdDispBox, thirdBuyBox, YELLOW, GOLD);
    Generator sign("Sign", 47, 1000, fourthDispBox, fourthBuyBox, BLUE, DARKBLUE);
    Generator vape("Sign", 260, 2000, fifthDispBox, fifthBuyBox, RED, MAROON);


    Texture2D imageShane = LoadTexture("AssetLibrary/Shane1.png");
    Texture2D imageOak = LoadTexture("AssetLibrary/oakridge.png");
    Texture2D imageOakClicked = LoadTexture("AssetLibrary/oakridge-clicked.png");
    Texture2D imageCursor = LoadTexture("AssetLibrary/cursor.png");
    Texture2D imageSweater = LoadTexture("AssetLibrary/sweater.png");
    Texture2D imageSign = LoadTexture("AssetLibrary/Sign.png");
    Texture2D imageVape = LoadTexture("AssetLibrary/vape.png");
    Texture2D background = LoadTexture("AssetLibrary/background.png");


    Rectangle oakCollisionBox = {168, 329, imageOak.width, imageOak.height};

    Achievement bronzeCursor("Bronze Cursor", "Bought 10 cursors", [&](){CPC*=2;});
    Achievement silverCursor("Silver Cursor", "Bought 25 cursors", [&](){CPC*=2;});
    Achievement goldCursor("Gold Cursor", "Bought 100 cursors", [&](){CPC*=2;});


    

    vector<Generator*> generators{&cursor, &shane, &sweater, &sign, &vape}; //Has to be pointer so that changes to shane/cursor actually affect the vector

    thread moneyGenerationThr([&]()     //Money and generators can be accesed by reference
    {
        while(WindowShouldClose() == false){

            for(Generator* generator : generators){ 
                
                money += generator->getGeneratorTotalCPS();   

            }

            sleep(1); //After it has increased money from all generators, pause for one second
        }
    }); //For generating money while other stuff is happening
    
    double clickStartTime = 0;
    bool timerIsStarted = false;

    int tempMouseX;
    int tempMouseY;

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(music);


        totalCPS = 0;
        for(Generator* generator : generators){ 
            
            totalCPS += generator->getGeneratorTotalCPS();
        }

        DrawText(TextFormat("%.2f", totalCPS), 30, 30, 22, GREEN);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

        //Draw Counters

        //Draw Display and shop Boxes (also polls whether a shop box has been clicked or not)
        


        shane.displayBoxes(money);
        cursor.displayBoxes(money);
        sweater.displayBoxes(money);
        sign.displayBoxes(money);
        vape.displayBoxes(money);
        DrawTexture(imageCursor, 1775, 161, WHITE);
        DrawTexture(imageShane, 1775, 289, WHITE);
        DrawTexture(imageSweater, 1775, 417, WHITE);
        DrawTexture(imageSign, 1775, 545, WHITE);
        DrawTexture(imageVape, 1775, 673, WHITE);
        


        DrawText(TextFormat("$ %.2f", money), 50, 50, 34, RED);
        DrawText(TextFormat("%.2f CPS", totalCPS), 600, 50, 34, BLUE);

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
                    DrawTexture(imageCursor, 590 + i*40 - 23*40, 255 + dispVar*-1, WHITE);
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
        for (int k = 0; k < sweater.getCounter(); k++)
        {
            dispVar *=-1;
            if (k < 22)
            {
                DrawTexture(imageSweater, 590 + k*40, 175 + dispBoxHeight*2 + dispVar, WHITE);
            }
        }
        for (int l = 0; l < sign.getCounter(); l++)
        {
            dispVar *=-1;
            if (l < 22)
            {
                DrawTexture(imageSign, 590 + l*40, 175 + dispBoxHeight*3 + dispVar, WHITE);
            }
        }
        for (int m = 0; m < vape.getCounter(); m++)
        {
            dispVar *=-1;
            if (m < 21)
            {
                DrawTexture(imageVape, 590 + m*40, 175 + dispBoxHeight*4 + dispVar, WHITE);
            }
        }
        
        // Draw the texture at the center of the screen
        if (CheckCollisionPointRec(GetMousePosition(), oakCollisionBox) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawTexture(imageOakClicked, oakCollisionBox.x + 39 , oakCollisionBox.y + 35, WHITE);
        }
        else
        {
            DrawTexture(imageOak, oakCollisionBox.x , oakCollisionBox.y, WHITE);
        }
        if (CheckCollisionPointRec(GetMousePosition(), oakCollisionBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            
            
            // Handle collision behavior here (e.g., increase money, perform some action, etc.)
            money+=CPC; // Adjust this according to your requirements
            clickStartTime = GetTime();
            timerIsStarted = true;
            tempMouseX = GetMouseX();
            tempMouseY = GetMouseY();
            
        }
        if (timerIsStarted && GetTime() - clickStartTime < 2)
        {   
            DrawText(TextFormat("+ %.2f", CPC), tempMouseX, tempMouseY - (GetTime() - clickStartTime) * 100, 25, BLACK);
        }
        

        bronzeCursor.checkIfAchieved(cursor.getCounter() >= 10, imageCursor, BROWN);
        silverCursor.checkIfAchieved(cursor.getCounter() >= 25, imageCursor, GRAY);
        goldCursor.checkIfAchieved(cursor.getCounter() >= 100, imageCursor, GOLD);




        DrawText(TextFormat("X: %d, Y: %d", GetMouseX(), GetMouseY()), 500, 500 , 18, BROWN);

        EndDrawing();
        
    }

    CloseWindow();
    UnloadTexture(imageShane);
    UnloadTexture(imageOak);
    UnloadTexture(imageSweater);
    UnloadTexture(imageSign);
    UnloadTexture(imageVape);
    UnloadTexture(background);
    UnloadTexture(imageOakClicked);
    UnloadMusicStream(music);
    return 0;
}

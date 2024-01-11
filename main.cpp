#include <iostream>
#include <unistd.h>
#include <raylib.h>
#include <thread> 
#include <vector>
#include "CookieGeneratorClass.hpp"

using namespace std;


void moneyGeneratingLoop(){



}

vector<Generator> generators; //DONT USE GLOBAL VARIABLES

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

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





    while (WindowShouldClose() == false)
    {
        


        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int shaneVar = 5;



        // Draw the texture at the center of the screen
       



        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}



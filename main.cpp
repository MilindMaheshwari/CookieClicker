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
    SetTargetFPS(60);

    while (WindowShouldClose() == false){

        

    
    }

    CloseWindow();
    return 0;
}



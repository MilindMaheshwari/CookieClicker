#include <iostream>
#include <string>
#include <raylib.h>

#pragma once

using namespace std;

class Generator{

    private: 
        string name;        
        float CPS;  //Cookies/Clicks per second
        float price;
        int counter;
        Rectangle buyBox;


    public:

        /// @brief 
        /// @param name 
        /// @param startingCPS 
        /// @param startingPrice 

        Generator(string name, float startingCPS, float startingPrice){     

            this->name = name;
            CPS = startingCPS;
            price = startingPrice;
            counter = 0;

        }

        void buyNew(){

            counter++;
            price *= 1.1;
        }


        int getTotalCPS(){  //How many CPS this type of generator is generating in total
            return CPS * counter;
        }

        int getUnitCPS(){   //How much just one unit produces
            return CPS;
        }

        int getCounter(){        
            return counter;
        }

        int getPrice(){
            return price;
        }

        void setBuyBox(Rectangle rec){
            buyBox = rec;
        }

        bool getClicked(){
            
            bool clicked = CheckCollisionPointRec(GetMousePosition(), buyBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
            if(clicked)  buyNew();
            return (CheckCollisionPointRec(GetMousePosition(), buyBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
        }
};

// class Cursor : Generator{

//     private:
//         static int counter;
//         static float price;
//         static float CPS;

//     public: 

//         Cursor(string name)



// };
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
        Rectangle dispBox;
        Rectangle buyBox;
        Color canBuyColor;
        Color noBuyColor;



    public:

        /// @brief 
        /// @param name 
        /// @param startingCPS 
        /// @param startingPrice 
        /// @param canBuyColor //Brighter color that is the background of displaybox, and is the color of buyBox when user can afford to buy the generator
        /// @param noBuyColor  //Duller color that is the color of buyBox when user can't afford generator

        Generator(string name, float startingCPS, float startingPrice, Rectangle dispBox, Rectangle buyBox, Color canBuyColor, Color noBuyColor){     

            this->name = name;
            CPS = startingCPS;
            price = startingPrice;
            this->dispBox = dispBox;
            this->buyBox = buyBox;
            this->canBuyColor = canBuyColor;
            this->noBuyColor = noBuyColor;
            
            counter = 0;

        }

        void buyNew(unsigned long long &money){

            counter++;  
            money -= price;
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

        bool getClicked(unsigned long long &money){
            
            bool clicked = CheckCollisionPointRec(GetMousePosition(), buyBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
            if(clicked)  buyNew(money);
            return (CheckCollisionPointRec(GetMousePosition(), buyBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
        }

        bool getAffordable(unsigned long long money){

            return (money >=  price);   //Returns true if the user has enough money to buy the product
        }

        void displayBoxes(unsigned long long &money){

            DrawRectangleRec(dispBox, canBuyColor);
            
            if(getAffordable(money)){
                DrawRectangleRec(buyBox, canBuyColor);
                getClicked(money);    
            }
            else{
                DrawRectangleRec(buyBox, noBuyColor);
            }


            DrawText("Buy", buyBox.x, buyBox.y, 22, WHITE);

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
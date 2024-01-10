#include <iostream>
#include <string>

#pragma once

using namespace std;


class Generator{

    private: 
        string name;        
        float CPS;  //Cookies/Clicks per second
        float price;
        int counter;


    public:

        Generator(string name, float startingCPS, float startingPrice){

            this->name = name;
            CPS = startingCPS;
            price = startingPrice;

        }

        void buyNew(){

            counter++;
            price *= 1.1;
        }


        int getTotalCPS(){  //How many CPS this type of generator is generating in total
            return CPS * counter;
        }

        int getUnitCPS(){   //How much just one unit produces

        }

        int getCounter(){        
            return counter;
        }

        int getPrice(){
            return price;
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
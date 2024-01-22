#include <iostream>
#include <string>
#include <raylib.h>

#pragma once

using namespace std;


class Achievement{

    private: 

        bool achieved; 
        double startTime;


    public:

        bool shouldBeOnScreen(){

            if(achieved && (GetTime() - startTime) <= 4){
                return true;
            }
            else{
                return false;
            }

        }

        void setAchieved(){
            
            if(achieved != true){   //If achievement isn't already achieved
                achieved = true;
                startTime = GetTime();
            }
        }

        bool getAchieved(){
            return achieved;
        }

        Achievement(){}
};
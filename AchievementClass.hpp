#include <iostream>
#include <string>
#include <raylib.h>

#pragma once

using namespace std;


class Achievement{

    private: 

        bool achieved; 
        double startTime;
        string achievementName;
        string achievementMessage;
        
        Rectangle achievementBox = {590, 780, 910, 240};




    public:

        Achievement(string achievementName, string achievementMessage){

            this->achievementName = achievementName;
            this->achievementMessage = achievementMessage;

        }


        bool shouldBeOnScreen(){

            if(achieved && (GetTime() - startTime) <= 4){       //If the achievement has been achieved less than four seconds ago, 
            
                DrawRectangleRec(achievementBox, RED);
                //DrawTexture();
                DrawText(TextFormat("%s: %s", achievementName.c_str(), achievementMessage.c_str()), achievementBox.x, achievementBox.y, 12, GREEN);

                return true;
            }
            else{                   //If the achievement hasn't been reached yet OR its been more than 4 seconds, 
                return false;
            }

        }

        void setAchieved(){
            
            if(achieved != true){   //If achievement isn't already achieved
                achieved = true;    
                startTime = GetTime();  //Store the current time in the startTime variable
            }
        }

        bool getAchieved(){
            return achieved;
        }

};
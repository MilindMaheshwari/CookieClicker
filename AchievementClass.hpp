#include <iostream>
#include <string>
#include <raylib.h>
#include <functional>

#pragma once

using namespace std;


class Achievement{

    private: 

        bool achieved; 
        double startTime;
        string achievementName;
        string achievementMessage;
        

        function<bool()> condition;  
        function<void()> whatToDo;
        
        Rectangle achievementBox = {590, 780, 910, 240};




    public:

        Achievement(string achievementName, string achievementMessage, function<void()> whatToDo){

            this->achievementName = achievementName;
            this->achievementMessage = achievementMessage;
            this->whatToDo = whatToDo;

        }

        void checkIfAchieved(bool conditionReached, Texture2D image, Color color){

            if(!achieved && conditionReached){

                achieved = true;
                startTime = GetTime();
                whatToDo(); //Run the command passed

            }
            
            if(achieved && (GetTime() - startTime) <= 4){       //If the achievement has been achieved less than four seconds ago, 
            
                DrawRectangleRec(achpotaievementBox, RED);
                DrawTexture(image, 590, 850, color);
                DrawText(TextFormat("%s: %s", achievementName.c_str(), achievementMessage.c_str()), achievementBox.x, achievementBox.y, 30, GREEN);
            }
        }

        // void setAchieved(){
            
        //     if(!achieved){   //If achievement isn't already achieved
        //         achieved = true;    
        //         startTime = GetTime();  //Store the current time in the startTime variable

        //         whatToDo();

        //     }
        // }

        // bool getAchieved(){
        //     return achieved;
        // }

};
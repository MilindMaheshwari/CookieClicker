#include <iostream>
#include <string>
#include <raylib.h>
#include <functional>

#pragma once

using namespace std;


class Achievement{

    private: 

        bool achieved = false; 
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


        // bool shouldBeOnScreen(){

        //     if(achieved && (GetTime() - startTime) <= 4){       //If the achievement has been achieved less than four seconds ago, 
            
        //         DrawRectangleRec(achievementBox, RED);
        //         DrawText(TextFormat("%s: %s", achievementName.c_str(), achievementMessage.c_str()), achievementBox.x, achievementBox.y, 12, GREEN);

        //         return true;
        //     }
        //     else{                   //If the achievement hasn't been reached yet OR its been more than 4 seconds, 
        //         return false;
        //     }

        // }

        void checkIfAchieved(bool conditionReached){

            if(!achieved && conditionReached){

                achieved = true;
                startTime = GetTime();
                whatToDo(); //Run the command passed

            }
            
            if(achieved && (GetTime() - startTime) <= 4){       //If the achievement has been achieved less than four seconds ago, 
            
                DrawRectangleRec(achievementBox, RED);
                DrawText(TextFormat("%s: %s", achievementName.c_str(), achievementMessage.c_str()), achievementBox.x, achievementBox.y, 30, GREEN);
            }

        }

        bool getAchieved(){
            return achieved;
        }

};
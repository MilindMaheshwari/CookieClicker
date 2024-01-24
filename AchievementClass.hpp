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
        bool runOneTime;

        function<bool()> condition;  
        function<void()> whatToDo;
        
        Rectangle achievementBox = {590, 780, 910, 240};




    public:

        Achievement(string achievementName, string achievementMessage, function<void()> whatToDo, bool runOneTime){

            this->achievementName = achievementName;
            this->achievementMessage = achievementMessage;
            this->whatToDo = whatToDo;
            this->runOneTime = runOneTime;

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

                if(runOneTime) whatToDo(); //If its supposed to be a one time command (ex. doubling cursor CPS), run the command here (first time)


            }
            
            if(achieved && (GetTime() - startTime) <= 4){       //If the achievement has been achieved less than four seconds ago, 
            
                DrawRectangleRec(achievementBox, RED);
                DrawText(TextFormat("%s: %s", achievementName.c_str(), achievementMessage.c_str()), achievementBox.x, achievementBox.y, 30, GREEN);

            }

            if(!runOneTime && achieved) whatToDo(); //If its supposed to be a repeating command (ex. adding to CPC, which resets everyframe), run the command here (every frame)

        }

        bool getAchieved(){
            return achieved;
        }

};
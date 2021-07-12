#include <string>
#pragma once

struct User {

    int starterCredits = 900;
    int credits = starterCredits;
    std::string creditstr;

    std::string username;
    std::string difficultyLvl;
};

struct Jobs {

    std::string currentJobStatus;

    // university degree stuffs

    bool csDegreeFinished = false;
    bool teachingDegreeFinished = false;
    bool cookingDegreeFinished = false;
    bool talkingDegreeFinished = false;
    bool wizardryDegreeFinished = false;

    // job = {pay per min}

    int programmer = 1000; // requires university degree in computer science
    int chef = 200; // requires university degree in cooking
    int lecturer = 300; // requires university degree in talking 
        
    int waiter = 25;
    int teacher = 50; // requires university degree in teaching

    struct University {

        int UniFee = 2000;

        void updateDifficultyLevel(std::string dif) {
            if (dif == "Impossible") {
                UniFee *= 100;
            }
        }

        int numOfDegrees = 0;

        std::string course1 = "Computer Science";
        std::string course2 = "Teaching";
        std::string course3 = "Cooking";
        std::string course4 = "Talking";
        std::string course5 = "Wizardry";

    };
};

struct shopItems {

    std::string shopItem1 = "Quantum Computer";
    std::string shopItem2 = "Teaching";
    std::string shopItem3 = "Cooking";
    std::string shopItem4 = "Talking";

    int shopItem1Price = 100000;
    int shopItem2Price = 1000;
    int shopItem3Price = 9000;
    int shopItem4Price = 50;
    int shopItem5Price = shopItem2Price * 2;

    void updateDifficultyLevel(std::string dif) {
        if (dif == "Easy") {
            shopItem1Price -= 100;
            shopItem2Price -= 50;
            shopItem3Price -= 50;
            shopItem4Price -= 50;
        } else if (dif == "Impossible") {
            shopItem1Price *= 100;
            shopItem2Price *= 50;
            shopItem3Price *= 50;
            shopItem4Price *= 50;
        }
    }

    bool hasItem1 = false;
    bool hasItem2 = false;
    bool hasItem3 = false;
    bool hasItem4 = false;

    int item1Amount;
    int item2Amount;
    int item3Amount;
    int item4Amount;

    bool hasAnItem = false;

};


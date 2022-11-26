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

        std::string csDegree = "Computer Science";
        std::string teachingDegree = "Teaching";
        std::string cookingDegree = "Cooking";
        std::string talkingDegree = "Talking";
        std::string wizardryDegree = "Wizardry";

    };
};

struct shopItems {

    std::string computer = "Quantum Computer";
    std::string house = "Big house";
    std::string board = "Skateboard";
    std::string cat = "Cat";

    int computerPrice = 100000;
    int housePrice = 1000;
    int boardPrice = 9000;
    int catPrice = 50;
    int shopItem5Price = housePrice * 2;

    void updateDifficultyLevel(std::string dif) {
        if (dif == "Easy") {
            computerPrice -= 100;
            housePrice -= 50;
            boardPrice -= 50;
            catPrice -= 50;
        } else if (dif == "Impossible") {
            computerPrice *= 100;
            housePrice *= 50;
            boardPrice *= 50;
            catPrice *= 50;
        }
    }

    bool hasComputer = false;
    bool hasHouse = false;
    bool hasBoard = false;
    bool hasCat = false;

    int computerAmount;
    int houseAmount;
    int boardAmount;
    int catAmount;

    bool hasAnItem = (hasComputer || hasHouse || hasBoard || hasCat) ? true : false;
    bool hasAllItems = (hasComputer && hasHouse && hasBoard && hasCat) ? true : false;

};


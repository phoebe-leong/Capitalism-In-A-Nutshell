#pragma once

struct Powerups {
    int cost = 3000;
    bool active = false;

    // Wait variables
    struct Wait {
        int maxCommands = 10;
        int commands = 0;

        void updateDifficultyLevel(std::string dif) {
            if (dif == "Easy") {
                maxCommands *= 2;
            } else if (dif == "Impossible") {
                maxCommands /= 2;
            }
        }
    };
    
        int incomeMultiplier = 200;
        bool incomePowerupActive = false;
        std::string powerup1 = "Income Multiplier Powerup";

        int payrise = 250;
        std::string powerup2 = "Payrise Powerup";
        bool payrisePowerupActive = false;

        void updateDifficultyLevel(std::string dif) {
            if (dif == "Easy") {
                incomeMultiplier *= 2;
                cost -= 500;
            } else if (dif == "Impossible") {
                incomeMultiplier /= 20;
                cost *= 100;
            }
        }
};

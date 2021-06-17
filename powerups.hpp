#pragma once

struct Powerups {
    // Cost for any given powerup
    int cost = 3000;
    // Whether a powerup is currently active
    bool active = false;

    // Wait variables
    struct Wait {
        int maxCommands = 10;
        int commands = 0;
    };
    
        int incomeMultiplier = 200;
        bool incomePowerupActive = false;
        std::string powerup1 = "Income Multiplier Powerup";
};

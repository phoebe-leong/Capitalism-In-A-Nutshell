#include <string>

class User {
    public:

    int starterCredits = 900;
    int credits = starterCredits;
    std::string username;

    class PowerUps {
        public:

        int powerUpMultiplier = 200;

        int powerUpCommandNum = 0;
        int maxPowerUpCommands = 10;

        bool pwrUpActive = false; // If there is an already active powerup
        bool incomePwrUpActive = false; // If the Income Multiplier Powerup is active
    };
};

class Jobs {
    public:

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
        int taxiDriver = 20; 

    class University {
        public:

        int UniFee = 2000;

        int numOfDegrees = 0;

        std::string course1 = "Computer Science";
        std::string course2 = "Teaching";
        std::string course3 = "Cooking";
        std::string course4 = "Talking";
        std::string course5 = "Wizardry";

    };
};

class shopItems {
    public:

    std::string shopItem1 = "Quantum Computer";
    std::string shopItem2 = "Teaching";
    std::string shopItem3 = "Cooking";
    std::string shopItem4 = "Talking";
    std::string shopItem5 = "Wizardry";

    int shopItem1Price = 100000;
    int shopItem2Price = 1000;
    int shopItem3Price = 9000;
    int shopItem4Price = 50;
    int shopItem5Price = shopItem2Price * 2;

    bool hasItem1 = false;
    bool hasItem2 = false;
    bool hasItem3 = false;
    bool hasItem4 = false;

    int item1Amount = 0;
    int item2Amount = 0;
    int item3Amount = 0;
    int item4Amount = 0;

    bool hasAnItem = false;

};


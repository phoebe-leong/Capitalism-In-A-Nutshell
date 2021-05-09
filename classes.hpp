#include <string>

class User {
    public:

    int starterCredits;
    int credits;
    std::string username;
};

class Jobs {
    public:

    std::string currentJobStatus;

    // university degree stuffs

    bool csDegreeFinished;
    bool teachingDegreeFinished;
    bool cookingDegreeFinished;
    bool talkingDegreeFinished;

    bool hasUniversityDegree;

    // job = {pay per min}

    int programmer; // requires university degree in computer science
    int chef; // requires university degree in cooking
    int lecturer; // requires university degree in talking 

    class StarterJobs {
        public:
        
        int waiter;
        int teacher; // requires university degree in teaching
        int taxiDriver; 
    };

    // wait for degree to finish = {2 mins}

    class University {
        public:

        int UniFee;

        std::string course1;
        std::string course2;
        std::string course3;
        std::string course4;

    };
};

class shopItems {
    public:

    std::string shopItem1;
    std::string shopItem2;
    std::string shopItem3;
    std::string shopItem4;

    int shopItem1Price;
    int shopItem2Price;
    int shopItem3Price;
    int shopItem4Price;

    bool hasItem1;
    bool hasItem2;
    bool hasItem3;
    bool hasItem4;

    int item1Amount;
    int item2Amount;
    int item3Amount;
    int item4Amount;

    bool hasAnItem;

};


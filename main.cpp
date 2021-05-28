
// #SpaghettiCode

#include <iostream>
#include <fstream>
#include <string>
#include "classes.hpp"

// variable declaration

std::string difficultyLvl;
User usr;
User::PowerUps pwrUps;
Jobs jobs;
Jobs::StarterJobs startingJobs;
Jobs::University uni;
shopItems shop;

std::ofstream file;
std::ifstream fileRead;

// function declaration
void init();
int close();
void usernameSelect();
void mainMenu();
void jobMenu();
void uniMenu();
void shopMenu();
void difficulty();
void InsufficientFunds();
void startScreen();
void endgame();

void startScreen() {

    fileRead.open("data.txt");
    getline(fileRead, usr.username);
    getline(fileRead, jobs.currentJobStatus);
    getline(fileRead, difficultyLvl);
    fileRead.close();

    init();

    system("clear");
    std::cout << "\n\n  Capitalism In A Nutshell ( CIAN )\n";
    std::cout << "        Made by PH03be\n\n";

    std::cout << "     Press enter to start\n";
    std::cin.get();

    if (usr.username.empty()) {
        usernameSelect();
    } else {
        mainMenu();
    }

}

void endgame() {
    std::cout << "Congratulations! You bought every item!\n";
    std::cout << "This means that you won!\n";
    std::cin.get();
    system("clear");
    mainMenu();
}

void init() {

    usr.starterCredits = 900;

    pwrUps.powerUpCommandNum = 0;
    pwrUps.maxPowerUpCommands = 10;
    pwrUps.powerUpMultiplier = 200;

    pwrUps.pwrUpActive = false;

    jobs.csDegreeFinished = false;
    jobs.teachingDegreeFinished = false;
    jobs.cookingDegreeFinished = false;
    jobs.talkingDegreeFinished = false;
    jobs.wizardryDegreeFinished = false;

    jobs.programmer = 1000;
    jobs.chef = 200;
    jobs.lecturer = 300;

    startingJobs.waiter = 25;
    startingJobs.teacher = 50;
    startingJobs.taxiDriver = 20;

    uni.UniFee = 2000;
    uni.numOfDegrees = 0;
    uni.course1 = "Computer Science";
    uni.course2 = "Teaching";
    uni.course3 = "Cooking";
    uni.course4 = "Talking";
    uni.course5 = "Wizardry";

    shop.shopItem1 = "Quantum Computer";
    shop.shopItem2 = "Big house";
    shop.shopItem3 = "Hoverboard";
    shop.shopItem4 = "Cat";
    shop.shopItem5 = "Pay Multiplier Power Up";

    shop.shopItem1Price = 100000;
    shop.shopItem2Price = 1000;
    shop.shopItem3Price = 9000;
    shop.shopItem4Price = 50;
    shop.shopItem5Price = shop.shopItem2Price * 2;

    shop.hasItem1 = false;
    shop.hasItem2 = false;
    shop.hasItem3 = false;
    shop.hasItem4 = false;

    shop.hasAnItem = false;

    if (jobs.currentJobStatus.empty()) {
        jobs.currentJobStatus = "Unemployed";
    }   

    if (difficultyLvl == "Easy" || difficultyLvl == "easy") {
        usr.credits = usr.starterCredits * 2;
        pwrUps.maxPowerUpCommands *= 2;
        pwrUps.powerUpMultiplier *=  2;

        shop.item1Amount -= 100;
        shop.item2Amount -= 50;
        shop.item3Amount -= 50;
        shop.item4Amount -= 50;

        uni.UniFee -= 100;
    } else if (difficultyLvl == "Normal" || difficultyLvl == "normal") {
        usr.credits = usr.starterCredits;
    } else if (difficultyLvl == "Impossible" || difficultyLvl == "impossible") {
        usr.credits = 0;
        shop.item1Amount *= 100;
        shop.item2Amount *= 50;
        shop.item3Amount *= 50;
        shop.item4Amount *= 50;

        pwrUps.powerUpMultiplier /= 20;

        pwrUps.maxPowerUpCommands /= 2;

        uni.UniFee *= 100;
    } else if (difficultyLvl.empty()) {
        usr.credits = usr.starterCredits;
    }
}

void difficulty() {
    std::cout << "Choose a difficulty: Easy, Normal, Impossible\n";
    std::cin >> difficultyLvl;

    // pretty dumb way of doing it but other ways don't work
    if (difficultyLvl == "Easy") {
        init();
        mainMenu();
    } else if (difficultyLvl == "easy") {
        init();
        mainMenu();
    } else if (difficultyLvl == "Normal") {
        init();
        mainMenu();
    } else if (difficultyLvl == "normal") {
        init();
        mainMenu();
    } else if (difficultyLvl == "Impossible") {
        init();
        mainMenu();
    } else if (difficultyLvl == "impossible") {
        init();
        mainMenu();
    } else {
        system("clear");
        std::cout << "Please choose a difficulty.\n";
        std::cout << "Press enter to go back to the difficulty select menu.\n";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        difficulty();
    }

}

// universal close function (of course)

int close() {

    file.open("data.txt");
    file << usr.username << "\n";
    file << jobs.currentJobStatus << "\n";
    file << difficultyLvl;
    file.close();

    system("clear");
    return 0;
}

void uniMenu() {

    std::string input;

    // checks whether the user has enough money for the course/s

    std::cout << "==========================================\n";
    std::cout << "           University Courses\n";
    std::cout << "==========================================\n\n";       

    if (usr.credits >= uni.UniFee) {

        if (jobs.csDegreeFinished == false) {
            if (shop.hasItem1 == true) {
                std::cout << uni.course1 << " - Requires a previous degree in another field\n";
            } else if (uni.numOfDegrees >= 1) {
                std::cout << uni.course1 << " - Requires 'Quantum Computer'\n";
            } else if (uni.numOfDegrees >= 1 && shop.hasItem1 == true) {
                std::cout << uni.course1 << " - Gives access to 'Programmer' job\n";
            }   
        }

        if (jobs.teachingDegreeFinished == false) {
            std::cout << uni.course2 << " - Gives access to '" << uni.course2 << "' job\n";
        }

        if (jobs.teachingDegreeFinished == false) {
            std::cout << uni.course4 << " - Requires '" << uni.course2 << "' degree\n";
        } else {
            std::cout << uni.course4 << " - Gives access to 'Lecturer' job\n";
        }

        if (jobs.cookingDegreeFinished == false) {
            std::cout << uni.course3 << " - Gives access to 'Chef' job\n";
        }

        if (jobs.wizardryDegreeFinished == false) {
            std::cout << uni.course5 << " - Gives access to Powerups and Upgrades\n";
        }

        std::cout << "\n";
        std::cout << "Commands\n";

        if (jobs.csDegreeFinished == false) {
            if (uni.numOfDegrees >= 1 && shop.hasItem1 == true) {
                std::cout << "'cs' to choose the " << uni.course1 << " degree\n"; 
            }
        }

        if (jobs.teachingDegreeFinished == false) {
            std::cout << "'teaching' to choose the " << uni.course2 << " degree\n";
        }

        if (jobs.teachingDegreeFinished == true && jobs.talkingDegreeFinished == false) {
            std::cout << "'talking' to choose the " << uni.course4 << " degree\n";
        }

        if (jobs.cookingDegreeFinished == false) {
            std::cout << "'cooking' to choose the " << uni.course3 << " degree\n";
        }

        if (jobs.wizardryDegreeFinished == false) {
            std::cout << "'wizard' to choose the " << uni.course5 << " degree\n";
        }

        std::cout << "'exit' to exit the university menu\n";
        std::cin >> input;

        if (jobs.csDegreeFinished == false) {
            if (uni.numOfDegrees >= 1 && shop.hasItem1 == true && input == "cs") {
                jobs.currentJobStatus = "Programmer";
                usr.credits -= uni.UniFee;
                usr.credits += jobs.programmer * 2;
                uni.numOfDegrees++;
                system("clear");
                mainMenu();
            }
        }

        if (jobs.teachingDegreeFinished == false && input == "teaching") {
            jobs.currentJobStatus = "Teacher";
            usr.credits -= uni.UniFee;
            usr.credits += startingJobs.teacher * 2;
            uni.numOfDegrees++;
            system("clear");
            mainMenu();
        }

        if (jobs.teachingDegreeFinished == true && jobs.talkingDegreeFinished == false && input == "talking") {
            jobs.currentJobStatus = "Lecturer";
            usr.credits -= uni.UniFee;
            usr.credits += jobs.lecturer * 2;
            uni.numOfDegrees++;
            system("clear");
            mainMenu();
        }

        if (jobs.cookingDegreeFinished == false && input == "cooking") {
            jobs.currentJobStatus = "Chef";
            usr.credits -= uni.UniFee;
            usr.credits += jobs.chef * 2;
            uni.numOfDegrees++;
            system("clear");
            mainMenu();
        }

        if (jobs.wizardryDegreeFinished == false && input == "wizard") {
            usr.credits -= uni.UniFee;
            jobs.wizardryDegreeFinished = true;
            system("clear");
            mainMenu();
        }

        if (input == "exit") {
            system("clear");
            mainMenu();
        }

    } else {

        std::cout << "          You need: $" << uni.UniFee << "\n\n"; 

        InsufficientFunds();

    }

}

void mainMenu() {
    system("clear");

    if (usr.credits < 0) {
    usr.credits = 0;
    }

    if (shop.hasItem1 && shop.hasItem2 && shop.hasItem3 & shop.hasItem4) {
            system("clear");
            endgame();
    }

    if (shop.item1Amount < 0) {
        shop.item1Amount = 0;
    }

    if (shop.item2Amount < 0) {
        shop.item2Amount = 0;
    }

    if (shop.item3Amount < 0) {
        shop.item3Amount = 0;
    }

    if (shop.item4Amount < 0) {
        shop.item4Amount = 0;
    }

    if (pwrUps.powerUpCommandNum == pwrUps.maxPowerUpCommands && pwrUps.pwrUpActive == true) {
        pwrUps.pwrUpActive = false;
        pwrUps.powerUpCommandNum = 0;
    }    

    std::cout << "Credits: $" << usr.credits << "\n";
    std::cout << "Name: " << usr.username << "\n";
    std::cout << "Job: " << jobs.currentJobStatus << "\n\n";

    // shows the players items (only shows the items list if they have any items)

    if (shop.hasAnItem == true) {

        std::cout << "Items:\n";

        if (shop.hasItem1 == true) {
            if (shop.item1Amount > 1) {
                std::cout  << shop.item1Amount << " Quantum Computers\n";
            } else {
                std::cout  << shop.item1Amount << " Quantum Computer\n";
            }
        }
        if (shop.hasItem2 == true) {
            if (shop.item2Amount > 1) {
                std::cout << shop.item2Amount << " Big houses\n";
            } else {
                std::cout << shop.item2Amount << " Big house\n";
            }
        }
        if (shop.hasItem3 == true) {
            if (shop.item3Amount > 1) {
                std::cout << shop.item3Amount << " Hoverboards\n";
            } else {
                std::cout << shop.item3Amount << " Hoverboard\n";
            }
        }
        if (shop.hasItem4 == true) {
            if (shop.item4Amount > 1) {
                std::cout << shop.item4Amount << " Cats\n";
            } else {
                std::cout << shop.item4Amount << " Cat\n";
            }
        }

        std::cout << "\n";
    }

    std::cout << "Commands:\n";
    std::cout << "'jobs' to go to the job list\n";
    std::cout << "'erase' to erase all your user data\n";
    std::cout << "'shop' to go to the shop\n";

    // work commands

    if (jobs.currentJobStatus != "Unemployed") {
        if (jobs.currentJobStatus == "Taxi Driver") {
            std::cout << "'drive' to work\n";
        } else if (jobs.currentJobStatus == "Waiter") {
            std::cout << "'serve' to work\n";
        } else if (jobs.currentJobStatus == "Teacher") {
            std::cout << "'teach' to work\n";
        } else if (jobs.currentJobStatus == "Programmer") {
            std::cout << "'code' to work\n";
        } else if (jobs.currentJobStatus == "Chef") {
            std::cout << "'cook' to work\n";
        } else if (jobs.currentJobStatus == "Lecturer") {
            std::cout << "'talk' to work\n";
        }    
    }

    std::cout << "'exit' to exit the program\n";
    std::cout << "'uni' to go to the university menu\n";

    std::string input;
    std::cin >> input;

    if (input == "exit") {
        system("clear");
        close();
    } else if (input == "erase") {
        std::cin.ignore();
        system("clear");

        std::cout << "Are you sure you want to start over? [y/n] \n";
        char yn;
        std::cin >> yn;

        if (yn == 'y') {
            system("clear");
            system("rm data.txt");
            system("./main");
        } else if (yn == 'n') {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            std::cout << "Invalid Input.\n Press enter to go back to the main menu.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            mainMenu();
        }

    } else if (input == "jobs" || input == "job") {
        std::cin.ignore();
        system("clear");
        jobMenu();
    } else if (input == "uni") {
        std::cin.ignore();
        system("clear");
        uniMenu();
    } else if (input == "shop") {
        std::cin.ignore();
        system("clear");
        shopMenu();
    } else if (jobs.currentJobStatus != "Unemployed") {
        if (jobs.currentJobStatus == "Taxi Driver" && input == "drive") {
            std::cin.ignore();
            if (pwrUps.pwrUpActive == true) {
                usr.credits += startingJobs.taxiDriver * pwrUps.powerUpMultiplier;
                pwrUps.powerUpCommandNum++;
            } else {
                usr.credits += startingJobs.taxiDriver;
            }
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Waiter" && input == "serve") {
            std::cin.ignore();
            if (pwrUps.pwrUpActive == true) {
                usr.credits += startingJobs.waiter * pwrUps.powerUpMultiplier;
                pwrUps.powerUpCommandNum++;
            } else {
                usr.credits += startingJobs.waiter;
            }            
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Teacher" && input == "teach") {
            std::cin.ignore();
            if (pwrUps.pwrUpActive == true) {
                usr.credits += startingJobs.teacher * pwrUps.powerUpMultiplier;
                pwrUps.powerUpCommandNum++;
            } else {
                usr.credits += startingJobs.teacher;
            }               
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Programmer" && input == "code") {
            std::cin.ignore();
            if (pwrUps.pwrUpActive == true) {
                usr.credits += jobs.programmer * pwrUps.powerUpMultiplier;
                pwrUps.powerUpCommandNum++;
            } else {
                usr.credits += jobs.programmer;
            }               
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Lecturer" && input == "talk") {
            std::cin.ignore();
            if (pwrUps.pwrUpActive == true) {
                usr.credits += jobs.lecturer * pwrUps.powerUpMultiplier;
                pwrUps.powerUpCommandNum++;
            } else {
                usr.credits += jobs.lecturer;
            }            
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Chef" && input == "cook") {
            std::cin.ignore();
            if (pwrUps.pwrUpActive == true) {
                usr.credits += jobs.chef * pwrUps.powerUpMultiplier;
                pwrUps.powerUpCommandNum++;
            } else {
                usr.credits += jobs.chef;
            }            
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    } else {
        system("clear");
        mainMenu();
    }
}

void usernameSelect() {
    system("clear");
    std::cout << "==========================================\n";
    std::cout << "             Make a username\n";
    std::cout << "==========================================\n";
    std::getline(std::cin, usr.username);
    system("clear");

    if (difficultyLvl.empty()) {
        difficulty();
    } else {
        mainMenu();
    }

    mainMenu();
}

void jobMenu() {

    std::string input;

    if (jobs.teachingDegreeFinished != true) {

        std::cout << "==========================================\n";
        std::cout << "          Available Jobs\n";
        std::cout << "==========================================\n\n";   

        // shows the lists of all the current jobs (starter jobs only)

        std::cout << "Waiter / Waitress - $" << startingJobs.waiter << "\n";

        // Shows university jobs
        if (uni.numOfDegrees >= 1) {
            std::cout << "Taxi Driver - $" << startingJobs.taxiDriver << "\n";

            if (jobs.teachingDegreeFinished == true && jobs.currentJobStatus != "Teacher") {
                std::cout << "Teacher - $" << startingJobs.teacher;

                if (uni.numOfDegrees > 1) {
                    std::cout << "\n";
                } else {
                    std::cout << "\n\n";
                }

            }

            if (jobs.talkingDegreeFinished == true && jobs.currentJobStatus != "Lecturer") {
                std::cout << "Lecturer - $" << jobs.lecturer;

                if (uni.numOfDegrees > 1) {
                    std::cout << "\n";
                } else {
                    std::cout << "\n\n";
                }
                
            }

            if (jobs.cookingDegreeFinished == true && jobs.currentJobStatus != "Chef") {
                std::cout << "Chef - $" << jobs.chef;

                if (uni.numOfDegrees > 1) {
                    std::cout << "\n";
                } else {
                    std::cout << "\n\n";
                }
                
            }

            if (jobs.csDegreeFinished == true && jobs.currentJobStatus != "Programmer") {
                std::cout << "Programmer - $" << jobs.programmer;
            }            

        } else {
            std::cout << "Taxi Driver - $" << startingJobs.taxiDriver;
        }

        std::cout << "\n\nMore jobs can be found in the university menu.\n\n";

        std::cout << "Commands:\n";
        std::cout << "'taxi' to select taxi job\n";
        std::cout << "'waiter' to select waiter / waitress job\n";
        std::cout << "'exit' to exit the job menu\n";
        std::cout << "'uni' to go to the university menu\n";
        std::cin >> input;

    system("clear");

        if (input == "exit") {
            mainMenu();


        } else if (input == "taxi") {
            jobs.currentJobStatus = "Taxi Driver";
            usr.credits += startingJobs.taxiDriver * 2;
            mainMenu(); 
        } else if (input == "waiter") {
            jobs.currentJobStatus = "Waiter";
            usr.credits += startingJobs.waiter * 2;
            mainMenu();
        } else if (input == "uni") {
            uniMenu();
        } else {
            jobMenu();
        }
    } else {

        std::cout << "==========================================\n";
        std::cout << "          Available Jobs\n";
        std::cout << "==========================================\n\n";   

        // shows the lists of all the current jobs

        std::cout << "Waiter / Waitress - $" << startingJobs.waiter << "\n";
        std::cout << "Teacher - $" << startingJobs.teacher << "\n";
        std::cout << "Taxi Driver - $" << startingJobs.taxiDriver << "\n\n";

        std::cout << "Commands:\n";
        std::cout << "'taxi' to select taxi job\n";
        std::cout << "'waiter' to select waiter / waitress job\n";
        std::cout << "'exit' to exit the job menu\n";
        std::cout << "'uni' to go to the university menu\n";
        std::cin >> input;

    system("clear");

        if (input == "exit") {
            mainMenu();
        } else if (input == "taxi") {
            jobs.currentJobStatus = "Taxi Driver";
            usr.credits += startingJobs.taxiDriver;
            mainMenu(); 
        } else if (input == "waiter") {
            jobs.currentJobStatus = "Waiter";
            usr.credits += startingJobs.waiter;
            mainMenu();
        } else if (input == "uni") {
            uniMenu();
        } else {
            std::cout << "Not an input.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            mainMenu();
        }
    }
}

void shopMenu() {

    if (usr.credits < 0) {
        usr.credits = 0;
    }

    std::string input;

    std::cout << "==========================================\n";
    std::cout << "                   Shop\n";
    std::cout << "==========================================\n\n";

    std::cout << "Credits: $" << usr.credits << "\n\n";

    std::cout << shop.shopItem1 << " - $" << shop.shopItem1Price << "\n";
    std::cout << shop.shopItem2 << " - $" << shop.shopItem2Price << "\n";
    std::cout << shop.shopItem3 << " - $" << shop.shopItem3Price << "\n";
    std::cout << shop.shopItem4 << " - $" << shop.shopItem4Price << "\n";

    if (pwrUps.pwrUpActive == false && jobs.wizardryDegreeFinished == true) {
        std::cout << shop.shopItem5 << " - $" << shop.shopItem5Price << "\n\n";
    } else if (pwrUps.pwrUpActive == false && jobs.wizardryDegreeFinished == false) {
        std::cout << shop.shopItem5 << " - Requires '" << uni.course5 << "' degree - $" << shop.shopItem5Price << "\n\n";
    }

    std::cout << "Commands:\n";
    std::cout << "'quantum' to buy the " << shop.shopItem1 << "\n";
    std::cout << "'house' to buy the " << shop.shopItem2 << "\n";
    std::cout << "'board' to buy the " << shop.shopItem3 << "\n";
    std::cout << "'cat' to buy the " << shop.shopItem4 << "\n";

    if (pwrUps.pwrUpActive == false && jobs.wizardryDegreeFinished == true) {
        std::cout << "'power' to buy the " << shop.shopItem5 << "\n";
    }

    std::cout << "'exit' to exit the shop\n";

    std::cin >> input;

    // checks if the user has enough money to buy it and if they do, gives it to them and adds one to the amount of the product they own
    // clears the screen and redirects them back to the shop menu

    if (input == "quantum") {

        if (usr.credits >= shop.shopItem1Price) {
        usr.credits -= shop.shopItem1Price;
        shop.hasItem1 = true;
        shop.item1Amount++;
        system("clear");
        shopMenu();
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }

    } else if (input == "house") {

        if (usr.credits >= shop.shopItem2Price) {
        usr.credits -= shop.shopItem2Price;
        shop.hasItem2 = true;
        shop.item2Amount++;
        shop.hasAnItem = true;
        system("clear");
        shopMenu();
        } else {

            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();

        }
    }  else if (input == "board") {

        if (usr.credits >= shop.shopItem3Price) {
            usr.credits -= shop.shopItem3Price;
            shop.hasItem3 = true;
            shop.item3Amount++;
            system("clear");
            shopMenu();
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }

    }  else if (input == "cat") {
        if (usr.credits >= shop.shopItem4Price) {
            usr.credits -= shop.shopItem4Price;
            shop.hasItem4 = true;
            shop.item4Amount++;
            shop.hasAnItem = true;
            system("clear");
            shopMenu();
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }
    } else if (input == "power" && pwrUps.pwrUpActive == false && jobs.wizardryDegreeFinished == true) {
        if (usr.credits >= shop.shopItem5Price) {
            usr.credits -= shop.shopItem5Price;
            pwrUps.pwrUpActive = true;

            system("clear");
            std::cout << "You now have the " << shop.shopItem5 << "!\n";
            std::cout << "This multiplies your income by " << pwrUps.powerUpMultiplier << " for " << pwrUps.maxPowerUpCommands << " commands.\n";
            std::cout << "Press enter to continue.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            shopMenu();

        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();            
        }
    } else if (input == "exit") {
        system("clear");
        mainMenu();
    } else {
        system("clear");
        mainMenu();
    }
}

void InsufficientFunds() {

    std::string input;

    std::cout << "          Insufficient funds.\n";
    std::cout << "   'exit' to go back to the main menu\n";
    std::cin >> input;

    if (input == "exit") {
        system("clear");
        mainMenu();
    } else {
        system("clear");
        InsufficientFunds();
    }

}

int main() {
    startScreen();
}

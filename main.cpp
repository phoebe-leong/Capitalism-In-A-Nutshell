#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "classes.hpp"
#include "powerups.hpp"
#include "cryptor/cryptor.hpp"

std::string path = "CIAN/";

// Variables
User usr;
Powerups pwrUps;
Powerups::Wait pwrWait;
Jobs jobs;
Jobs::University uni;
shopItems shop;

void save() {
    std::ofstream file(path + "data.txt");
    file << cryptor::encrypt(usr.username) << "\n";
    file << cryptor::encrypt(jobs.currentJobStatus) << "\n";
    file << cryptor::encrypt(usr.difficultyLvl) << "\n";
    file << cryptor::encrypt(std::to_string(usr.credits));
    file.close();
}

// Function declaration
void init();
void usernameSelect();
int mainMenu();
void jobMenu();
void uniMenu();
void shopMenu();
void powerupsMenu();
void difficulty();
void InsufficientFunds();
void startScreen();
void settings();

void startScreen() {
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

void init() {
    std::ifstream fileRead;

    std::string wizardryDegreeFinishedStr;
    std::string incomePowerupActiveStr;
    std::string payrisePowerUpActive;

    fileRead.open("CIAN/data.txt");
    getline(fileRead, usr.username);
    getline(fileRead, jobs.currentJobStatus);
    getline(fileRead, usr.difficultyLvl);
    getline(fileRead, usr.creditstr);
    fileRead.close();

    fileRead.open("CIAN/powerups.txt");
    getline(fileRead, wizardryDegreeFinishedStr);
    getline(fileRead, incomePowerupActiveStr);
    getline(fileRead, payrisePowerUpActive);
    fileRead.close();

    if (cryptor::decrypt(wizardryDegreeFinishedStr) == "1") {
        jobs.wizardryDegreeFinished = true;
    }

    if (cryptor::decrypt(incomePowerupActiveStr) == "1") {
        pwrUps.incomePowerupActive = true;
    }

    if (cryptor::decrypt(payrisePowerUpActive) == "1") {
        pwrUps.payrisePowerupActive = true;

        jobs.chef += pwrUps.payrise;
        jobs.lecturer += pwrUps.payrise;
        jobs.programmer += pwrUps.payrise;
        jobs.teacher += pwrUps.payrise;
        jobs.waiter += pwrUps.payrise;
    }

    usr.username = cryptor::decrypt(usr.username);
    jobs.currentJobStatus = cryptor::decrypt(jobs.currentJobStatus);
    usr.difficultyLvl = cryptor::decrypt(usr.difficultyLvl);

    if (!usr.creditstr.empty()) {
        usr.credits = std::stoi(cryptor::decrypt(usr.creditstr));
    }

    if (jobs.currentJobStatus.empty()) {
        jobs.currentJobStatus = "Unemployed";
    }

    shop.updateDifficultyLevel(usr.difficultyLvl);
    pwrUps.updateDifficultyLevel(usr.difficultyLvl);
    pwrWait.updateDifficultyLevel(usr.difficultyLvl);
    uni.updateDifficultyLevel(usr.difficultyLvl);

    save();
    startScreen();
}

void difficulty() {
    std::cout << "Choose a difficulty: Easy, Normal, Impossible\n";
    std::cin >> usr.difficultyLvl;

    if (islower(usr.difficultyLvl[0])) {
        usr.difficultyLvl[0] = toupper(usr.difficultyLvl[0]);
    }

    if (usr.difficultyLvl == "Easy" || usr.difficultyLvl == "Normal" || usr.difficultyLvl == "Impossible")  {
        shop.updateDifficultyLevel(usr.difficultyLvl);
        pwrUps.updateDifficultyLevel(usr.difficultyLvl);
        pwrWait.updateDifficultyLevel(usr.difficultyLvl);
        uni.updateDifficultyLevel(usr.difficultyLvl);

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

void uniMenu() {

    std::string input;

    // checks whether the user has enough money for the course/s

    std::cout << "==========================================\n";
    std::cout << "           University Courses\n";
    std::cout << "==========================================\n\n";       

    if (!(usr.credits >= uni.UniFee)) {
        std::cout << "          You need: $" << uni.UniFee << "\n\n"; 
        InsufficientFunds();
        mainMenu();

    } else {
        if (!jobs.csDegreeFinished) {
            if (shop.hasComputer) {
                std::cout << uni.csDegree << " - Requires a previous degree in another field\n";
            } else if (uni.numOfDegrees >= 1) {
                std::cout << uni.csDegree << " - Requires 'Quantum Computer'\n";
            } else if (uni.numOfDegrees >= 1 && shop.hasComputer == true) {
                std::cout << uni.csDegree << " - Gives access to 'Programmer' job\n";
            }   
        }

        if (!jobs.teachingDegreeFinished) {
            std::cout << uni.teachingDegree << " - Gives access to '" << uni.teachingDegree << "' job\n";
            std::cout << uni.talkingDegree << " - Requires '" << uni.teachingDegree << "' degree\n";
        } else {
            std::cout << uni.teachingDegree << " - Gives access to '" << uni.teachingDegree << "' job\n";
            std::cout << uni.talkingDegree << " - Gives access to 'Lecturer' job\n";
        }

        if (!jobs.cookingDegreeFinished) {
            std::cout << uni.cookingDegree << " - Gives access to 'Chef' job\n";
        }

        if (!jobs.wizardryDegreeFinished) {
            std::cout << uni.wizardryDegree << " - Gives access to Powerups and Upgrades\n";
        }

        std::cout << "\n";
        std::cout << "Commands\n";

        if (!jobs.csDegreeFinished) {
            if (uni.numOfDegrees >= 1 && shop.hasComputer) {
                std::cout << "'cs' to choose the " << uni.csDegree << " degree\n"; 
            }
        }

        if (!jobs.teachingDegreeFinished) {
            std::cout << "'teaching' to choose the " << uni.teachingDegree << " degree\n";
        }

        if (jobs.teachingDegreeFinished && !jobs.talkingDegreeFinished) {
            std::cout << "'talking' to choose the " << uni.talkingDegree << " degree\n";
        }

        if (!jobs.cookingDegreeFinished) {
            std::cout << "'cooking' to choose the " << uni.cookingDegree << " degree\n";
        }

        if (!jobs.wizardryDegreeFinished) {
            std::cout << "'wizard' to choose the " << uni.wizardryDegree << " degree\n";
        }

        std::cout << "'exit' to exit the university menu\n";
        std::cin >> input;

        if (input == "cs" && !jobs.csDegreeFinished) {
            if (uni.numOfDegrees >= 1 && shop.hasComputer) {
                jobs.currentJobStatus = "Programmer";

                if (jobs.wizardryDegreeFinished) {
                    jobs.currentJobStatus += " and part-time Wizard";
                }

                usr.credits -= uni.UniFee;
                usr.credits += jobs.programmer;
                uni.numOfDegrees++;
                system("clear");

                save();
                mainMenu();
            }
        } else if (input == "teaching" && !jobs.teachingDegreeFinished) {
            jobs.currentJobStatus = "Teacher";

            if (jobs.wizardryDegreeFinished) {
                jobs.currentJobStatus += " and part-time Wizard";
            }

            usr.credits -= uni.UniFee;
            usr.credits += jobs.teacher;
            uni.numOfDegrees++;
            system("clear");

            save();
            mainMenu();
        } else if (input == "talking" && jobs.teachingDegreeFinished && !jobs.talkingDegreeFinished) {
            jobs.currentJobStatus = "Lecturer";

            if (jobs.wizardryDegreeFinished) {
                jobs.currentJobStatus += " and part-time Wizard";
            }

            usr.credits -= uni.UniFee;
            usr.credits += jobs.lecturer;
            uni.numOfDegrees++;

            save();
            system("clear");
            mainMenu();
        } else if (input == "cooking" && !jobs.cookingDegreeFinished) {
            jobs.currentJobStatus = "Chef";

            if (jobs.wizardryDegreeFinished) {
                jobs.currentJobStatus += " and part-time Wizard";
            }

            usr.credits -= uni.UniFee;
            usr.credits += jobs.chef;
            uni.numOfDegrees++;
            system("clear");

            save();
            mainMenu();
        } else if (input == "wizard" && !jobs.wizardryDegreeFinished) {
            usr.credits -= uni.UniFee;
            jobs.wizardryDegreeFinished = true;
            jobs.currentJobStatus += " and part-time Wizard";

            std::ofstream file;
            file.open("CIAN/powerups.txt");
            file << cryptor::encrypt(std::to_string(jobs.wizardryDegreeFinished)) << std::endl;
            file << cryptor::encrypt(std::to_string(pwrUps.incomePowerupActive));
            file.close();
            save();

            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            std::cout << "Not an input.\nPress enter to go back to the uni menu and try again\n";
            std::cin.ignore();
            std::cin.get();

            system("clear");
            uniMenu();
        }
    }
}

void settings() {
    std::string input;

    std::cout << "==========================================\n";
    std::cout << "               Settings\n";
    std::cout << "==========================================\n\n"; 

    std::cout << "Commands:\n";
    std::cout << "'dif' to change your difficulty level\n";
    std::cout << "'erase' to erase your user data\n";
    std::cout << "'exit' to exit the settings menu\n";
    std::cin >> input;

    if (input == "dif") {
        system("clear");
        difficulty();
    } else if (input == "erase") {
        system("clear");
        std::cout << "Are you sure you want to start over? [y/n]\n";
        char yn;
        std::cin >> yn;

        switch (yn) {
            case 'y':
                system("clear");

                system("rm CIAN/data.txt");
                system("rm CIAN/powerups.txt > /dev/null");
                system("rmdir CIAN");

                system("./main");
            case 'n':
                system("clear");
                mainMenu();
            default:
                system("clear");
                std::cout << "Invalid input.\nPress enter to go back to the main menu.\n";
                std::cin.get();

                system("clear");
                mainMenu();
        }
    } else if (input == "exit") {
        system("clear");
        mainMenu();
    } else {
        std::cout << "Not an input.\nPress enter to go back to the settings menu.\n";
        std::cin.get();

        system("clear");
        settings();
    }
}

int mainMenu() {
    system("clear");
    std::string input;

    if (usr.credits < 0) {
    usr.credits = 0;
    }

    if (shop.hasAllItems) {
        system("clear");

        std::cout << "Congratulations! You bought every item!\n";
        std::cout << "That means that you won!\n";
        std::cin.get();
        system("clear");



        mainMenu();
    }

    if (shop.computerAmount < 0) {
        shop.computerAmount = 0;
    }

    if (shop.houseAmount < 0) {
        shop.houseAmount = 0;
    }

    if (shop.boardAmount < 0) {
        shop.boardAmount = 0;
    }

    if (shop.catAmount < 0) {
        shop.catAmount = 0;
    }

    if (pwrWait.commands == pwrWait.maxCommands && pwrUps.active) {
        pwrUps.active = false;
        pwrWait.commands = 0;
    }

    std::ifstream fileRead("CIAN/data.txt");
    std::string line;
    getline(fileRead, line);
    fileRead.close();

    if (line.empty() || !fileRead) {
        save();
    }

    const std::string version = "7.4";

    std::cout << "Credits: $" << usr.credits << "\n";
    std::cout << "Name: " << usr.username << "\n";
    std::cout << "Job: " << jobs.currentJobStatus << "\n";
    std::cout << "Version: " << version << "\n\n";

    // shows the players items (only shows the items list if they have any items)
    if (shop.hasAnItem) {
        std::cout << "Items:\n";

        if (shop.hasComputer) {
            if (shop.computerAmount > 1) {
                std::cout  << shop.computerAmount << " Quantum Computers\n";
            } else {
                std::cout  << shop.computerAmount << " Quantum Computer\n";
            }
        }
        if (shop.hasHouse) {
            if (shop.houseAmount > 1) {
                std::cout << shop.houseAmount << " Big houses\n";
            } else {
                std::cout << shop.houseAmount << " Big house\n";
            }
        }
        if (shop.hasBoard) {
            if (shop.boardAmount > 1) {
                std::cout << shop.boardAmount << " Hoverboards\n";
            } else {
                std::cout << shop.boardAmount << " Hoverboard\n";
            }
        }
        if (shop.hasCat) {
            if (shop.catAmount > 1) {
                std::cout << shop.catAmount << " Cats\n";
            } else {
                std::cout << shop.catAmount << " Cat\n";
            }
        }

        std::cout << "\n";
    }

    std::cout << "Commands:\n";
    std::cout << "'jobs' to go to the job menu\n";
    std::cout << "'shop' to go to the shop\n";
    if (jobs.wizardryDegreeFinished) {
        std::cout << "'pwr' to go to the powerups menu\n";
    }
    std::cout << "'uni' to go to the university menu\n";

    // work commands
    if (jobs.currentJobStatus != "Unemployed") {
        if (jobs.currentJobStatus.rfind("Waiter", 0) == 0) {
            std::cout << "'serve' to work\n\n";
        } else if (jobs.currentJobStatus.rfind("Teacher", 0) == 0) {
            std::cout << "'teach' to work\n\n";
        } else if (jobs.currentJobStatus.rfind("Programmer", 0) == 0) {
            std::cout << "'code' to work\n\n";
        } else if (jobs.currentJobStatus.rfind("Chef", 0) == 0) {
            std::cout << "'cook' to work\n\n";
        } else {
            std::cout << "'talk' to work\n\n";
        }    
    } else {
        std::cout << "\n";
    }

    std::cout << "'set' to go to the settings menu\n";
    std::cout << "'exit' to exit the program\n";
    std::cin >> input;

    if (input == "exit") {
        system("clear");
        return 0;
    } else if (input == "set") {
        system("clear");
        settings();
    } else if (input == "jobs") {
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
    } else if (input == "pwr" && jobs.wizardryDegreeFinished) {
        if (pwrUps.active == true) {
            std::cout << "You already have an active powerup!\n";
            std::cout << "Press enter to go back to the main menu.\n";
            std::cin.ignore();
            std::cin.get();

            system("clear");
            mainMenu();
        } else {
            system("clear");
            powerupsMenu();
        }
    } else if (input == "serve" && jobs.currentJobStatus == "Waiter") {
        std::cin.ignore();
        if (pwrUps.incomePowerupActive == true) {
            usr.credits += jobs.waiter * pwrUps.incomeMultiplier;
            pwrWait.commands++;
        } else {
            usr.credits += jobs.waiter;
        }

        save();
        system("clear");
        mainMenu();
    } else if (input == "teach" && jobs.currentJobStatus == "Teacher") {
        std::cin.ignore();
        if (pwrUps.incomePowerupActive == true) {
            usr.credits += jobs.teacher * pwrUps.incomeMultiplier;
            pwrWait.commands++;
        } else {
            usr.credits += jobs.teacher;
        }

        save();
        system("clear");
        mainMenu();
    } else if (input == "code" && jobs.currentJobStatus == "Programmer") {
        std::cin.ignore();
        if (pwrUps.incomePowerupActive == true) {
            usr.credits += jobs.programmer * pwrUps.incomeMultiplier;
            pwrWait.commands++;
        } else {
            usr.credits += jobs.programmer;
        }

        save();
        system("clear");
        mainMenu();
    } else if (input == "talk" && jobs.currentJobStatus == "Lecturer") {
        std::cin.ignore();
        if (pwrUps.incomePowerupActive == true) {
            usr.credits += jobs.lecturer * pwrUps.incomeMultiplier;
            pwrWait.commands++;
        } else {
            usr.credits += jobs.lecturer;
        }            

        save();
        system("clear");
        mainMenu();
    } else if (input == "cook" && jobs.currentJobStatus == "Chef") {
        std::cin.ignore();
        if (pwrUps.incomePowerupActive == true) {
            usr.credits += jobs.chef * pwrUps.incomeMultiplier;
            pwrWait.commands++;
        } else {
            usr.credits += jobs.chef;
        }            

        save();
        system("clear");
        mainMenu();
    } else {
        system("clear");
        std::cout << "Not an input.\nPress enter to go back to the menu and try again.\n";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        mainMenu();
    }

    return -1;
}

void usernameSelect() {
    system("clear");
    std::cout << "==========================================\n";
    std::cout << "             Make a username\n";
    std::cout << "==========================================\n";
    std::getline(std::cin, usr.username);
    system("clear");

    if (usr.difficultyLvl.empty()) {
        difficulty();
    }

    mainMenu();
}

void jobMenu() {
    std::string input;

    std::cout << "==========================================\n";
    std::cout << "          Available Jobs\n";
    std::cout << "==========================================\n\n";   

    if (jobs.currentJobStatus != "Waiter") {
        std::cout << "Waiter / Waitress - $" << jobs.waiter << "\n";
    }

    // Shows university jobs
    if (uni.numOfDegrees == 0) {
        std::cout << "\nMore jobs can be found in the university menu\n\n";
    } else if (uni.numOfDegrees >= 1) {
        if (jobs.teachingDegreeFinished == true && jobs.currentJobStatus != "Teacher") {
            std::cout << "Teacher - $" << jobs.teacher;

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
    }

    std::cout << "Commands:\n";
    if (jobs.currentJobStatus != "Waiter") {
        std::cout << "'waiter' to select waiter / waitress job\n";
    }
    std::cout << "'exit' to exit the job menu\n";
    std::cout << "'uni' to go to the university menu\n";
    std::cin >> input;

    system("clear");
    if (input == "exit") {
        mainMenu(); 
    } else if (input == "waiter" && jobs.currentJobStatus != "Waiter") {
        jobs.currentJobStatus = "Waiter";
        usr.credits += jobs.waiter;

        save();
        mainMenu();
    } else if (input == "uni") {
        if (usr.credits < uni.UniFee) {
            std::cin.ignore();
        }

        uniMenu();
    } else {
        jobMenu();
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

    std::cout << shop.computer << " - $" << shop.computerPrice << "\n";
    std::cout << shop.house << " - $" << shop.housePrice << "\n";
    std::cout << shop.board << " - $" << shop.boardPrice << "\n";
    std::cout << shop.cat << " - $" << shop.catPrice << "\n\n";

    std::cout << "Commands:\n";
    std::cout << "'quantum' to buy the " << shop.computer << "\n";
    std::cout << "'house' to buy the " << shop.house << "\n";
    std::cout << "'board' to buy the " << shop.board << "\n";
    std::cout << "'cat' to buy the " << shop.cat << "\n";

    if (pwrUps.active == false && jobs.wizardryDegreeFinished == true) {
        std::cout << "'power' to buy the " << pwrUps.powerup1 << "\n";
    }

    std::cout << "'exit' to exit the shop\n";
    std::cin >> input;

    // checks if the user has enough money to buy it and if they do, gives it to them and adds one to the amount of the product they own
    // clears the screen and redirects them back to the shop menu

    if (input == "quantum") {
        if (usr.credits >= shop.computerPrice) {
            usr.credits -= shop.computerPrice;
            shop.hasComputer = true;
            shop.computerAmount++;

            system("clear");
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }
        shopMenu();
    } else if (input == "house") {
        if (usr.credits >= shop.housePrice) {
        usr.credits -= shop.housePrice;

        shop.hasHouse = true;
        shop.houseAmount++;

        system("clear");
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }
        shopMenu();
    }  else if (input == "board") {
        if (usr.credits >= shop.boardPrice) {
            usr.credits -= shop.boardPrice;

            shop.hasBoard = true;
            shop.boardAmount++;

            system("clear");
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }
        shopMenu();
    }  else if (input == "cat") {
        if (usr.credits >= shop.catPrice) {
            usr.credits -= shop.catPrice;

            shop.hasCat = true;
            shop.catAmount++;

            system("clear");
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }
        shopMenu();
    } else if (input == "power" && pwrUps.active == false && jobs.wizardryDegreeFinished == true) {
        if (usr.credits >= pwrUps.cost) {
            usr.credits -= pwrUps.cost;
            pwrUps.active = true;

            system("clear");
            std::cout << "You now have the " << pwrUps.powerup1 << "!\n";
            std::cout << "This multiplies your income by " << pwrUps.incomeMultiplier << " for " << pwrWait.maxCommands << " commands.\n";
            std::cout << "Press enter to continue.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
        } else {
            system("clear");

            std::cout << "==========================================\n";
            std::cout << "                   Shop\n";
            std::cout << "==========================================\n\n";

            std::cin.ignore();
            InsufficientFunds();
        }
        shopMenu();
    } else if (input == "exit") {
        system("clear");
        mainMenu();
    } else {
        system("clear");
        std::cout << "Not an input.\nPress enter to go back to the shop menu and try again\n";
        std::cin.ignore();
        std::cin.get();

        system("clear");
        shopMenu();
    }
}

void powerupsMenu() {
    std::cout << "==========================================\n";
    std::cout << "                 Powerups\n";
    std::cout << "==========================================\n\n";

    std::string input;
    if (pwrUps.active == false) {
        std::cout << "Credits: $" << usr.credits << "\n\n";

        std::cout << pwrUps.powerup1 << " - $" << pwrUps.cost << "\n";
        std::cout << pwrUps.powerup2 << " - $" << pwrUps.cost << "\n\n";

        std::cout << "Commands:\n";
        if (!pwrUps.active) {
            if (!pwrUps.incomePowerupActive) {
                std::cout << "'mult' to buy the " << pwrUps.powerup1 << "\n";
            }
            if (!pwrUps.payrisePowerupActive) {
                std::cout << "'pay' to buy the " << pwrUps.powerup1 << "\n";
            }
        }
        std::cout << "'exit' to exit the powerup shop\n";
        std::cin >> input;

        if (input == "mult" && !pwrUps.incomePowerupActive) {
            if (usr.credits >= pwrUps.cost) {
                usr.credits -= pwrUps.cost;
                pwrUps.active = true;
                pwrUps.incomePowerupActive = true;

                system("clear");
                std::cout << "You now have the " << pwrUps.powerup1 << "!\n";
                std::cout << "This multiplies your income by " << pwrUps.incomeMultiplier << " for " << pwrWait.maxCommands << " commands.\n";
                std::cout << "Press enter to continue.\n";
                std::cin.ignore();
                std::cin.get();
                system("clear");

                std::ofstream file;
                file.open("CIAN/powerups.txt");
                file << cryptor::encrypt(std::to_string(jobs.wizardryDegreeFinished)) << std::endl;
                file << cryptor::encrypt(std::to_string(pwrUps.incomePowerupActive)) << std::endl;
                file << cryptor::encrypt(std::to_string(pwrUps.payrisePowerupActive));
                file.close();

                powerupsMenu();
            } else {
                system("clear");

                std::cout << "==========================================\n";
                std::cout << "                 Powerups\n";
                std::cout << "==========================================\n\n";

                std::cin.ignore();
                InsufficientFunds(); 
                powerupsMenu();
            }
        } else if (input == "pay" && !pwrUps.payrisePowerupActive) {
            if (usr.credits >= pwrUps.cost) {
                usr.credits -= pwrUps.cost;
                pwrUps.payrisePowerupActive = true;
                pwrUps.active = true;

                if (jobs.currentJobStatus == "Waiter") {
                    jobs.waiter += pwrUps.payrise;
                } else if (jobs.currentJobStatus == "Chef") {
                    jobs.chef += pwrUps.payrise;
                } else if (jobs.currentJobStatus == "Teacher") {
                    jobs.teacher += pwrUps.payrise;
                } else if (jobs.currentJobStatus == "Programmer") {
                    jobs.programmer += pwrUps.payrise;
                } else if (jobs.currentJobStatus == "Lecturer") {
                    jobs.lecturer += pwrUps.payrise;
                }

                std::ofstream file;

                file.open("CIAN/powerups.txt");
                file << cryptor::encrypt(std::to_string(jobs.wizardryDegreeFinished)) << std::endl;
                file << cryptor::encrypt(std::to_string(pwrUps.incomePowerupActive)) << std::endl;
                file << cryptor::encrypt(std::to_string(pwrUps.payrisePowerupActive));
                file.close(); 

                system("clear");
                std::cout << "You now have the " << pwrUps.powerup2 << "!\n";
                std::cout << "This rises your pay by $" << pwrUps.payrise << "!\n";
                std::cout << "Press enter to continue.\n";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                powerupsMenu();
            } else {
                system("clear");

                std::cout << "==========================================\n";
                std::cout << "                 Powerups\n";
                std::cout << "==========================================\n\n";

                std::cin.ignore();
                InsufficientFunds();
                powerupsMenu();
            }
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            std::cout << "Not an input.\nPress enter to go back to the powerups menu and try again.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            powerupsMenu();
        }
    } else {
        std::cout << "You already have an active powerup!\n";
        std::cout << "Press enter to go back to the main menu.\n";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        mainMenu();
    }
}

void InsufficientFunds() {

    std::cout << "         Insufficient funds\n";
    std::cout << "        Press enter to go back\n";
    std::cin.get();

    system("clear");
}

int main() {

    const std::string &dir = "CIAN";
    struct stat buffer;

    if (!(stat(dir.c_str(), &buffer) == 0)) {
        system("mkdir CIAN");
    }

    cryptor::set_key("cian");
    init();
}

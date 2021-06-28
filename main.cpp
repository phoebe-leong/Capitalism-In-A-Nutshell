#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "classes.hpp"
#include "powerups.hpp"
#include "cryptor/cryptor.hpp"

// Variables
User usr;
Powerups pwrUps;
Powerups::Wait pwrWait;
Jobs jobs;
Jobs::University uni;
shopItems shop;

// function declaration
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
void endgame();

void startScreen() {
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
    std::cout << "That means that you won!\n";
    std::cin.get();
    system("clear");
    mainMenu();
}

void init() {

    if (islower(usr.difficultyLvl[0])) {
        usr.difficultyLvl[0] = toupper(usr.difficultyLvl[0]);
    }

    if (jobs.currentJobStatus.empty()) {
        jobs.currentJobStatus = "Unemployed";
    }   

    if (usr.difficultyLvl == "Easy") {
        if (usr.creditstr.empty()) {
            usr.credits *= 2;
        }
        pwrWait.maxCommands *= 2;
        pwrUps.incomeMultiplier *=  2;
        pwrUps.cost -= 500;

        shop.item1Amount -= 100;
        shop.item2Amount -= 50;
        shop.item3Amount -= 50;
        shop.item4Amount -= 50;

        uni.UniFee -= 100;
    } else if (usr.difficultyLvl == "Normal") {
        if (usr.creditstr.empty()) {
            usr.credits = usr.starterCredits;
        }
    } else if (usr.difficultyLvl == "Impossible") {
        if (usr.creditstr.empty()) {
            usr.credits = 0;
        }

        shop.item1Amount *= 100;
        shop.item2Amount *= 50;
        shop.item3Amount *= 50;
        shop.item4Amount *= 50;

        pwrUps.incomeMultiplier /= 20;
        pwrUps.cost *= 100;
        pwrWait.maxCommands /= 2;

        uni.UniFee *= 100;
    }
}

void difficulty() {
    std::cout << "Choose a difficulty: Easy, Normal, Impossible\n";
    std::cin >> usr.difficultyLvl;

    if (usr.difficultyLvl == "Easy" || usr.difficultyLvl == "easy" || usr.difficultyLvl == "Normal" || usr.difficultyLvl == "normal" || usr.difficultyLvl == "Impossible" || usr.difficultyLvl == "impossible")  {
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

void uniMenu() {

    std::string input;

    // checks whether the user has enough money for the course/s

    std::cout << "==========================================\n";
    std::cout << "           University Courses\n";
    std::cout << "==========================================\n\n";       

    if (usr.credits >= uni.UniFee) {

        if (!jobs.csDegreeFinished) {
            if (shop.hasItem1) {
                std::cout << uni.course1 << " - Requires a previous degree in another field\n";
            } else if (uni.numOfDegrees >= 1) {
                std::cout << uni.course1 << " - Requires 'Quantum Computer'\n";
            } else if (uni.numOfDegrees >= 1 && shop.hasItem1 == true) {
                std::cout << uni.course1 << " - Gives access to 'Programmer' job\n";
            }   
        }

        if (!jobs.teachingDegreeFinished) {
            std::cout << uni.course2 << " - Gives access to '" << uni.course2 << "' job\n";
        }

        if (!jobs.teachingDegreeFinished) {
            std::cout << uni.course4 << " - Requires '" << uni.course2 << "' degree\n";
        } else {
            std::cout << uni.course4 << " - Gives access to 'Lecturer' job\n";
        }

        if (!jobs.cookingDegreeFinished) {
            std::cout << uni.course3 << " - Gives access to 'Chef' job\n";
        }

        if (!jobs.wizardryDegreeFinished) {
            std::cout << uni.course5 << " - Gives access to Powerups and Upgrades\n";
        }

        std::cout << "\n";
        std::cout << "Commands\n";

        if (!jobs.csDegreeFinished) {
            if (uni.numOfDegrees >= 1 && shop.hasItem1) {
                std::cout << "'cs' to choose the " << uni.course1 << " degree\n"; 
            }
        }

        if (!jobs.teachingDegreeFinished) {
            std::cout << "'teaching' to choose the " << uni.course2 << " degree\n";
        }

        if (jobs.teachingDegreeFinished && !jobs.talkingDegreeFinished) {
            std::cout << "'talking' to choose the " << uni.course4 << " degree\n";
        }

        if (!jobs.cookingDegreeFinished) {
            std::cout << "'cooking' to choose the " << uni.course3 << " degree\n";
        }

        if (!jobs.wizardryDegreeFinished) {
            std::cout << "'wizard' to choose the " << uni.course5 << " degree\n";
        }

        std::cout << "'exit' to exit the university menu\n";
        std::cin >> input;

        if (!jobs.csDegreeFinished) {
            if (uni.numOfDegrees >= 1 && shop.hasItem1 && input == "cs") {
                jobs.currentJobStatus = "Programmer";
                usr.credits -= uni.UniFee;
                usr.credits += jobs.programmer * 2;
                uni.numOfDegrees++;
                system("clear");

                std::ofstream file;
                file.open("CIAN/data.txt");
                file << cryptor::encrypt(usr.username) << std::endl;
                file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
                file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
                file << cryptor::encrypt(std::to_string(usr.credits));
                file.close(); 

                mainMenu();
            }
        }
        
        if (!jobs.teachingDegreeFinished && input == "teaching") {
            jobs.currentJobStatus = "Teacher";
            usr.credits -= uni.UniFee;
            usr.credits += jobs.teacher * 2;
            uni.numOfDegrees++;
            system("clear");

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            mainMenu();
        } else if (jobs.teachingDegreeFinished && !jobs.talkingDegreeFinished && input == "talking") {
            jobs.currentJobStatus = "Lecturer";
            usr.credits -= uni.UniFee;
            usr.credits += jobs.lecturer * 2;
            uni.numOfDegrees++;

            std::ofstream file;
            file.open("data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            system("clear");
            mainMenu();
        } else if (!jobs.cookingDegreeFinished && input == "cooking") {
            jobs.currentJobStatus = "Chef";
            usr.credits -= uni.UniFee;
            usr.credits += jobs.chef * 2;
            uni.numOfDegrees++;
            system("clear");

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            mainMenu();
        } else if (!jobs.wizardryDegreeFinished && input == "wizard") {
            usr.credits -= uni.UniFee;
            jobs.wizardryDegreeFinished = true;

            std::ofstream file;
            file.open("CIAN/powerups.txt");
            file << cryptor::encrypt(std::to_string(jobs.wizardryDegreeFinished)) << std::endl;
            file << cryptor::encrypt(std::to_string(pwrUps.incomePowerupActive));
            file.close();

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

    } else {

        std::cout << "          You need: $" << uni.UniFee << "\n\n"; 

        InsufficientFunds();

    }

}

int mainMenu() {
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

    if (pwrWait.commands == pwrWait.maxCommands && pwrUps.active) {
        pwrUps.active = false;
        pwrWait.commands = 0;
    }

    std::ifstream fileRead("CIAN/data.txt");
    std::string line;
    getline(fileRead, line);
    fileRead.close();

    if (line.empty()) {
        std::ofstream file("CIAN/data.txt");

        file << cryptor::encrypt(usr.username) << std::endl;
        file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
        file << cryptor::encrypt(std::to_string(usr.credits)) << std::endl;
        file.close();
    }

    const std::string version = "7.0";

    std::cout << "Credits: $" << usr.credits << "\n";
    std::cout << "Name: " << usr.username << "\n";
    std::cout << "Job: " << jobs.currentJobStatus << "\n";
    std::cout << "Difficulty: " << usr.difficultyLvl << "\n";
    std::cout << "Version: " << version << "\n\n";

    // shows the players items (only shows the items list if they have any items)

    if (shop.hasAnItem) {

        std::cout << "Items:\n";

        if (shop.hasItem1) {
            if (shop.item1Amount > 1) {
                std::cout  << shop.item1Amount << " Quantum Computers\n";
            } else {
                std::cout  << shop.item1Amount << " Quantum Computer\n";
            }
        }
        if (shop.hasItem2) {
            if (shop.item2Amount > 1) {
                std::cout << shop.item2Amount << " Big houses\n";
            } else {
                std::cout << shop.item2Amount << " Big house\n";
            }
        }
        if (shop.hasItem3) {
            if (shop.item3Amount > 1) {
                std::cout << shop.item3Amount << " Hoverboards\n";
            } else {
                std::cout << shop.item3Amount << " Hoverboard\n";
            }
        }
        if (shop.hasItem4) {
            if (shop.item4Amount > 1) {
                std::cout << shop.item4Amount << " Cats\n";
            } else {
                std::cout << shop.item4Amount << " Cat\n";
            }
        }

        std::cout << "\n";
    }

    std::cout << "Commands:\n";
    std::cout << "'jobs' to go to the job menu\n";
    std::cout << "'shop' to go to the shop\n";
    std::cout << "'pwr' to go to the powerups menu\n";
    std::cout << "'uni' to go to the university menu\n";

    // work commands

    if (jobs.currentJobStatus != "Unemployed") {
        if (jobs.currentJobStatus == "Waiter") {
            std::cout << "'serve' to work\n\n";
        } else if (jobs.currentJobStatus == "Teacher") {
            std::cout << "'teach' to work\n\n";
        } else if (jobs.currentJobStatus == "Programmer") {
            std::cout << "'code' to work\n\n";
        } else if (jobs.currentJobStatus == "Chef") {
            std::cout << "'cook' to work\n\n";
        } else {
            std::cout << "'talk' to work\n\n";
        }    
    }

    std::cout << "'dif' to change your difficulty level\n";
    std::cout << "'erase' to erase your user data\n";
    std::cout << "'redirect' to toggle release redirect on startup\n";
    std::cout << "'exit' to exit the program\n";

    std::string input;
    std::cin >> input;

    if (input == "exit") {
        system("clear");
        return 0;
    } else if (input == "erase") {
        std::cin.ignore();
        system("clear");

        std::cout << "Are you sure you want to start over? [y/n] \n";
        char yn;
        std::cin >> yn;

        if (yn == 'y') {
            system("clear");
            system("rmdir CIAN");
            system("./main");
        } else if (yn == 'n') {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            std::cout << "Invalid Input.\nPress enter to go back to the main menu.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            mainMenu();
        }

    }  else if (input == "redirect") {

        std::ifstream fileRead("CIAN/redirect.txt");
        std::string redirecttoggle;
        getline(fileRead, redirecttoggle);

        if (redirecttoggle == "redirecttoggle") {
            system("rm CIAN/redirect.txt");
            std::cout << "'Release redirect on startup' is now toggled on.\n";
            std::cout << "Press enter to go back to the main menu.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            mainMenu();
        } else {
            std::ofstream file("CIAN/redirect.txt");
            file << "redirecttoggle";
            file.close();
            system("clear");
            std::cout << "'Release redirect on startup' is now toggled off.\n";
            std::cout << "Press enter to go back to the main menu.\n";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            mainMenu();
        }
    } else if (input == "dif") {
        system("clear");
        difficulty();
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
    } else if (input == "pwr") {
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
    } else if (jobs.currentJobStatus != "Unemployed") {
         if (jobs.currentJobStatus == "Waiter" && input == "serve") {
            std::cin.ignore();
            if (pwrUps.incomePowerupActive == true) {
                usr.credits += jobs.waiter * pwrUps.incomeMultiplier;
                pwrWait.commands++;
            } else {
                usr.credits += jobs.waiter;
            }

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close();  

            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Teacher" && input == "teach") {
            std::cin.ignore();
            if (pwrUps.incomePowerupActive == true) {
                usr.credits += jobs.teacher * pwrUps.incomeMultiplier;
                pwrWait.commands++;
            } else {
                usr.credits += jobs.teacher;
            }

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Programmer" && input == "code") {
            std::cin.ignore();
            if (pwrUps.incomePowerupActive == true) {
                usr.credits += jobs.programmer * pwrUps.incomeMultiplier;
                pwrWait.commands++;
            } else {
                usr.credits += jobs.programmer;
            }

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Lecturer" && input == "talk") {
            std::cin.ignore();
            if (pwrUps.incomePowerupActive == true) {
                usr.credits += jobs.lecturer * pwrUps.incomeMultiplier;
                pwrWait.commands++;
            } else {
                usr.credits += jobs.lecturer;
            }            

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Chef" && input == "cook") {
            std::cin.ignore();
            if (pwrUps.incomePowerupActive == true) {
                usr.credits += jobs.chef * pwrUps.incomeMultiplier;
                pwrWait.commands++;
            } else {
                usr.credits += jobs.chef;
            }            

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
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

        if (jobs.currentJobStatus != "Waiter") {
            std::cout << "Waiter / Waitress - $" << jobs.waiter << "\n";
        }

        // Shows university jobs
        if (uni.numOfDegrees >= 1) {

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

        std::cout << "\n\nMore jobs can be found in the university menu.\n\n";

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
            usr.credits += jobs.waiter * 2;

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

            mainMenu();
        } else if (input == "uni") {
            if (usr.credits < uni.UniFee) {
                std::cin.ignore();
                uniMenu();
            } else {
                uniMenu();
            }
        } else {
            jobMenu();
        }
    } else {

        std::cout << "==========================================\n";
        std::cout << "          Available Jobs\n";
        std::cout << "==========================================\n\n";   

        // shows the lists of all the current jobs

        std::cout << "Waiter / Waitress - $" << jobs.waiter << "\n";
        std::cout << "Teacher - $" << jobs.teacher << "\n";

        std::cout << "Commands:\n";
        std::cout << "'waiter' to select waiter / waitress job\n";
        std::cout << "'exit' to exit the job menu\n";
        std::cout << "'uni' to go to the university menu\n";
        std::cin >> input;

    system("clear");

        if (input == "exit") {
            mainMenu();
        } else if (input == "waiter") {
            jobs.currentJobStatus = "Waiter";
            usr.credits += jobs.waiter;

            std::ofstream file;
            file.open("CIAN/data.txt");
            file << cryptor::encrypt(usr.username) << std::endl;
            file << cryptor::encrypt(jobs.currentJobStatus) << std::endl;
            file << cryptor::encrypt(usr.difficultyLvl) << std::endl;
            file << cryptor::encrypt(std::to_string(usr.credits));
            file.close(); 

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

    if (pwrUps.active == false && jobs.wizardryDegreeFinished == true) {
        std::cout << pwrUps.powerup1 << " - $" << pwrUps.cost << "\n\n";
    } else if (pwrUps.active == false && jobs.wizardryDegreeFinished == false) {
        std::cout << pwrUps.powerup1 << " - Requires '" << uni.course5 << "' degree - $" << pwrUps.cost << "\n\n";
    }

    std::cout << "Commands:\n";
    std::cout << "'quantum' to buy the " << shop.shopItem1 << "\n";
    std::cout << "'house' to buy the " << shop.shopItem2 << "\n";
    std::cout << "'board' to buy the " << shop.shopItem3 << "\n";
    std::cout << "'cat' to buy the " << shop.shopItem4 << "\n";

    if (pwrUps.active == false && jobs.wizardryDegreeFinished == true) {
        std::cout << "'power' to buy the " << pwrUps.powerup1 << "\n";
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

    if (jobs.wizardryDegreeFinished) {

        std::string input;
        if (pwrUps.active == false) {
            std::cout << "Credits: $" << usr.credits << "\n\n";

            std::cout << pwrUps.powerup1 << " - $" << pwrUps.cost << "\n";
            std::cout << pwrUps.powerup2 << " - $" << pwrUps.cost << "\n\n";

            std::cout << "Commands:\n";
            if (!pwrUps.incomePowerupActive) {
                std::cout << "'mult' to buy the " << pwrUps.powerup1 << "\n";
            }
            if (!pwrUps.payrisePowerupActive) {
                std::cout << "'pay' to buy the " << pwrUps.powerup1 << "\n";
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
    } else if (!jobs.wizardryDegreeFinished) {
        std::cout << "Requires '" << uni.course5 << "' degree.\n";
        std::cout << "Press enter to go back to the main menu.\n";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        mainMenu();
    }

}

void InsufficientFunds() {

    std::cout << "         Insufficient funds\n";
    std::cout << " Press enter to go back to the main menu\n";
    std::cin.get();

    system("clear");
    mainMenu();
}

int main() {

    const std::string &dir = "CIAN";
    struct stat buffer;

    if (!(stat(dir.c_str(), &buffer) == 0)) {
        system("mkdir CIAN");
    }

    // Checks for internet and opens the releases GitHub page if the user has an internet connection

    std::ifstream fileRead("CIAN/redirect.txt");
    std::string redirecttoggle;
    getline(fileRead, redirecttoggle);
    fileRead.close();


    if (redirecttoggle != "redirecttoggle") {
        system("ping -c 1 google.com > CIAN/internet.txt");

        std::ifstream fileRead("CIAN/internet.txt");
        std::string useless;
        getline(fileRead, useless);

        std::string internet;
        getline(fileRead, internet);
        fileRead.close();
        system("rm CIAN/internet.txt");

        if (internet.rfind("64 bytes from", 0) == 0) {
            system("clear");
            std::cout << "Press enter to be redirected to the releases page on GitHub." << std::endl;
            std::cout << "If there is an update, please replace this program with it." << std::endl;
            std::cout << "To remove this message on startup, you can change it in the main menu." << std::endl;
            std::cin.get();

            system("open https://github.com/phoebe-leong/Capitalism-In-A-Nutshell/releases");
            system("clear");
        }
    }

    cryptor::set_key("cian");
    startScreen();
}

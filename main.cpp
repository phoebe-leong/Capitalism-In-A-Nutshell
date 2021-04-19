
// #SpaghettiCode

#include <iostream>
#include "classes.hpp"
using namespace std;

// variable declaration

User usr;
Jobs jobs;
Jobs::StarterJobs startingJobs;
Jobs::University uni;
shopItems shop; 

// function declaration
void classVariables();
int close();
void usernameSelect();
void mainMenu();
void jobMenu();
void uniMenu();
void shopMenu();
void InsufficientFunds();
void ShopInsufficientFunds();

void startScreen();
void endgame();

void startScreen() {

    system("clear");
    cout << "\n\n  Capitalism In A Nutshell\n";
    cout << "    Made by PH03be\n\n";

    cout << "  Press enter to start\n";
    cin.get();
    usernameSelect();

}

void endgame() {
    cout << "Congratulations! You bought every item!\n";
    cout << "This means that you won!\n";
    cout << "GG\n";
    cin.get();
    system("clear");
    mainMenu();
}

void classVariables() {

    // apparently i cant actually initialise the variables in classes.hpp
    // cause its a "C++11 extension"
    // so here we are

    usr.credits = 900;

    jobs.currentJobStatus = "Unemployed";
    jobs.csDegreeFinished = false;
    jobs.teachingDegreeFinished = false;
    jobs.cookingDegreeFinished = false;
    jobs.talkingDegreeFinished = false;

    jobs.hasUniversityDegree = false;

    jobs.programmer = 1000;
    jobs.chef = 200;
    jobs.lecturer = 300;

    startingJobs.waiter = 25;
    startingJobs.teacher = 50;
    startingJobs.taxiDriver = 20;

    uni.UniFee = 2000;
    uni.course1 = "Computer Science";
    uni.course2 = "Teaching";
    uni.course3 = "Cooking";
    uni.course4 = "Talking";

    shop.shopItem1 = "Quantum Computer";
    shop.shopItem2 = "Big house";
    shop.shopItem3 = "Hoverboard";
    shop.shopItem4 = "Cat";

    shop.shopItem1Price = 100000;
    shop.shopItem2Price = 1000;
    shop.shopItem3Price = 9000;
    shop.shopItem4Price = 50;

    shop.hasItem1 = false;
    shop.hasItem2 = false;
    shop.hasItem3 = false;
    shop.hasItem4 = false;

    shop.item1Amount = 0;
    shop.item2Amount = 0;
    shop.item3Amount = 0;
    shop.item4Amount = 0;

    shop.hasAnItem = false;
}

// universal close function (of course)

int close() {
    cout << "Press enter to close the program:\n";
    cin.get();
    system("clear");
    return 0;
}

void uniMenu() {

    string input;

    // checks whether the user has enough money for the course/s

    cout << "==========================================\n";
    cout << "           University Courses\n";
    cout << "==========================================\n\n";

    if (usr.credits >= uni.UniFee) {

    cout << "Uni Course Fee: $" << uni.UniFee << "\n\n";

    // if the user meets specific requirements, show specific text

     if (jobs.hasUniversityDegree == true && shop.hasItem1 == true) {
        cout << "Computer Science - Gives access to 'Programmer' job\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Cooking - Gives access to 'Chef' job\n";

        cout << "\n";
        cout << "Commands:\n";
        cout << "'cs' to choose the Computer Science degree\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'exit' to exit the university menu\n";

        cin >> input;

        if (input == "cs") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.csDegreeFinished = true;
            jobs.currentJobStatus = "Programmer";
            system("clear");
            mainMenu();
        } else if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.currentJobStatus = "Chef";
            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }

    } else if (jobs.teachingDegreeFinished  == true && jobs.hasUniversityDegree == true && shop.hasItem1 == true) {
        cout << "Computer Science - Gives access to 'Programmer job'\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Talking - Gives access to 'Lecturer' job\n";
        cout << "Cooking - Gives access to 'Chef' job\n\n";

        cout << "Commands:\n";
        cout << "'cs' to choose the Computer Science degree\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'talking' to choose the Talking degree\n";
        cout << "'exit' to exit the university menu\n";
        
        cin >> input;

        if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.currentJobStatus = "Chef";
            jobs.hasUniversityDegree = true;
            system("clear");
            mainMenu();
        } else if (input == "cs") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.csDegreeFinished = true;
            jobs.currentJobStatus = "Programmer";
            system("clear");
            mainMenu();
        } else if (input == "talking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.talkingDegreeFinished = true;
            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    }  else if (jobs.hasUniversityDegree == true && jobs.teachingDegreeFinished == true) {
        cout << "Computer Science - Requires 'Quantum Computer'\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Talking - Gives access to 'Lecturer' job\n";
        cout << "Cooking - Gives access to 'Chef' job\n\n";

        cout << "Commands:\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'talking' to choose the Talking degree\n";
        cout << "'exit' to exit the university menu\n";
        
        cin >> input;

        if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Chef";
            system("clear");
            mainMenu();
        } else if (input == "talking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.talkingDegreeFinished = true;
            jobs.currentJobStatus = "Lecturer";
            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    } else if (jobs.hasUniversityDegree == true) {
        cout << "Computer Science - Requires 'Quantum Computer'\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Talking - Requires 'Teaching' degree\n";
        cout << "Cooking - Gives access to 'Chef' job\n\n";

        cout << "Commands:\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'exit' to exit the university menu\n";
        
        cin >> input;

        if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Chef";
            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    } else if (shop.hasItem1 == true) {
        cout << "Computer Science - Requires a previous degree in another field\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Talking - Requires 'Teaching' degree\n";
        cout << "Cooking - Gives access to 'Chef' job\n\n";

        cout << "Commands:\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'exit' to exit the university menu\n";
        
        cin >> input;

        if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Chef";
            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    } else if (shop.hasItem1 == true && jobs.teachingDegreeFinished == true) {
        cout << "Computer Science - Requires a previous degree in another field\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Talking - Gives access to 'Lecturer' job\n";
        cout << "Cooking - Gives access to 'Chef' job\n\n";

        cout << "Commands:\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'talking' to choose the Talking degree\n";
        cout << "'exit' to exit the university menu\n";
        
        cin >> input;

        if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Chef";
            system("clear");
            mainMenu();
        } else if (input == "talking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.talkingDegreeFinished = true;
            jobs.currentJobStatus = "Lecturer";
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    } else {
        cout << "Computer Science - Requires a previous degree in another field and 'Quantum Computer'\n";
        cout << "Teaching - Gives access to 'Teaching' job\n";
        cout << "Talking - Requires 'Teaching' degree\n";
        cout << "Cooking - Gives access to 'Chef' job\n\n";

        cout << "Commands:\n";
        cout << "'teaching' to choose the Teaching degree\n";
        cout << "'cooking' to choose the Cooking degree\n";
        cout << "'exit' to exit the university menu\n";
        
        cin >> input;

        if (input == "teaching") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.teachingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Teacher";
            system("clear");
            mainMenu();
        } else if (input == "cooking") {
            usr.credits = usr.credits - uni.UniFee;
            jobs.cookingDegreeFinished = true;
            jobs.hasUniversityDegree = true;
            jobs.currentJobStatus = "Chef";
            system("clear");
            mainMenu();
        } else if (input == "exit") {
            system("clear");
            mainMenu();
        } else {
            system("clear");
            mainMenu();
        }
    }   
    } else {

        cout << "          You need: $" << uni.UniFee << "\n\n"; 

        InsufficientFunds();

    }

}

void mainMenu() {

    // floating bits of code

    if (usr.credits < 0) {
    usr.credits = 0;
    }

    if (shop.hasItem1 && shop.hasItem2 && shop.hasItem3 & shop.hasItem4) {
            system("clear");
            endgame();
    }

    cout << "Credits: $" << usr.credits << "\n";
    cout << "Name: " << usr.username << "\n";
    cout << "Job: " << jobs.currentJobStatus << "\n\n";

    // shows the players items (only shows the items list if they have any items)

    if (shop.hasAnItem == true) {

        cout << "Items:\n";

        if (shop.hasItem1 == true) {
            if (shop.item1Amount > 1) {
                cout  << shop.item1Amount << " Quantum Computers\n";
            } else {
                cout  << shop.item1Amount << " Quantum Computer\n";
            }
        }
        if (shop.hasItem2 == true) {
            if (shop.item2Amount > 1) {
                cout << shop.item2Amount << " Big houses\n";
            } else {
                cout << shop.item2Amount << " Big house\n";
            }
        }
        if (shop.hasItem3 == true) {
            if (shop.item3Amount > 1) {
                cout << shop.item3Amount << " Hoverboards\n";
            } else {
                cout << shop.item3Amount << " Hoverboard\n";
            }
        }
        if (shop.hasItem4 == true) {
            if (shop.item4Amount > 1) {
                cout << shop.item4Amount << " Cats 'meow'\n";
            } else {
                cout << shop.item4Amount << " Cat 'meow'\n";
            }
        }

        cout << "\n";
    }

    cout << "Commands:\n";
    cout << "'jobs' to go to the job list\n";
    cout << "'shop' to go to the shop\n";

    // work commands

    if (jobs.currentJobStatus != "Unemployed") {
        if (jobs.currentJobStatus == "Taxi Driver") {
            cout << "'drive' to work\n";
        } else if (jobs.currentJobStatus == "Waiter") {
            cout << "'serve' to work\n";
        } else if (jobs.currentJobStatus == "Teacher") {
            cout << "'teach' to work\n";
        } else if (jobs.currentJobStatus == "Programmer") {
            cout << "'code' to work\n";
        } else if (jobs.currentJobStatus == "Chef") {
            cout << "'cook' to work\n";
        } else if (jobs.currentJobStatus == "Lecturer") {
            cout << "'talk' to work\n";
        }
    }

    cout << "'exit' to exit the program\n";
    cout << "'uni' to go to the university menu\n";

    string input;
    cin >> input;
    cin.ignore();

    if (input == "exit") {
        system("clear");
        close();
    } else if (input == "jobs" || input == "job") {
        system("clear");
        jobMenu();
    } else if (input == "uni") {
        system("clear");
        uniMenu();
    } else if (input == "shop") {
        system("clear");
        shopMenu();
    } else if (jobs.currentJobStatus != "Unemployed") {
        if (jobs.currentJobStatus == "Taxi Driver" && input == "drive") {
            usr.credits = usr.credits + startingJobs.taxiDriver;
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Waiter" && input == "serve") {
            usr.credits = usr.credits + startingJobs.waiter;
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Teacher" && input == "teach") {
            usr.credits = usr.credits + startingJobs.teacher;
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Programmer" && input == "code") {
            usr.credits = usr.credits + jobs.programmer;
            system("clear");
            mainMenu();
        } else if (jobs.currentJobStatus == "Lecturer" && input == "talk") {
            usr.credits = usr.credits + jobs.lecturer;
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
    cout << "==========================================\n";
    cout << "             Make a username\n";
    cout << "==========================================\n";
    cin >> usr.username;
    system("clear");
    mainMenu();
}

void jobMenu() {

    string input;

    if (jobs.teachingDegreeFinished != true) {

        cout << "==========================================\n";
        cout << "          Available Jobs\n";
        cout << "==========================================\n\n";   

        // shows the lists of all the current jobs (starter jobs only)

        cout << "Waiter / Waitress - $" << startingJobs.waiter << "\n";
        cout << "Teacher - Requires University Degree in Teaching - $" << startingJobs.teacher << "\n";
        cout << "Taxi Driver - $" << startingJobs.taxiDriver << "\n\n";

        cout << "Commands:\n";
        cout << "'taxi' to select taxi job\n";
        cout << "'waiter' to select waiter / waitress job\n";
        cout << "'exit' to exit the job menu\n";
        cout << "'uni' to go to the university menu\n";
        cin >> input;

    system("clear");

        if (input == "exit") {
            mainMenu();

            // visually displays the job on the menu and assigns them 15 time the normal salary on hire

        } else if (input == "taxi") {
            jobs.currentJobStatus = "Taxi Driver";
            usr.credits = usr.credits + (startingJobs.taxiDriver * 15);
            mainMenu(); 
        } else if (input == "waiter") {
            jobs.currentJobStatus = "Waiter";
            usr.credits = usr.credits + (startingJobs.waiter * 15);
            mainMenu();
        } else if (input == "uni") {
            uniMenu();
        } else {
            jobMenu();
        }
    } else {

        cout << "==========================================\n";
        cout << "          Available Jobs\n";
        cout << "==========================================\n\n";   

        // shows the lists of all the current jobs

        cout << "Waiter / Waitress - $" << startingJobs.waiter << "\n";
        cout << "Teacher - $" << startingJobs.teacher << "\n";
        cout << "Taxi Driver - $" << startingJobs.taxiDriver << "\n\n";

        cout << "Commands:\n";
        cout << "'taxi' to select taxi job\n";
        cout << "'waiter' to select waiter / waitress job\n";
        cout << "'exit' to exit the job menu\n";
        cout << "'uni' to go to the university menu\n";
        cin >> input;

    system("clear");

        if (input == "exit") {
            mainMenu();
        } else if (input == "taxi") {
            jobs.currentJobStatus = "Taxi Driver";
            usr.credits = usr.credits + startingJobs.taxiDriver;
            mainMenu(); 
        } else if (input == "waiter") {
            jobs.currentJobStatus = "Waiter";
            usr.credits = usr.credits + startingJobs.waiter;
            mainMenu();
        } else if (input == "uni") {
            uniMenu();
        } else {
            cout << "Not an input.\n";
            cin.ignore();
            cin.get();
            system("clear");
            mainMenu();
        }
    }
}

void shopMenu() {

    if (usr.credits < 0) {
        usr.credits = 0;
    }

    string input;

    cout << "==========================================\n";
    cout << "                   Shop\n";
    cout << "==========================================\n\n";

    cout << "Credits: $" << usr.credits << "\n\n";

    cout << shop.shopItem1 << " - $" << shop.shopItem1Price << "\n";
    cout << shop.shopItem2 << " - $" << shop.shopItem2Price << "\n";
    cout << shop.shopItem3 << " - $" << shop.shopItem3Price << "\n";
    cout << shop.shopItem4 << " - $" << shop.shopItem4Price << "\n\n";

    cout << "Commands:\n";
    cout << "'quantum' to buy the " << shop.shopItem1 << "\n";
    cout << "'house' to buy the " << shop.shopItem2 << "\n";
    cout << "'board' to buy the " << shop.shopItem3 << "\n";
    cout << "'cat' to buy the " << shop.shopItem4 << "\n";
    cout << "'exit' to exit the shop\n";

    cin >> input;

    // checks if the user has enough money to buy it and if they do, gives it to them and adds one to the amount of the product they own
    // clears the screen and redirects them back to the shop menu

    if (input == "quantum") {

        if (usr.credits >= shop.shopItem1Price) {
        usr.credits = usr.credits - shop.shopItem1Price;
        shop.hasItem1 = true;
        shop.item1Amount++;
        system("clear");
        shopMenu();
        } else {
            system("clear");

            cout << "==========================================\n";
            cout << "                   Shop\n";
            cout << "==========================================\n\n";

            ShopInsufficientFunds();
        }

    } else if (input == "house") {

        if (usr.credits >= shop.shopItem2Price) {
        usr.credits = usr.credits - shop.shopItem2Price;
        shop.hasItem2 = true;
        shop.item2Amount++;
        shop.hasAnItem = true;
        system("clear");
        shopMenu();
        } else {

            system("clear");

            cout << "==========================================\n";
            cout << "                   Shop\n";
            cout << "==========================================\n\n";

            ShopInsufficientFunds();

        }
    }  else if (input == "board") {

        if (usr.credits >= shop.shopItem3Price) {
            usr.credits = usr.credits - shop.shopItem3Price;
            shop.hasItem4 = true;
            shop.item3Amount++;
            system("clear");
            shopMenu();
        } else {
            system("clear");

            cout << "==========================================\n";
            cout << "                   Shop\n";
            cout << "==========================================\n\n";

            ShopInsufficientFunds();
        }

    }  else if (input == "cat") {

        if (usr.credits >= shop.shopItem4Price) {
            usr.credits = usr.credits - shop.shopItem4Price;
            shop.hasItem4 = true;
            shop.item4Amount++;
            shop.hasAnItem = true;
            system("clear");
            shopMenu();
        } else {
            system("clear");

            cout << "==========================================\n";
            cout << "                   Shop\n";
            cout << "==========================================\n\n";

            ShopInsufficientFunds();
        }

    } else if (input == "exit") {
        system("clear");
        mainMenu();
    } else {
        system("clear");
        mainMenu();
    }
}

// shows that the user doesn't have enough money
// i had to make another function for the shop because otherwise it just skipped over everything

void InsufficientFunds() {

    string input;

    cout << "          Insufficient funds.\n";
    cout << "   'exit' to go back to the main menu\n";
    cin >> input;

    if (input == "exit") {
        system("clear");
        mainMenu();
    } else {
        system("clear");
        uniMenu();
    }

}

void ShopInsufficientFunds() {

    string input;

    cout << "          Insufficient funds.\n";
    cout << "   'exit' to go back to the shop menu\n";
    cin >> input;

    if (input == "exit") {
        system("clear");
        shopMenu();
    } else {
        system("clear");
        shopMenu();
    }

    system("clear");
    mainMenu(); 

}

int main() {
    classVariables();
    startScreen();
}
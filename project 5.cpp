#include <iostream>
#include <string>
#include <climits> // Required for INT_MAX

using namespace std;

// Function prototypes
void intro();
void exploreRoom();
void encounterCharacter(bool &gameOverFlag); // Pass gameOverFlag by reference
void exploreDungeon(bool &gameOverFlag);  // Added reference to gameOverFlag
void finalChoice();
void gameOver(bool &gameOverFlag); // Modify gameOverFlag in this function
void victory();

int main() {
    int choice;
    bool gameOverFlag = false;
    
    intro();

    while (!gameOverFlag) {
        cout << "\nYou are standing in the main hall of the castle. What would you like to do?\n";
        cout << "1. Enter the library.\n";
        cout << "2. Go to the kitchen.\n";
        cout << "3. Explore the dungeon.\n";
        cout << "4. Leave the castle.\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        // Input validation
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');  // Fix: Use INT_MAX after including <climits>
            cout << "Invalid choice. Please choose a number between 1 and 4: ";
            cin >> choice;
        }

        // Branching decisions based on player choice
        switch (choice) {
            case 1:
                exploreRoom();
                break;
            case 2:
                encounterCharacter(gameOverFlag); // Pass the gameOverFlag
                break;
            case 3:
                exploreDungeon(gameOverFlag);  // Pass gameOverFlag
                break;
            case 4:
                victory();
                gameOverFlag = true;  // Set gameOverFlag to true
                break;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
                break;
        }
    }

    return 0;
}

void intro() {
    cout << "You wake up in a dark, cold room. As your eyes adjust, you realize you are in an ancient castle.\n";
    cout << "The walls are covered in dust and cobwebs, and there is an eerie silence in the air.\n";
    cout << "You feel a sense of dread but also curiosity. You must find a way out.\n";
}

void exploreRoom() {
    int choice;
    cout << "\nYou enter the library. It is filled with old, dusty books. In the corner, you see a chest.\n";
    cout << "What do you want to do?\n";
    cout << "1. Open the chest.\n";
    cout << "2. Search the shelves for something useful.\n";
    cout << "3. Leave the library.\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    // Input validation
    while (cin.fail() || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');  // Fix: Use INT_MAX after including <climits>
        cout << "Invalid choice. Please choose a number between 1 and 3: ";
        cin >> choice;
    }

    switch (choice) {
        case 1:
            cout << "You open the chest and find a golden key! You now have a way to unlock the dungeon.\n";
            break;
        case 2:
            cout << "You search the shelves and find an ancient map. This could be useful later.\n";
            break;
        case 3:
            cout << "You decide to leave the library and return to the main hall.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

void encounterCharacter(bool &gameOverFlag) {  // Pass gameOverFlag by reference
    int choice;
    cout << "\nYou enter the kitchen. There, you encounter a strange old woman cooking something in a pot.\n";
    cout << "She turns to you and says, 'I can help you leave this castle, but first, you must prove yourself.'\n";
    cout << "What will you do?\n";
    cout << "1. Accept her challenge.\n";
    cout << "2. Refuse and leave the kitchen.\n";
    cout << "Enter your choice (1-2): ";
    cin >> choice;

    // Input validation
    while (cin.fail() || choice < 1 || choice > 2) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');  // Fix: Use INT_MAX after including <climits>
        cout << "Invalid choice. Please choose a number between 1 and 2: ";
        cin >> choice;
    }

    string answer; // Declare 'answer' before the switch statement

    switch (choice) {
        case 1:
            cout << "The old woman gives you a riddle. If you solve it, she will help you escape.\n";
            cout << "'I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?'\n";
            cout << "Your answer: ";
            cin >> answer;
            if (answer == "echo") {
                cout << "Correct! The woman smiles and hands you a magical potion that will help you escape.\n";
            } else {
                cout << "Wrong answer. The woman cackles and disappears in a puff of smoke.\n";
                gameOver(gameOverFlag);  // Call gameOver and pass gameOverFlag
            }
            break;
        case 2:
            cout << "You decide to leave the kitchen and go back to the main hall.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

void exploreDungeon(bool &gameOverFlag) {
    int choice;
    cout << "\nYou descend into the dungeon. The air is damp, and the sound of dripping water echoes around you. There are two paths ahead.\n";
    cout << "Which way will you go?\n";
    cout << "1. Take the left path.\n";
    cout << "2. Take the right path.\n";
    cout << "Enter your choice (1-2): ";
    cin >> choice;

    // Input validation
    while (cin.fail() || choice < 1 || choice > 2) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');  // Fix: Use INT_MAX after including <climits>
        cout << "Invalid choice. Please choose a number between 1 and 2: ";
        cin >> choice;
    }

    switch (choice) {
        case 1:
            cout << "You take the left path and find a treasure chest with gold and a key to the castle's front door!\n";
            break;
        case 2:
            cout << "You take the right path and encounter a group of skeletons. They surround you and... game over.\n";
            gameOver(gameOverFlag);  // Trigger game over
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

void finalChoice() {
    int choice;
    cout << "\nYou find yourself standing before the dungeon door. It is locked, but you have the key.\n";
    cout << "What will you do?\n";
    cout << "1. Unlock the door and enter the dungeon.\n";
    cout << "2. Leave the castle without entering.\n";
    cout << "Enter your choice (1-2): ";
    cin >> choice;

    // Input validation
    while (cin.fail() || choice < 1 || choice > 2) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');  // Fix: Use INT_MAX after including <climits>
        cout << "Invalid choice. Please choose a number between 1 and 2: ";
        cin >> choice;
    }

    switch (choice) {
        case 1:
            cout << "You unlock the door and descend into the dungeon. After solving several puzzles, you find the exit!\n";
            victory();
            break;
        case 2:
            cout << "You decide it's too dangerous and leave the castle, never to return.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

void victory() {
    cout << "\nCongratulations! You've successfully escaped the castle and survived your adventure.\n";
}

void gameOver(bool &gameOverFlag) {
    cout << "\nGame Over. You have been trapped in the castle forever.\n";
    gameOverFlag = true;  // Set gameOverFlag to true to stop the loop
}

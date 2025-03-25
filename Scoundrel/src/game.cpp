/**
 * Author: Paul Cagaanan
 * Description: This .cpp file implements game mechanics as member functions.
 * Functionalites for running combat, weapon, and healing encounters. Implemented in Scoundrel.
 * 
 * * ====================== Update Log ======================
 * - [2025-03-24] Updated promptEncounter() and getRoomChoice() to fix crashing issue
 *   -  Updated input handling to prevent crashing from trying to access an out-of-memory element
 * - [2025-03-23] Updated documentation and added printEncounter() and message()
 * - [2025-03-20]   Created file.
 * -    Added encounter functions: runCombat(), runWeapon(), runHeal()
 * 
 */

#include "game.h"

/**
 * @brief Handles a combat encounter between the player and a monster.
 * 
 * Prompts the player to choose between equipping a weapon or fighting barehanded,
 * calculates the damage taken, and updates the player's health accordingly.
 * 
 * @param m The reference to Monster being fought.
 */
void Game::runCombat(const Monster& m)
{
    int choice = 0;
    int reduced = max(m.getAtk() - player.getAtk(), 0);
    int full = m.getAtk();

    printEncounter(m.getAtk(), "monster"); // Prints the monster description
    cout << "You face the " << m.getName() << ". \n\n"
         << "[1] EQUIP WEAPON (Take " << reduced << " damage)\n"
         << "[2] FIGHT BAREHANDED (Take " << full <<  " damage)\n "
         << "How will you fight: ";
    cin >> choice;
    clearInput();
    cout << endl;

    printEncounter(choice, "combat");
    player.attack(m, choice == 1);
    cout << "You take " << (choice == 1 ? reduced : full) << " points of damage. "
         << "You have " << player.getHP() << " HP remaining." << endl;
}

/**
 * @brief Handles an encounter of player finding and equipping a weapon.
 * 
 * Updates the player's attack with the given weapon.
 * 
 * @param w The reference to Weapon being equipped. 
 */
void Game::runEquip(const Weapon& w)
{
    printEncounter(w.getAtk(), "equip");
    player.equip(w);
    cout << "You equipped the " << w.getName() << "." << endl;
}

/**
 * @brief Handles an encounter of player finding and consuming a potion.
 * 
 * Restores the player's health by the potion's heal amount.
 * 
 * @param p The reference to Potion being consumed.
 */
void Game::runHeal(const Potion& p)
{
    printEncounter(p.getHealAmount(), "heal");
    player.drink(p);
    cout << "You drink the " << p.getName() << ", restoring " << p.getHealAmount() << " health points." << endl;
    cout << "You have " << player.getHP() << " health points left." << endl;
}

// ====================== Input Handling ====================== 

int promptRoom(const bool& skipFlag)
{ 
    int choice;
    cout << "[1] ENTER ROOM? ";
            if (!skipFlag) { cout << "[2] RUN AWAY? "; } // If room wasn't skipped last turn
            cout << "[0] QUIT GAME?" << endl;
            cin >> choice;
            cout << endl;

    return choice;
}

int getRoomChoice(const bool& skipFlag)
{ 
    int choice;
    do {
        choice = promptRoom(skipFlag);
        clearInput();
    } while (skipFlag ? choice < 0 || choice > 1 : choice < 0 || choice > 2);
    
    return choice;
}

int promptEncounter(int availableChoices)
{
    int choice;
    do {
        cout << "Choose an encounter: ";
        cin >> choice;
        cout << endl;
        clearInput();
    } while (choice < 1 || choice > availableChoices);

    return choice;
}

void clearInput()
{
    if (cin.fail()) { // Input validation block
        cin.clear();
        while (cin.get() != '\n'); 
        cout << "Invalid input. Please enter 1 or 2." << endl;
    } else { cin.get(); }
}

// ====================== Game Flow ====================== 

void enterRoom(int& room, const vector<Card>& myHand)
{
    cout << "You enter the room.\n\n";
    cout << setfill('-') << setw(10) << ""
        << " ROOM " << room << " "
        << setw(10) << "" << setfill(' ') << endl;

    for (int i = 0; i < myHand.size(); i++)
    {
        const Card& card = myHand[i];
        string action;

        if (card.suit == "Clubs" || card.suit == "Spades") { action = "FIGHT A MONSTER"; }
        else if (card.suit == "Diamonds") { action = "EQUIP A WEAPON"; }
        else if (card.suit == "Hearts") { action = "DRINK A POTION"; }
        else { action = "--COMPLETED--"; }

        cout << "[ " << i + 1 << " ] " << left << setw(16) << action << " : "
            << card.name << "(" << card.value << ")\n";
    }
} 

void skipRoom(Deck& myDeck, vector<Card>& myHand)
{
    cout << "You skipped the room, shuffling cards...\n\n"
         << "Drawing new room...\n";
    myDeck.addCard(myHand);
    myHand = myDeck.drawCard(4);
}

void runEncounter(Game& game, const Card& chosenCard)
{
    if (chosenCard.suit == "Clubs" || chosenCard.suit == "Spades") { game.runCombat(Monster(chosenCard.name, chosenCard.value)); }
    else if (chosenCard.suit == "Diamonds") { game.runEquip(Weapon(chosenCard.name, chosenCard.value)); }
    else if (chosenCard.suit == "Hearts") { game.runHeal(Potion(chosenCard.name, chosenCard.value)); }
}

// ====================== Display/Output ======================

void displayRoom(const vector<Card>& myHand)
{
    cout << "You drew: \n\n";
    
    for (int i = 0; i < myHand.size(); i++)
    {
        const Card& card = myHand[i];
        cout << "[ " << i + 1 << " ] " << card.name << "\n";
    }
}

void printEncounter(const int& value, const string& type)
{
    if (type != "equip" && type != "heal" && type != "monster") { cout << message(value, type) << endl; return; }
    if (value >= 1 && value <= 3) { cout << message(1, type) << endl; }
    else if (value >= 4 && value <= 6) { cout << message(2, type) << endl; }
    else if (value >= 7 && value <= 9) { cout << message(3, type) << endl; }
    else if (value == 10) { cout << message(4, type) << endl; }

    switch (value) {
    case 11:
        cout << message(5, type) << endl; break;
    case 12:
        cout << message(6, type) << endl; break;
    case 13:
        cout << message(7, type) << endl; break;
    case 14:
        cout << message(8, type) << endl; break;
    }
}

// ====================== Helper Functions ====================== 

string message(int value, const string& type)
{
    if (type == "equip") { // Returns description of finding a weapon
        switch (value) {
        case 1: return "You find a low tier weapon: value is 1-3."; 
        case 2: return "You find a mid tier weapon: value is 4-6.";
        case 3: return "You find a high tier weapon: value is 7-9.";
        case 4: return "You find a legendary weapon: value is 10.";
        } 
    }
    else if (type == "heal") { // Returns description of finding a potion
        switch (value) {
            case 1: return "You find a low tier potion: value is 1-3.";
            case 2: return "You find a mid tier potion: value is 4-6.";
            case 3: return "You find a high tier potion: value is 7-9.";
            case 4: return "You find a legendary potion: value is 10.";
        } 
    }
    else if (type == "monster") { // Returns description of a monster
        switch (value) {
            case 1: return "You fight a small creature: value is 1-3.";
            case 2: return "You fight a medium creature: value is 4-6.";
            case 3: return "You fight a large creature: value is 7-9.";
            case 4: return "You fight a boss creature: value is 10.";
            case 5: return "You fight a boss creature Jack: value is 11.";
            case 6: return "You fight a boss creature Queen: value is 12.";
            case 7: return "You fight a boss creature King: value is 13.";
            case 8: return "You fight a legendary creature Ace: value is 14.";
        }
    }
    else if (type == "combat") { // Returns description of player combat
        switch (value) {
            case 1: return "You fight with your weapon.";
            case 2: return "You fight barehanded.";
        }
    }
            
    return "Valid statement not found.";
}


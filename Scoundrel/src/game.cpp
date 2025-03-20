/**
 * Author: Paul Cagaanan
 * Description: This .cpp file implements game mechanics as member functions.
 * Functionalites for running combat, weapon, and healing encounters. Implemented in Scoundrel.
 * 
 * * ====================== Update Log ======================
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
    int reduced = m.getAtk() - player.getAtk();
    int full = m.getAtk();

    cout << "You face the " << m.getName() << ". \n\n"
         << "[1] EQUIP WEAPON (Take " << reduced << " damage)\n"
         << "[2] FIGHT BAREHANDED (Take " << full <<  " damage)\n "
         << "How will you fight: ";
    cin >> choice;
    cout << endl;

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
    player.drink(p);
    cout << "You drink the " << p.getName() << ", restoring " << p.getHealAmount() << "health points." << endl;
    cout << "You have " << player.getHP() << "health points left." << endl;
}

// ====================== Standalone Functions ====================== 

void displayRoom(const vector<Card>& myHand)
{
    cout << "You drew: \n\n";
    for (int i = 0; i < myHand.size(); i++)
    {
        const Card& card = myHand[i];
        cout << "[ " << i + 1 << " ] " << card.name << "\n";
    }
}
int promptRoom(const bool& skipFlag)
{ 
    int choice;
    cout << "[1] ENTER ROOM? ";
            if (!skipFlag) { cout << "[2] RUN AWAY? "; } 
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
    } while (choice < 0 || choice > 2);
    
    return choice;
}

void enterRoom(int& room, const vector<Card>& myHand)
{
    room++;
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

int promptEncounter()
{
    int choice;
    do {
        cout << "Choose an encounter: ";
        cin >> choice;
        cout << endl;
        clearInput();
    } while (choice < 1 || choice > 4);

    return choice;
}

void runEncounter(Game& game, const Card& chosenCard)
{
    if (chosenCard.suit == "Clubs" || chosenCard.suit == "Spades") { game.runCombat(Monster(chosenCard.name, chosenCard.value)); }
    else if (chosenCard.suit == "Diamonds") { game.runEquip(Weapon(chosenCard.name, chosenCard.value)); }
    else if (chosenCard.suit == "Hearts") { game.runHeal(Potion(chosenCard.name, chosenCard.value)); }
}

void clearInput()
{
    if (cin.fail()) { // Input validation block
        cin.clear();
        while (cin.get() != '\n'); 
        cout << "Invalid input. Please enter 1 or 2." << endl;
    } else { cin.get(); }
}
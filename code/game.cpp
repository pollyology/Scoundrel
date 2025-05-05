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
#include "messages.h"
#include "Deck.h"

using std::string, std::cout, std::endl;

const string PRESS_ENTER = "Press 'Enter' to continue...";
const string ERASE_LINE = "\r\033[K";
const string CLEAR_SCREEN = "\033[2J\033[H";

// +==================================================+
// |                    GAME FLOW                     |
// +==================================================+

string startMenu()
{
    string playerName;
    
    while(true)
    {
        cout << endl;
        cout << welcomeToScoundrel() << endl << endl;
        cout << "[1] PLAY " << "[2] TUTORIAL " << "[3] QUIT" << endl;
        
        int choice = getMenuChoice(1, 3);
        string erase = ERASE_LINE; // Escape code for erasing current line

        switch (choice)
        {
            case 1: cout << "\nWhat is your name?\n> ";
                    cin >> playerName; 
                    clearScreen();
                    return playerName;

            case 2: cout << message("tutorial", 1) << "\n\n";
                    pressEnterToContinue();
                    clearScreen();
                    break;

            case 3: cout << "Quitting game.." << endl;
                    exit(0);
        }
    }
    return "";
}

int Game::roomMenu()
{ 
    cout << "[1] ENTER ROOM? ";
    if (!skipFlag) { cout << "[2] RUN AWAY? "; } // If room wasn't skipped last turn
    cout << "[0] QUIT GAME?" << endl;  
            
    int choice = skipFlag ? getMenuChoice(0, 1) : getMenuChoice(0, 2);
    cout << endl;

    return choice;
}

void Game::enterRoom(int& room, const vector<Card>& myHand)
{
    for (const Card& card : myHand)
    {
        if (card.name != "empty")
        {
            printBanner("YOU ENTER THE ROOM.");
            cout << "\n";
            cout << "It is dusty and the walls are lined with moss...\n";
            printBanner("ROOM " + to_string(room));
            displayHand(myHand);
        }
        break;
    }

    string choose = "+============== CHOOSE AN ENCOUNTER ==============+";
    cout << choose << endl;
    
    for (int i = 0; i < myHand.size(); i++)
    {   
        const Card& card = myHand[i];
        string action, statValue;
        string rightPart = "  :  " + card.name;

        if (card.suit != "empty")
        {
            if (card.type == "MONSTER") { action = "FIGHT A MONSTER"; statValue = "DMG"; }
            else if (card.type == "WEAPON") { action = "EQUIP A WEAPON "; statValue = "ATK"; }
            else if (card.type == "POTION") { action = "DRINK A POTION "; statValue = "HP"; }
            statValue = "(" + to_string(card.value) + " " + statValue + ")";
        }
        else 
        { 
            action = "--COMPLETED--";
            rightPart = ""; 
        }  

        string leftPart = " [" + to_string(i + 1) + "] " + action;
        int totalWidth = choose.length();
        int fullLength = leftPart.length() + rightPart.length();
        int padding = totalWidth - fullLength - statValue.length() - 2;

        cout << "|" <<  leftPart << rightPart << string(padding, ' ') << statValue << "|\n";
    }
    cout << ("+" + string(49, '=') + "+") << endl;
} 

void Game::skipRoom(Deck& myDeck, vector<Card>& myHand)
{
    cout << "You skipped the room...\n\n";
    cout << "Shuffling cards...\n\n";    
    myDeck.addCard(myHand);
    myHand = myDeck.drawCard(4);
    setSkipFlag(true);
}

void Game::refreshHand(Deck& deck, vector<Card>& hand)
{
    if (deck.getDeck().empty()) { return; } 

    // Draws a new hand, while preserving the last card
    Card preservedCard = hand[0];
    hand = deck.drawCard(3);
    hand.insert(hand.begin(), preservedCard);
}

void Game::clearEmptyCards(vector<Card>& hand)
{
    // Using remove_if from <algorithm>
    // Syntax:  remove_if(start_iterator, end_iterator, condition)
    // hand.erase(remove_if(), hand.emd());

    hand.erase
    (
        remove_if(hand.begin(), hand.end(), [](const Card& card)
        {
            return card.name == "empty";
        }),
        hand.end()
    );
}

// +=================================================+
// |               ENCOUNTER HANDLING                |
// +=================================================+

void Game::handleRoomEncounter(int& room, Player& player, vector<Card>& myHand, vector<Card>& discardPile)
{
    enterRoom(room, myHand); 
    cout << endl; 
    player.displayStatus();
    cout << endl;
    
    int cardChoice = promptEncounter(myHand.size()); // Prompt player to choose an encounter
    Card chosenCard = myHand[cardChoice - 1]; // Construct card from choice
    
    runEncounter(chosenCard); // Run appropriate encounter from card choice
    if (isPlayerDead(player)) { return; }
    
    myHand.erase(myHand.begin() + (cardChoice - 1)); // Erase chosen card
    myHand.insert(myHand.begin() + (cardChoice - 1), Card("empty")); // Replace with empty card
    discardPile.push_back(chosenCard); // Move chosen card to discard pile after resolving encounter
    printBanner("ROOM " + to_string(room));
    displayHand(myHand);
}

int promptEncounter(int availableChoices)
{
    cout << "Choose an encounter: " << endl;
    int choice = getMenuChoice(1, availableChoices);
    return choice;
}

void Game::runEncounter(const Card& chosenCard)
{   
    displayCard(chosenCard);
    if (chosenCard.type == "MONSTER") { runCombat(Monster(chosenCard.name, chosenCard.value)); }
    else if (chosenCard.type == "WEAPON") { runEquip(Weapon(chosenCard.name, chosenCard.value)); }
    else if (chosenCard.type == "POTION") { runHeal(Potion(chosenCard.name, chosenCard.value)); }
}

void Game::runCombat(const Monster& m)
{
    int choice = -1;
    int reducedDamage = max(m.getAtk() - player.getWeaponAtk(), 0);
    int fullDamage = m.getAtk();
    int hpBefore = player.getHP();

    printBanner("COMBAT BEGINS!");

    printEncounter("monster", m.getAtk()); // Prints the monster description
    cout << "You face the " << m.getName() << ". \n\n";

    // Display combat choices
    if (m.getAtk() > player.getWeaponDurability())
    { cout << "[1] CANNOT USE WEAPON (Take " << fullDamage << " damage)\n"; }
    else { cout << "[1] EQUIP WEAPON (Take " << reducedDamage << " damage)\n"; }

    cout << "[2] FIGHT BAREHANDED (Take " << fullDamage <<  " damage)\n "
         << "How will you fight: " << endl;
    
    choice = getMenuChoice(1, 2);
    cout << endl;

    // Executes player combat
    string header = "--------------------------------------------------\n";
    cout << header;
    printEncounter("combat", choice);
    player.attack(m, choice == 1);

    // Calculate damage taken
    int damageTaken = hpBefore - player.getHP();
    cout << "> You take " << damageTaken << " points of damage.\n"
         << "> Remaining HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";

    if (damageTaken != fullDamage)
    {
        cout << "> Your weapon loses durability.\n" 
             << "> Durability: " << player.getWeaponDurability() << "\n";
    }

    cout << header;
    printBanner("COMBAT ENDS.");
    pressEnterToContinue();
    clearScreen();
}

void Game::runEquip(const Weapon& w)
{
    printEncounter("equip", w.getAtk());
    player.equip(w);
    cout << "You equipped the " << w.getName() << "." << endl;
}

void Game::runHeal(const Potion& p)
{
    if (potionFatigue)
    {
        cout << "You drank the potion, but it had no effect! " << endl; 
    }
    else 
    {
        printEncounter("heal", p.getHealAmount());
        player.drink(p, potionFatigue);
        cout << "You drink the " << p.getName() << ", restoring " << p.getHealAmount() << " health points. ";
    }

        cout << "Remaining HP: " << player.getHP() << "/" << player.getMaxHP() << endl;
        setPotionFatigue(true);
}

// +=================================================+
// |                DISPLAY / OUTPUT                 |
// +=================================================+

void displayCard(const Card& card)
{
   // Given a card, use 7 rows to print a text version of it
   CardDisplay cardFace = getCardDisplay(card);
   string displayValue = cardFace.displayValue;
   string symbol = cardFace.symbol;
   string borderRow = " --------- \n";
   string middleRow = "|    " + symbol + "    |\n";
   string emptyRow = "|         |\n";
   string leftCorner = card.value == 10 ? "|" + displayValue + symbol +  "      |\n" :
                                     "|" + displayValue + symbol +  "       |\n";

   string rightCorner = card.value == 10 ? "|      " + displayValue + symbol + "|\n":
                                      "|       " + displayValue + symbol + "|\n";
  
   string asciiCard = borderRow + leftCorner + emptyRow + middleRow + emptyRow + rightCorner + borderRow;
   cout << asciiCard << endl;
}

void displayHand(const vector<Card>& myHand)
{
    for (int row = 0; row < 7; row++) // Prints a playing card by printing 7 rows of characters
    {
        for (int i = 0; i < myHand.size(); i++) // Prints through each row for each card in hand
        {   
            const Card& card = myHand[i];
            CardDisplay cardFace = getCardDisplay(card);
            string symbol = cardFace.symbol;
            string displayValue = cardFace.displayValue;

            // Quick and dirty solution because I hate figuring out <iomanip>
            if (row == 0 || row == 6) { cout << " --------- "; }                                // 1. Prints top and bottom row
            else if (row == 1)                                                                  // 2. Prints left-side symbol
            {
                if (card.value == 10) { cout << "|" << displayValue << symbol <<  "      |"; }
                else if (card.value != 0) { cout << "|" << displayValue << symbol <<  "       |"; }
                else { cout << "|         |"; }

            }
            else if (row == 2 || row == 4) { cout << "|         |"; }                           // 3. Prints empty borders
            else if (row == 5)                                                                  // 4. Prints right-side symbol
            {
                if (card.value == 10) { cout << "|      " << displayValue << symbol << "|"; }
                else if (card.value != 0) { cout << "|       " << displayValue << symbol << "|"; }
                else { cout << "|         |"; }
            }
            else if (card.value != 0) { cout << "|    " << symbol << "    |"; }                 // 5. Prints middle row
            else { cout << "|  EMPTY  |"; }

            if (i < myHand.size()) { cout << "  "; }                                            // 6. Prints " " between each card
        }
        cout << endl;
    }
    for (int i = 0; i < myHand.size(); i++) // Kinda yucky implementation of position numbers underneath hand
    {
        cout << string(4, ' ') << '[' << (i + 1) << ']' << string(6, ' ');
    }
    cout << endl;
    cout << endl;
}

void displayRoom(const vector<Card>& myHand, Deck& myDeck)
{
    //int handSize = myHand.size();
    int deckSize = myDeck.getDeck().size();

    //cout << "\nYou draw " + to_string(handSize) + " cards!\n\n"
    printBanner("DRAWING NEW ROOM");
    cout << "\nRemaining cards in deck: " + to_string(deckSize) + "\n";
    cout << "\n";
    
    displayHand(myHand);    
    for (int i = 0; i < myHand.size(); i++)
    {
        const Card& card = myHand[i];
        cout << "[" << i + 1 << "] " << card.name << "\n";
    }
    cout << endl;
    cout << "--------------------------------------------------\n";
}

void printEncounter(const string& type, const int& value)
{
    if (type != "equip" && type != "heal" && type != "monster") { cout << message(type, value) << endl; return; }

    // Message handling for runEquip(), runHeal(), runCombat():
    if (value >= 1 && value <= 3) { cout << message(type, 1) << endl; }
    else if (value >= 4 && value <= 6) { cout << message(type, 2) << endl; }
    else if (value >= 7 && value <= 9) { cout << message(type, 3) << endl; }
    else if (value == 10) { cout << message(type, 4) << endl; }

    switch (value) {
    case 11:
        cout << message(type, 5) << endl; break;
    case 12:
        cout << message(type, 6) << endl; break;
    case 13:
        cout << message(type, 7) << endl; break;
    case 14:
        cout << message(type, 8) << endl; break;
    }
}

// +=================================================+
// |               HELPER FUNCTIONS                  |
// +=================================================+

void assignCardType(Deck& deck)
{
    for (Card& card : deck.getDeck())
    {
        if (card.suit == "Clubs" || card.suit == "Spades") { card.type = "MONSTER"; }
        else if (card.suit == "Diamonds") { card.type = "WEAPON"; }
        else if (card.suit == "Hearts") { card.type = "POTION"; }
    }
}

bool isPlayerDead(const Player& player)
{
    return player.getHP() <= 0;
}

void pressEnterToContinue()
{
    cout << PRESS_ENTER;
    if (cin.peek() != '\n')
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
}

void clearScreen()
{
    cout << CLEAR_SCREEN;
}

void printBanner(const string& message)
{
   int textLength = message.length();
   bool isEven = (textLength % 2 == 0);
   int width = isEven ? 50 : 49; 
   int padWidth = width - textLength - 2;
   
   string borderRow = "+" + string(width - 2, '=') + "+\n";
   string middleRow = "|" + string(padWidth / 2, ' ') + message + string(padWidth / 2, ' ') + "|\n";

   cout << borderRow << middleRow << borderRow;
}

void printHeader(const string& message)
{
   int textLength = message.length();
   bool isEven = (textLength % 2 == 0);
   int width = isEven ? 50 : 49; 
   int padWidth = width - textLength - 2;
   
   string topRow = "+" + string(width - 2, '=') + "+\n";
   string bottomRow = "+" + string(width - 2, '-') + "+\n";
   string middleRow = "|" + string(padWidth / 2, ' ') + message + string(padWidth / 2, ' ') + "|\n";

   cout << topRow << middleRow << bottomRow;
}


int getMenuChoice(int minChoice, int maxChoice)
{
    int choice = -1;
    string input;
    string erase = "\r\033[K"; // Escape code for clearing from cursor to end of line
    

    // Keep this commented for now, this allows single line reuse,
    // but for some reason creates an extra ">" when entering a room.
    // string erase = "\033[F\033[2K" 

    while (true) // Airtight input validation block, could probably copy-paste template for other menu functions
    {
        cout << "r\033[2K> "; // Clear entire line then print "> "
        getline(cin, input);

        if (input == "Quit" || input == "quit")
        {
            cout << "Quitting program..." << endl;
            exit(0);
        }

        bool isValidInput = !input.empty() && isdigit(input[0]) && input.size() == 1; 
        if (!isValidInput) // Checks if input is a valid single-digit number
        {
            cout << erase;
            continue; // Restart loop
        }

        try
        {
            choice = stoi(input);
            if (choice >= minChoice && choice <= maxChoice) { return choice; } // Checks if choice is within range
            else { cout << erase; }
        }
        catch (const out_of_range& e)
        {
            cout << erase;
        }
        catch (const invalid_argument& e)
        {
            cout << erase;
        }
    }
    
}

string message(const string& type, int value)
{
    if (type == "tutorial") { return TUTORIAL_MESSAGE; }

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

string welcomeToScoundrel()
{
return R"(  
 +===============================================================================+
||                                                                               ||      
||   █     █▓█████ ██▓    ▄████▄  ▒█████  ███▄ ▄███▓█████    ▄▄▄█████▓▒█████     ||
||   ▓█░ █ ░█▓█   ▀▓██▒   ▒██▀ ▀█ ▒██▒  ██▓██▒▀█▀ ██▓█   ▀    ▓  ██▒ ▓▒██▒  ██▒  ||
||   ▒█░ █ ░█▒███  ▒██░   ▒▓█    ▄▒██░  ██▓██    ▓██▒███      ▒ ▓██░ ▒▒██░  ██▒  ||
||   ░█░ █ ░█▒▓█  ▄▒██░   ▒▓▓▄ ▄██▒██   ██▒██    ▒██▒▓█  ▄    ░ ▓██▓ ░▒██   ██░  ||
||   ░░██▒██▓░▒████░██████▒ ▓███▀ ░ ████▓▒▒██▒   ░██░▒████▒     ▒██▒ ░░ ████▓▒░  ||
||   ░ ▓░▒ ▒ ░░ ▒░ ░ ▒░▓  ░ ░▒ ▒  ░ ▒░▒░▒░░ ▒░   ░  ░░ ▒░ ░     ▒ ░░  ░ ▒░▒░▒░   || 
||     ▒ ░ ░  ░ ░  ░ ░ ▒  ░ ░  ▒    ░ ▒ ▒░░  ░      ░░ ░  ░       ░     ░ ▒ ▒░   ||
||     ░   ░    ░    ░ ░  ░       ░ ░ ░ ▒ ░      ░     ░        ░     ░ ░ ░ ▒    ||
||       ░      ░  ░   ░  ░ ░         ░ ░        ░     ░  ░               ░ ░    ||
||                        ░                                                      ||
||     ██████ ▄████▄  ▒█████  █    ██ ███▄    █▓█████▄ ██▀███ ▓█████ ██▓         ||
||   ▒██    ▒▒██▀ ▀█ ▒██▒  ██▒██  ▓██▒██ ▀█   █▒██▀ ██▓██ ▒ ██▓█   ▀▓██▒         ||
||   ░ ▓██▄  ▒▓█    ▄▒██░  ██▓██  ▒██▓██  ▀█ ██░██   █▓██ ░▄█ ▒███  ▒██░         ||
||     ▒   ██▒▓▓▄ ▄██▒██   ██▓▓█  ░██▓██▒  ▐▌██░▓█▄   ▒██▀▀█▄ ▒▓█  ▄▒██░         ||
||   ▒██████▒▒ ▓███▀ ░ ████▓▒▒▒█████▓▒██░   ▓██░▒████▓░██▓ ▒██░▒████░██████▒     ||
||   ▒ ▒▓▒ ▒ ░ ░▒ ▒  ░ ▒░▒░▒░░▒▓▒ ▒ ▒░ ▒░   ▒ ▒ ▒▒▓  ▒░ ▒▓ ░▒▓░░ ▒░ ░ ▒░▓  ░     ||
||   ░ ░▒  ░ ░ ░  ▒    ░ ▒ ▒░░░▒░ ░ ░░ ░░   ░ ▒░░ ▒  ▒  ░▒ ░ ▒░░ ░  ░ ░ ▒  ░     ||
||   ░  ░  ░ ░       ░ ░ ░ ▒  ░░░ ░ ░   ░   ░ ░ ░ ░  ░  ░░   ░   ░    ░ ░        ||
||         ░ ░ ░         ░ ░    ░             ░   ░      ░       ░  ░   ░  ░     ||
||           ░                                  ░                                ||
 +===============================================================================+)";
}

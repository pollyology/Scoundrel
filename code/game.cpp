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
const string header = "--------------------------------------------------\n";

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

            case 2: printEncounter("tutorial", 1);
                    cout << "\n\n";
                    cout << "[DEBUG] Next char in buffer: " << cin.peek() << endl;
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
    if (!m_skipFlag) { cout << "[2] RUN AWAY? "; } // If room wasn't skipped last turn
    cout << "[0] QUIT GAME?" << endl;  
            
    int choice = m_skipFlag ? getMenuChoice(0, 1) : getMenuChoice(0, 2);
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
    
    if (chosenCard.type != "empty") { runEncounter(chosenCard); } // Run appropriate encounter from card choice
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
    //displayCard(chosenCard);
    if (chosenCard.type == "MONSTER") { runCombat(chosenCard); }
    else if (chosenCard.type == "WEAPON") { runEquip(chosenCard); }
    else if (chosenCard.type == "POTION") { runHeal(chosenCard); }
}

void Game::runCombat(const Card& monsterCard)
{
    Monster monster(monsterCard.name, monsterCard.value);
    string p_weaponType = m_player.getWeaponType();
    int choice = -1;
    int reducedDamage = max(monster.getAtk() - m_player.getWeaponAtk(), 0);
    int fullDamage = monster.getAtk();
    int hpBefore = m_player.getHP();


    printEncounter("monster", monster.getAtk()); // Prints the monster description
    cout << "You face the " << monster.getName() << ". \n\n";
    
    pressEnterToContinue();
    clearScreen();
    printBanner("COMBAT BEGINS!");

    // Display combat choices
    if (monster.getAtk() > m_player.getWeaponDurability())
    { cout << "[1] CANNOT USE WEAPON (Take " << fullDamage << " damage)\n"; }
    else { cout << "[1] EQUIP WEAPON (Take " << reducedDamage << " damage)\n"; }

    cout << "[2] FIGHT BAREHANDED (Take " << fullDamage <<  " damage)\n "
         << "How will you fight: " << endl;
    
    choice = getMenuChoice(1, 2);
    cout << endl;

    // Executes player combat
    cout << header;
    printEncounter("combat", choice);   // Pass '1' or '2'
    m_player.attack(monster, choice == 1);

    // Calculate damage taken
    int damageTaken = hpBefore - m_player.getHP();
    printEncounter(p_weaponType, damageTaken);
    cout << header;
    cout << "> You take " << damageTaken << " points of damage.\n"
         << "> Remaining HP: " << m_player.getHP() << "/" << m_player.getMaxHP() << "\n";

    if (damageTaken != fullDamage)
    {
        cout << "> Your weapon loses durability.\n" 
             << "> Durability: " << m_player.getWeaponDurability() << "\n";
    }

    
    printBanner("COMBAT ENDS.");
    cout.flush();
    //cout << "[DEBUG] Next char in buffer: " << cin.peek() << endl;
    pressEnterToContinue();
    clearScreen();
}

void Game::runEquip(const Card& weaponCard)
{   
    Weapon weapon(weaponCard.name, weaponCard.value);
    string banner;

    if (weaponCard.value <= 3) { banner = "A RUSTY DAGGER"; }
    else if (weaponCard.value <= 6) { banner = "AN OLD SWORD"; }
    else if (weaponCard.value <= 9) { banner = "THE GUARDMAN'S SPEAR"; }
    else { banner = "A KNIGHT'S LAST STAND"; }
    
    printBanner(banner);
    printEncounter("equip", weapon.getAtk());
    m_player.equip(weapon);
    cout << header << endl;

    cout << "You equipped the " << weapon.getName() << ".\n" << endl;
    displayCard(weaponCard);
    pressEnterToContinue();
    clearScreen();
}

void Game::runHeal(const Card& potionCard)
{
    Potion potion(potionCard.name, potionCard.value);
    string banner;

    if (potionCard.value <= 3) { banner = "TINCTURE OF HERBS"; }
    else if (potionCard.value <= 6) { banner = "AN ABANDONED CACHE"; }
    else if (potionCard.value <= 9) { banner = "SANCUTARY SHRINE"; }
    else { banner = "ALTAR OF HEALING"; }

    if (m_potionFatigue)
    {
        cout << "You drank the potion, but it had no effect! " << endl; 
    }
    else 
    {
        printBanner(banner);
        printEncounter("heal", potion.getHealAmount());
        m_player.drink(potion, m_potionFatigue);
        cout << header << endl;
        displayCard(potionCard);
        cout << "You drink the " << potion.getName() << ", restoring " << potion.getHealAmount() << " health points. ";
    }
        cout << "\nRemaining HP: " << m_player.getHP() << "/" << m_player.getMaxHP() << endl;
        setPotionFatigue(true);

    pressEnterToContinue();
    clearScreen();
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

   string topRow = "┌─────────┐\n";
   string bottomRow = "└─────────┘\n";
   string middleRow = "│    " + symbol + "    │\n";
   string emptyRow = "│         │\n";

   string leftCorner = card.value == 10 ? "│" + displayValue + symbol +  "      │\n" :
                                     "│" + displayValue + symbol +  "       │\n";

   string rightCorner = card.value == 10 ? "│      " + displayValue + symbol + "│\n":
                                      "│       " + displayValue + symbol + "│\n";
  
   string asciiCard = topRow + leftCorner + emptyRow + middleRow + emptyRow + rightCorner + bottomRow;
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
			switch (row)
			{
            	case 0: cout << "┌─────────┐"; break;
				case 6: cout << "└─────────┘"; break;                                // 1. Prints top and bottom row
            	case 1:        		                                                 // 2. Prints left-side symbol
                	if (card.value == 10) { cout << "│" << displayValue << symbol <<  "      │"; }
                	else if (card.value != 0) { cout << "│" << displayValue << symbol <<  "       │"; }
                	else { cout << "│         │"; }
					break;
				case 2:
				case 4:
        			cout << "│         │";
					break;                           // 3. Prints empty borders
				case 3:
					if (card.value != 0) { cout << "│    " << symbol << "    │"; }                 // 5. Prints middle row
					else { cout << "│  EMPTY  │"; }
					break;
				case 5:                                                                 // 4. Prints right-side symbol
					if (card.value == 10) { cout << "│      " << displayValue << symbol << "│"; }
					else if (card.value != 0) { cout << "│       " << displayValue << symbol << "│"; }
					else { cout << "│         │"; }
					break;
			}
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
    printBanner("DRAWING NEW ROOM!");
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
    MessageType messageType = getMessageType(type, value);
    printMessage(messageType);
}

 void printMessage(MessageType messageType)
 {
    cout << getMessageText(messageType) << endl;
 }

// +=================================================+
// |               HELPER FUNCTIONS                  |
// +=================================================+

string getMessageText(MessageType type)
{
       auto it = messageMap.find(type);
       if (it != messageMap.end())
       {
              return it->second;
       }
       return "[Message not found]";
};

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
    cout << PRESS_ENTER << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
   
   // \u250c fancy top left
   // \u2510 fancy top right
   // \u2514 fancy bottom left
   // \u2518 fancy bottom right
   // \u2500 fancy horizontal
   // \u2502 fancy vertical

   string topRow;       // Loop for top row
   topRow += u8"\u250c";
   for (int i = 0; i < width - 2; i++)
   {
        topRow += u8"\u2500";
   }
   topRow += u8"\u2510"; 

   string middleRow;    // Loop for middle row
   middleRow += u8"\u2502";
   for (int i = 0; i < padWidth / 2; i++)
   {
       middleRow += ' ';
   }
   middleRow += message;
   for (int i = 0; i < padWidth / 2; i++)
   {
       middleRow += ' ';
   }
   middleRow += u8"\u2502";

   string bottomRow;    // Loop for bottom row
   bottomRow += u8"\u2514";
   for (int i = 0; i < width - 2; i++)
   {
        bottomRow += u8"\u2500";
   }
   bottomRow += u8"\u2518";

   cout << topRow << endl << middleRow << endl << bottomRow << endl;
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

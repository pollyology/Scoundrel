/*Prep:
Remove Aces, Jack, Queens, and Kings of Hearts & Diamonds for a 44-card deck
Start with 20 health points
Draw 4 cards to start first room

Gameplay:

Creating Rooms: The first Room is created by drawing four cards.
Completing Rooms: You complete a room by resolving three cards.
You can fight a Monster, equip a Weapon, or heal with a Potion.
After completing a Room, draw three more cards to make the next Room.
Skipping Rooms: At the start of a new room, you can choose to run away. 
Shuffle the four cards into the bottom of the deck; you can't skip twice in a row.


Card Mechanics
Monsters (Spades and Clubs): Deal damage to player equal to their value.
Weapons (Diamonds): Equip them to reduce damage equal to their value, but they can "break" with use.
Health Potions (Hearts): Recover health points equal to their value, can only be used once per room.

EQUIPPING WEAPONS
1-3: Rusty Dagger
 You stumbled upon a small, lifeless creature. Embedded in its torso, is a dagger.
 With a slight tug of the hilt, the dagger slides out. The blade is rusted and stained with blood.
 But a blade nonethess. "You equipped the (1-3) of Diamonds."

4-6: Old Sword
You find, slumped against the wall, the skeleton of a long-dead adventurer. 
 His armor now a leather coffin, laid to rest with sword still in hand.
 You take the blade. Its edge dull, yet enough heft to cleave a limb or two.
 "You equipped the (4-6) of Diamonds."
7-9: Royal Sword
 
10: Lost Knight's Sword
 You could barely call it a sword. The weapon is colossal- 
nearly your height, chipped and blackened by time.

Yet even dulled, its iron hums with weight and finality.

HEALING POTIONS
1-3: Minor healing
4-6: Moderate healing
7-9: Major healing
10: Altar/Fountain of Healing

Heal Messages (4 unique messages)
Minor Heal (1-3 Heal): 
"You drink the healing potion, and a mild warmth spreads through your body.
 The aches and pains dull, but it's not enough to fully restore your strength."

Moderate Heal (4-6 Heal):
"The healing potion goes down smooth, and you feel a surge of energy.
 Your wounds start to close, and your body regains some of its strength."

Major Heal (7-9 Heal): 
"You drink the potion, and a rush of warmth floods your system. 
 Your body feels revitalized, your wounds nearly gone. 
 You're back on your feet, stronger than before."

Altar of Healing (10 Heal): 
"You kneel before the altar, and a golden light envelops you.
 Your wounds vanish completely, and you feel an overwhelming sense
 of peace and vitality course through your body."

🍵 1–3: Minor Heal — "Tincture of Herbs"
A faint trail of dried blood leads to a collapsed figure slumped against the wall.
Beside them lies a leather satchel, torn open, its contents spilled across the floor.
Among broken vials and shattered glass, one small bottle remains intact—
a tincture of herbs, bitter on the tongue but potent enough to dull the pain.

You drink it. Warmth spreads through your limbs. The worst of your wounds begin to knit.

🧪 4–6: Moderate Heal — "Bandaged Cache"
You stumble upon a makeshift camp tucked behind a fallen pillar.
The fire’s long gone cold, but a canvas pack rests beneath a stone altar,
filled with dusty bandages, dried poultices, and a sealed waterskin.

You patch yourself up, the scent of herbs and ash lingering in the air.
It's not elegant, but it’ll hold. You feel steadier.

🕯️ 7–9: Major Heal — "Sanctuary Shrine"
A narrow corridor opens into a small sanctuary—walls carved with sigils of peace and healing.
Melted candlewax pools beneath cracked sconces, and a statue of a forgotten goddess watches silently.
At her feet, offerings lie untouched: healing salves, linen wrappings, and a basin of clean water.

You kneel, and tend to your wounds. The room hums with stillness,
as if the air itself wills your body to mend.

⛪ 10: Altar of Healing — "The Font Eternal"
You descend into a vaulted chamber, the stonework untouched by time.
Braziers flicker with pale blue flame, casting long shadows over intricate murals—
scenes of warriors blessed, restored, reborn.

At the center stands a marble font filled with shimmering water.
As your hands cup the liquid, it glows faintly—cool and luminous.

You drink deeply. Light floods your body. Every wound closes.
For a moment, it feels as if death itself would hesitate.



FACING MONSTERS
1-3: Small creature
4-6: Medium creature
7-9: Large Creature
10, Jack, Queen, King, Ace

Code for Drawing Rooms:

myDeck.shuffle();
myDeck.drawCards(4);
if (card.suit == "Clubs" || card.suit == "Spades") { // assign card value to Monster(); i++}
else if (card.suit == "Diamonds) { // assign card value to Weapon(); i++}
else if (card.suit == "Hearts") { // assign card value to Potion(); i++}
}


cout << "You drew " << printHand.myHand << endl;
ENTER ROOM? [1] RUN AWAY? [2]

//Run option selected: You skipped the room, shuffling cards...
//Drawing new room...
//Enter option selected: You enter the room..

----------------- ROOM 1 ----------------- 

[1] FIGHT A MONSTER : Rank " of " Suit (i.e "14")
[2] EQUIP A WEAPON  : Rank " of " Suit (i.e "5")
[3] DRINK A POTION  : Rank " of " Suit (i.e "10")
[4] <PRINT MESSAGE> : <CARD NAME> (<CARD VALUE)>

FACE A TRIAL: 2

"You walk into..." // Event message
"You equipped the <CARD> of Diamonds."

                  ROOM 1
[1] FIGHT A MONSTER : Rank " of " Suit (i.e "14")
[2] --COMPLETED-- 
[3] DRINK A POTION  : Rank " of " Suit (i.e "10")
[4] <PRINT MESSAGE> : <CARD NAME> (<CARD VALUE)>

When int trial = 3,

*/

/**
 * ====================== Update Log ======================
 * - [2025-03-19] - File created
 * -    Debugged and compiled working prototype
 * -    Implemented game functions: runCombat(), runEquip(), runHeal()
 *
 * ====================== To Do ======================
 * -    Encapsulate game logic into separate functions: createRoom(), printRoom(), encounterMenu()...
 * -    Create proper input validation for choices
 * -    Display Player HP
 * 
 * ====================== Known Bugs ======================
 * - [2025-03-20]
 * -    Game skipping room when typing "1" - FIXED: Swapped logic
 * -    Game prompts "enter room" after each encounter
 *      -   Fix so "Enter Room" only prompts at the start of a new Room
 * -    Game ends prematurely after three encounters
 *      -   Fix while (encounter < 3) logic, so after 3 encounters, build new Room
 */
#include "game.h"


int main() 
{
    // Initialization
    Player player("Player"); // Player object
    Game game(player); // Game object
    Deck myDeck; // Deck object

    myDeck.shuffle();
    vector<Card> discardPile;
    int room = 1;
    int encounter = 0;
    int choice = -1;
    bool skipFlag = false; // Flips true if last room was skipped 

while (myDeck.getDeck().size() > 0 && player.getHP() > 0)
{
    // Draw cards, then populate menu [1-4] with hand
    vector<Card> myHand = myDeck.drawCard(4);

    while (encounter < 3) 
    {
        cout << "You drew: \n\n";
        for (int i = 0; i < myHand.size(); i++)
        {
            Card& card = myHand[i];
            cout << "[ " << i + 1 << " ] " << card.name << "\n";
        }
        cout << endl;

        // Room choice menu
        do {
            cout << "[1] ENTER ROOM? ";
            if (!skipFlag) { cout << "[2] RUN AWAY? "; } 
            cout << "[0] QUIT GAME?" << endl;
            cin >> choice;
            cout << endl;
            
            if (cin.fail()) { // Input validation block
                cin.clear();
                while (cin.get() != '\n'); 
                cout << "Invalid input. Please enter 1 or 2." << endl;
            } else { cin.get(); }
        } while (choice < 0 || choice > 2);  
        
        // Room choice selection
        if (choice == 0) { cout << "Quitting program."; return 0;} // Quit option
        else if (choice == 1) // Enter option selected:
        {
            room++;
            cout << "You enter the room.\n\n";
            cout << setfill('-') << setw(10) << ""
                << " ROOM " << room << " "
                << setw(10) << "" << setfill(' ') << endl;

            for (int i = 0; i < myHand.size(); i++)
            {
                Card& card = myHand[i];
                string action;

                if (card.suit == "Clubs" || card.suit == "Spades") { action = "FIGHT A MONSTER"; }
                else if (card.suit == "Diamonds") { action = "EQUIP A WEAPON"; }
                else if (card.suit == "Hearts") { action = "DRINK A POTION"; }
                else { action = "--COMPLETED--"; }

                cout << "[ " << i + 1 << " ] " << left << setw(16) << action << " : "
                    << card.name << "(" << card.value << ")\n";
            }
        } 
        else if (choice == 2) // Run option selected:
        {
            cout << "You skipped the room, shuffling cards...\n"
                << "Drawing new room...\n";
            myDeck.addCard(myHand);
            myHand = myDeck.drawCard(4);
        }
        

        // Prompt choice
        do {
            cout << "Choose an encounter: ";
            cin >> choice;
            cout << endl;

            if (cin.fail()) { // Input validation block
                cin.clear();
                while (cin.get() != '\n'); 
                cout << "Invalid input. Please enter 1 or 2." << endl;
            } else { cin.get(); }
            
        } while (choice < 1 || choice > 4);

        // Given chosen Card, construct object from Card and run the appropriate encounter
        Card& chosenCard = myHand[choice - 1];

        runEncounter(game, chosenCard);

        // Move chosen card to discard pile after resolving encounter
        encounter++;
        discardPile.push_back(chosenCard);
        myHand.erase(myHand.begin() + (choice - 1));
        
        if (encounter % 3 == 0)
        { 
            myHand = myDeck.drawCard(3);
            room++;
        }
    }
}
    cout << "Game Over." << endl; // TO DO: Make proper ending
    return 0;
}

/* How to implement weapon durability mechanic?
- 1. When equipped, a weapon's durability isn't set.

- 2. When attacking with a weapon for the first time,
- its durability becomes equal to the target monster's attack value.

- 3. Once set, you can only attack monsters with an attack value lower
- than your weapon's current durability score.

- 4. Subsequent attacks will set your weapon's durability score equal
- to the target monster's attack value.alignas

- When you attack a monster with a weapon for the first time, it will gain a durability
- score equal to the monster's attack value. After this, you can only target monsters
- with an attack lower than the current durability. Future attacks will set durability score
- to the target monster's attack lower until: either "breaking" at durability 2 or until you
- equip a new weapon.

PSEUDOCODE:
if (monster.getAtk() >= weapon.getDurability) 
{ cout << "[1] EQUIP WEAPON (Take " << full << " damage)\n"}
else { cout << "[1] EQUIP WEAPON (Take " << reduced << " damage)\n"}

damage -= useWeapon ? weapon.getAtk : 0

Player::displayPlayerStatus(const Player& player)
Player::displayPlayerStatus()
{
    cout << "[HP: " << player.getHP() << "/20" << " | " 
         <<  "[Weapon: " << weapon.getName() << " " << "(Durability: " << weapon.getDurability() << " ]\n";
}


int getWeaponDurability() { return weapon.getDurability(); }
string getWeaponName() { return weapon.getName(); }
*/

void displayRoom(const vector<Card>& myHand)
{
    cout << "You drew: \n\n";

    for (int row = 0; row < 5; row++)
    {
        for (int i = 0; i < myHand.size(); i++)
        {   
            const Card& card = myHand[i];
            if (row == 0) { cout << " --------- "; }
            else if (row == 1) { cout << "| " << card.value << "A" << " |"; }
            else if (row == 2 || row == 3) { cout << "|         |"; }
            else { cout << " ---------- "; }

            if (i < myHand.size()) { cout << "  "; }
        }
        cout << endl;
    }

    
    for (int i = 0; i < myHand.size(); i++)
    {
        const Card& card = myHand[i];
        cout << "[" << i + 1 << "] " << card.name << "\n";
    }
}

/*
--------------------------------------------------

You drew: 

 ---------    ---------    ---------    ---------   
|2♥       |  |10♦      |  |J♣       |  |4♠       |  
|         |  |         |  |         |  |         |  
|    ♥    |  |    ♦    |  |    ♣    |  |    ♠    |  
|         |  |         |  |         |  |         |  
|       2♥|  |      10♦|  |       J♣|  |       4♠|  
 ---------    ---------    ---------    ---------   

 ---------    ---------    ---------    ---------   
|---------|  |XXXXXXXXX|  |||||||||||  |.........|  
|---------|  |XXXXXXXXX|  |||||||||||  |.........|  
|---------|  |XXXXXXXXX|  |||||||||||  |.........|  
|---------|  |XXXXXXXXX|  |||||||||||  |.........|  
|---------|  |XXXXXXXXX|  |||||||||||  |.........|  
 ---------    ---------    ---------    --------- 

 string empty = R"(
 ---------   
|---------| 
|---------| 
|---------| 
|---------| 
|---------|
 --------- )";

[1] Two of Hearts
[2] Ten of Diamonds
[3] Jack of Clubs
[4] Four of Spades

--------------------------------------------------

 ---------    ---------    ---------    ---------   
|3♣       |  |3♠       |  |Q♣       |  |6♠       |  
|         |  |         |  |         |  |         |  
|    ♣    |  |    ♠    |  |    ♣    |  |    ♠    |  
|         |  |         |  |         |  |         |  
|       3♣|  |       3♠|  |       Q♣|  |       6♠|  
 ---------    ---------    ---------    ---------   
    [1]          [2]          [3]          [4]      

 */

 void displayCard(const Card& card)
 {
    // Given a card, use 7 rows to print a text version of it
    CardDisplay cardFace = getCardDisplay(card);
    string displayValue = cardFace.displayValue;
    string symbol = cardFace.symbol;
    string topRow, bottomRow = " -------- " + '\n';
    string middleRow = "|    " + symbol + "    |" + '\n';
    string emptyRow = "|         |" + '\n';
    string leftCorner = card.value == 10 ? "|" + displayValue + symbol +  "      |" + '\n' :
                                      "|" + displayValue + symbol +  "       |" + '\n';

    string rightCorner = card.value == 10 ? "|      " + displayValue + symbol + "|" + '\n':
                                       "|       " + displayValue + symbol + "|" + '\n';
   

    string asciiCard = topRow + leftCorner + emptyRow + middleRow + emptyRow + rightCorner + bottomRow;

    cout << asciiCard << endl;
 }

 /*
 >>> You enter the room. Your torch burns bright

 >>> A cold breeze sweeps through the entrance. Old moss clinging to the cobblestone walls.
 >>> You shudder and inhale, the air thick with the scent of mold and decay.

 >>> You enter the room.

 >>> Your footsteps kick up dust. 

 >>> You glance down a hallway. In a far-off corner, a pair of eyes pierce at you. 
 >>> Footsteps scurrying about.
 */

 void printBanner(const string& message)
 {
    int textLength = message.length();
    int width = (textLength % 2 == 0) ? 50 : 49; 
    int innerWidth = width - textLength - 2;
    string padding = (textLength % 2 == 0) ? string(innerWidth / 2, ' '): string(innerWidth / 3, ' ');
    string borderRow = "+" + string(innerWidth, '=') + "+\n";
    string middleRow = "|" + padding + message + padding + "|\n";

    cout << borderRow << middleRow << borderRow;
 };

 /**
  * SCOUNDREL: A Solo Card-Based Dungeon Crawl
  * 
  * Goal:
  * Scoundrel is a single-player game where you explore a dungeon created by
  * a deck of cards. Each room is formed by drawing cards from the deck, which
  * could be a monster, weapon, or potion card. You must battle monsters, equip
  * weapons, and manage your health to surive. Your goal is to complete all the 
  * rooms (depleting all cards from the deck) and survive the dungeon!
  * ----------------------------------------------
  * 
  * Setup:
  * - Use a standard 52-card deck (red face cards and Aces are removed).
  * - You start with 20 health points.
  * - The deck forms the dungeon. Each room is made up of 4 cards dealt face up.
  * - Select 3 cards to play to complete the room. The last card is kept for the next room.
  * - You choose to skip a room. The game will put all 4 cards back in the deck and deal a new hand.
  * - You can skip as many times as you want, but cannot skip twice in a row.
  * 
  * ----------------------------------------------
  * Card Values:
  * - Number cards are valued at their face value (e.g., 2♣ = 2, 3♠ = 3).  
  * - Face cards: Jack = 11, Queen = 12, King = 13, Ace = 14.
  * 
  * Monsters
  * - Clubs and Spades are monsters that deal damage equal to their value (2-14).
  * - When a monster appears in a room, you'll see its value, and must choose how to fight it.
  * 
  * Weapons
  * - Diamonds are weapons.
  * - Only equip one weapon at a time. When a new weapon is equipped, it replaces the old one.
  * - A weapon can only attack a monster weaker than the last monster it defeated.
  * - If you equip a weapon, you can use it to reduce damage from a monster's attack.
  * 
  * Health Potions
  * - Hearts are health potions.
  * - You consume **one** potion per room to heal.
  *     - This first potion restores health based on its value (e.g., 2♥ = +2 health).
  *     - Additional potions consumed in the same room will have no effect.
  * 
  * ----------------------------------------------
  * Combat
  * - When you select a monster to fight in a room, you enter combat.
  * - You'll automatically defeat the monster, but you will take damage.
  * - For example, if you face the Jack of Clubs (11 damage), you must choose how to fight:
  *     - No weapon? Fight barehanded and take full damage = monster's damage.
  *     - With a weapon, subtract the weapon's attack from the monster's damage.
  * 
  * - After defeating a monster, your weapon's durability will decrease.
  * - It can no longer fight monsters with an attack equal or greater to the last monster fought the weapon.
  * 
  * ----------------------------------------------
  * Winning:
  * - Complete all rooms in the dungeon to win.
  * - If your health drops to 0, the dungeon defeats you. Try again!
  * 
  */

  
  SCOUNDREL: A Solo Card-Based Dungeon Crawl\n\n
   
  Goal:\n
  Scoundrel is a single-player game where you explore a dungeon created by\n
  a deck of cards. Each room is formed by drawing cards from the deck, which\n
  could be a monster, weapon, or potion card. You must battle monsters, equip\n
  weapons, and manage your health to surive. Your goal is to complete all the\n
  rooms (depleting all cards from the deck) and survive the dungeon!\n
  ----------------------------------------------\n\n

  Setup:\n
  - Use a standard 52-card deck (red face cards and Aces are removed).\n
  - You start with 20 health points.\n
  - The deck forms the dungeon. Each room is made up of 4 cards dealt face up.\n
  - Select 3 cards to play to complete the room. The last card is kept for the next room.\n
  - You choose to skip a room. The game will put all 4 cards back in the deck and deal a new hand.\n
  - You can skip as many times as you want, but cannot skip twice in a row.\n\n
  
  ----------------------------------------------\n
  Card Values:\n
  - Number cards are valued at their face value (e.g., 2♣ = 2, 3♠ = 3).\n  
  - Face cards: Jack = 11, Queen = 12, King = 13, Ace = 14.\n\n
  
  Monsters\n
  - Clubs and Spades are monsters that deal damage equal to their value (2-14).\n
  - When a monster appears in a room, you'll see its value, and must choose how to fight it.\n\n
 
  Weapons\n
  - Diamonds are weapons.\n
  - Only equip one weapon at a time. When a new weapon is equipped, it replaces the old one.\n
  - A weapon can only attack a monster weaker than the last monster it defeated.\n
  - If you equip a weapon, you can use it to reduce damage from a monster's attack.\n\n
  
  Health Potions\n
  - Hearts are health potions.\n
  - You consume **one** potion per room to heal.\n
        - This first potion restores health based on its value (e.g., 2♥ = +2 health).\n
        - Additional potions consumed in the same room will have no effect.\n\n
 
  ----------------------------------------------\n
  Combat\n
  - When you select a monster to fight in a room, you enter combat.\n
  - You'll automatically defeat the monster, but you will take damage.\n
  - For example, if you face the Jack of Clubs (11 damage), you must choose how to fight:\n
        - No weapon? Fight barehanded and take full damage = monster's damage.\n
        - With a weapon, subtract the weapon's attack from the monster's damage.\n\n
  
  - After defeating a monster, your weapon's durability will decrease.\n
  - It can no longer fight monsters with an attack equal or greater to the last monster fought the weapon.\n\n

  ----------------------------------------------\n
  Winning:\n
  - Complete all rooms in the dungeon to win.\n
  - If your health drops to 0, the dungeon defeats you. Try again!\n
  
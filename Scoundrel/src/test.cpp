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
 

HEALING POTIONS
1-3: Minor healing
4-6: Major healing
7-9: Altar
10: Fountain

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

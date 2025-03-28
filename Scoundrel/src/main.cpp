/**
 * ====================== Update Log ======================
 * - [2025-03-24]
 * -    Game now removes cards from deck to fit with Scoundrel rules
 * -    Game now tracks player death and triggers game over properly
 * -    Game now tracks skip room logic properly and prevent invalid inputs
 * -    FIXED: Invalid inputs still being processed during encounter and room choices
 * -    FIXED: Game crashing after skipping rooms or choosing an encounter out-of-bounds
 * - [2025-03-23]
 * -    Implemented new game functions printEncounter() and message() for outputting text descriptions
 * -    FIXED: Issue where combat displays negative damage
 * -    Updated game loop logic to fix multiple bugs:
 *      -   FIXED: Game would display "enter room" after every encounter
 *      -   FIXED: Rooms wouldn't increment properly after displayRoom()
 *      -   FIXED: Choosing an encounter would always result with first option being run
 * 
 * - [2025-03-22]
 * -    Solved ANNOYING 'extra draw' bug by adding hand.clear() to drawCard()
 * -    Refactored while (encounters < 3) to for loop, using encounter as the iterator
 *      -   Encounter is now declared with the for loop
 *      -   Room skip logic now breaks inner for loop by setting encounter = 3
 *      -   Draw new room logic doesn't use encounter conditional anymore
 * -    Updated new room logic to not need tempHand vector, improving clarity
 *     
 * - [2025-03-20]
 * -    Implemented new helper functions from game.h: 
 *      -   displayRoom(), promptRoom(), promptEncounter(), getRoomChoice(),
 *      -   enterRoom(), skipRoom(), runEncounter(), clearInput()
 * 
 * - [2025-03-19] - File created
 * -    Debugged and compiled working prototype
 * -    Implemented game functions: runCombat(), runEquip(), runHeal()
 *
 * ====================== To Do ======================
 * -    DONE: Encapsulate game logic into separate functions: createRoom(), printRoom(), encounterMenu()...
 * -    DONE: Create proper input validation for choices
 * -    Display Player HP
 * -    DONE: Adjust card values: J = 11, Q = 12, K = 13, A = 14
 * -    DONE: Implement weapon durability mechanic
 * -    Create a way for player to access discard pile to see what cards they've already completed:
 *      -   Example:
 *      -   Encounters completed: <discardPile.size()>      Cards left in dungeon: <myDeck.getDeck().size()>
 * -    -   Diamonds (1/10 found)
 *      -   card1...
 *      -   Hearts (0/10 found)
 *      -   ...
 *      -   Clubs (2/13 fought)
 *      -   card1, card2...
 *      -   Spades  (4/13 fought)
 *      -   card1, card2, card3, card4...
 * 
 * ====================== Known Bugs ======================
 * 
 * ====================== Fixed Bugs :D ======================
 * -    FIXED: When choosing encounter, valid input only selects option [1]
 * -    FIXED: Game prompts "enter room" after each encounter
 *      -   "Enter Room" only prompts at the start of a new RoomFIXED: Game draws 8 cards after attempting to build new room, after 3 encounters
 *      -   Issue was within drawCard() logic; function saved the previous hand size
 *      -   without clearing it, thus drawing 7 cards total (4 from starting hand + 3 from new hand)
 * -    FIXED: Game skipping room when typing "1"
 *      -   Swapped logic between (choice == 1) and (choice == 2)
 * -    FIXED: Game ends prematurely after three encounters
 *      -   Change inner game-loop logic, so, after 3 encounters, correctly builds a new Room
 */
#include "game.h"

int main() 
{

// cout << "WELCOME TO SCOUNDREL << endl;"
/* cout << "[1] PLAY"
        << "[2] TUTORIAL"
        << "[3] QUIT"
cin << choice;
switch (choice) {
    case 1: break;
    case 2: cout << message("tutorial", 1) << endl;
    case 3: cout << "Quitting game.." << endl; return 0;
    default: cout << "Debug: Choice loop failed."
}

==============================================*/
//gameMenu() or menuGame()
int choice = -1;
do {
    cout << "WELCOME TO SCOUNDREL" << endl;
    cout << "[1] PLAY " << "[2] TUTORIAL " << "[3] QUIT \n";
    cin >> choice;
    switch (choice) {
        case 1: break;
        case 2: cout << message("tutorial", 1) << "\n\n"; break;
        case 3: cout << "Quitting game.." << endl; return 0; 
    } 
} while (choice < 1 || choice > 3);

    Player player("Player"); // Player object
    Game game(player); // Game object
    Deck myDeck; // Deck object
    myDeck.remove();
    // Debug statement - myDeck.printDeck(); 

    myDeck.shuffle();
    vector<Card> discardPile;
    vector<Card> myHand = myDeck.drawCard(4); // Draws the starting hand
    
    int room = 1;
    choice = -1;
    bool skipFlag = false; // Flips true if last room was skipped 
    

while (myDeck.getDeck().size() > 0 && player.getHP() > 0)
{   
    
    for (int encounter = 0; encounter < 3; encounter++)
    {
        displayRoom(myHand); // Populates menu with hand as options [1-4]
        cout << "Deck size after draw: " << myDeck.getDeck().size() << endl; // Debug statement
        cout << endl;

        choice = getRoomChoice(skipFlag); // Room choice menu
        

        if (choice == 0) { cout << "Quitting program."; return 0; } // Quit option selected
        else if (choice == 2 && !skipFlag) { skipRoom(myDeck, myHand); skipFlag = true; encounter = 3; } // Run option selected
        else if (choice == 1) // Enter option selected
        {
            skipFlag = false;
            while (myHand.size() > 1)
            {
                enterRoom(room, myHand); 
                int cardChoice = promptEncounter(myHand.size()); // Prompt player to choose an encounter
                Card chosenCard = myHand[cardChoice - 1]; // Construct card from choice
                runEncounter(game, chosenCard); // Run appropriate encounter from card
                if (player.getHP() <= 0) { break; }
    
                myHand.erase(myHand.begin() + (cardChoice - 1));
                discardPile.push_back(chosenCard); // Move chosen card to discard pile after resolving encounter
                encounter++;
                
            } 
            room++;
        } 
        if (player.getHP() <= 0) { break; }
    }
    if (player.getHP() <= 0) { break; }
    if (myDeck.getDeck().size() > 0)
    { 
        Card firstCard = myHand[0]; // Preserve last card as first card in next hand
        myHand.clear();
        myHand = myDeck.drawCard(3);
        myHand.insert(myHand.begin(), firstCard);
    }
}
    cout << "Game Over." << endl; // TO DO: Make proper ending
    return 0;
}



/**
 * ====================== Update Log ======================
 * - [2025-03-22]
 * -    Solved ANNOYING 'extra draw' bug by adding hand.clear() to drawCard()
 * -    Refactored while (encounters < 3) to for loop, using encounter as the iterator
 *      -   Encounter is now declared with the for loop
 *      -   Room skip logic now breaks inner for loop by setting encounter = 3
 *      -   Draw new room logic doesn't use encounter conditional anymore
 * -    Updated new room logic to not need tempHand vector, improving clarity
 * -    
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
 * -    Encapsulate game logic into separate functions: createRoom(), printRoom(), encounterMenu()...
 * -    Create proper input validation for choices
 * -    Display Player HP
 * 
 * ====================== Known Bugs ======================
 * - [2025-03-20]
 * -    FIX: Game prompts "enter room" after each encounter
 *      -   "Enter Room" only prompts at the start of a new Room
 * 
 * ====================== Fixed Bugs :D ======================
 * -    FIXED: Game draws 8 cards after attempting to build new room, after 3 encounters
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
    Player player("Player"); // Player object
    Game game(player); // Game object
    Deck myDeck; // Deck object

    myDeck.shuffle();
    vector<Card> discardPile;
    vector<Card> myHand = myDeck.drawCard(4); // Draws the starting hand
    
    int room = 0;
    int choice = -1;
    bool skipFlag = false; // Flips true if last room was skipped 

while (myDeck.getDeck().size() > 0 && player.getHP() > 0)
{   

    for (int encounter = 0; encounter < 3; encounter++)
    {
        displayRoom(myHand); // Populates menu [1-4] with hand
        cout << endl;

        choice = getRoomChoice(skipFlag); // Room choice menu
        

        if (choice == 0) { cout << "Quitting program."; return 0; } // Quit option selected
        else if (choice == 1) { enterRoom(room, myHand); room++; } // Enter option selected
        else if (choice == 2) { skipRoom(myDeck, myHand); encounter = 3; }// Run option selected

    
        promptEncounter(); // Prompt choice
        Card& chosenCard = myHand[choice - 1]; // Construct card from choice
        runEncounter(game, chosenCard); // Run appropriate encounter from card
 
        myHand.erase(myHand.begin() + (choice - 1));
        discardPile.push_back(chosenCard); // Move chosen card to discard pile after resolving encounter
    }
    
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

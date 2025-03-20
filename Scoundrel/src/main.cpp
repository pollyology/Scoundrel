/**
 * ====================== Update Log ======================
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
 * -    Game draws 8 cards after attempting to build new room, after 3 encounters
 *      -   FIX: Update lines 49-58 to properly clear hand and draw room with 4 cards
 * -    Game skipping room when typing "1"
 *      -   FIXED: Swapped logic between (choice == 1) and (choice == 2)
 * -    Game prompts "enter room" after each encounter
 *      -   FIX: "Enter Room" only prompts at the start of a new Room
 * -    Game ends prematurely after three encounters -
 *      -   FIXED: Change while (encounter < 3) logic, so after 3 encounters, build new Room
 *      -   FIXED: Game stops ending early and builds room, but build doesn't work
 */
#include "game.h"

int main() 
{
    Player player("Player"); // Player object
    Game game(player); // Game object
    Deck myDeck; // Deck object

    myDeck.shuffle();
    vector<Card> discardPile;
    vector<Card> myHand;
    vector<Card> tempHand;
    
    int room = 0;
    int encounter = 0;
    int choice = -1;
    bool skipFlag = false; // Flips true if last room was skipped 

while (myDeck.getDeck().size() > 0 && player.getHP() > 0)
{   
    if (encounter == 0) { myHand = myDeck.drawCard(4); } 
    else if (encounter == 3)
    { 
        tempHand.push_back(myHand[0]);
        myHand.clear();
        myHand = myDeck.drawCard(3);
        myHand.insert(myHand.begin(), tempHand[0]);
        tempHand.clear();
        encounter = 0;
    }

    while (encounter < 3) 
    {
        displayRoom(myHand); // Draw cards, then populate menu [1-4] with hand
        cout << endl;

        choice = getRoomChoice(skipFlag); // Room choice menu
        

        if (choice == 0) { cout << "Quitting program."; return 0; } // Quit option selected
        else if (choice == 1) { enterRoom(room, myHand); room++; } // Enter option selected
        else if (choice == 2) { skipRoom(myDeck, myHand); encounter = 0; }// Run option selected

    
        promptEncounter(); // Prompt choice
        Card& chosenCard = myHand[choice - 1]; // Construct card from choice
        runEncounter(game, chosenCard); // Run appropriate encounter from card
        encounter++; // Keep track of resolved encounters
 
        myHand.erase(myHand.begin() + (choice - 1));
        discardPile.push_back(chosenCard); // Move chosen card to discard pile after resolving encounter
    }
}
    cout << "Game Over." << endl; // TO DO: Make proper ending
    return 0;
}
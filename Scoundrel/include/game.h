#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "player.h"
#include "monster.h"
#include "items.h"

class Game
{
  public: 
    Game(Player& p) : player(p) {}
    void runCombat(const Monster& m);
    void runEquip(const Weapon& w);
    void runHeal(const Potion& p);

  private:
    Player& player;  
};

// Input Handling
int promptRoom(const bool& skipFlag);
int getRoomChoice(const bool& skipFlag);
int promptEncounter();
void clearInput();

// Game Flow
void enterRoom(int& room, const vector<Card>& myHand);
void skipRoom(Deck& myDeck, vector<Card>& myHand);
void runEncounter(Game& game, const Card& chosenCard);

// Display/Output
void displayRoom(const vector<Card>& myHand);
void printEncounter(const int& value, const string& type);

// Helper Functions
string message(int value, const string& type);
#endif

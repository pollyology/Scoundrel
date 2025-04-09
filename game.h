#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "player.h"
#include "monster.h"
#include "items.h"

class Game
{
  public: 
    Game(Player& p) : player(p), potionFatigue(false), skipFlag(false) {}
    
    // Game Flow
    void enterRoom(int& room, const vector<Card>& myHand);
    void skipRoom(Deck& myDeck, vector<Card>& myHand);
    void runEncounter(const Card& chosenCard);
    void runCombat(const Monster& m);
    void runEquip(const Weapon& w);
    void runHeal(const Potion& p);
    
    // Setters & Getters 
    void setPotionFatigue(bool state) { potionFatigue = state; }
    void resetPotionFatigue() { potionFatigue = false; }
    void setSkipFlag(bool state) { skipFlag = state; }
    bool getSkipFlag() { return skipFlag; }

    // Input Handling
    int promptRoom();
    int roomMenu();

  private:
    Player& player;
    bool potionFatigue; 
    bool skipFlag; 
};

// Input Handling
int promptEncounter(int availableChoices);
int getMenuChoice(int minChoice, int maxChoice);

// Display/Output
void displayCard(const Card& card);
void displayHand(const vector<Card>& myHand);
void displayRoom(const vector<Card>& myHand);
void printEncounter(const string& type, const int& value);

// Helper Functions
void printBanner(const string& message);
string startMenu();
string message(const string& type, int value);
string welcomeToScoundrel();

#endif
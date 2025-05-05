#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "player.h"
#include "monster.h"
<<<<<<< HEAD
=======
#include "messages.h"
>>>>>>> ed9f8fd (Update project files)
#include "items.h"

class Game
{
  public: 
<<<<<<< HEAD
    Game(Player& p) : player(p), potionFatigue(false), skipFlag(false) {}
    
    // Game Flow
    void handleRoomEncounter(int& room, Player& player, vector<Card>& myHand, vector<Card>& discardPile);
    void enterRoom(int& room, const vector<Card>& myHand);
    void skipRoom(Deck& myDeck, vector<Card>& myHand);
    void runEncounter(const Card& chosenCard);
    void runCombat(const Monster& m);
    void runEquip(const Weapon& w);
    void runHeal(const Potion& p);
    void refreshHand(Deck& deck, vector<Card>& hand);
    void clearEmptyCards(vector<Card>& hand);
    
    // Setters & Getters 
    void setPotionFatigue(bool state) { potionFatigue = state; }
    void resetPotionFatigue() { potionFatigue = false; }
    void setSkipFlag(bool state) { skipFlag = state; }
    bool getSkipFlag() { return skipFlag; }
=======
    Game(Player& p) : m_player(p), m_potionFatigue(false), m_skipFlag(false) {}
    
    // Game Flow
    void handleRoomEncounter(int& t_room, Player& t_player, vector<Card>& t_hand, vector<Card>& t_discardPile);
    void enterRoom(int& room, const vector<Card>& t_hand);
    void skipRoom(Deck& myDeck, vector<Card>& t_hand);
    void runEncounter(const Card& chosenCard);
    void runCombat(const Card& monsterCard);
    void runEquip(const Card& weaponCard);
    void runHeal(const Card& potionCard);
    void refreshHand(Deck& t_deck, vector<Card>& t_hand);
    void clearEmptyCards(vector<Card>& t_hand);
    
    // Setters & Getters 
    void setPotionFatigue(bool state) { m_potionFatigue = state; }
    void resetPotionFatigue() { m_potionFatigue = false; }
    void setSkipFlag(bool state) { m_skipFlag = state; }
    bool getSkipFlag() { return m_skipFlag; }
>>>>>>> ed9f8fd (Update project files)

    // Input Handling
    int promptRoom();
    int roomMenu();

  private:
<<<<<<< HEAD
    Player& player;
    bool potionFatigue; 
    bool skipFlag; 
=======
    Player& m_player;
    bool m_potionFatigue; 
    bool m_skipFlag; 
>>>>>>> ed9f8fd (Update project files)
};

// Input Handling
int promptEncounter(int availableChoices);
int getMenuChoice(int minChoice, int maxChoice);

// Display/Output
<<<<<<< HEAD
void displayCard(const Card& card);
void displayHand(const vector<Card>& myHand);
void displayRoom(const vector<Card>& myHand, Deck& myDeck);
void printEncounter(const string& type, const int& value);

// Helper Functions
void assignCardType(Deck& deck);
bool isPlayerDead(const Player& player);
=======
void displayCard(const Card& t_card);
void displayHand(const vector<Card>& t_hand);
void displayRoom(const vector<Card>& t_hand, Deck& t_deck);
void printEncounter(const string& type, const int& value);
void printMessage(MessageType messageType);

// Helper Functions
string getMessageText(MessageType type);
void assignCardType(Deck& t_deck);
bool isPlayerDead(const Player& t_player);
>>>>>>> ed9f8fd (Update project files)
void pressEnterToContinue();
void clearScreen();
void printBanner(const string& message);
void printHeader(const string& message);
string startMenu();
string message(const string& type, int value);
string welcomeToScoundrel();

#endif
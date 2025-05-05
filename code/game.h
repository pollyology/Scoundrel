#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "player.h"
#include "monster.h"
#include "messages.h"
#include "items.h"

class Game
{
  public: 
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

    // Input Handling
    int promptRoom();
    int roomMenu();

  private:
    Player& m_player;
    bool m_potionFatigue; 
    bool m_skipFlag; 
};

// Input Handling
int promptEncounter(int availableChoices);
int getMenuChoice(int minChoice, int maxChoice);

// Display/Output
void displayCard(const Card& t_card);
void displayHand(const vector<Card>& t_hand);
void displayRoom(const vector<Card>& t_hand, Deck& t_deck);
void printEncounter(const string& type, const int& value);
void printMessage(MessageType messageType);

// Helper Functions
string getMessageText(MessageType type);
void assignCardType(Deck& t_deck);
bool isPlayerDead(const Player& t_player);
void pressEnterToContinue();
void clearScreen();
void printBanner(const string& message);
void printHeader(const string& message);
string startMenu();
string message(const string& type, int value);
string welcomeToScoundrel();

#endif
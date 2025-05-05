#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct Card
{
    string name;
    string suit;
    string type;
    int value;

    Card(string n, string s, int v) : name(n), suit(s), type(""), value(v) {}
    Card(string empty) : name{"empty"}, suit("empty"), type("empty"), value{0} {}
};

struct CardDisplay
{
    string displayValue;
    string symbol;
};

CardDisplay getCardDisplay(const Card& card);

class Deck
{
public:
    Deck() { fillDeck(); };
    void fillDeck();
    void remove();
    void shuffle();
    void addCard(vector<Card>& hand);
    vector<Card>& drawCard(int cards);


    void printDeck();
    void printHand(const vector<Card>& hand);
    void printCard(const Card& card);

    const vector<Card>& getHand() const { return hand; };
    const vector<Card>& getDeck() const { return deck; };
    vector<Card>& getDeck() {return deck; };
    

private:
    vector<Card> deck;
    vector<Card> hand;
};

ostream& operator<<(ostream& os, const Card& card);
ostream& operator<<(ostream& os, const vector<Card>& cards);

#endif
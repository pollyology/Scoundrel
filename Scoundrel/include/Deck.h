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
    int value;

    Card(string n, string s, int v) : name(n), suit(s), value(v) {}
};

class Deck
{
public:
    Deck() { fillDeck(); };
    void fillDeck();
    void shuffle();
    void addCard(const vector<Card>& hand);
    vector<Card>& drawCard(int cards);


    void printDeck();
    void printHand(const vector<Card>& hand);
    void printCard(const Card& card);

    const vector<Card>& getHand() const { return hand; };
    const vector<Card>& getDeck() const { return deck; };

private:
    vector<Card> deck;
    vector<Card> hand;
};

ostream& operator<<(ostream& os, const Card& card);
ostream& operator<<(ostream& os, const vector<Card>& cards);

#endif
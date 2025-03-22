/*
 * ====================== Project ======================
 * Title: Deck.cpp
 * Author: Paul Cagaanan
 * Description: This .cpp file implements a deck of cards with functions
 * to draw, print, and shuffle cards. Using for Scoundrel card game.
 * 
 * ====================== Update Log ======================
 * -[2025-03-22]
 * -    Updated drawCard() to clear hand before draw and added debug statement
 * - [2025-03-20]
 * -    Updated addCard() to use deck.insert() instead of push_back()
 * 
 * - [2025-03-19]
 * -    Fully implemented Deck.cpp into Scoundrel
 * -    Added addCard() for placing cards in hand back into deck
 * 
 * - [2025-03-18]
 * -    Version ready for implementation in Scoundrel
 * -    Updated formatting output for Deck.cpp
 * -    Included <iomanip> in Deck.h
 * 
 * - [2025-03-17]
 * -    Updated documentation for all functions
 * -    Added initial documentation; experimenting w/ Doxygen
 * -    Changed drawCard(); return type to vector<Card>&
 * -    Moved getHand(), getDeck(), and Deck() to Deck.h for readability
 * -    Updated shuffle() to use Fisher-Yates algorithm
 * 
 * - [2025-03-16]
 * -    Downloaded extensions: C/C++, Code Runner, Doxygen
 * -    Fully set-up C++ compiler on VS Code; can run code through g++
 * -    Migrated project from Visual Studio (PC) to VS Code (macOS)
 * 
 * - [2025-03-09]   Project started
 * 
 * ====================== To Do ======================
 * - Updated printing functions to use <iomanip> to improve formatting
 * ================================================================== 
 */

 #include "Deck.h"

 /**
  * @brief Populates the deck with a standard of 52 playing cards.
  * 
  * Creates cards for each combination of suit & rank
  * by assigning appropriate values: suit, name, value.
  */
void Deck::fillDeck()
{
    string suit[4] = { "Clubs", "Spades", "Hearts", "Diamonds" };
    string rank[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    // { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

    for (const string& cardSuit : suit)
    {
        for (int i = 0; i < 13; i++)
        {
            string cardName = rank[i] + " of " + cardSuit;
            int cardValue = (i < 10) ? (i + 1) : 10; // defaults face card value to 10

            deck.push_back({ cardName, cardSuit, cardValue });
        }
    }
}

/**
 * @brief Shuffles deck using Fisher-Yates algorithm.
 * 
 * Fisher-Yates Shuffle: Randomly swaps each card with a card before it
 */
void Deck::shuffle()
{
    srand(42); // Explicitly seeded for testing (to do: replace with time(0))

    for (int i = deck.size() - 1; i > 0; i--)
    {
        int random = rand() % (i + 1);
        swap(deck[i], deck[random]);
    }
}

/**
 * @brief Takes current cards in hand and moves them back into deck.
 * 
 * This function iterates through each card in hand, inserts each element
 * into first position of deck.
 * 
 * @param hand Reference to the hand we want to add back into deck.
 */
void Deck::addCard(vector<Card>& hand)
{
    for (const Card& card : hand) 
    {
        deck.insert(deck.begin(), card);
        this->hand.pop_back();
    }
}

/**
 * @brief Draws cards from deck and moves it into hand.
 * 
 * This function removes cards from top of the deck and places them in player's hand.
 * Ensures if, drawn cards exceeds remaining cards in deck, only remaining cards will be drawn.
 * 
 * @param cards The number of Cards to be drawn from Deck
 * @return vector<Card>& Reference to the hand holding the drawn cards
 * 
 */
vector<Card>& Deck::drawCard(int cards)
{
    hand.clear();
    for (int i = 0; i < cards && !deck.empty(); i++)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }
    cout << "Drew: " << hand.size() << " cards!" << endl; // Debug statement
    return hand;
}

// ====================== Printers ====================== 
//Card, Hand, and Deck

/**
 * @brief Prints the given card.
 * 
 * @param card Reference to a Card
 */
void Deck::printCard(const Card& card)
{
    cout << left << setw(20) << card;
}

/**
 * @brief Prints the given hand of cards.
 * 
 * This function will iterate through all the cards in the hand
 * and print them to the output stream, using printCard() for each card.
 * 
 * @param hand Reference to a vector of Cards
 */
void Deck::printHand(const vector<Card>& hand)
{
    for (const Card& card : hand)
    {
        printCard(card);
    }
}

/**
 * @brief Prints the current cards remaining in the deck.
 * 
 * This function will iterate through all the cards in the deck
 * and print them to the output stream, using printCard() for each card.
 */
void Deck::printDeck()
{   int count = 0;

    for (const Card& card : deck)
    {
        printCard(card);
        count++;
        if (count % 4 == 0) { cout << endl; }
        else { cout << " "; }
    }

}

// ====================== Overloaded Operators ====================== 
// Overloads << for single Card and vector<Card>.
// Needed for printHand() and printDeck() to work.

/**
 * @brief Overloads the << operator to print a Card object.
 * 
 * Allows a Card object to be printed directly to an output stream
 * (such as std::cout) by printing the card's name
 * 
 * @param os The output stream to print to (std::out)
 * @param card The card we want to print
 * @return ostream& Reference to the output stream
 */
ostream& operator<<(ostream& os, const Card& card)
{
    return os << card.name; // For printing just card name; "Ace of Diamonds"
}

/**
 * @brief Overloads the << operators to print multiple Card objects.
 * 
 * Enables printing a vector of Card objects directly to an output stream
 * Each card is printed with a separating comma ", "
 * 
 * @param os The output stream to print to (std::cout)
 * @param cards The card(s) we want to print 
 * @return ostream& Reference to the output stream 
 */
ostream& operator<<(ostream& os, const vector<Card>& cards)
{
    for (int i = 0; i < cards.size(); i++)
    {
        os << cards[i] << ", ";
    }
    return os;
}

#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include <string>

using namespace std;

const string TUTORIAL_MESSAGE = R"(
==========================================
       SCOUNDREL: A Solo Dungeon Crawl
==========================================

Goal:
Explore a dungeon made from a card deck. 
Fight monsters, equip weapons, and use potions.
Survive all rooms to win!

------------------------------------------
Setup:
- Use a 52-card deck (remove red face cards & Aces)
- Start with 20 health
- Each room = 4 cards (play 3, carry 1)
- You can skip a room (but not two in a row)

------------------------------------------
Card Types & Rules:

Clubs ♣ & Spades ♠ = Monster
Diamonds ♦ = Weapon
Hearts ♥ = Potion

[Card Values]
- Number cards: 2 - 10
- Jack = 11, Queen = 12, King = 13, Ace = 14

[Monsters - ♣ ♠]
- Damage = card value

[Weapons - ♦]
- Equip 1 at a time
- Can only attack weaker monsters than last one beaten
- Reduces damage taken

[Potions - ♥]
- Heal = potion value
- Only 1 potion works per room

------------------------------------------
Combat:
- Pick a monster: you win the fight, but take damage
- No weapon = full damage
- Equipped weapon = damage reduced
- Weapon weakens after each use

------------------------------------------
Winning:
- Clear all rooms (deplete the deck)
- If health drops to 0, you lose

==========================================
           GOOD LUCK, SCOUNDREL!
==========================================)";



#endif
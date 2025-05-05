#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include <string>
#include <cctype>

using std::string;

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

// Total unique messages = 50  + 2 (Intro and Ending)
/**
 * ROOM MESSAGES
 * Unique room descriptions for Rooms 1 - 10:
 * 10 unique messages
 */
/**
 * WEAPON MESSAGES
 * Unique weapon descriptions based on attack value: 
 * 1-3 = Rusty Dagger
 * 4-6 = Old Sword
 * 7-9 = Guardsmen Spear
 * 10 = Legendary Sword 
 * 
 * 4 unique messages
 */
/**
 * HEAL MESSAGES
 * Unique healing descriptions based on heal amount:
 * 
 * 1-3 = Minor Heal
 * 4-6 = Moderate Heal
 * 7-9 = Major Heal
 * 10 = Altar of Healing
 * 
 * 4 unique messages
 */
/**
 * MONSTER MESSAGES
 * Unique monster desciptions based on damage value:
 * 1-3 = Small Creature     Slime, Giant Spider
 * 4-6 = Medium Creature    Goblin, Kobold, Orc
 * 7-9 = Large Creature     Ogre, Troll
 * 10  = Undead Knight
 * Jack = 
 * Queen
 * King
 * Ace
 * 
 * 4 generic monster types x 2 variants + 4 unique bosses
 * = 12 unique messages
 */
/**
 
 * COMBAT MESSAGES
 * Unique combat descriptions based on weapon type and damage taken:
 * 
 * WEAPON TYPE
 * 1 = Rusty Dagger
 * 2 = Old Sword
 * 3 = Guardsmen Spear
 * 4 = Knight's Greatsword
 * 
 * DAMAGE TAKEN
 * 0 == Perfect reaction, no damage
 * 1-3 == Slight cut, low damage
 * 4-6 == Considerable gash, moderate damage
 * 7-9 == Severe wounds, high damage
 * 10+ == Near-fatal wound
 * 
 * 4 weapons x 5 damage states = 20 unique messages
 */

const string COMBAT_DAGGER_1 = R"(
You brandish your dagger. Your hand is trembling as
the beast charges towards you, letting out a guttural roar.

A wild swing tears into your side. Warmth and pain blooms.

But, now you're too close to miss.
One precise thrust. The blade sinks deep.

The beast heaves a final gasp... then silence.)";

const string COMBAT_SPEAR_2;
const string COMBAT_BROADSWORD_3;


string toUpperCase(const string& input)
{
       string result = input;
       for (char& ch : result)
       {
              ch = toupper(ch);
       }
       return result;
}

void intro(string& name)
{
       
};

       const string LETTER_1 = R"(
       ------------------------------------------------------------
       DEAR POLLY,

       You owe more than coin.

       The Guild kept you alive when the streets would have swallowed you whole.

       We trained you, armed you, and looked the other way more times than you deserve.

       Now it’s time to pay up.

       The Old Depths have reopened. No one's made it past the first floor in years—
       but there's something down there we need. Something *valuable*. 
       You’ll know it when you see it.

       Make it back alive, and your debt is cleared. Fail, and... 
       well, we’ll consider your silence partial payment.

       Good luck, Scoundrel. You’re going to need it.

       — G
       ------------------------------------------------------------
)";
#endif
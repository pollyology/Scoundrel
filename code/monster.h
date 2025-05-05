/**
 * Author: Paul Cagaanan
 * Description: This header file implements a Monster class that can be attacked by Player.
 * Monster damage reduces Player's HP or can be reduced by Player's attack. Implemented in Scoundrel.
 * 
 * * ====================== Update Log ======================
 * - [2025-03-19]   Updated documentation and code to improve readability
 * 
 */

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>

using namespace std;
/**
  * @brief  Monsters are hostile entities that can reduce the Player's HP to 0, ending the game.
  * Players use Potions and/or Weapons to counteract Monster damage.
  * (Scoundrel) Monsters will take a Card object to set their name and damage.
  * 
  * e.g. A "Six of Spades" Card creates a Monster named "Six of Spades" that deals 6 damage to Player.
  */
class Monster
{
  public:
    Monster(string name, int value) : name(name), atk(value) {}
    string getName() const { return name; };
    int getAtk() const { return atk; }; 
  
  private:
    string name;
    int atk;
};

#endif
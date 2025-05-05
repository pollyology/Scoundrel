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

using std::string;
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
    Monster(string t_name, int t_atk) : m_name(t_name), m_atk(t_atk) {}
    string getName() const { return m_name; };
    int getAtk() const { return m_atk; }; 
  
  private:
    string m_name;
    int m_atk;
};

#endif
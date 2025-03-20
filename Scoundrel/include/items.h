/**
 * Author: Paul Cagaanan
 * Description: This header file implements two classes: Potion and Weapon.
 * Interactable items that affect the Player character. Implemented in Scoundrel.
 * 
 * * ====================== Update Log ======================
 * - [2025-03-19]   Updated documentation and code to improve readability
 * 
 */

 #ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <string>

using namespace std;

 /**
  * @brief  Potions are consumable items that restores the Player's health.
  * (Scoundrel) Potions will take a Card object to set their name and healAmount.
  * 
  * e.g. A "Nine of Hearts" Card creates a Potion named "Nine of Hearts" that restores 9 health.
  */
class Potion
{
  public:
    Potion(string name, int heal) : name(name), healAmount(heal) {}
    string getName() const { return name; };
    int getHealAmount() const { return healAmount; };
    
  private:
    string name;
    int healAmount;
    
};

/**
 * @brief Weapons are equippable items that increase the Player's attack.
 * (Scoundrel) Weapons will take a Card object to set their name and attack power.
 * 
 * e.g. A "Three of Diamonds" Card creates a Weapon named "Three of Diamonds" that sets the Player's attack to 3
 */
class Weapon
{
  public:
    Weapon(string name, int atk) : name(name), atk(atk) {}
    string getName() const { return name; };
    int getAtk() const { return atk; };
    
  private:
    string name;
    int atk;
};

#endif
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

using std::string;

 /**
  * @brief Potions are consumable items that restores the Player's health.
  * (Scoundrel) Potions will take a Card object to set their name and healAmount.
  * 
  * e.g. A "Nine of Hearts" Card creates a Potion named "Nine of Hearts" that restores 9 health.
  */
class Potion
{
  public:
    Potion(string t_name, int t_heal) : m_name(t_name), m_healAmount(t_heal) {}
    string getName() const { return m_name; };
    int getHealAmount() const { return m_healAmount; };
    
  private:
    string m_name;
    int m_healAmount;
    
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
    Weapon() : m_name("None"), m_atk(0), m_durability(0) {}  
    Weapon(string t_name, int t_atk) : m_name(t_name), m_atk(t_atk), m_durability(99)
    {
      setWeaponType(t_atk);
    }

    void setDurability(int t_durability) { m_durability = t_durability; }
    void setWeaponType(int t_atk)
    {   
        if (t_atk <= 3) { m_type = "Dagger"; }
        else if (t_atk <= 6) { m_type = "Sword"; }
        else if (t_atk <= 9) { m_type = "Spear"; }
        else if (t_atk == 10) { m_type = "Claymore"; }
        else { m_type = ""; } 
    };

    string getName() const { return m_name; }
    string getType() const { return m_type; }
    int getAtk() const { return m_atk; }
    int getDurability() const { return m_durability; }
    
  private:
    string m_name;
    string m_type;
    int m_atk;
    int m_durability;
};

#endif
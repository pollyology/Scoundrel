#ifndef PLAYER_H
#define PLAYER_H

#include "items.h"
#include <wchar.h>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>

class Potion;
class Weapon;
class Monster;

using std::string;

class Player
{
  public:
    Player(string t_name);
    void attack(const Monster& monster, bool useWeapon);
    void equip(const Weapon& t_weapon);
    void drink(const Potion& potion, bool fatigue);
    void displayStatus();
 
    int getHP() const { return m_hp; }
    int getMaxHP() const {return m_maxHP; }
    int getAtk() const { return m_atk; }
    int getWeaponAtk() const { return m_weapon.getAtk(); }
    int getWeaponDurability() const { return m_weapon.getDurability(); }
    string getWeaponType() const { return m_weapon.getType(); }
    string getWeaponName() const { return m_weapon.getName(); }
    string getHealthBar() const; 

    
  
  private:
    string m_name;
    int m_maxHP;
    int m_hp;
    int m_atk;
    Weapon m_weapon;
};

#endif


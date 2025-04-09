#ifndef PLAYER_H
#define PLAYER_H

#include "items.h"
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <string>

class Potion;
class Weapon;
class Monster;

using namespace std;

class Player
{
  public:
    Player(string name);
    void attack(const Monster& monster, bool useWeapon);
    void equip(const Weapon& weapon);
    void drink(const Potion& potion, bool fatigue);
    void displayStatus();
 
    int getHP() const { return hp; };
    int getMaxHP() const {return maxHP; }
    int getAtk() const { return atk; };
    int getWeaponAtk() const { return weapon.getAtk(); }
    int getWeaponDurability() const { return weapon.getDurability(); }
    string getWeaponName() const { return weapon.getName(); }
    string getHealthBar() const; 

    
  
  private:
    string name;
    int maxHP;
    int hp;
    int atk;
    Weapon weapon;
};

#endif


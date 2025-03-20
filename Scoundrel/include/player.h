#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Potion;
class Weapon;
class Monster;

class Player
{
  public:
    Player(string name);
    void attack(const Monster& monster, bool useWeapon);
    void equip(const Weapon& weapon);
    void drink(const Potion& potion);
    
    int getHP() const { return hp; };
    int getAtk() const { return atk; };
  
  private:
    string name;
    int hp;
    int atk;
};

#endif
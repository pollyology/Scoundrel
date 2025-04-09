/**
 * Author: Paul Cagaanan
 * Description: This .cpp file implements a player character with functions
 * for attacking monsters, equipping weapons, and using items.
 * Implemented for Scoundrel.
 * 
 * * ====================== Update Log ======================
 * - [2025-03-19]   Updated documentation and code to improve readability
 * 
 */

#include "player.h"
#include "monster.h"
#include "items.h"

using namespace std;
 /**
 * @brief Constructs a Player with a name, 20 HP, and 0 attack.
 * @param name The name of the Player.
 */
Player::Player(string name)
{
  this->name = name;
  maxHP = 20;
  hp = 20;
  atk = 0;
  weapon = Weapon();
}

/**
 * @brief Player attacks a Monster, optionally using their weapon.
 * 
 * If useWeapon is true, the player's weapon attack is subtracted from the damage.
 * If useWeapon is false, the player takes full damage.
 * Uses max() to ensure damage and HP doesn't go below 0.
 * 
 * @param monster The Monster being fought.
 * @param useWeapon Whether the Player uses their weapon in the attack.
 */
void Player::attack(const Monster& monster, bool useWeapon)
{
  int damage = monster.getAtk();
  int durability = weapon.getDurability();
  
  if (useWeapon) { damage -= (durability > monster.getAtk()) ? weapon.getAtk() : atk; }
  else {damage -= atk; }
  weapon.setDurability(monster.getAtk());

  damage = max(damage, 0);                   

  hp -= damage;
  hp = max(hp, 0);
}

/**
 * @brief Heals the Player by drinking a Potion, capped at 20 HP.
 * @param potion The Potion being consumed.
 */
void Player::drink(const Potion& potion, bool fatigue)
{
  if (fatigue) { return; } // If potionFatigue from game.h == true, then potion has no effect
  hp += potion.getHealAmount();
  hp = min(hp, 20);
}

/**
 * @brief Equips a Weapon, updating the Player's attack value.
 * @param weapon The Weapon being equipped.
 */
void Player::equip(const Weapon& weapon)
{ this->weapon = weapon; }

void Player::displayStatus()
{
  int HP = getHP();
  int maxHP = getMaxHP();
  
    cout << "\n==================== " << name << " ====================\n"
         << "[HP: " << HP << "/" << maxHP << "  [" << getHealthBar() << "]\n" 
         << "[Weapon: " << getWeaponName() 
         << " (Durability: " << getWeaponDurability() << ")]\n"
         << "========================================================\n" << endl;
}

string Player::getHealthBar() const
{
  int HP = getHP();
  int maxHP = getMaxHP();
  int maxHearts = 10;
  int heartsLeft = HP / 2;

  const string colorRed = "\033[31m";
  const string reset = "\033[0m";
  const string redHeart = colorRed + "♥" + reset;
  const string emptyHeart = "♥"; 
  string healthBar = "";

  for (int i = 0; i < heartsLeft; i++)
  {
    healthBar += redHeart;
  }

  for (int i = heartsLeft; i < maxHearts; i++)
  {
    healthBar += emptyHeart;
  }

  return healthBar;
}
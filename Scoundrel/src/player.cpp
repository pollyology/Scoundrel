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

 /**
 * @brief Constructs a Player with a name, 20 HP, and 0 attack.
 * @param name The name of the Player.
 */
Player::Player(string name)
{
  this->name = name;
  hp = 20;
  atk = 0;
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
  damage -= useWeapon ? atk : 0;
  damage = max(damage, 0);                   

  hp -= damage;
  hp = max(hp, 0);
}

/**
 * @brief Heals the Player by drinking a Potion, capped at 20 HP.
 * @param potion The Potion being consumed.
 */
void Player::drink(const Potion& potion)
{
  hp += potion.getHealAmount();
  hp = min(hp, 20);
}

/**
 * @brief Equips a Weapon, updating the Player's attack value.
 * @param weapon The Weapon being equipped.
 */
void Player::equip(const Weapon& weapon)
{ atk = weapon.getAtk(); }

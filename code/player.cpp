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
Player::Player(string t_name)
{
  this->m_name = t_name;
  m_maxHP = 20;
  m_hp = 20;
  m_atk = 0;
  m_weapon = Weapon();
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
  int durability = m_weapon.getDurability();
  
  if (useWeapon) 
  { 
    damage -= (durability > monster.getAtk()) ? m_weapon.getAtk() : m_atk;
    m_weapon.setDurability(monster.getAtk());
  }
  else {damage -= m_atk; }
  
  damage = max(damage, 0);                   

  m_hp -= damage;
  m_hp = max(m_hp, 0);
}

/**
 * @brief Heals the Player by drinking a Potion, capped at 20 HP.
 * @param potion The Potion being consumed.
 */
void Player::drink(const Potion& potion, bool fatigue)
{
  if (fatigue) { return; } // If potionFatigue from game.h == true, then potion has no effect
  m_hp += potion.getHealAmount();
  m_hp = min(m_hp, 20);
}

/**
 * @brief Equips a Weapon, updating the Player's attack value.
 * @param weapon The Weapon being equipped.
 */
void Player::equip(const Weapon& t_weapon)
{ this->m_weapon = t_weapon; }

void Player::displayStatus()
{
  int HP = getHP();
  int maxHP = getMaxHP();
  string status = "+================= STATUS ================+";
  int width = status.length() - 4;
  string o_hp = "HP: " + to_string(HP) + "/" + to_string(maxHP) + "  ";
  string o_weapon = "Weapon: " + getWeaponName();
  string o_atk = "Attack: " + to_string(m_weapon.getAtk());
  string o_durability = "(Durability: " + to_string(getWeaponDurability()) + ')';

  if (getWeaponName() == "None") { o_atk = ""; o_durability = ""; }
  if (getWeaponDurability() == 99) { o_durability = ""; }
  int padding = width - (o_atk.length() + o_durability.length());
  string statsDisplay = o_atk + string(padding, ' ') + o_durability;
  
    cout << "+================ STATUS ================+\n";
    cout << "| " << left << setw(width) << m_name << "|\n";
    cout << "| " << o_hp << string(7, ' ') << getHealthBar() << " |\n";
    cout << "| " << left << setw(width) << o_weapon << "|\n";
    cout << "| " << statsDisplay << "|\n";
    cout << "+========================================+\n";
}

string Player::getHealthBar() const
{
  int HP = getHP();
  int maxHP = getMaxHP();
  int maxHearts = 20; // To scale to 10 hearts, set to 10.
  int heartsLeft = HP; // To scale to 10 hearts, set to HP / 2.

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
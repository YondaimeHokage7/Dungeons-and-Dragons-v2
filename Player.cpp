#include <iostream>
#include "Player.hpp"

void Player::initializeStats(const Class& _characterClass)
{
    increaseMaxHealth(MAX_HEALTH);
    switch (_characterClass)
    {
        case Mage:
            increaseIntellect(MAGE_INTELLECT);
            increaseStrength(MAGE_STRENGTH);
            break;
        case Warrior:
            increaseStrength(WARRIOR_STRENGTH);
            increaseIntellect(WARRIOR_INTELLECT);
            break;
    }
}

Player::Player(const Class& _characterClass) : Entity(0, 0, 0), characterClass(_characterClass), weapon("Sword", Weapon, 20), spell("Fireball", Spell, 20), armor("", Nothing, 0)
{
    initializeStats(_characterClass);
}

bool Player::hasWeapon() const
{
    return weapon.getItemType() != Nothing;
}

bool Player::hasSpell() const
{
    return spell.getItemType() != Nothing;
}

bool Player::hasArmor() const
{
    return armor.getItemType() != Nothing;
}

void Player::takeDamage(unsigned int amount)
{
    unsigned int postMitigationDamage{(unsigned int) (amount - (double) armor.getModifier() / 100 * amount)};
    std::cout << "You took " << postMitigationDamage << " damage from this attack\n";
    takeTrueDamage(postMitigationDamage);
}

void Player::basicAttack(Entity& target)
{
    std::cout << "You basic attacked the dragon for " << getStrength() + weapon.getModifier() << '\n';
    target.takeDamage(getStrength() + weapon.getModifier());
}

void Player::castASpell(Entity& target)
{
    std::cout << "You cast a spell that deals " << getIntellect() + spell.getModifier() << " damage\n";
    target.takeDamage(getIntellect() + spell.getModifier());
}

void Player::attack(Entity& target)
{
    std::cout << "How would you like to attack?\n";
    std::string input;
    std::getline(std::cin, input);
    if (input == "basic attack")
    {
        basicAttack(target);
    }
    else if (input == "cast a spell")
    {
        castASpell(target);
    }
}

void Player::levelUp()
{
    unsigned int points{30};
    std::cout << "You leveled up!\n";
    unsigned int strength;
    unsigned int intellect;
    unsigned int maxHealth;
    std::cout << "You can now distribute " << points << " points among your stats\n";
    while (points > 0)
    {
        std::cout << "How many points would you like to add to your strength?\n";
        std::cin >> strength;
        std::cout << "How many points would you like to add to your intellect?\n";
        std::cin >> intellect;
        std::cout << "How many points would you like to add to your max health?\n";
        std::cin >> maxHealth;
        if (strength + intellect + maxHealth > points)
        {
            std::cout << "You cannot spend over " << points << " points!\n";
        }
        else
        {
            points = points - (strength + intellect + maxHealth);
            increaseStrength(strength);
            increaseIntellect(intellect);
            increaseMaxHealth(maxHealth);
        }
    }
}


/*
CSCI235 Fall 2023
Project 2 - Mage Class
Michelle Khanan
September 22 2023
Mage.cpp implements the constructors and member functions of the Mage class.
*/

#include "Mage.hpp"
#include "Character.hpp"

/**
  Default constructor.
  Default-initializes all private members. 
  Default character name: "NAMELESS". Booleans are default-initialized to False. 
  Default school of magic and weapon: "NONE". 
*/
Mage::Mage():Character(), school_of_magic_{"NONE"}, weapon_{"NONE"}, can_summon_incarnate_{false}
{
}

/**
  Parameterized constructor.
  @param      : The name of the character (a const string reference)
  @param      : The race of the character (a const string reference)
  @param      : The character's vitality (an integer). Default to 0
  @param      : The character's max armor level (an integer). Default to 0
  @param      : The character's level (an integer). Default to 0
  @param      : A flag indicating whether the character is an enemy. Default to false.
  @param      : The character's school of magic (a const string reference). Valid schools: 
                [ELEMENTAL, NECROMANCY, ILLUSION]. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the school name is invalid, set it to "NONE"
  @param      : The character's choice of weapon (a const string reference). 
                Valid weapons: [WAND, STAFF]
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the weapon is invalid, set it to "NONE"
  @param      : A flag indicating whether the character is able to summon an 
                incarnate. Default to false.
  @post       : The private members are set to the values of the corresponding 
                parameters.
                REMEMBER: If the school of magic or weapon is not provided or invalid, the 
                variables should be set to "NONE". 
*/

Mage::Mage(const string& name, const string& race, int vitality, int armor, int level, bool enemy, string school_of_magic, string weapon, bool can_summon_incarnate):Character(name, race, vitality, armor, level, enemy)
{
    if (!setSchool(school_of_magic))
    {
        school_of_magic_ = "NONE";
    }
    if (!setCastingWeapon(weapon))
    {
        weapon_ = "NONE";
    }
    can_summon_incarnate_ = can_summon_incarnate;
}

/**
    @param  : a reference to a string representing the school of magic
    @post   : sets the private member variable to the value of the parameter. If 
              the provided school of magic is not one of the following: [ELEMENTAL, 
              NECROMANCY, ILLUSION], do nothing and return false.
              String inputs can be in lowercase, but must be converted to 
              uppercase when setting the variable.
    @return  : true if setting the variable was successful, false otherwise.
**/

bool Mage::setSchool(const string& school_of_magic)
{
    string new_school_of_magic = "";
    for(int i = 0; i<school_of_magic.size();i++)
    {
            new_school_of_magic += toupper(school_of_magic[i]);
    }
    if (new_school_of_magic == "ELEMENTAL" || new_school_of_magic == "NECROMANCY" || new_school_of_magic == "ILLUSION")
    {
        school_of_magic_ = new_school_of_magic;
        return true;
    }
    else
    {
        return false;
    }
}

/**
  @return  : the string indicating the character's school of magic
**/
string Mage::getSchool()const
{
    return school_of_magic_;
}

/**
    @param  : a reference to a string representing the character's weapon
    @post   : sets the private member variable to the value of the parameter.
              String inputs can be in lowercase, but must be converted to 
              uppercase when setting the variable.
              If the provided weapon is not one of the following: 
              [WAND, STAFF], do nothing and return false.
    @return  : true if setting the variable was successful, false otherwise.
**/

bool Mage::setCastingWeapon(const string& weapon)
{
    string new_weapon = "";
    for(int i = 0; i<weapon.size();i++)
    {
            new_weapon += toupper(weapon[i]);
    }
    if (new_weapon == "WAND" || new_weapon == "STAFF")
    {
        weapon_ = new_weapon;
        return true;
    }
    else
    {
        return false;
    }
}

/**
  @return  : the string indicating the character's weapon
**/
string Mage::getCastingWeapon()const
{
    return weapon_;
}

/**
  @param  : a reference to boolean
  @post   : sets the private member variable indicating whether the character can 
            summon an incarnate
**/
void Mage::setIncarnateSummon(const bool& can_summon_incarnate)
{
    can_summon_incarnate_ = can_summon_incarnate;
}

/**
  @return  : the summon-incarnate flag
**/
bool Mage::hasIncarnateSummon()const
{
    return can_summon_incarnate_;
}
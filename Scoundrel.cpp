/*
CSCI235 Fall 2023
Project 2 - Scoundrel Class
Michelle Khanan
September 22 2023
Scoundrel.cpp implements the constructors and member functions of the Scoundrel class.
*/

#include "Scoundrel.hpp"
#include "Character.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default character name: "NAMELESS". Booleans are default-initialized to False. 
    Default dagger: WOOD. Default faction: "NONE". 
*/
Scoundrel::Scoundrel():Character(), dagger_{WOOD}, faction_{"NONE"}, has_disguise_{false}
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
    @param      : The character's dagger type (a const string reference).
                  String inputs can be in lowercase, but must be converted to 
                  uppercase when setting the dagger enum. Default to WOOD
    @param      : The character's Faction (a const string reference). 
                  Valid Factions: [CUTPURSE, SHADOWBLADE, SILVERTONGUE] 
                  String inputs can be in lowercase, but must be converted to 
                  uppercase when setting the variable. Default to "NONE"
    @param      : A flag indicating whether the character has a disguise. Default to false
    @post       : The private members are set to the values of the corresponding 
                  parameters.
                 If the dagger type is not provided or invalid, the variable should 
                  be set to WOOD. 
                 If the Faction is not provided or invalid, the variable should be 
                  set to "NONE". 
*/
Scoundrel::Scoundrel(const string& name, const string& race, int vitality, int armor, int level, bool enemy, string dagger, string faction, bool has_disguise):Character(name, race, vitality, armor, level, enemy)
{
    setDagger(dagger);
    setFaction(faction);
    has_disguise_ = has_disguise;
}

/**
   @param     : a reference to a string representing the dagger type
   @post      : sets the private member variable to the value of the parameter. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the dagger type is not valid (i.e, is one of the following: 
                [WOOD, BRONZE, IRON, STEEL, MITHRIL, ADAMANT, RUNE]), 
                the variable should be set to WOOD. 
**/
void Scoundrel::setDagger(const string& dagger)
{
    string new_dagger = "";
    for(int i = 0; i<dagger.size();i++)
    {
            new_dagger += toupper(dagger[i]);
    }
    if(new_dagger == "WOOD")
    {
        dagger_ = WOOD; 
    }
    else if(new_dagger == "BRONZE")
    {
        dagger_ = BRONZE; 
    }
    else if(new_dagger == "IRON")
    {
        dagger_ = IRON; 
    }
    else if(new_dagger == "STEEL")
    {
        dagger_ = STEEL; 
    }
    else if(new_dagger == "MITHRIL")
    {
        dagger_ = MITHRIL; 
    }
    else if(new_dagger == "ADAMANT")
    {
        dagger_ = ADAMANT; 
    }
    else if(new_dagger == "RUNE")
    {
        dagger_ = RUNE; 
    }
    else
    {
        dagger_ = WOOD;
    }

}

/**
  @return     : the string indicating the character's dagger type
**/
string Scoundrel::getDagger()const
{
    if(dagger_ == WOOD)
    {
        return "WOOD"; 
    }
    else if(dagger_ == BRONZE)
    {
        return "BRONZE"; 
    }
    else if(dagger_ == IRON)
    {
        return "IRON"; 
    }
    else if(dagger_ == STEEL)
    {
        return "STEEL"; 
    }
    else if(dagger_ == MITHRIL)
    {
        return "MITHRIL"; 
    }
    else if(dagger_ == ADAMANT)
    {
        return "ADAMANT"; 
    }
    else if(dagger_ == RUNE)
    {
        return "RUNE"; 
    }
    else
    {
        return "WOOD";
    }
}

/**
    @param    : a reference to a string representing the character's Faction
    @post     : sets the private member variable to the value of the parameter. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the provided faction is not one of the following: 
               [NONE, CUTPURSE, SHADOWBLADE, SILVERTONGUE], 
               do nothing and return false.
    @return   : true if setting the variable was successful, false otherwise.
**/
bool Scoundrel::setFaction(const string& faction)
{
    string new_faction = "";
    for(int i = 0; i<faction.size();i++)
    {
            new_faction += toupper(faction[i]);
    }
    if (new_faction == "NONE" || new_faction == "CUTPURSE" || new_faction == "SHADOWBLADE" || new_faction == "SILVERTONGUE")
    {
        faction_ = new_faction;
        return true;
    }
    else
    {
        return false;
    }
}

/**
  @return  : the string indicating the character's Faction
**/
string Scoundrel::getFaction()const
{
    return faction_;
}

/**
  @param  : a reference to boolean
  @post   : sets the private member variable indicating whether the character has a disguise
**/
void Scoundrel::setDisguise(const bool& has_disguise)
{
    has_disguise_ = has_disguise;
}

/**
  @return  : the visual aid flag
**/
bool Scoundrel::hasDisguise()const
{
    return has_disguise_;
}
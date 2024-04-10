#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <iostream>
#include <string>
#include <cctype> 
using namespace std;

class Character
{
    public:
        enum Race {NONE, HUMAN, ELF, DWARF, LIZARD, UNDEAD};
        Character(); //Default constructor
        Character(const string& name, const string& race, const int& vitality = 0, const int& armor = 0, const int& level = 0, const bool& enemy = false); //Parameterized constructor
        void setName(const string& name);
        string getName()const;
        void setRace(const string& race);
        string getRace()const;
        void setVitality(const int& vitality);
        int getVitality()const;
        void setArmor(const int& armor);
        int getArmor()const;
        void setLevel(const int& level);
        int getLevel()const;
        void setEnemy();
        bool isEnemy()const;
        
    private:
        string name_; //The name of the character (a string in UPPERCASE)
        Race race_; //The race of the character (an enum)
        int vitality_; //The character's vitality (a non-negative integer)
        int armor_; //The character's max armor level (a non-negative integer)
        int level_; //The character's level (a non-negative integer)
        bool enemy_; //A flag indicating whether the character is an enemy
}; //end Character class

#endif
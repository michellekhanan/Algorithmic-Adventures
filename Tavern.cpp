/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Michelle Khanan
October 6 2023
Tavern.cpp defines the constructors and private and public function implementation of the Tavern class
*/

#include "Tavern.hpp"

/**
Default constructor.
Default-initializes all private members. 
*/
Tavern::Tavern():ArrayBag<Character>(), sum_{0}, count_{0}
{
}

/** @param:   A const reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to the tavern (i.e. items_),
            false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count 
              if the character is an enemy.
 **/
bool Tavern::enterTavern(const Character& enter_character)
{

    if (add(enter_character))
    {
        sum_ += enter_character.getLevel();
        if (enter_character.isEnemy())
        {
            count_++;
        }
        return true;
    }
    return false;
}

/** @param:   A const reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from the tavern (i.e. items_),
            false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count
              if the character is an enemy.
 **/
bool Tavern::exitTavern(const Character& exit_character)
{
    if (remove(exit_character))
    {
        sum_ -= exit_character.getLevel();
        if (exit_character.isEnemy())
        {
            count_--;
        }
        return true;
    }
    return false;
}

/** 
    @return:  The integer level count of all the characters currently in the Tavern
 **/
int Tavern::getLevelSum()const
{
    return sum_;
}

/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Computes the average level of the Tavern rounded to the NEAREST integer.
 **/
int Tavern::calculateAvgLevel()const
{
    return round(sum_ / getCurrentSize());
}

/** 
    @return:  The integer enemy count of the Tavern
 **/
int Tavern::getEnemyCount()const
{
    return count_;
}

/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Computes the enemy percentage of the Tavern rounded up to 2 decimal places.
 **/
double Tavern::calculateEnemyPercentage()const
{
    if (item_count_ == 0)
    {
        return 0.00;
    }
    double percentage = (((double)count_ / item_count_) * 100);
    return round(percentage * 100) / 100.00;
}

/** 
    @param:   A const reference to a string representing a character Race with value in 
              ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]
    @return:  An integer tally of the number of characters in the Tavern of the given race. 
              If the argument string does not match one of the expected race values, 
              the tally is zero. NOTE: no pre-processing of the input string necessary, only
              uppercase input will match.
 **/
int Tavern::tallyRace(const std::string& race) const
{
    int tally = 0;
    for(int i = 0; i < item_count_; i++)
    {
        if (race == items_[i].getRace())
        {
            tally++;
        }
    }
    return tally;
}

/**
@post:      Outputs a report of the characters currently in the tavern in the form:
            "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average
            level is: [x] \n[x]% are enemies.\n"
            Note that the average level should be rounded to the NEAREST integer, and the enemy
            percentage should be rounded to 2 decimal places.

            Example output: 
            Humans: 3
            Elves: 5
            Dwarves: 8
            Lizards: 6
            Undead: 0

            The average level is: 7
            46.67% are enemies.
*/
void Tavern::tavernReport()const
{
    std::cout << "Humans: " << tallyRace("HUMAN") << "\n";
    std::cout << "Elves: " << tallyRace("ELF") << "\n";
    std::cout << "Dwarves: " << tallyRace("DWARF") << "\n";
    std::cout << "Lizards: " << tallyRace("LIZARD") << "\n";
    std::cout << "Undead: " << tallyRace("UNDEAD") << "\n";
    std::cout << "The average level is: " << calculateAvgLevel() << "\n";
    std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies. \n";
}
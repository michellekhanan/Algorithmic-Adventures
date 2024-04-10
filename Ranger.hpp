/*
CSCI235 Fall 2023
Project 2 - Ranger Class
Michelle Khanan
September 22 2023
Ranger.hpp declares the Ranger class along with its private and public members
*/
#ifndef RANGER_HPP_
#define RANGER_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cctype>
#include "Character.hpp"

using namespace std;

struct Arrows 
{
    string type_;
    int quantity_;
    };

class Ranger : public Character
{

    public:
        /**
        Default constructor.
        Default-initializes all private members. Default character name: "NAMELESS". 
        Booleans are default-initialized to False. 
        */
        Ranger();
        /**
        Parameterized constructor.
        @param      : The name of the character (a const string reference)
        @param      : The race of the character (a const string reference)
        @param      : The character's vitality (an integer). Default to 0
        @param      : The character's max armor level (an integer). Default to 0
        @param      : The character's level (an integer). Default to 0
        @param      : A flag indicating whether the character is an enemy. Default to false
        @param      : A vector of arrows. Valid arrow types are: [WOOD, FIRE, WATER, POISON, BLOOD]
                    Lowercase valid arrow types are retained but converted to uppercase.
                    Invalid arrows are those with non-positive quantities or invalid types.
                    If the vector contains invalid arrows, those arrows are discarded. 
                    Default to empty vector
        @param      : A vector of affinities. Valid Affinities: [FIRE, WATER, POISON, BLOOD]
                    String inputs can be in lowercase, but must be converted to uppercase.
                    If the vector contains invalid affinities, those affinities are discarded.
                    Default to empty vector
        @param      : A flag indicating whether the character is able to recruit an animal companion. 
                    Default to false
        @post       : The private members are set to the values of the corresponding parameters
        */
        Ranger(const string& name, const string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, vector<Arrows> arrows = {}, vector<string> affinity = {}, bool has_companion = false);
        /**
        @param    : a reference to string representing the arrow type
        @param    : a reference to an integer quantity
        @post     : If the character already has that type of arrow, the quantity in the vector 
                    is updated. If not, the arrow is added to the vector. 
                    Valid arrow types are: [WOOD, FIRE, WATER, POISON, BLOOD]
                    Lowercase valid arrow types are retained but converted to uppercase.
                    Quantity of arrows must be greater than 0
                    Invalid arrows are those with non-positive quantities or invalid types.
                    If the arrows are invalid, they are not added.
        @return   : True if the arrows were added successfully, false otherwise
        **/
        bool addArrows(const string& type, const int& quantity);
        /**
        @return     : a vector of the Character's arrows
        **/
        vector<Arrows> getArrows()const;
        /**
        @param    : a reference to string representing the arrow type
        @post     : If the character has the listed arrow AND enough arrows to fire one, 
                    the quantity of remaining arrows in the vector is updated.
                    Lowercase valid arrow types are accepted but converted to uppercase.
                    If firing the last arrow, simply decrement the quantity to 0.
        @return   : True if the character had the listed arrow AND enough arrows, False otherwise.
        **/
        bool fireArrow(const string& type);
        /**
        @param  : a reference to string representing an affinity 
        @post   : If the affinity does not already exist in the vector, add it to the vector.
                Valid Affinities: [FIRE, WATER, POISON, BLOOD] 
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
                There should be no duplicate affinities.
                If the affinity is invalid, it is NOT added.
        @return : True if the affinity was added successfully, false otherwise
        **/
        bool addAffinity(const string& affinity);
        /**
        @return     : a vector of the Character's affinities
        **/
        vector<string> getAffinities()const;
        /**
        @param    : a reference to a boolean indicating whether the character is able to recruit 
                    an animal companion
        @post     : sets the private member variable to the value of the parameter.
        **/
        void setCompanion(const bool& has_companion);
        /**
        @return   : a boolean indicating whether the character is able to recruit an animal companion
        **/
        bool getCompanion()const;

    private:
        vector<Arrows> arrows_; //A vector of arrows
        vector<string> affinities_; //A vector of affinities (strings)
        bool has_companion_; //A boolean indicating if they are able to recruit an animal companion
};

#endif
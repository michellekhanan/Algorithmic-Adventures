/*
CSCI235 Fall 2023
Project 4 - Tavern Class
Michelle Khanan
October 27 2023
Tavern.hpp defines the constructors and private and public function implementation of the Tavern class
*/
#include "Tavern.hpp"


/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}


/**
   @param: the name of an input file
   @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive integer
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
   @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/
Tavern::Tavern(const std::string &file) :ArrayBag<Character*>()
{
  std::ifstream file_name(file);

  std::string line, holder, name, race, subclass, main_weapon, weapon, dagger, arrow, arrow_tq, arrow_type, offhand, school_faction, affinity;
  int level, vitality, armor, arrow_quantity;
  bool enemy, summoning, disguise, enraged;

  while (std::getline(file_name, line)) 
  {
    std::istringstream s(line);
    
    std::getline(s, holder, ',');
    name = holder;

    std::getline(s, holder, ',');
    race = holder;

    std::getline(s, holder, ',');
    subclass = holder;

    std::getline(s, holder, ',');
    std::istringstream levels(holder);
    levels >> level;

    std::getline(s, holder, ',');
    std::istringstream vitalities(holder);
    vitalities >> vitality;

    std::getline(s, holder, ',');
    std::istringstream armors(holder);
    armors >> armor;

    std::getline(s, holder, ',');
    std::istringstream enemies(holder);
    enemies >> enemy;
  
    if(subclass == "BARBARIAN")
    {
      Barbarian* barbarian = new Barbarian;
      barbarian->setName(name);
      barbarian->setRace(race);
      barbarian->setLevel(level);
      barbarian->setVitality(vitality);
      barbarian->setArmor(armor);
     if(enemy== true)
     {
      barbarian->setEnemy();
     }
     std::getline(s, holder, ',');
     main_weapon = holder;
     barbarian->setMainWeapon(main_weapon);
     std::getline(s, holder, ',');
     offhand = holder;
     barbarian->setSecondaryWeapon(offhand);
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::istringstream enrageds(holder);
     enrageds >> enraged;
     barbarian->setEnrage(enraged);
     enterTavern(barbarian);
   }
   
   if(subclass == "MAGE")
   {
     Mage* mage = new Mage;
     mage->setName(name);
     mage->setRace(race);
     mage->setLevel(level);
     mage->setVitality(vitality);
     mage->setArmor(armor);
     if(enemy== true)
     {
       mage->setEnemy();
     }
     std::getline(s, holder, ',');
     weapon = holder;
     mage->setCastingWeapon(weapon);
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::istringstream school_factions(holder);
     school_factions >> school_faction;
     mage->setSchool(school_faction);
     std::istringstream summonings(holder);
     summonings >> summoning;
     mage->setIncarnateSummon(summoning);
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     enterTavern(mage);
   }

   if(subclass == "SCOUNDREL")
   {
     Scoundrel* scoundrel = new Scoundrel;
     scoundrel->setName(name);
     scoundrel->setRace(race);
     scoundrel->setLevel(level);
     scoundrel->setVitality(vitality);
     scoundrel->setArmor(armor);
     if(scoundrel->isEnemy() != enemy)
     {
       scoundrel->setEnemy();
     }
     std::getline(s, holder, ',');
     dagger = holder;
     scoundrel->setDagger(dagger);
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::istringstream school_factions(holder);
     school_factions >> school_faction;
     scoundrel->setFaction(school_faction);
     std::getline(s, holder, ',');
     std::istringstream disguises(holder);
     disguises >> disguise;
     scoundrel->setDisguise(disguise);
     std::getline(s, holder, ',');
     enterTavern(scoundrel);
   }
  
   if(subclass == "RANGER")
   {
     Ranger* ranger = new Ranger;
     ranger->setName(name);
     ranger->setRace(race);
     ranger->setLevel(level);
     ranger->setVitality(vitality);
     ranger->setArmor(armor);
     if(ranger->isEnemy() != enemy)
     {
       ranger->setEnemy();
     }
     std::getline(s, holder, ',');
     std::istringstream arrow(holder);
     while(std::getline(arrow, holder, ';'))
     {
       std::istringstream arrow_tq(holder);
       arrow_tq >> arrow_type >> arrow_quantity;
       ranger->addArrows(arrow_type, arrow_quantity);
     }
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     std::istringstream summonings(holder);
     summonings >> summoning;
     ranger->setCompanion(summoning);
     std::getline(s, holder, ',');
     std::istringstream affinities(holder);
     while(std::getline(affinities, holder, ';'))
     {
       affinity = holder;
       ranger->addAffinity(affinity);
     }
     std::getline(s, holder, ',');
     std::getline(s, holder, ',');
     enterTavern(ranger);
   }
 }
 file_name.close();
}


/**
   @param:   A pointer to a Character entering the Tavern
   @return:  returns true if a Character was successfully added to items_, false otherwise
   @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character *a_character)
{
 if(add(a_character))
 {
   level_sum_ += a_character->getLevel();
   if(a_character->isEnemy())
   {
     num_enemies_++;
   }
   return true;
 }
 else
 {
   return false;
 }
}


/** @param:   A pointer to a Character leaving the Tavern 
   @return:  returns true if a character was successfully removed from items_, false otherwise
   @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character *a_character)
{
 if(remove(a_character))
 {
   level_sum_ -= a_character->getLevel();
   if(a_character->isEnemy())
     num_enemies_--;
     a_character = nullptr;
   return true;
 }
 return false;
}


/**
   @return:  The integer level count of all the characters currently in the Tavern
   **/
   int Tavern::getLevelSum()
   {
     return level_sum_;
   }


/**
   @return:  The average level of all the characters in the Tavern
   @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
  return (level_sum_>0) ? round(double(level_sum_) / getCurrentSize()) : 0.0;
}


/**
   @return:  The integer enemy count of the Tavern
   **/
   int Tavern::getEnemyCount()
   {
     return num_enemies_;
   }


/**
   @return:  The percentage (double) of all the enemy characters in the Tavern
   @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
 double enemy_percent = (getEnemyCount()>0) ?  (double(getEnemyCount()) / getCurrentSize()) * 100: 0.0;
 std::cout<< enemy_percent;
 return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
}


/**
   @param:   A string reference to a race
   @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
 int frequency = 0;
 int curr_index = 0;  
 while (curr_index < item_count_)
 {
   if(items_[curr_index]->getRace() == race)
   {
     frequency++;
   }
   curr_index++;
 }
 return frequency;
}

/**
 @post:    Outputs a report of the characters currently in the tavern in the form:
 "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"


 Example output:
 Humans: 5
 Elves: 8
 Dwarves: 3
 Lizards: 7
 Undead: 2


 The average level is: 16
 24% are enemies.
*/
void Tavern::tavernReport()
{
 int humans = tallyRace("HUMAN");
 int elves = tallyRace("ELF");
 int dwarves = tallyRace("DWARF");
 int lizards = tallyRace("LIZARD");
 int undead = tallyRace("UNDEAD");
  std::cout << "Humans: " << humans << std::endl;
 std::cout << "Elves: " << elves << std::endl;
 std::cout << "Dwarves: " << dwarves << std::endl;
 std::cout << "Lizards: " << lizards << std::endl;
 std::cout << "Undead: " << undead << std::endl;
 std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
 std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}


/**
    @post: For every character in the tavern, displays each character's information
*/
void Tavern::displayCharacters()
{
  if (isEmpty()) 
  {
    std::cout << "The tavern is empty." << std::endl;
  } 
  else 
  {
    for (int i = 0; i < getCurrentSize(); ++i) 
    {
      Character* character = items_[i];
      if (character != nullptr) 
      {
        character->display();
        std::cout << std::endl;
      }
    }
  }
}
    

/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information

*/
void Tavern::displayRace(const std::string& race)
{
  int count = 0;
  for (int i = 0; i < getCurrentSize(); i++) 
  {
    Character* character = items_[i];
    if (character->getRace() == race) 
    {
      character->display();
      count++;
    }
  }
  if (count == 0) 
  {
      std::cout << "No characters of race " << race << " found in the tavern." << std::endl;
  }
}
    

/**
    @post: Every character in the tavern eats a tainted stew.
*/
void Tavern::taintedStew()
{
  for (int i = 0; i < getCurrentSize(); i++) 
  {
    Character* character = items_[i];
    character->eatTaintedStew();
  }
}
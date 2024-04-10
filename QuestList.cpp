/*
CSCI235 Fall 2023
Project 5 - QuestList Class
Michelle Khanan
November 10 2023
QuestList.cpp defines the constructors and public function implementation of the QuestList class
*/

#include "QuestList.hpp"

/**
    Default Constructor
*/
QuestList::QuestList() : DoublyLinkedList<Quest*>()
{
}


/**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

*/
QuestList::QuestList(const std::string& input_file) : DoublyLinkedList<Quest*>() 
{
    std::ifstream file(input_file);
    std::string line, title, description, temp, dependencies, subquests;
    std::getline(file, line); 

    while (std::getline(file, line))
    {
        if (line.back() == '\r')
        {
            line.pop_back();
        }
        std::istringstream ss(line);
        std::getline(ss, title, ',');
        std::getline(ss, description, ',');
        std::getline(ss, temp, ',');
        bool completed = stoi(temp);
        std::getline(ss, temp, ',');
        int experience_points = stoi(temp);
        std::getline(ss, dependencies, ',');
        std::getline(ss, subquests);

        std::vector<Quest*> dependenciesVec = {};
        if (dependencies != "NONE")
        {
            std::istringstream ff(dependencies);
            while (std::getline(ff, temp, ';'))
            {
                if (contains(temp) == true)
                {
                    dependenciesVec.push_back(getPointerTo(getPosOf(temp))->getItem());
                }
                else
                {
                    Quest* newQuest = new Quest(temp, "NOT DISCOVERED", false, 0, {}, {});
                    dependenciesVec.push_back(newQuest);
                }
            }
        }
        std::vector<Quest*> subquestsVec = {};
        if (subquests != "NONE")
        {
            std::istringstream gg(subquests);
            while (std::getline(gg, temp, ';'))
            {
                if (contains(temp) == true)
                {
                    subquestsVec.push_back(getPointerTo(getPosOf(temp))->getItem());
                }
                else
                {
                    Quest* newQuest = new Quest(temp, "NOT DISCOVERED", false, 0, {}, {});
                    subquestsVec.push_back(newQuest);
                }
            }
        }
        addQuest(title, description, completed, experience_points, dependenciesVec, subquestsVec);
    }
}



/**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
int QuestList::getPosOf(const std::string& quest_title)
{
    int position = 0;
    Node<Quest*>* current = getHeadNode();
    while (current != nullptr)
    {
        if (current->getItem()->title_ == quest_title)
        {
            return position;
        }
        else{
            current = current->getNext();
            position++;
        }
    }
    return -1;
}



/**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
bool QuestList::contains(const std::string& quest_title)
{
    Node<Quest*>* current = getHeadNode();
    while (current != nullptr) {
        if (current->getItem()->title_ == quest_title) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}



/**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
           
    @return: True if the quest was added or updated successfully, False otherwise
*/
bool QuestList::addQuest(Quest* quest) {
    int pos = getPosOf(quest->title_);

    if (pos != -1) {
        Node<Quest*>* existingQuestNode = getPointerTo(pos);
        if (existingQuestNode && !existingQuestNode->getItem()->completed_) {
            quest = existingQuestNode->getItem();
            return true;
        }
        if (existingQuestNode->getItem()->description_ == "NOT DISCOVERED")
        {
            existingQuestNode->getItem()->description_ = quest->description_;
            existingQuestNode->getItem()->completed_ = quest->completed_;
            existingQuestNode->getItem()->subquests_ =  quest->subquests_;
            existingQuestNode->getItem()->dependencies_ = quest->dependencies_;
            existingQuestNode->getItem()->experience_points_ = quest->experience_points_;
            return true;
        }
        return false;
    }
    if (pos == -1)
    {
        insert(item_count_, quest);
        for (Quest* dependency : quest->dependencies_) {
        if (getPosOf(dependency->title_) == -1) {
            addQuest(dependency);
        }
        }
        for (Quest* subquest : quest->subquests_) {
            if (getPosOf(subquest->title_) == -1) {
                addQuest(subquest);
        }
        return true;
    }
    }
    return false;
}



/**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
             If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
             Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
             

    @return: True if the quest was added or updated successfully, False otherwise

*/
bool QuestList::addQuest(const std::string& title, const std::string& description, bool completed, int experience_points, const std::vector<Quest*>& dependencies, const std::vector<Quest*>& subquests)
{
    Quest *quest = new Quest();
    quest->title_ = title;
    quest->description_ = description;
    quest->completed_ = completed;
    quest->experience_points_ = experience_points;
    quest->dependencies_ = dependencies;
    quest->subquests_ = subquests;
    if (addQuest(quest))
    {
        return true;
    }
    return false;
}



/**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
bool QuestList::dependenciesComplete(Quest* quest)
{
    for (Quest* dependency : quest->dependencies_)
    {
        int pos = getPosOf(dependency->title_);
        if (pos != -1)
        {
            if (!getPointerTo(pos)->getItem()->completed_)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}




/**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/
bool QuestList::questAvailable(Quest* quest)
{
    if (quest->completed_)
    {
        return false;
    }
    return dependenciesComplete(quest);
}




/**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
void QuestList::printQuest(Quest* quest)
{
    std::cout << quest->title_ << ": " << (quest->completed_ ? "Complete" : "Not Complete") << "\n";
    std::cout << quest->description_ << "\n\n";
}




/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
              [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
              [Dependency2]
              [Quest Title]
              
     If the given quest title is not found in the list, print "No such quest."
*/
void QuestList::questQuery(const std::string& quest_title)
{
    std::cout << "Query: " << quest_title << std::endl;
    int pos = getPosOf(quest_title);


    if (contains(quest_title) == false) {
        std::cout << "No such quest." << std::endl;
    }

    Node<Quest*>* questNode = getPointerTo(pos);
    Quest* quest = questNode->getItem();

    if (quest->completed_) {
        std::cout << "Quest Complete" << std::endl;
    }
    questQueryHelper(quest_title);
}

void QuestList::questQueryHelper(const std::string& quest_title)
{
    int pos = getPosOf(quest_title);
    Node<Quest*>* questNode = getPointerTo(pos);
    Quest* quest = questNode->getItem();

    for (Quest* i : quest->dependencies_)
    {
        questQueryHelper(i->title_);
    }
    if (questAvailable(quest))
    {
        std::cout << "Ready: " << quest->title_ << std::endl;
    }
    if (!dependenciesComplete(quest))
    {
        std::cout << "  " << quest->title_ << std::endl;
    }

}



/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
int QuestList::calculateGainedExperience()
{
    int totalExperience = 0;
    Node<Quest*>* current = getHeadNode();
    while (current != nullptr)
    {
        Quest* quest = current->getItem();
        if (quest->completed_)
        {
            totalExperience += quest->experience_points_;
        }
        current = current->getNext();
    }
    return totalExperience;
}


/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
int QuestList::calculateProjectedExperience(Quest* main_quest)
{
    int totalExperience = main_quest->experience_points_;
    for (Quest* subquest : main_quest->subquests_) {
        totalExperience += calculateProjectedExperience(subquest);
    }
    return totalExperience;
}




/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
int QuestList::calculatePathwayExperience(Quest* main_quest) 
{

    int totalExperience = 0;
    if (main_quest->completed_)
    {
        totalExperience += main_quest->experience_points_;
    }
    for (Quest* subquest : main_quest->subquests_) {
        totalExperience += calculatePathwayExperience(subquest);
    }
    return totalExperience;
}




/**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
           With filter "COMPLETE":   Only print out the completed quests in the list.
           With filter "INCOMPLETE": Only print out the incomplete quests in the list.
           With filter "AVAILABLE":  Only print out the available quests in the list.
           If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
void QuestList::questHistory(const std::string& filter) 
{
    if (filter != "NONE" && filter != "COMPLETE" && filter != "INCOMPLETE" && filter != "AVAILABLE") {
        std::cout << "Invalid Filter\n";
        return;
    }
    if (filter == "NONE")
    {
        for (int i = 0 ; i < item_count_; i++){
            printQuest(getItem(i));
        }
    }
    if (filter == "COMPLETE")
    {
        for (int i = 0 ; i < item_count_; i++)
        {
            if (getItem(i)->completed_ == 1)
            {
                printQuest(getItem(i));
            }
        }
    }
    if (filter == "INCOMPLETE")
    {
        for (int i = 0 ; i < item_count_; i++)
        {
            if (getItem(i)->completed_ == 0)
            {
                printQuest(getItem(i));
            }
        }
    }
    if (filter == "AVAILABLE")
    {
        for (int i = 0 ; i < item_count_; i++)
        {
            if(questAvailable(getItem(i)))
            {
                printQuest(getItem(i));
            }
        }

    }
}




/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
void QuestList::printQuestDetails(Quest* main_quest) {
    float pathwayExperience = calculatePathwayExperience(main_quest);
    float projectedExperience = calculateProjectedExperience(main_quest);
    
    std::cout << main_quest->title_ << " (" << (pathwayExperience/projectedExperience)*100 << "% Complete)" << std::endl;
    for (Quest* subquest : main_quest->subquests_) {
        printQuestDetailsHelper(subquest);
    }
}

void QuestList::printQuestDetailsHelper(Quest* main_quest)
{
    std::string space = " ";
    for (Quest* subquest : main_quest->subquests_) {
        space += " ";
        printQuestDetailsHelper(subquest);
    }
    std::string complete;
    if (main_quest->completed_)
    {
        complete = "Complete";

    }
    else{
        complete = "Not Complete";
    }
    std::cout << space << main_quest->title_ << ": " << complete << std::endl;

}
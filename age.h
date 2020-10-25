//  age.h

#ifndef age_h
#define age_h
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// Create a struct to hold the age data
struct ageStruct
{
    string geoid;
    int under_5;
    int under_18;
    int over_65;
    int key;
};

// Create a struct for linkedlist
struct Node
{
    ageStruct ageObjForLl;
    Node* nextTuple;
};

// Create the hash table for age file
class ageTable
{
private:
    // Create a 2d vector
    vector<vector<ageStruct>>ageTableVector2d;
    
    // Set table size as 100
    static const int tableSize = 131;
    
public:
    // Hash table
    ageTable(){
        ageTableVector2d.resize(tableSize);
    }
    
    // Declare hash function
    int hashfn(string geo_id);
    
    // Declare INSERT functions
    void INSERT(string str);
    
    // Declare other query functions
    void UPDATE(string updateInput);
    
    // SELECT and DELETE need linkedlist
    void SELECT(string selectInput);
    void DELETE(string deleteInput);
    
    // Outputting table
    void DISPLAY ();
    // Outputting updated table
    void WRITE ();
    
};

// Create a LinkedList class
class LinkedList
{
private:
    Node *head;
public:
    LinkedList();
    
    // Declare functions for LinkedList
    void addNode(ageStruct ageObj);
    string SELECT(ageStruct ageObj);
    void DELETE(string deleteInput);
};

#endif /* age_h */

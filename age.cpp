// This part of the program 

#include "age.h"

// Define hash function, using modulo hashing

int ageTable::hashfn(string geo_id)
{
    int index = 0;
        
    for (int i = 0; i < geo_id.length(); i++)
    {
         //cout << "Adding: " << index << " + " << (int)geo_id[i] << endl;
        index = index + geo_id[i];
    }
    
    //cout << "Modding: " << index << " % " << tableSize << endl;
    
    index = index % tableSize;
    
    //cout << "Results: " << index << endl;
    
    return index;
}

// Create an object for ageStruct
ageStruct temp;

// Define INSERT function with chaining collision strategy
void ageTable::INSERT(string str)
{
    // Create a temporary vector
    vector<string>tempVect;
    string line = str;
    //cout << line << endl;
    
    // Parse the entry
    stringstream ss;
    ss.str(str);
    
    // Use ',' as delimeter and push parsed entries into temp vector
    while(getline(ss, str, ','))
    {
        // store into tmp vect
        tempVect.push_back(str);
    }
    
    // Using chaining as collision strategy
    // Use temp vect to create ageStruct obj
    // And push back to the 2d vector
    temp.geoid = tempVect[0];
    // cout << temp.geoid << endl; // Testing only
    temp.key = hashfn(temp.geoid);
    // cout << temp.key << endl; // Testing only
    temp.under_5 = stoi(tempVect[1]);
    // cout << temp.under_5 << endl; // Testing only
    temp.under_18 = stoi(tempVect[2]);
    // cout << temp.under_18 << endl; // Testing only
    temp.over_65 = stoi(tempVect[3]);
    // cout << temp.over_65 << endl; // Testing only
    
    ageTableVector2d[temp.key].push_back(temp);
    
    // Print out the insertion to users
    cout << "Inserted: " << line << " in age" << endl;

    tempVect.clear();
    
    /*
    // Testing if things are being stored correctly in 2d vector
    for (int i = 0; i < ageTableVector2d.size(); i++)
          {
              for (int j = 0; j < ageTableVector2d[i].size(); j++)
              {
                  cout << ageTableVector2d[i][j].geoid << endl;
                  cout << ageTableVector2d[i][j].under_5 << endl;
                  cout << ageTableVector2d[i][j].under_18 << endl;
                  cout << ageTableVector2d[i][j].over_65 << endl;
                  cout << ageTableVector2d[i][j].key << endl;
              }
          }
     */
}

// Set head node equals to null in LinkedList basic constructor
LinkedList::LinkedList()
{
    head = NULL;
}

// Define addNode fucntion to create a LinkedList
void LinkedList::addNode(ageStruct ageObj)
{
    Node *newTuple = new Node;
    newTuple->ageObjForLl = ageObj;
    newTuple->nextTuple = NULL;
    
    if (head == NULL)
    {
        head = newTuple;
    }
    
    else if (head->nextTuple == NULL)
    {
        head->nextTuple = newTuple;
    }
    
    else
    {
        Node* currentNode = head;
        
        while(currentNode->nextTuple != NULL)
        {
            currentNode = currentNode->nextTuple;
        }
        currentNode->nextTuple = newTuple;
    }
}

// Define UPDATE function
void ageTable::UPDATE(string updateInput)
{
    //cout << updateInput << endl;
    
    //Use stringstream to parse updateInput to get geoid information
    stringstream ss1;
    ss1.str(updateInput);
    string tempGeo_id;
    string line = updateInput;
    getline(ss1, tempGeo_id, ',');
    
    //Use getline to parse updateInput to get rest of the attribute information
    string tempunder5;
    string tempunder18;
    string tempover65;
    
    getline(ss1, tempunder5, ',');
    //cout << tempunder5 << endl;
    getline(ss1, tempunder18, ',');
    //cout << tempunder18 << endl;
    getline(ss1, tempover65, ',');
    //cout << tempover65 << endl;
    
    // Assign index to tempGeo_id value passed through hashfn
    int index = hashfn(tempGeo_id);
    
    // Go through the table to find the entry that matches the given key, if matches, assign update query information to the entry values in the vector
    for (int i = 0; i < ageTableVector2d.size(); i++)
    {
        for (int j = 0; j < ageTableVector2d[i].size(); j++)
        {
            if (ageTableVector2d[i][j].key == index)
            {
                if (ageTableVector2d[i][j].geoid == tempGeo_id)
                {
                    //cout << tempGeo_id << "---" << ageTableVector2d[i][j].geoid;
                    ageTableVector2d[i][j].geoid = tempGeo_id;
                    ageTableVector2d[i][j].under_5 = stoi(tempunder5);
                    ageTableVector2d[i][j].under_18 = stoi(tempunder18);
                    ageTableVector2d[i][j].over_65 = stoi(tempover65);
                    
                    // Print update result out for the user
                    cout << "Updated: "<< tempGeo_id << "," << tempunder5 << "," << tempunder18 << "," << tempover65 << " in age" << endl;
                }
                
                // If the key givne doesn't match the key in the table, print out the failure prompt
                if (ageTableVector2d[i][j].geoid != tempGeo_id)
                {
                    cout << "Failed to update: "<< tempGeo_id << "," << tempunder5 << "," << tempunder18 << "," << tempover65 << " in age" << endl;
                }
            }
        }
    }
}

// Define SELECT function
void ageTable::SELECT(string selectInput)
{
    // Use stringstream to parse selectInput to get geoid information
    stringstream ss2;
    ss2.str(selectInput);
    string tempGeo_id;
    string line = selectInput;
    getline(ss2, tempGeo_id, ',');
    
    //cout << "This is the geo_id: " << tempGeo_id << endl;
    
    if (tempGeo_id != "*")
    {
    // Assign index to tempGeo_id value passed through hashfn
    int index = hashfn(tempGeo_id);
    
        // Go through the table to find the entry that matches the given key, if matches, print out the selected entry to the user
        for (int i = 0; i < ageTableVector2d.size(); i++)
        {
            for (int j = 0; j < ageTableVector2d[i].size(); j++)
            {
                //cout << ageTableVector2d[i][j].key << "---" << index << endl;

                if (ageTableVector2d[i][j].key == index)
                {
                    if (ageTableVector2d[i][j].geoid == tempGeo_id)
                    {
                        cout << "Selected: "<< ageTableVector2d[i][j].geoid << "," << ageTableVector2d[i][j].under_5 << "," << ageTableVector2d[i][j].under_18 << "," << ageTableVector2d[i][j].over_65 << " in age" << endl;

                    }
                }
            }
        }
    }
}

//Define SELECT function for LinkedList
//string LinkedList::SELECT(ageStruct ageObj)
//{
//    string selectInput;
//    stringstream ss2;
//    ss2.str(selectInput);
//    string tempGeo_id;
//    string line = selectInput;
//    getline(ss2, tempGeo_id, ',');
//
//    if(tempGeo_id == "*")
//    {
//        if (head == NULL)
//        {
//            return false;
//        }
//        if (head->ageObjForLl = ageObj)
//            {
//
//            }
//    }
//}


// Define DELETE function
void ageTable::DELETE(string deleteInput)
{
    // Use stringstream to parse deleteInput to get geoid information
    stringstream ss3;
    ss3.str(deleteInput);
    string tempGeo_id;
    string line = deleteInput;
    getline(ss3, tempGeo_id, ',');
    
    if (tempGeo_id != "*")
    {
    // Assign index to tempGeo_id value passed through hashfn
    int index = hashfn(tempGeo_id);
    
    // Go through the table to find the entry that matches the given key, if matches, erase the entry
        for (int i = 0; i < ageTableVector2d.size(); i++)
        {
            for (int j = 0; j < ageTableVector2d[i].size(); j++)
            {
                if (ageTableVector2d[i][j].key == index)
                {
                    if (ageTableVector2d[i][j].geoid == tempGeo_id)
                    {
                        //cout << "before: " << ageTableVector2d[i].size() << endl;
                        ageTableVector2d[i].erase(ageTableVector2d[i].begin()+j);
                        //cout << "after: " << ageTableVector2d[i].size() << endl;
                        
                        cout << "Deleted: " << ageTableVector2d[i][j].geoid << "," << ageTableVector2d[i][j].under_5 << "," << ageTableVector2d[i][j].under_18 << "," << ageTableVector2d[i][j].over_65 << " in age" << endl;
                    }
                }
            }
        }
         
    }
}

//void LinkedList::DELETE(string deleteInput)
//{
//    // Use stringstream to parse deleteInput to get geoid information
//    stringstream ss3;
//    ss3.str(deleteInput);
//    string tempGeo_id;
//    string line = deleteInput;
//    getline(ss3, tempGeo_id, ',');
//
//    if (tempGeo_id == "*")
//    {
//        Node* currentNode = ;
//    }
//}

// Define DISPLAY function
void ageTable::DISPLAY()
{
    // Print out an age table display promt and the format of the table display
    cout << "Age Table display: " << endl;
    cout << "geo_geoid" << setw(13) << "under_5" << setw(10) << "under_18" << setw(10) << "over_65" << endl;
    
    // Go through the table and print the table out in the previously set up format
    for (int i = 0; i < ageTableVector2d.size(); i++)
    {
        for (int j = 0; j < ageTableVector2d[i].size(); j++)
        {

        cout << ageTableVector2d[i][j].geoid << setw(8) << ageTableVector2d[i][j].under_5 << setw(9) << ageTableVector2d[i][j].under_18 << setw(11) << ageTableVector2d[i][j].over_65 << endl;
        }
    }
}



// Define WRITE function WRITE is just to have an out file of the updated file
void ageTable::WRITE()
{
    // Using filestream, print out the table to a file
    string copyTable;
    ofstream outFile("out_Age.csv");
    outFile << "geo_geoid" << endl << "geo_geoid,under_5,under_18,over_65" << endl;
    
    // Walk through the vector to access table to put in the outFile.
    for (int i = 0; i < ageTableVector2d.size(); i++)
    {
        for (int j = 0; j < ageTableVector2d[i].size(); j++)
        {

        outFile << ageTableVector2d[i][j].geoid << "," << ageTableVector2d[i][j].under_5 << "," << ageTableVector2d[i][j].under_18 << "," << ageTableVector2d[i][j].over_65 << endl;
        }
    }
    
}

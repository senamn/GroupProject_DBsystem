#include "Library.h"

string read_inname(){
    string name;
    cout << "Please enter the main file's filename: " << endl;
    cin >> name;

    return name;
}

void output_matcher_info(smatch matcher){
    cout << "MATCH SIZE: " << matcher.size() << endl;
    cout << "COMMAND NAME: " << matcher[1] << endl; //This holds the command name
    cout << "TUPLE: " << matcher[3] << endl; //This holds the tuple
    cout << "TABLE NAME: " << matcher[4] << endl; //This holds the table name
}

void Display_Tables(){
    //Include in this function a call to your own hash table's display function
}

void Write_Tables(){
    //Include in this function a call to your own hash table's write function
}

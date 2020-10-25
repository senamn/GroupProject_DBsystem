#include "age.h"
#include "Library.h"


using namespace std;

int main()
{
    //Declaration for the strings and filestreams for file input
    string input_name;
    string geo_name, age_name, dis_name;
    fstream input_file;
    fstream geo_file, age_file, dis_file;

    //Strings to hold input from files
    string input_holder;
    string geo_holder, age_holder, dis_holder;
    string geo_key, age_key, dis_key;
    string geo_scheme, age_scheme, dis_scheme;

    //creating regex patterns
    regex insert_pattern("(INSERT)(\(.*\),)([a-z]+)");
    regex update_pattern("(UPDATE)(\(.*\),)([a-z]+)");
    regex select_pattern("(SELECT)(\(.*\),)([a-z]+)");
    regex delete_pattern("(DELETE)(\(.*\),)([a-z]+)");
    regex display_pattern("DISPLAY\(\)");
    regex write_pattern("WRITE\(\)");

    //Create age table & age linked list object
    ageTable ageTableObj;
    LinkedList agelinkedListObj;


    input_name = read_inname();

    //Open input file, output message if successful, output message and return if unsuccessful
    input_file.open(input_name);
    if(input_file.is_open()) cout << "Input file: " << input_name << " opened." << endl;
    else{
        cout << "Input file not found. Ending program." << endl;
        return 1;
    }


    //This for loop reads the first three lines of the input file
    //  These lines contain a pair of strings: the name of a file and the name of that file's
    //      corresponding table. The for loop will parse this information and open the appropriate files
    for(int z = 0; z < 3; z ++){
        //cout << "read a line" << endl;
        string input_holder2;
        getline(input_file, input_holder2); //Gets a line from the input file
        istringstream input_read(input_holder2); //String stream to operate on line from input
        string read_holder1, read_holder2; //Holds both strings in the line
        getline(input_read, read_holder1, ' '); //Gets first part of the line
        getline(input_read, read_holder2, ' '); //Gets second part of the line
        cout << read_holder1 << "    " << read_holder2 << endl;
        if(read_holder2 == "age"){ //If statement, self-explanatory{
            //cout << "Entered age if" << endl;
            age_file.open(read_holder1); //Opens age file
            if(age_file.is_open()) cout << "Age file: " << read_holder1 << " opened." << endl;
            else{
                cout << "Age file not found. Ending program." << endl;
                return 1;
            }
        }
        else if(read_holder2 == "geography"){
            //cout << "Entered geo if" << endl;
            geo_file.open(read_holder1); //Opens geography file
            if(geo_file.is_open()) cout << "Geography file: " << read_holder1 << " opened." << endl;
            else{
                cout << "Geography file not found. Ending program." << endl;
                return 1;
            }
        }
        else if(read_holder2 == "disability"){
            //cout << "Entered dis if" << endl;
            dis_file.open(read_holder1); //Opens disability file
            if(dis_file.is_open()) cout << "Disability file: " << read_holder1 << " opened." << endl;
            else{
                cout << "Disability file not found. Ending program." << endl;
                return 1;
            }
        }
    }
    //All files are now opened
    //Reads the empty line after the three lines with file information
    getline(input_file, input_holder);

    //Read in input from the age file
    cout << "Processing age table." << endl;
    getline(age_file, age_key);
    getline(age_file, age_scheme);
    while(getline(age_file, age_holder)){
        //cout << "Got another age line" << endl;
        //cout << age_holder << endl;

        // Part 3, Sena
        // Call INSERT function from age.h to store process age_holder and store in ageTableVector
        ageTableObj.INSERT(age_holder);
        // Part 3, Sena done using age_holder

    }
    //The process of opening all of the files is left in main. When it is done in Library.cpp, it caused a
    //      "Use of deleted function" error. To avoid unnecessary complexity and use of copy constructors
    //      the implementation is simply done in main.

 /*
    //Read in input from the geo file
    cout << "Processing geo table." << endl;
    getline(geo_file, geo_key);
    getline(geo_file, geo_scheme);
    while(getline(geo_file, geo_holder)){
        cout << "Got another geo line" << endl;
        cout << geo_holder << endl;
        //This would be the best place to put code to read in entries
        //A new entry has been read from the input file, and the full tuple is stored in geo_holder




    }

    //Read in input from the dis file
    cout << "Processing dis table." << endl;
    getline(dis_file, dis_key);
    getline(dis_file, dis_scheme);
    while(getline(dis_file, dis_holder)){
        cout << "Got another dis line" << endl;
        cout << dis_holder << endl;
        //This would be the best place to put code to read in entries
        //A new entry has been read from the input file, and the full tuple is stored in dis_holder




    }

  */
    
    //cout << ageTableObj.ageTableVector2d[9][0].geoid << endl;
    //cout << ageTableObj.ageTableVector2d[9][1].geoid << endl;


    //while statement to read in each query and process it using regex
    //the queries are split into three portions:
    //      The Command Name (i.e. INSERT, UPDATE, DELETE, etc.)
    //      The tuple of the command
    //      The table the command operates on
    while(getline(input_file, input_holder)){
        smatch matcher;
        if(regex_search(input_holder, matcher, insert_pattern)){
             //These are testing comments to ensure input was read in properly
           // cout << "Found an insert" << endl;
           // output_matcher_info(); //Command name in matcher[1], tuple in matcher[3], table name in matcher[4]
            
            //Operate for the corresponding query in this if statement
            //matcher[1] holds the command name
            //matcher[3] holds the tuple (there is an additional '(' at the start, keep that in mind
            //matcher[4] holds the table name
           
            //Part 3 - Sena
            // Using matcher[4] to find the query for age table, read in the query line
            if (matcher[4] == "age")
            {
                // Use substring to ignore first 8 characters
                string line = input_holder.substr(8);
                // Using stringstream to parse the line and use getline to get the necessary part to pass to INSERT function
                stringstream ss;
                ss.str(line);
                
                getline(ss, line, ')');
                ageTableObj.INSERT(line);
            }
            //Part 3 - Sena done using insert_pattern
            
        }
        else if(regex_search(input_holder, matcher, update_pattern)){
            /* //These are testing comments to ensure input was read in properly
            cout << "Found an update" << endl;
            output_matcher_info(); //Command name in matcher[1], tuple in matcher[3], table name in matcher[4]
            */
            //Operate for the corresponding query in this if statement
            //matcher[1] holds the command name
            //matcher[3] holds the tuple (there is an additional '(' at the start, keep that in mind
            //matcher[4] holds the table name
            
            //Part 3 - Sena
            // Using matcher[4] to find the query for age table, read in the query line
            if (matcher[4] == "age")
            {
                // Use substring to ignore first 8 characters
                string line = input_holder.substr(8);
                // Using stringstream to parse the line and use getline to get the necessary part to pass to UPDATE function
                stringstream ss;
                ss.str(line);
                    
                getline(ss, line, ')');
                ageTableObj.UPDATE(line);
                   }
            //Part 3 - Sena done using insert_pattern

        }
        else if(regex_search(input_holder, matcher, select_pattern)){
            /* //These are testing comments to ensure input was read in properly
            cout << "Found a select" << endl;
            output_matcher_info(); //Command name in matcher[1], tuple in matcher[3], table name in matcher[4]
            */
            //Operate for the corresponding query in this if statement
            //matcher[1] holds the command name
            //matcher[3] holds the tuple (there is an additional '(' at the start, keep that in mind
            //matcher[4] holds the table name
            
            //Part 3 - Sena
            // Using matcher[4] to find the query for age table, read in the query line
            if (matcher[4] == "age")
            {
                // Use substring to ignore first 8 characters
                string line = input_holder.substr(8);
                
                // Using stringstream to parse the line and use getline to get the necessary part to pass to SELECT function
                stringstream ss;
                ss.str(line);
                getline(ss,line,')');
                
                ageTableObj.SELECT(line);
                //agelinkedListObj.SELECT(line);
                                
            }
            //Part 3 - Sena done using insert_pattern

        }
        else if(regex_search(input_holder, matcher, delete_pattern)){
            /* //These are testing comments to ensure input was read in properly
            cout << "Found a delete" << endl;
            output_matcher_info(); //Command name in matcher[1], tuple in matcher[3], table name in matcher[4]
            */
            //Operate for the corresponding query in this if statement
            //matcher[1] holds the command name
            //matcher[3] holds the tuple (there is an additional '(' at the start, keep that in mind
            //matcher[4] holds the table name
            
            //Part 3 - Sena
            // Using matcher[4] to find the query for age table, read in the query line
            if (matcher[4] == "age")
            {
                // Use substring to ignore first 8 characters
                string line = input_holder.substr(8);
                // Using stringstream to parse the line and use getline to get the necessary part to pass to SELECT function
                stringstream ss;
                ss.str(line);
                
                getline(ss, line, ')');
                ageTableObj.DELETE(line);
                //agelinkedListObj.DELETE(line);
            }
            //Part 3 - Sena done using insert_pattern

        }
        else if(regex_search(input_holder, matcher, display_pattern)){
             //These are testing comments to ensure input was read in properly
            //cout << "Found a display" << endl;
            /*
            cout << "MATCH SIZE: " << matcher.size() << endl;
            cout << "COMMAND NAME: " << matcher[0] << endl;
            */
            //Operate for the corresponding query in this if statement
            //Display_Tables();
            
            //Part 3 - Sena
            ageTableObj.DISPLAY();
            //Part 3 - Sena done displaying age table

            
        }
        else if(regex_search(input_holder, matcher, write_pattern)){
            /* //These are testing comments to ensure input was read in properly
            cout << "Found a write" << endl;
            cout << "MATCH SIZE: " << matcher.size() << endl;
            cout << "COMMAND NAME: " << matcher[0] << endl;
            */
            //Operate for the corresponding query in this if statement
            //Write_Tables();
            
            //Part 3 - Sena
            ageTableObj.WRITE();
            //Part 3 - Sena done writing age table

        }
    }

    input_file.close();
    age_file.close();
    geo_file.close();
    dis_file.close();
    return 0;
}

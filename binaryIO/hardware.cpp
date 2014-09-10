//
//  hardware.cpp
//  Hardware
//
//  Created by Ben Johnson on 5/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include "hardware.h"
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;


const string filename = "hardware.dat";

//Constants
static const int MAX = 100;
static const int NUMFIELD = 10;
static const int MAXSTRING = 256;
static const int MAXFIELD = 30;

struct hardware
{
    int id;
    char name[MAXSTRING];
    int quantity;
    float price;
    bool hidden;
    
};



static hardware database[MAX];
//Database 27.2KB

int numrecord;
int numberOfRecordsActive;
int numberOfRecordsInactive;



int FindRecordByID(const int identifier)
{
    bool found;
    int recordNum = -1;
    int counter = 0;
    
    while (found != true && counter < numrecord ) {
        if (identifier == database[counter].id && database[counter].hidden == false) {
            return counter;
        }
        counter++;
    }
    
    return recordNum;

}


int FindRecordByTitle(const char key[])
{
    bool found;
    int recordNum = -1;
    int counter = 0;
    
    while (found != true && counter < 0 ) {
        if (strcmp(key, database[counter].name)) {
            
        }
    }

    return recordNum;
}

hardware newRecord(char name[MAXSTRING], int quantity, float price, int id)
{
    hardware newHardware;
    strcpy(newHardware.name, name);
    newHardware.quantity = quantity;
    newHardware.price = price;
    newHardware.id = id;
    newHardware.hidden = false;
    
    return newHardware;
}

void printHeader()
{
    cout << left << setw(NUMFIELD) <<  "Record#";
    cout << left << setw(MAXFIELD)  << "Tool Name";
    cout << setw(NUMFIELD)  << "Quantity";
    cout << setw(NUMFIELD) <<  "Cost" << endl;
    
}

void printRecord(hardware record)
{
    if (record.hidden == false) {

        cout << setw(NUMFIELD) << record.id;
        cout << setw(MAXFIELD) << record.name;
        cout << setw(NUMFIELD) << record.quantity;
        cout << setw(NUMFIELD) << record.price << endl;
        
    }
    
}
bool deleteRecordWithID(int identifier)
{
 

    int position = FindRecordByID(identifier);
    if (position != -1) {
        //Do Stuff
        hardware record = database[position];
        record.hidden = true;
        ofstream out(filename,ios::in|ios::out | ios::binary);
        out.seekp(position * sizeof(hardware));
        
        //out.seekp(0,ios::end);
        out.write((char*)&record,sizeof(hardware));
        out.close();
        
        //Save to database
    }
    else
    {
        cout << "Cannot update record, doesn't exist!" << endl;
        return false;
    }
    LoadDatabase();
    return true;

}

bool updateRecordWithID(int identifier, char name[256],int quantity,float price)
{
    int position = FindRecordByID(identifier);
    if (position != -1) {
        //Do Stuff
        strcpy(database[position].name, name);
        database[position].quantity = quantity;
        database[position].price = price;
        ofstream out(filename,ios::in|ios::out | ios::binary);
        out.seekp(position * sizeof(hardware));
        
        //out.seekp(0,ios::end);
        out.write((char*)&database[position],sizeof(hardware));
        out.close();
        

        //Save to database
    }
    else
    {
        cout << "Cannot update record, doesn't exist!" << endl;
        return false;
    }


    return true;
    
}

void printRecordWithID(int identifier)
{
    int recordID = FindRecordByID(identifier);
    if (recordID != -1) {
        printHeader();
        printRecord(database[recordID]);

    }
    else
    {
        cout << "Record not found" << endl;
    }
}

void printRecords()
{
    if (numberOfRecordsActive > 0) {
        printHeader();

        for (int i = 0; i < numrecord; i++) {
            printRecord(database[i]);
        }
    }
    else
    {
        cout << "No records found." << endl;
    
    }
   
}

bool saveRecord(hardware newHardware)
{
    // Space in database
    if (numrecord < MAX) {
        //Checks to see if there is any records that are deleted(hidden) and overwrite them with new record
        if (numberOfRecordsInactive > 0) {
            ofstream out(filename, ios::in|ios::out | ios::binary);

            for (int i = 0; i < numrecord; i++) {
                if (database[i].hidden == true) {

                    out.seekp(i * sizeof(hardware));
                    out.seekp(0,ios::end);
                    out.write((char*)&newHardware,sizeof(newHardware));
                    out.close();
                    LoadDatabase();
                    
                    return true;
                    
                }
            }
        }
        ofstream out(filename,ios::binary |ios::app);
        out.write((char*)&newHardware,sizeof(newHardware));
        out.close();
        LoadDatabase();
        
        return true;
        //Place Record
        
    }
    return false;

}
bool LoadDatabase()
{
    ifstream file (filename, ios::binary |ios::in);
    numberOfRecordsActive = 0;
    numberOfRecordsInactive = 0;
    int index = 0;
    

    if (file.good()) {
        numrecord = index;
        while (file.good() && index < MAX) {
      
            hardware currentHardware;
          
            file.read((char *) &(currentHardware), sizeof(hardware));
            if (file.eof()) {
                break;
            }
            database[index] = currentHardware;
            if (database[index].hidden == false) {
                numberOfRecordsActive++;
            }
            else
            {
                numberOfRecordsInactive++;
            }

            index++;
            //Required as the last entry is read twice as EOF hasn't been read. Maybe a bit hacky?
        numrecord = index;
        }
        
    }
    else
    {
        file.close();

        return false;
    }
    file.close();

    return true;
    
}
bool createDatabase()
{
  //     int  init = 0;
    ofstream out(filename); //this creates it.
    out.close();
   
    return true;
    
}


bool createRecord(char name[MAXSTRING], int quantity, float price, int identifier)
{
    saveRecord(newRecord(name, quantity, price, identifier));
    return true;
    
}

int LoadFile(const char[]);
int WriteFile(const char[]);

//Add Record
    //IF there is a space
    //Request Data
    //Place the record

//Delete Record
//Modify Record
//Print Record

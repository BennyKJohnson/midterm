//
//  main.cpp
//  PhoneTimes
//
//  Created by Ben Johnson on 6/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

struct organisation
{
    char name[256];
    float times[128];
    int numOfTimes;
    float SD;

};

organisation database[200];
float calculateMean(float values[],int numValues)
{
    float sum = 0;
    int i = 0;
    for ( i =0; i < numValues; i++) {
        sum += values[i];
    }
    return sum / numValues;
}
float calculateVariance(float values[],int numValues, float mean)
{
    float sum = 0;
    int i = 0;
    for ( i =0; i < numValues; i++) {
        sum += pow((values[i] - mean), 2);
        
    }
    
    return sum / numValues;
}


float calculateSD(float variance)
{
    return sqrt(variance);
}

int main(int argc, const char * argv[])
{
    char filename[256];
  
    cout << "Filename: ";
    cin.getline(filename, 255,'\n');
    
    ifstream file;
    file.open(filename);
    int record = 0;
    
    while (file.good()) {
        if (!file.eof()) {
            file.getline(database[record].name, 255,'\t');
            int index = 0;
            while (file.peek() != '\n' && index < 128 && !file.eof()) {
                file >> database[record].times[index];
                index++;
            }
            database[record].numOfTimes = index;
            file.ignore();
            record++;
            
        }
    }
    cout << left << setw(30) << "ORGANISATION" << setw(10)  << "MEAN"  << setw(10) << "SD" << endl << endl;

    for (int i = 0; i<record; i++) {
       
        float mean = calculateMean(database[i].times, database[i].numOfTimes);
        database[i].SD = calculateSD(calculateVariance(database[i].times, database[i].numOfTimes, mean));
        cout  << setw(30) << database[i].name;
        cout  << setw(10) <<  mean;
        cout  << setw(10) <<  database[i].SD;
        cout << endl;
        
    }
    
    //Calculate Min and Max
    int minOrganisation = 0;
    int maxOrganisation = 0;
    
    for (int i = 0; i<record; i++) {
        if (database[i].SD < database[minOrganisation].SD) {
            minOrganisation = i;
        }
        else if(database[i].SD > database[maxOrganisation].SD)
        {
            maxOrganisation = i;
        }
    }
    
    cout << endl;
    cout << setw(20) << "Worst Organisation: " << database[maxOrganisation].name << endl;
    cout << setw(20) << "Best Organisation: " << database[minOrganisation].name << endl;
    
    return 0;
}


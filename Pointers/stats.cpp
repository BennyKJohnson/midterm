//
//  main.cpp
//  Stats
//
//  Created by Ben Johnson on 31/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{
    
    float n = 0;
    int *pointer = NULL;

    while (true) {
        cout << "Enter Positive Num: ";
        int temp;
        cin >> temp;
        if (temp != -1) {
          
            if (pointer == NULL) {
                int *storedNum = new int;
                
                pointer = storedNum;
                *pointer = temp;
                
            }
            else
                *pointer = temp;
            
            n++;
            pointer++;
        }
        else
        {
            pointer--;
            break;
        }
    }
    
    int sum = 0;
    for (int i =0; i<n; i++) {
        sum += *(pointer - i);
        
    }
    
    cout << "Average: " << sum / n << endl;
    cout << "Median: " << sum / 2.0 << endl;
    
    return 0;
}


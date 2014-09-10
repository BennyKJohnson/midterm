//
//  main.cpp
//  Donations
//
//  Created by Ben Johnson on 31/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{
    float donations[100];
    int n = 0;
    for (int i = 0; i < 100; i++) {
        cout << "Enter donation: ";
        float temp;
        
        cin >> temp;
        if (temp != -1)
        {
            donations[i] = temp;
            n++;
        }
        else
        {
            break;
        }
    }
    float *pointers = new float[100];
    for (int i = 0; i < 100; i++) {
        pointers[i] = donations[i];
    }
    //Loop through all elements
    
    //pos_min is short for position of min
    
    int pos_min,temp;
    
	for (int i=0; i < n-1; i++)
	{
	    pos_min = i;//set pos_min to the current index of pointersay
		
		for (int j=i+1; j < n; j++)
		{
            
            if (pointers[j] < pointers[pos_min])
                pos_min=j;
		}
		
        if (pos_min != i)
        {
            temp = pointers[i];
            pointers[i] = pointers[pos_min];
            pointers[pos_min] = temp;
        }
	}
    
    for (int i = 0; i < n; i++) {
        cout << pointers[i] << endl;
    }

    
    return 0;
}


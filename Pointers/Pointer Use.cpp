//
//  main.cpp
//  lecture
//
//  Created by Ben Johnson on 26/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include <iostream>

using namespace std;
void funct(int*& p)
{
    p = new int;
    if (p == NULL) {
        return;
    }
    *p = 9;
}


int main()
{
    int *p = NULL;
    funct(p);
    cout << "Address of pointer: " << &p << endl;
    cout << "Pointer is pointing to address: " <<  p << endl;
    cout << "Pointer value: " << *p << endl;

    return 0;
}


//
//  depend.cpp
//  HeaderDetector
//
//  Created by Ben Johnson on 20/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include "depend.h"
int currentPosition = 0;

bool get_text(char currentChar,char (&find)[256], int &currentPosition)

{
   // char find[] = "#include";
    if (find[currentPosition] == currentChar && find[currentPosition + 1] == '\0') {
            currentPosition = 0;
            return true;
    }
    else if (find[currentPosition] == currentChar)
    {
        currentPosition++;
    
    }
    else
    {
        currentPosition = 0;
        return false;
    }
    
    return false;
}
void get_dependencies(ifstream &file,char (&result)[10][256], int &currentArrayPosition)
{
    char find[256] = "#include";
    int currentPosition = 0;
    
    while (file.good()) {
        
        if (get_text(file.get(), find, currentPosition) && !file.eof()) {
            while (file.good()) {
                
                char currentChar = file.get();
                if (currentChar == '"' || currentChar == '<') {
                    //Beginning Of content
                    int headerPosition = 0;
                    while (file.good()) {
                        currentChar = file.get();
                        if (currentChar == '"' || currentChar == '>') {
                            result[currentArrayPosition][headerPosition] = '\0';
                            currentArrayPosition++;
                            
                            break;
                        }
                        else
                        {
                            result[currentArrayPosition][headerPosition] = currentChar;
                            headerPosition++;
                        }
                    }
                    
                }
                else if (currentChar != ' ' || currentChar == '\t')
                {
                    break;
                }
            }
            
        }
        
    }

}


#include "vignere.h"
#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

char saveFilename[256];
char openFilename[256];

void setSaveFile(char filename[256])
{
    strcpy(saveFilename, filename);
    

}
void openFile(char filename[256])
{
}
void vignere_encrypt(char data[], char key[])
{
    int i = 0;
    int keyPosition = 0;
    int keyLength =0;
    while (key[i] != '\0') {
        keyLength++;
        i++;
    }
    i =0;
    
   // char result[1024];
    
    //Go to null byte
    while (data[i] != '\0') {
        //cout << "Data: " << data[i] - 65;
        if (64<data[i] && data[i] <91) {
            data[i] = ((data[i] - 65) + (key[keyPosition] - 65) % 26);
            if (data[i] > 25) {
                data[i] = data[i] % 26;
            }
            data[i] += 65;

        }
        else
        {
            data[i] = data[i];
            keyPosition--;
        
        }
        if ((keyPosition) == keyLength) {
            keyPosition = 0;
        }
    //    cout << data[i];
        i++;
        keyPosition++;
        
        
    }
   // data = result;
    
    ofstream out(saveFilename, ios::out | ios::app);
    out.write((char *)data, i);
    out << endl;
    out.close();
    


}

void vignere_decrypt(char data[], char key[])
{
    cout << endl;
    int i = 0;
    int keyPosition = 0;
    int keyLength =0;
    
    while (key[i] != '\0') {
        keyLength++;
        i++;
    }
    i = 0;
    
    //Go to null byte
    while (data[i] != '\0') {
        if (64<data[i] && data[i] <91) {
            data[i] = ((data[i] - 65) - (key[keyPosition] - 65) % 26);
            int numResult = data[i];
            if (numResult < 0) {
                data[i] = 26 + numResult;
            }
            data[i] += 65;

        }
        else
        {
            data[i] = data[i];
            keyPosition--;
            
            
        }
        if ((keyPosition) == keyLength) {
            keyPosition = 0;
        }

        
        
        
        //cout << "Data: " << data[i] - 65;
        keyPosition++;
        i++;
        
        
    }

    ofstream out(saveFilename, ios::out|ios::app);
    out.write((char *)data, i);
    out << endl;
    out.close();
    



}
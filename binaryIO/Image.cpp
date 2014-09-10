//
//  Image.cpp
//  Image2
//
//  Created by Ben Johnson on 24/08/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include "Image.h"
#include <iostream>

using namespace std;



void assignPixelsFromStream(image &(currentImage),ifstream &(stream), int width, int height)
{
    
    for (int h = height;h < currentImage.height + height; h++) {
        for (int w = width;w < currentImage.width + width; w++) {
            
            
            stream >>  currentImage.pixels[h+height][w+width].r;
            stream >>  currentImage.pixels[h+height][w+width].g;
            stream >> currentImage.pixels[h+height][w+width].b;
        }
        
        //Ignore WhiteSpace
        //stream.ignore();
    }
    
}
bool writeImageFile(image &(source),bool header, int tag)
{
    ofstream outFile;
    if(tag == 0)
    {
        outFile.open("test.ppm", ios::out| ios::binary|ios::app);
    }
    else
    {
        char name[] = "imga.ppm";
        // name[3] = static_cast<char>(tag);
        outFile.open(name, ios::out| ios::binary);
        
    }
    
	if (!outFile.good())
		return 0;
    if (header) {
        outFile << source.magicNumber << endl;
        outFile << source.comment << endl;
        if (tag > 0) {
            outFile << (source.width) << " ";
            outFile << (source.height ) << endl;
        }
        else
        {
            outFile << (source.width * 2) << " ";
            outFile << (source.height * 2 ) << endl;
        }
        
        outFile << source.bitDepth << endl;
    }
    
    
    //writing overall mosaic.
    // height and horizantal is multiplied by 2 because 2 images of same size
    if (tag > 0) {
        for (int i =0; i < (source.height); i++)
        {
            for (int j =0; j < (source.width); j++)
            {
                outFile << source.pixels[i][j].r;
                outFile << source.pixels[i][j].g;
                outFile << source.pixels[i][j].b;
            }
        }
    }
    else
    {
        for (int i =0; i < (source.height); i++)
        {
            for (int j =0; j < (source.width*2); j++)
            {
                outFile << source.pixels[i][j].r;
                outFile << source.pixels[i][j].g;
                outFile << source.pixels[i][j].b;
            }
        }
        
    }
    
    outFile.close();
    
    
    return true;
}

void createMosaic(image images[], int width, int height)
{
    image mosaic;
    mosaic.dimension.width = images[0].dimension.width * 2;
    mosaic.dimension.height = images[0].dimension.height * 2;
    mosaic.bitDepth = images[0].bitDepth;
    
    
    for (int i = 0; i < 2; i++) {
        //Set Width
        if (i % 2 == 0)
            width = images[i].dimension.width;
        else
            width = 0;
        
        if (i / 2 > 0)
            height = images[i].dimension.height;
        
        else
            height = 0;
        
        for (int h = 0;h < images[h].dimension.height / 2; h++) {
            for (int w = 0;w < images[h].dimension.width; w++) {
                mosaic.pixels[height + h][width + w].r = images[h].pixels[h][w].r;
                mosaic.pixels[height + h][width + w].g = images[h].pixels[h][w].g;
                mosaic.pixels[height + h][width + w].b = images[h].pixels[h][w].b;
            }
        }
        //Set width for 2,
    }
    
    // writeImageFile(mosaic, height);
    
}

bool readImage(char filename[], image &(source), int width, int height, bool header)
{
    ifstream inFile(filename, ios::in | ios::binary );
    //ifstream openFile(filename, ios::in | ios::binary);
    
	if (inFile.good())
	{
        
        while(!inFile.eof())
        {
            
            inFile >> source.magicNumber;
            inFile >> source.comment;
            inFile >> source.width;
            inFile >> source.height;
            inFile >> source.bitDepth;
            if (source.width > 400 || source.height > 400) {
                return false;
            }
            
            //assignPixelsFromStream(source, inFile, width, height);
            for (int h = height;h < source.height + height; h++) {
                for (int w = width;w < source.width + width; w++) {
                    
                    
                    inFile >>  source.pixels[h][w].r;
                    inFile >>  source.pixels[h][w].g;
                    inFile >> source.pixels[h][w].b;
                }
            }
            inFile.peek();
            
            
            
            
        }
    }
    inFile.close();
    return true;
    
}
bool collapseMosaic()
{
    ifstream inFile("test.ppm" , ios::in | ios::binary);
    int width = 0;
    int height = 0;
    image source;
    
    while(!inFile.eof())
    {
        
        inFile >> source.magicNumber;
        inFile >> source.comment;
        inFile >> source.width;
        inFile >> source.height;
        inFile >> source.bitDepth;
        
        
        //To keep track of the number of pixels
        int i = 0;
        int j = 0;
        
        
        for (int i = 0; i <	source.width ; i++)
        {
            for (int j = 0; j < source.height ; j++)
            {
                inFile >> source.pixels[i][j].r;
                inFile >> source.pixels[i][j].g;
                inFile >> source.pixels[i][j].b;
            }
        }
        inFile.peek();
        
        
    }
    
    inFile.close();
    int h = 0;
    for (int i = 0; i < 4; i+=2) {
        image images[2];
        
        char filename1[128];
        char filename2[128];
        
        
        for (int i = 0; i<source.height /2; i++) {
            int j;
            for (j = 0; j<(source.width/2); j++) {
                images[0].pixels[i][j].r = source.pixels[i + h][j].r;
                images[0].pixels[i][j].g = source.pixels[i + h][j].g;
                images[0].pixels[i][j].b = source.pixels[i + h][j].b;
                
                
            }
            for (int k = j; k<source.width; k++) {
                images[1].pixels[i][k - j].r = source.pixels[i + h][k].r;
                images[1].pixels[i][k - j].g = source.pixels[i + h][k].g;
                images[1].pixels[i][k - j].b = source.pixels[i + h][k].b;
            }
        }
        h = source.height /2;
        
        cout << "Enter Output File Name " << i+1 <<  "(quadrant " << i+1 << "): ";
        cin >> filename1;
        cout << "Enter Output File Name " << i+2 <<  "(quadrant " << i+2 << "): ";
        cin >> filename2;
        
        ofstream outFile(filename1, ios::out | ios::binary );
        
        
        outFile << source.magicNumber << endl;
        outFile << source.comment << endl;
        outFile << (source.width / 2) << " ";
        outFile << (source.height / 2) << endl;
        outFile << source.bitDepth << endl;
        
        for (int i = 0; i < (source.height/2) ; i++)
        {
            for (int j = 0; j < (source.width/2) ; j++)
            {
                outFile << images[0].pixels[i][j].r;
                outFile << images[0].pixels[i][j].g;
                outFile << images[0].pixels[i][j].b;
            }
        }
        outFile.close();
        outFile.open(filename2, ios::out | ios::binary );
        
        outFile << source.magicNumber << endl;
        outFile << source.comment << endl;
        outFile << (source.width / 2) << " ";
        outFile << (source.height / 2) << endl;
        outFile << source.bitDepth << endl;
        
        for (int i = 0; i < (source.height/2) ; i++)
        {
            for (int j = 0; j < (source.width/2) ; j++)
            {
                outFile << images[1].pixels[i][j].r;
                outFile << images[1].pixels[i][j].g;
                outFile << images[1].pixels[i][j].b;
            }
        }
        outFile.close();
        
    }
    
    
    return true;
    
}
bool buildMosaic()
{
    
	char filenames[4][256];
	//char targetName[128];
	image source;
	//ppmFile target;
    int width = 0;
    int height = 0;
    
	cout << "Enter source filename: ";
	//cin >> filename;
    bool header = true;
    
    
    for (int i = 0; i < 4; i++) {
        if ((i + 1) % 2 == 0)
        {
            width = source.width;
            header = false;
            
        }
        else
            width = 0;
        
        if (i / 2 > 0)
        {
            //height = source.height;
            if (i == 2) {
                writeImageFile(source, true);
            }
            
        }
        else
            height = 0;
        
        
        
        cout << "Enter Input File Name " << i+1 << " (quadrant " << i+1 << "): ";
        cin >> filenames[i];
        if(!readImage(filenames[i],source,width,height,header))
        {
            return false;
        }
    }
    writeImageFile(source, false);
    
    return true;
    
    
}

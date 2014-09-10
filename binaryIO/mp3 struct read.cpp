//
//  main.cpp
//  mp3
//
//  Created by Ben Johnson on 27/05/2014.
//  Copyright (c) 2014 Ben Johnson. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;
struct Tag
{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[29];
    char tracknumber;
    char genre;
    
};

int example = 0;
char genre[126][128] = {"Blues", "Classic Rock", "Country", "Dance","Disco", "Funk", "Grunge", "Hip-Hop",
    "Jazz", "Metal", "New Age", "Oldies", "Other", "Pop",
    "R&B", "Rap", "Reggae", "Rock", "Techno", "Industrial",
    "Alternative","Ska", "Death Metal", "Pranks", "Soundtrack",
    "Euro-Techno","Ambient", "Trip-Hop", "Vocal", "Jazz+Funk",
    "Fusion", "Trance","Classical", "Instrumental", "Acid",
    "House",
    "Game", "Sound Clip","Gospel", "Noise",
    "AlternRock","Bass", "Soul", "Punk", "Space", "Meditative",
    "Instrumental Pop", "Instrumental Rock","Ethnic", "Gothic",
    "Darkwave", "Techno-Industrial", "Electronic","Pop-Folk",
    "Eurodance", "Dream", "Souther Rock", "Comedy", "Cult",
    "Gangsta", "Top 40", "Christian Rap", "Pop/Funk", "Jungle",
    "Native American", "Cabaret", "New Wave", "Psychadelic",
    "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk",
    "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock",
    "Folk", "Folk-Rock", "National Folk",
    "Swing", "Fast Fusion", "Bebob", "Latin", "Revival",
    "Celtic", "Bluegrass", "Avantgarde", "Gothic Rock",
    "Progressive Rock", "Psychedelic Rock", "Symphonic Rock",
    "Slow Rock", "Big Band", "Chorus", "Easy Listening",
    "Acoustic", "Humour", "Speech", "Chanson", "Opera",
    "Chamber Music", "Sonata", "Symphony", "Booty Bass",
    "Primus", "Porn Groove", "Satire", "Slow Jam", "Club",
    "Tango", "Samba", "Folklore", "Ballad", "Power Ballad",
    "Rhythmic Soul", "Freestyle", "Duet", "Punk Rock", "Drum Solo",
    "Acapella", "Euro-House", "Dance Hall"};





bool hasText(char content[],char search[],int length)
{
    int currentChar = 0;
    int csc = 0;
    
    while (content[currentChar] != 0) {
        if (content[currentChar] == search[csc]) {
            csc++;
        }
        else
        {
        if(csc > 0)
            csc = 0;
        
        }
        currentChar++;
    }
    if (csc == length) {
        return true;
        
    }
    return false;
}
void printTag(Tag tag)
{
    cout << "Title: ";
    cout.write(tag.title, 30);
    cout << endl;
    
    cout << "Artist: ";
    cout .write(tag.artist, 30);
    cout << endl;
    
    cout << "Album: ";
    cout.write(tag.album, 30);
    cout << endl;
    
    cout << "Year: ";
    cout .write(tag.year, 4);
    cout << endl;
 
    cout << "Comment: ";
    cout.write(tag.comment, 29);
    cout << endl;
    
    cout << "Track Number: " <<static_cast<int> ( tag.tracknumber ) << endl;
    cout << "Genre: " << genre[tag.genre] << endl;


}
void getLineFromStream(char input[])
{
    bool takeInput = true;
    
    int count = 0;
    
    while (cin && takeInput) {
        char currentChar = cin.get();
        if (currentChar == '\n') {
            takeInput = false;
        }
        else
        {
            input[count] = currentChar;
            count++;
            
        }
        
    }

}
int main(int argc, const char * argv[])
{
    char filename[256];// = "/Users/benjohnson/Desktop/test.mp3";
    cin >> filename;
    
    char search[256] = ".mp3";

    ifstream file;
    file.open(filename, ios::binary);
    

    if (file.good()) {
  
    if (hasText(filename, search, 4)) {
        Tag mp3Tag;
        file.seekg (-128L,ios::end );
        file.read((char *) &(mp3Tag), sizeof(Tag));
        file.close();
        
        if(strcmp(mp3Tag.tag, "TAG"))
        {
            
            cout << "File is OK and has valid ID3v1.1 tag" << endl;
            printTag(mp3Tag);
            cout << "Do you wish to update the comment field Y/N? ";
            char response;
            cin >> response;
            if (response == 'y' || response == 'Y') {
                cout << "Comment: ";
                char comment[29];
                //cin >> comment;
                cin.get();
                cin.getline(comment, 29,'\n');
                
                ofstream out (filename,ios::in |ios::out);
                out.seekp(-31L,ios::end);
                out.write((char*)&comment,sizeof(comment));
                
                out.close();
            }
        }
    }
    else
    {
    cout << "Not a mp3 file";
    }
        file.close();

    }
    // insert code here...
  //  std::cout << "Hello, World!\n";
    return 0;
}


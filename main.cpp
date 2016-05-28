//
//  main.cpp
//  Project 4
//
//  Created by Samuel Donner on 5/25/16.
//  Copyright © 2016 Samuel Donner. All rights reserved.
//

#include <iostream>
#include <sstream>  // for istringstream and ostringstream
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd)  ||  (cmd == '\n'  &&  !inf.get(cmd)) )
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
    }
    return false;
}

void createDelta(istream& oldf, istream& newf, ostream& deltaf);
// create delata use one pass for the new file, store to a hash table, and the hash table map to a character or integer
// second pass going through the old file
bool applyDelta(istream& oldf, istream& deltaf, ostream& newf)
{
    char command;
    int length;
    int offset;
    char currentChar;
    
    do
    {
        if(!getCommand(deltaf, command, length, offset))
            exit(1);
        if(command == 'A')
        {
            for(int i = 0; i < length; i++)
            {
                deltaf.get(currentChar);
                newf << currentChar;
            }
        }
        if(command == 'C')
        {
            oldf.seekg(offset);
            for(int i = 0; i < length; i++)
            {
                oldf.get(currentChar);
                newf << currentChar;
            }
        }
    }
    while(command != 'x');
    
    
    return true;
}


int main()
{
    ifstream oldFile;
    oldFile.open("/Users/samueldonner/Desktop/UCLA/Q3/Computer\ Science\ 32/Project\ 4/Project\ 4/smallmart1.txt", ifstream::in);
    ifstream deltaF;
    deltaF.open("/Users/samueldonner/Desktop/UCLA/Q3/Computer\ Science\ 32/Project\ 4/Project\ 4/smallMartDelta.txt", ifstream::in);
    ofstream newF;
    newF.open("/Users/samueldonner/Desktop/UCLA/Q3/Computer\ Science\ 32/Project\ 4/Project\ 4/smallMartOutput.txt", ifstream::out);
    applyDelta( oldFile, deltaF, newF);
}
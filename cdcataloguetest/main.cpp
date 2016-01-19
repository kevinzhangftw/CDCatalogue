//
//  main.cpp
//  cdcataloguetest
//
//  Created by Kai Zhang on 2016-01-18.
//  Copyright © 2016 Kai Zhang. All rights reserved.
//

#include <iostream>
#include <string>
#include <assert.h>

#include "cd.h"
#include "cdcatalogue.h"

using namespace std;

// forward function declarations
void TestFunc1();
void TestFunc2();
void TestFunc3();
void PrintMenu();

int main(int argc, const char * argv[]) {
    cout << "Entering test function 1: " << endl;
    TestFunc1();
    
    cout << "Returned from test function 1.\nEntering test function 2: " << endl;
    //TestFunc2();
    
    cout << "Returned from test function 2.\nEntering interactive test function: " << endl;
    //TestFunc3();
    return 0;
}

// test function code
void TestFunc1()
{
    // call default constructor
    CDCatalogue cat1;
    
//    // remove some non-existent item
//    cat1.Remove(CD("Wham!", "Make It Big"));
    
    
    //Dude do you take duplicates?
    
    // insert some item
//    for (int i = 0; i < 100; i++) {
//        //TODO: duplicates not allowed.
//        cat1.Insert(CD("KISS", "Destroyer"));
//        cat1.Insert(CD("Rick", "AStley"));
//    }
//
    
    cat1.Insert(CD("ASS", "Destroyer1"));
    cat1.Insert(CD("BASS", "Destroyer2"));
    cat1.Insert(CD("CASS", "Destroyer3"));
    cat1.Insert(CD("DASS", "Destroyer4"));
    cat1.Insert(CD("EASS", "Destroyer5"));
    cat1.Insert(CD("FASS", "Destroyer6"));
    cat1.Insert(CD("GASS", "Destroyer7"));
    
    
    // remove some non-existent item
    //TODO: expecting to remove ass destroyer 1
    cat1.Remove(CD("ASS", "Destroyer1"));
    assert(cat1.Count() == 6);
    cout << "Number of discs in collection: " << cat1.Count() << endl;
    cout << endl;
}

void TestFunc2()
{
    CDCatalogue cat1;
    
    // copy constructor
    CDCatalogue cat2(cat1);
    
    // remaining function calls
    cat2.Boycott("Aqua");
    
    int index = cat1.Find(CD("New Kids on the Block", "Hangin' Tough"));
//
//    // set function calls
//    CDCatalogue catjoin(cat1.Join(cat2));
//    CDCatalogue catcommon(cat1.Common(cat2));
//    CDCatalogue catsplit(cat1.Split(cat2));
}

void TestFunc3()
{
    // local variables for interaction
    int choice = -1;
    string inputchoice;
    string inputartist;
    string inputalbum;
    int findindex;
    bool boycottresult;
    
    CDCatalogue mycat;
    
    while (choice != 6)
    {
        PrintMenu();
        // get the menu choice from standard input
        getline(cin, inputchoice);
        choice = atoi(inputchoice.c_str());
        
        switch (choice)
        {
            case 1: // Add a CD
                cout << "\nEnter the artist name: ";
                getline(cin, inputartist);
                cout << "\nEnter the album name: ";
                getline(cin, inputalbum);
                if (mycat.Insert(CD(inputartist, inputalbum)))
                    cout << "CD added to collection." << endl;
                else
                    cout << "You already have this CD." << endl;
                break;
            case 2: // Remove a CD
                cout << "\nEnter the artist name: ";
                getline(cin, inputartist);
                cout << "\nEnter the album name: ";
                getline(cin, inputalbum);
                if (mycat.Remove(CD(inputartist, inputalbum)))
                    cout << "CD removed from collection." << endl;
                else
                    cout << "You don't own this CD." << endl;
                break;
            case 3: // Display collection size
                cout << "Collection contains " << mycat.Count() << " CDs." << endl;
                break;
            case 4: // Find a CD index
                cout << "\nEnter the artist name: ";
                getline(cin, inputartist);
                cout << "\nEnter the album name: ";
                getline(cin, inputalbum);
                findindex = mycat.Find(CD(inputartist, inputalbum));
                if (findindex >= 0)
                    cout << "CD found at index " << findindex << "." << endl;
                else
                    cout << "CD not found." << endl;
                break;
            case 5: // Boycott an artist
                cout << "\nEnter the artist name: ";
                getline(cin, inputartist);
                boycottresult = mycat.Boycott(inputartist);
                if (boycottresult)
                    cout << "All CDs by " << inputartist << " have been dumped on craigslist." << endl;
                else
                    cout << "No eligible CDs to dump." << endl;
                break;
            case 6: // Quit
                // no need to do anything, will cause while loop to break
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

void PrintMenu()
{
    cout << "********************************************************\n"
    << "* Please select an option:                             *\n"
    << "* 1. Add a CD                  5. Boycott an artist    *\n"
    << "* 2. Remove a CD                                       *\n"
    << "* 3. Display collection size                           *\n"
    << "* 4. Find a CD index           6. Quit                 *\n"
    << "********************************************************\n" << endl;
    cout << "Enter your choice: ";
}

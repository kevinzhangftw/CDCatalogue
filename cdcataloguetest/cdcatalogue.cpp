#include "cdcatalogue.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#include "cd.h"

///////////////////////////////
// Constructors / Destructor //
///////////////////////////////

// Default constructor
// Creates an empty CDCatalogue with default array size (4)
CDCatalogue::CDCatalogue(){
    maxsize = 4;
    numcds = 0;
    cds= new CD[maxsize];
    //cout << "cat created maxsize is " << maxsize << endl;
    //cout << "cat created numcds is " << numcds << endl;
}

void CDCatalogue::CopyArray(const CDCatalogue& cat){
    maxsize = cat.maxsize;
    numcds = cat.numcds;
    cds = new CD[cat.maxsize];
    copy(cat.cds, cat.cds+cat.maxsize, cds);
    //cout << "cat(params) created maxsize is " << maxsize << endl;
    //cout << "cat(params) created numcds is " << numcds << endl;
}

// Copy constructor
// Creates a new CDCatalogue object,
//   performs a deep copy of the cat parameter's fields
CDCatalogue::CDCatalogue(const CDCatalogue& cat){
    CopyArray(cat);
}


// Destructor
// Releases all memory allocated to private pointer members
CDCatalogue::~CDCatalogue(){
    delete[] cds;
}

// Insert - performs a set insertion with the CD catalogue
// Inserts CD and returns true if CD is not already in the catalogue
// Does not insert and returns false if a CD with a matching artist and album name
//   already exists in the registry
// If the array is already filled before the insertion occurs, then
//   first create a new dynamic array double the size of the old array,
//   copy all CD objects from old array to new array,
//   deallocate memory associated with the old array,
//   and insert the new CD and return true.
// POST:  catalogue contains CD
// PARAM: disc = item to be inserted, its fields should not be empty string
// NOTE:  since overloaded assignment operator has not been defined,
//          "insertion" will mean updating all fields of the CD at the appropriate index
bool CDCatalogue::Insert(CD disc){
    if (numcds ==0) {
        //just insert  cd
        cds[0]= disc;
        numcds++;
        return true;
    }else{
        //check for duplicates
        for (int i =0; i<numcds; ++i) {
            //if there are no duplicates
            if (disc != cds[i]) {
                //if the array is full
                if (numcds==maxsize){
                    CD* oldcds = cds;
                    maxsize = 2*maxsize;
                    cds = new CD[maxsize];
                    copy(oldcds, oldcds+maxsize, cds);
                    delete[] oldcds;
                }
                //insert CD
                cds[i]= disc;
                numcds++;
                cout <<"CD inserted" << endl;
                return true;
            }else{ //if there is a duplicate
                cout <<"error, CD is already here" << endl;
                return false;
            }
        }
        cout <<"for loop never run, not suppose to be here" << endl;
        return false;
    }
    
//    for (int i = 0; i<maxsize; i++){
//        if (disc != cds[i]) {
//            if (numcds==maxsize){
//                CD* oldcds = cds;
//                maxsize = 2*maxsize;
//                cds = new CD[maxsize];
//                copy(oldcds, oldcds+maxsize, cds);
//                delete[] oldcds;
//            }
//            //insert CD
//            cds[i]= disc;
//            numcds++;
//            cout <<"CD inserted" << endl;
//            return true;
//        }else{
//            cout <<"error, CD is already here" << endl;
//            return false;
//        }
//    }
//    return false; //HAX
}

// Remove - performs a set removal with the CD catalogue
// Removes a CD with all matching parameters if one exists in the catalogue
// Returns false if a CD with the same parameters does not exist in the catalogue
// POST:  catalogue does not contain CD
// PARAM: disc = item to be removed, its fields should not be empty string
// NOTE:  "removal" if successful will be done by updating the parameters of the
//          CD at the appropriate index using the parameters of the CD in
//          the last valid index of the collection; then decrements count and returns true;
bool CDCatalogue::Remove(CD disc){
    if (numcds == 0) {
        //collections is empty, nothing to remove
        cout <<"collection is empty, nothing to remove" << endl;
        return false;
    }else{
        //check all the cds
        for (int i=0; i<numcds; ++i){
            //if match found
            if (disc == cds[i]){
                //remove cd
                cds[i]= cds[numcds-1];
                numcds--;
                cout <<"cd removed" << endl;
                return true;
            }else{ //if no match found
                cout <<"no such cd" << endl;
                return false;
            }
        }
        cout <<"error: for loop never run, not suppose to be here" << endl;
        return false; //HAX
    }
}

// Locates the array index of a CD with matching parameters
// Returns -1 if no CD with matching parameters exists in the catalogue
// PARAM: disc = item to be located, its fields should not be empty string
int CDCatalogue::Find(CD disc) const{
    if (numcds==0) {
        cout <<"no such cd, collection is empty" << endl;
        return -1;
    }else{
        for (int i=0; i<numcds; ++i){
            if (disc == cds[i]){
                //cd located
                cout <<"cd index is "<< i << endl;
                return i;
            }else{
                cout <<"no such cd" << endl;
                return -1;
            }
        }
        cout <<"error: for loop didnt run" << endl;
        return false; //HAX
    }

}

// Removes all CDs from the catalogue with artist matching the provided argument
// Returns false if there are not matching CDs or input is empty string,
//   otherwise returns true if at least one CD is removed
// Remaining items may appear in the array in any order, with the requirement that
//   there are no "empty" spaces in the array (i.e. an array with 5 items must occupy indices 0-4)
// POST:  catalogue contains no instances of CDs with the supplied artist name
// PARAM: dontlikeanymore = name of artist whose CDs should be removed from the catalogue
bool CDCatalogue::Boycott(string dontlikeanymore){
    if (numcds==0) {
        cout <<"nothing to boycott" << endl;
        return false;
    }else{
        //check all the cds
        for (int i=0; i<numcds; ++i){
            if (dontlikeanymore == cds[i].GetArtist()){
                //remove cd
                cds[i]= cds[numcds-1];
                numcds--;
            }else{
                cout <<"not matching CDs or input is empty string" << endl;
                return false;
            }
        }
        cout <<"all targeted CDs removed" << endl;
        return true;
    }

}

// Returns the number of CDs in the catalogue
int CDCatalogue::Count() const{
    return numcds;
}

//    // Returns the set union of this and cat
//   // POST: union contains CD of this and cat, with no duplicate CDs (both parameters matching).
CDCatalogue CDCatalogue::Join(const CDCatalogue& cat) const{
	CDCatalogue joinedcds = CDCatalogue();
	for (int i=0; i<numcds; ++i){
		//compare the 2 catalogues
		//add or dont add to joinedcds
	}
	return joinedcds;
}
//
//   // Returns the set intersection of this and cat
//   // POST: intersection contains CDs in both this and cat (both parameters matching).
//   CDCatalogue CDCatalogue::Common(const CDCatalogue& cat) const{
//	for (int i=0; i<numcds; ++i){

//	}
//}
//
//   // Returns the set difference of this and cat
//   // CDs in both catalogues must have a full set of matching parameters
//   //   for a CD to be removed in the split.
//   // POST: difference contains CDs in this but not also in cat
//   CDCatalogue CDCatalogue::Split(const CDCatalogue& cat) const{
//	for (int i=0; i<numcds; ++i){

//	}
//}

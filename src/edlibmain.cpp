/*
 *   The way to run this code is 
 *   1. g++ -o hirschberg hirschberg.cpp
 *   2. ./hirschberg
 *   Reads a new file in.txt with two strings
 *   A new file output.txt is generated with allignment 
*/

#include<bits/stdc++.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include <cstdio>
#include "edlib.h"

using namespace std;

int main(int argc, char *argv[]){


    if (argc < 3){
        cout<< "provide both testfiles for X and Y";
        return 0;
    }

    string Xfile, Yfile, X, Y;
    Xfile = argv[1];
    Yfile = argv[2];

    ifstream input1 (Xfile);
    ifstream input2 (Yfile);
    ofstream output ("outputEdlib.txt");

    input1 >> X;
    input2 >> Y;

    EdlibAlignResult result = edlibAlign(X.c_str(), X.size(), Y.c_str(), Y.size(), edlibDefaultAlignConfig());
    if (result.status == EDLIB_STATUS_OK) {
        printf("edit_distance(' %s %lu', ' %s' %lu) = %d\n", Xfile.c_str(), X.size(),  Yfile.c_str(), Y.size(), result.editDistance);
        printf("Alignment %s %d" , result.alignment, result.alignmentLength);
    }
    
    edlibFreeAlignResult(result);
    return 0;

}
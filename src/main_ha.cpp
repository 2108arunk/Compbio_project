#include<bits/stdc++.h>
#include <lib.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// This is the implementation of Hirshberg's Algorithm

int editDistanceNaive(string &X, string &Y){

    int ins = 1, del = 1;
    int row = X.size()+1, col = Y.size()+1;

    int *dp = (int*)malloc(sizeof(int) * (row) * (col));
    
    *(dp) = 0;
 
    for (uint64_t i = 1; i <= X.size(); i++)
        *(dp + i*col + 0) = *(dp + (i-1)*col + 0) + 1;

    for (uint64_t j = 1; j <= Y.size(); j++)
        *(dp + 0*col + j ) = *(dp + 0*col + (j-1)) + 1;


    for (uint64_t i = 1; i <= X.size(); i++){
        for (uint64_t j = 1; j <= Y.size(); j++){
            int delta = 0;
            if ( X[i-1] != Y[j-1]){
                    delta = 1;
            }
            *( dp + i*col + j) =     *(dp + (i-1)*col + (j-1)) + delta;
            *( dp + i*col + j) = min(*(dp + (i)*col + j), *(dp + (i-1)*col + (j)) + ins );
            *( dp + i*col + j) = min(*(dp + (i)*col + j), *(dp + (i)*col + ((j-1))) + del);
        }
    }

    free(dp);

    return 0;
}

// This is an Spacemoptimised implementation using n + O(1)
// Temp array of n words, two extra variables ed & prev are used
// amouting to a total complexity of n + O(1)

void printNaive(vector <vector<int>> temp, string X){

     for (uint64_t i = 0; i < temp.size(); i++){
        if (i==0)
            printf("x = %3c |", '*');
        else
            printf("x = %3c |", X[i-1]);

        for (uint64_t j = 0; j < temp[0].size(); j++){
            printf("%2d ", temp[i][j]);
        }
        cout << endl;
    }
}

void print(vector<int> &temp, int xmid, string str){
    cout<<str;
    printf("x = %3d |", xmid);
    for (auto &x:temp)
        printf("%2d ", x);
    cout << endl;
}

uint64_t editDistanceSpace( string &X, string &Y, vector <uint64_t> &xm){

    xm.resize(Y.size()+1, 0);

    vector <uint64_t> temp(Y.size(),0);
    uint64_t ed=0, prev;

    for (uint64_t i = 0; i < temp.size(); i++)
        temp[i] = i+1;

    for (uint64_t i = 0; i < X.size(); i++){        
        ed = i+1;
        prev = i;

        if (i == X.size()/2-1)
            xm[0] = ed;

        for (uint64_t j = 0; j < Y.size(); j++){
            if ( X[i] != Y[j]){
                prev = prev + 1;
            }
            ed = min( min(ed+1, temp[j]+1 ),prev );
            prev = temp[j];
            temp[j] = ed;
        }

        if (i == X.size()/2-1){
            for (uint64_t k = 0; k < Y.size(); k++){   
                xm[k+1] = temp[k];     
            }
        }
    }
    return ed;
}


uint64_t editDistanceSpace2( string &X, string &Y, vector <uint64_t> &xm){

    xm.resize(Y.size()+1, 0);

    vector <uint64_t> temp(Y.size(),0);
    uint64_t ed=0, prev;

    for (uint64_t i = 0; i < temp.size(); i++)
        temp[i] = i+1;

    for (uint64_t i = 0; i < X.size(); i++){        
        ed = i+1;
        prev = i;

        if (i == X.size() - X.size()/2-1)
            xm[0] = ed;
        
        for (uint64_t j = 0; j < Y.size(); j++){
            if ( X[i] != Y[j]){
                prev = prev + 1;
            }
            ed = min( min(ed+1, temp[j]+1 ),prev );
            prev = temp[j];
            temp[j] = ed;
        }

        if (i == X.size() - X.size()/2-1){
            for (uint64_t k = 0; k < Y.size(); k++){   
                xm[k+1] = temp[k];     
            }
        }

    }
    return ed;
}

uint64_t calculateIndex(string &X, string &Y, vector <uint64_t> EdXmid){

    string Xr = X;
    string Yr = Y;

    reverse(Yr.begin(), Yr.end());
    reverse(Xr.begin(), Xr.end());

    vector <uint64_t> EdXrY;
    uint64_t ed = editDistanceSpace2(Xr, Yr, EdXrY);
    reverse(EdXrY.begin(), EdXrY.end());
    uint64_t index=0;

    for (uint64_t i = 0 ; i < EdXrY.size(); i++){
        if ( (EdXmid[i]+EdXrY[i]) == ed ){
            index = i;
            break;
        }
    }
    return index;
}

pair<string, string> HirschbergsAlgo( string &X, string &Y){

    if (X == "" && Y == "")
        return make_pair("","");

    if (X.length()==1 && Y.length()==1)
        return make_pair(X,Y);

    if (X == ""){
        string str;
        int k = Y.size();
        while (k--)
            str.push_back('-');
        return make_pair(str, Y);
    }

   if (Y == ""){   
        string str;
        int k = X.size();
        while (k--)
            str.push_back('-');
        return make_pair(X, str);
    }

    if (X.length() == 1){

        string y;
        bool flag = true;

        for (uint64_t i = 0; i < Y.size()-1; i++){
            if (X[0] == Y[i] && flag == true){
                y.push_back(X[0]);
                flag = false;
                continue;
            }
            y.push_back('-');
        }
        if (flag == true){
            y.push_back(X[0]);
        } else {
            y.push_back('-');
        }
        return make_pair(y,Y);
    }

    if (Y.length() == 1){
        string y;
        bool flag = true;
        for (uint64_t i = 0; i < X.size()-1; i++){
            if (Y[0] == X[i] && flag == true){
                y.push_back(Y[0]);
                flag = false;
                continue;
            }
            y.push_back('-');
        }
        if (flag == true){
             y.push_back(Y[0]);
        } else {
            y.push_back('-');
        }
        return make_pair(X,y);
    }

    int xl = X.length();
    int xmid = xl/2;

    vector <uint64_t> EdXmid;
    editDistanceSpace(X, Y, EdXmid);
    uint64_t yindex = calculateIndex(X, Y, EdXmid);

    string Xl = X.substr(0, xmid  ); 
    string Yl = Y.substr(0, yindex);
    string Xr, Yr;

    Xr = X.substr(xmid  ,  X.size() - xmid);
    Yr = Y.substr(yindex , Y.size() - yindex);

    auto tl = HirschbergsAlgo(Xl, Yl);
    auto tr = HirschbergsAlgo(Xr, Yr);

    return make_pair(tl.first + tr.first, tl.second + tr.second);

}

int main(int argc, char* argv[]){

    if (argc < 3){
        cout<< "provide both testfiles for X and Y";
        return 0;
    }

    string Xfile, Yfile, X, Y;
    Xfile = argv[1];
    Yfile = argv[2];


    ifstream input1 (Xfile);
    ifstream input2 (Yfile);
    ofstream output ("output.txt");

    input1 >> X;
    input2 >> Y;

    clock_t ct = clock();
    ct = clock();
    auto t = HirschbergsAlgo(X,Y);
    

    string edits(t.first.size(), ' ');
    uint64_t countedits = 0;

    for(uint64_t i = 0 ; i < t.first.size(); i++){
        if (t.first[i] == t.second[i])
            edits[i] = ('|');
        else
            countedits++;
    }
  
    ct = clock() - ct;
    //printf ("Hirschbergs Algo It took me (%f seconds).\n", ((float)ct)/CLOCKS_PER_SEC);

    output << t.first << endl;
    output << edits << endl;
    output << t.second << endl;
    
    input1.close();
    input2.close();
    return countedits;
}



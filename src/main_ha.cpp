#include<bits/stdc++.h>
#include <lib.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int editDistanceNaive(string &X, string &Y){

    int ins = 1, del = 1;
    int row = X.size()+1, col = Y.size()+1;

    int *dp = (int*)malloc(sizeof(int) * (row) * (col));
    
    *(dp) = 0;
 
    for (int i = 1; i <= X.size(); i++)
        *(dp + i*col + 0) = *(dp + (i-1)*col + 0) + 1;

    for (int j = 1; j <= Y.size(); j++)
        *(dp + 0*col + j ) = *(dp + 0*col + (j-1) ) +1;

    int ed;

    for (int i = 1; i <= X.size(); i++){

        for (int j = 1; j <= Y.size(); j++){
            int delta = 0;
            if ( X[i-1] != Y[j-1]){
                    delta = 1;
            }
            *( dp + i*col + j) =     *(dp + (i-1)*col + (j-1)) + delta;
            *( dp + i*col + j) = min(*(dp + (i)*col + j), *(dp + (i-1)*col + (j)) + ins );
            *( dp + i*col + j) = min(*(dp + (i)*col + j), *(dp + (i)*col + ((j-1))) + del);
            ed = *( dp + i*col + j);
        }
    }

    cout << "Edit distance Naive = " << ed << endl; 
    free(dp);

    return 0;
}

// This is an Spacemoptimised implementation using n + O(1)
// Temp array of n words, two extra variables ed & prev are used
// amouting to a total complexity of n + O(1)

void printNaive(vector <vector<int>> temp, string X){

     for (int i = 0; i < temp.size(); i++){

        if (i==0)
            printf("x = %3c |", '*');
        else
            printf("x = %3c |", X[i-1]);

        for (int j = 0; j < temp[0].size(); j++){
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

int editDistanceSpace( string &X, string &Y, vector <int> &xm){

    xm.resize(Y.size()+1, 0);

    vector <int> temp(Y.size(),0);
    int ed, prev;

    for (int i = 0; i < temp.size(); i++)
        temp[i] = i+1;

    for (int i = 0; i < X.size(); i++){        
        ed = i+1;
        prev = i;

        if (i == X.size()/2-1)
            xm[0] = ed;

        for (int j = 0; j < Y.size(); j++){
            if ( X[i] != Y[j]){
                prev = prev + 1;
            }
            ed = min( min(ed+1, temp[j]+1 ),prev );
            prev = temp[j];
            temp[j] = ed;
        }

        if (i == X.size()/2-1){
            for (int i = 0; i < Y.size(); i++){   
                xm[i+1] = temp[i];     
            }
        }
    }
    return ed;
}


int editDistanceSpace2( string &X, string &Y, vector <int> &xm){

    xm.resize(Y.size()+1, 0);

    vector <int> temp(Y.size(),0);
    int ed, prev;

    for (int i = 0; i < temp.size(); i++)
        temp[i] = i+1;

    for (int i = 0; i < X.size(); i++){        
        ed = i+1;
        prev = i;

        if (i == X.size() - X.size()/2-1)
            xm[0] = ed;
        
        for (int j = 0; j < Y.size(); j++){
            if ( X[i] != Y[j]){
                prev = prev + 1;
            }
            ed = min( min(ed+1, temp[j]+1 ),prev );
            prev = temp[j];
            temp[j] = ed;
        }

        if (i == X.size() - X.size()/2-1){
            for (int i = 0; i < Y.size(); i++){   
                xm[i+1] = temp[i];     
            }
        }

    }
    return ed;
}

int calculateIndex(string &X, string &Y, vector <int> EdXmid, int xmid){

    string Xr = X;
    string Yr = Y;

    reverse(Yr.begin(), Yr.end());
    reverse(Xr.begin(), Xr.end());

    vector <int> EdXrY;
    int ed = editDistanceSpace2(Xr, Yr, EdXrY);
    reverse(EdXrY.begin(), EdXrY.end());
    int index;

    for (int i = 0 ; i < EdXrY.size(); i++){
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

    if (X == Y)
        return make_pair(X,Y);

    if (X.length()==1 && Y.length()==1)
        return make_pair("|","|");

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

        for (int i = 0; i < Y.size()-1; i++){
            if (X[0] == Y[i] && flag == true){
                y.push_back(X[0]);
                flag = false;
                continue;
            }
            y.push_back('-');
        }
        if (flag == true){
            if (X[0] == Y[Y.size()-1])
                y.push_back(X[0]);
            else {
                Y[Y.size()-1] = '|';
                y.push_back('|');
            }
        } else {
            Y[Y.size()-1] = '|';
            y.push_back('|');
        }
        return make_pair(y,Y);
    }

    if (Y.length() == 1){
        string y;
        bool flag = true;
        for (int i = 0; i < X.size()-1; i++){
            if (Y[0] == X[i] && flag == true){
                y.push_back(Y[0]);
                flag = false;
                continue;
            }
            y.push_back('-');
        }
        if (flag == true){
            if (Y[0] == X[X.size()-1])
                y.push_back(Y[0]);
            else {
                X[X.size()-1] = '|';
                y.push_back('|');
            }
        } else {
            X[X.size()-1] = '|';
            y.push_back('|');
        }
        return make_pair(X,y);
    }

    int xl = X.length();
    int yl = Y.length();
    int xmid = xl/2;

    vector <int> EdXmid;
    int ed = editDistanceSpace(X, Y, EdXmid);

    //printf("Edit Distance from HA: %d\n", ed);
    int yindex = calculateIndex(X, Y, EdXmid, xmid);

    string Xl = X.substr(0, xmid  ); 
    string Yl = Y.substr(0, yindex);
    string Xr, Yr;

    Xr = X.substr(xmid  ,  X.size() - xmid);
    Yr = Y.substr(yindex , Y.size() - yindex);

    auto tl = HirschbergsAlgo(Xl, Yl);
    auto tr = HirschbergsAlgo(Xr, Yr);

    return make_pair(tl.first + tr.first, tl.second + tr.second);

}

int main(){

    string X, Y;
    ifstream input1 ("data/xaa");
    ifstream input2 ("data/xab");

    input1 >> X;
    input2 >> Y;

    cout << X.size() <<" "<<Y.size()<<endl;
    clock_t ct = clock();

    ct = clock();
    auto t = HirschbergsAlgo(X,Y);
    ct = clock() - ct;
    printf ("Hirschbergs Algo It took me %ld clicks (%f seconds).\n",ct, ((float)ct)/CLOCKS_PER_SEC);

    int countedits = 0;

    for (int i = 0; i < t.first.size(); i++){
        if (t.first[i] == '|' || t.first[i] == '-' ||
           t.second[i] == '|' || t.second[i] == '-')
           countedits++;
    }

    cout<<"No of Edits are:" << countedits << endl;

    input1.close();
    input2.close();

    return 0;
}



#include<bits/stdc++.h>
#include <lib.hpp>

using namespace std;

// This is an Spacemoptimised implementation using n + O(1)
// Temp array of n words, two extra variables ed & prev are used
// amouting to a total complexity of n + O(1)
// void printNaive(vector <vector<int>> temp);
// int editDistanceNaive(string &X, string &Y);
// void print(vector<int> &temp);


void printNaive(vector <vector<int>> temp){
     for (int i = 0; i < temp.size(); i++){
        printf("x = %3d |", i);
        for (int j = 0; j < temp[0].size(); j++){
            printf("%d ", temp[i][j]);
        }
        cout << endl;
    }
}

void print(vector<int> &temp, int xmid, string str){
    cout<<str;
    printf("x = %3d |", xmid);
    for (auto &x:temp)
        printf("%d ", x);
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

int calculateIndex(string &X, string &Y, vector <int> EdXmid, int xmid){

    string Xr = X;
    string Yr = Y;

    reverse(Yr.begin(), Yr.end());
    reverse(Xr.begin(), Xr.end());

    vector <int> EdXrY;
    int ed = editDistanceSpace(Xr, Yr, EdXrY);
    cout<<"ED = "<<ed<<endl;
    reverse(EdXrY.begin(), EdXrY.end());

    int index;
    for (int i = 0 ; i < EdXrY.size(); i++){
        //cout<< (EdXmid[i])<<" "<<EdXrY[i]<<endl;
        if ( (EdXmid[i]+EdXrY[i]) == ed ){
            index = i;
            //cout<< "ybreak  = " << i << endl;
        }
    }

    // string Xl = X.substr(0, xmid); 
    // string Yl = Y.substr(0, ybreak);
    // string Xt = X.substr(xmid+1, X.size()-xmid); 
    // string Yt = Y.substr(ybreak+1, Y.size()-ybreak); 

    // editDistanceNaive( Xl, Yl);
    // editDistanceNaive( Xt, Yt);

    //print(EdXrY, 0, "y cal");

    return index;
}

pair<string, string> HirschbergsAlgo( string &X, string &Y){

    if (X == "" && Y == ""){
        return make_pair("*","*");
    }
    
    if ( X == "" ){
        string y;
        for (int i = 0; i < Y.size(); i++)
            y.push_back('-'); 
        return make_pair("*", y);
    }
        
    if ( Y == "" ){
        string x;
        for (int i = 0; i < X.size(); i++)
            x.push_back('-'); 
        return make_pair(x, "*");
    }

    int xl = X.length();
    int yl = Y.length();
    int xmid = xl/2;

    vector <int> EdXmid;
    int ed = editDistanceSpace(X, Y, EdXmid);

    printf("Edit Distance from HA: %d\n", ed);
    int yindex = calculateIndex(X, Y, EdXmid, xmid);

    string Xl = X.substr(0, xmid  ); 
    string Yl = Y.substr(0, yindex);
    
    string Xr, Yr;

    if (xmid + 1 < X.size())
        Xr = X.substr(xmid   +1, X.size()- xmid);
    else
        Xr = "";
    
    if (yindex +1 <  Y.size())
        Yr = Y.substr(yindex +1, Y.size() - yindex);
    else
        Yr = "";

    printf("Xindex = %d, Yindex = %d\n", xmid, yindex); 

    auto tl = HirschbergsAlgo(Xl, Yl);
    auto tr = HirschbergsAlgo(Xr, Yr);

    if (tl.first == "*" && tl.second != "*"){
        Yl = Yl + tl.second; 
    } 
    else
    if (tl.first != "*" && tl.second == "*"){
        Xl = Xl + tl.first; 
    }        
    
    if (tr.first == "*" && tr.second != "*"){
        Yr = tr.second +  Yr; 
    } 
    else
    if (tr.first != "*" && tr.second == "*"){
        Xr = tr.first + Xr; 
    }   
    
    return make_pair(Xl + Xr, Yl+Yr);
}

int main(){

    string X = "GCTTGCCG";
    string Y = "GTTACTCGA";

    //editDistanceNaive(X,Y);
    auto t = HirschbergsAlgo(X,Y);

    cout<< t.first<< endl;
    cout<< t.second << endl;

    return 0;
}



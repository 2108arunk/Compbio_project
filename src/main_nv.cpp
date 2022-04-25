#include<bits/stdc++.h>
#include <lib.hpp>
//#include <mainh.hpp>

int editDistanceNaive(string &X, string &Y){

    int ins = 1, del = 1;
    int row = X.size()+1, col = Y.size()+1;
    int *dp = (int*)malloc(sizeof(int) * (row) * (col));

    *(dp) = 0;
 
    cout<<"editDistanceNaive2"<<endl;
    for (int i = 1; i <= X.size(); i++)
        *(dp + i*col + 0) = *(dp + (i-1)*col + 0) + 1;

    cout<<"editDistanceNaive1"<<endl;
    for (int j = 1; j <= Y.size(); j++)
        *(dp + 0*col + j ) = *(dp + 0*col + (j-1) ) +1;

    int ed;

    for (int i = 1; i <= X.size(); i++){
        if (i % 100000 == 0)
            cout << i << endl;

        for (int j = 1; j <= Y.size(); j++){
            int delta = 0;
            if ( X[i-1] != Y[j-1]){
                    delta = 1;
            }
            *( dp + i*col + j) =     *(dp + (i-1)*col + (j-1)) + delta;
            *( dp + i*col + j) = min(*(dp + (i)*col + j), *(dp + (i-1)*col + (j)) + ins);
            *( dp + i*col + j) = min(*(dp + (i)*col + j), *(dp + (i)*col + (j-1)) + del);
            ed = *( dp + i*col + j);
        }
    }

    cout << "Edit distance Naive = " << ed << endl; 
    free(dp);

    return 0;
}


using namespace std;

int main(){

    string X, Y;
    ifstream input1 ("data/xaa");
    ifstream input2 ("data/xab");

    input1 >> X;
    input2 >> Y;

    cout << X.size() <<" "<<Y.size()<<endl;

    clock_t ct = clock();
    editDistanceNaive(X, Y);
    ct = clock() - ct;
    printf ("Naive Algorithm It took me %d clicks (%f seconds).\n",ct, ((float)ct)/CLOCKS_PER_SEC);

    //editDistanceNaive(X,Y);
    // cout << X << endl;
    // cout << Y << endl;
    // cout << t.first << endl;
    // cout << t.second << endl;
    // string Xr = X;
    // string Yr = Y;
    // int countedits = 0;
    // for (int i = 0; i < t.first.size(); i++){
    //     if (t.first[i] == '|' || t.first[i] == '-' ||
    //        t.second[i] == '|' || t.second[i] == '-')
    //        countedits++;
    // }
    // cout<<"No of Edits are:" << countedits << endl;

    // input1.close();
    // input2.close();

    return 0;
}


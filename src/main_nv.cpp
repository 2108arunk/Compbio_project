#include<bits/stdc++.h>
#include <lib.hpp>
//#include <mainh.hpp>

void naive_ed(string &X, string &Y)
{
    uint64_t row = X.size() + 1, col = Y.size() + 1,tempind;
    uint64_t a_size = X.size() + Y.size(),fill;
    uint64_t *dp = (uint64_t *)malloc((row * col) * sizeof(uint64_t));
    char *a_X = (char *)malloc(a_size * sizeof(char));
    char *a_Y = (char *)malloc(a_size * sizeof(char));

    dp[0] = 0;
    for(uint64_t i=1;i<row;i++)
        dp[i * col] = i;
    for(uint64_t j=1;j<col;j++)
        dp[j] = j;
    
    for(uint64_t i=1; i < row; i++){
        
        for(uint64_t j=1;j< col; j++){
            tempind = (uint64_t)(i * col + j);
            if (tempind %1000000 == 0)
                cout<<tempind<<endl;

            dp[tempind] = (X[i-1]==Y[j-1]) ? dp[tempind-col-1] : dp[tempind-col-1] + 1;
            dp[tempind] = min(dp[tempind],dp[tempind-1] + 1);
            dp[tempind] = min(dp[tempind],dp[tempind- col] + 1);
        }
    }

    printf("Edit distance is %ld\n",dp[row*col - 1]);
    free(a_X);free(a_Y);free(dp);

}


int editDistanceNaive(string &Y, string &X){

    int ins = 1, del = 1;
    int row = X.size()+1, col = Y.size()+1;
    int *dp = (int*)malloc(sizeof(int) * (row) * (col));

    *(dp) = 0;
 
    cout<<"editDistanceNaive3"<<endl;
    for (int i = 1; i <= X.size(); i++)
        *(dp + i*col + 0) = *(dp + (i-1)*col + 0) + 1;

    cout<<"editDistanceNaive2"<<endl;
    for (int j = 1; j <= Y.size(); j++)
        *(dp + 0*col + j ) = *(dp + 0*col + (j-1) ) +1;
    
    cout<<"editDistanceNaive1"<<endl;
    
    int ed;


    for (int i = 1; i <= X.size(); i++){
        if (i % 10000 == 0)
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
    naive_ed(X, X);
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


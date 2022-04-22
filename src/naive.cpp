#include<bits/stdc++.h>
//#include <mainh.hpp>

using namespace std;
//int editDistanceSpace( string X, string Y, vector <int> &xm);
//This is a Naive implementation used for Testing only

int editDistanceNaive(string &X, string &Y){

    int ins = 1, del = 1;
    vector <vector<int>> dp(X.size()+1, vector<int>(Y.size()+1,0));
    dp[0][0] = 0;
 
    for (int i = 1; i <= X.size(); i++)
        dp[i][0] = dp[i-1][0]+1;

    for (int j = 1; j <= Y.size(); j++)
        dp[0][j] = dp[0][j-1]+1;

    for (int i = 1; i <= X.size(); i++){
        for (int j = 1; j <= Y.size(); j++){
            int delta = 0;
            if ( X[i-1] != Y[j-1]){
                    delta = 1;
            }
            dp[i][j] = dp[i-1][j-1] + delta;
            dp[i][j] = min (dp[i][j], dp[i-1][j] + ins );
            dp[i][j] = min (dp[i][j], dp[i][j-1] + del );
        }
    }

    //printNaive(dp);
    cout << "Edit distance Naive = " << dp[X.size()][Y.size()] << endl; 

    return 0;
}
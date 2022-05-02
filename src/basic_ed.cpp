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
using namespace std;

void print_a(char *a_X,char *a_Y,uint64_t si,\
             uint64_t a_size)
{
    ofstream out_file; 
    out_file = ofstream("outputNaive.txt");
    for(uint64_t i=si+1;i < a_size; i++)
        out_file << a_X[i];
    out_file << endl;
    for(uint64_t i=si+1;i < a_size; i++)
        out_file << (((a_X[i]!='_' && a_Y[i]!='_') && (a_X[i] == a_Y[i]))?\
        '|' : ' ');
    out_file << endl;
    for(uint64_t i=si+1;i < a_size; i++)
        out_file << a_Y[i];
    out_file.close();
}

int fill_a( uint64_t *dp,char *a_X,char *a_Y,
            string &X,string&Y, uint64_t row, uint64_t col,
            uint64_t pos)
{
    uint64_t m = row - 1, n = col - 1, tempind;

    while(m!=0 && n!=0){
        tempind = m * col + n;
        if(((X[m-1]==Y[n-1]) && dp[tempind] == dp[tempind - col - 1])
            || dp[tempind] == dp[tempind - col -1] + 1){
            a_X[pos] = X[m-1];
            a_Y[pos] = Y[n-1];
            m--;
            n--;
        }

        else if (dp[tempind] == dp[tempind - 1] + 1)
        {
            a_X[pos] = '_';
            a_Y[pos] = Y[n-1];
            n--;
        }

        else
        {
            a_X[pos] = X[m-1];
            a_Y[pos] = '_';
            m--;
        }
        pos--;
    }

    if(n!=0)
    {
        while(n!=0)
        {
            a_Y[pos] = Y[n-1];
            a_X[pos] = '_';
            n--;
            pos--;
        }
    }

    if(m!=0)
    {
        while(m!=0)
        {
            a_X[pos]= X[m-1];
            a_Y[pos] = '_';
            m--;
            pos--;
        }
    }

    return pos;

}


uint64_t naive_ed(string &X, string &Y)
{
    uint64_t row = X.size() + 1, col = Y.size() + 1,tempind;
    uint64_t a_size = X.size() + Y.size(),fill;
    uint64_t *dp = new uint64_t[(row * col) * sizeof(uint64_t)];
    char *a_X = new char[a_size * sizeof(char)];
    char *a_Y = new char[a_size * sizeof(char)];
    uint64_t ret;
    dp[0] = 0;
    for(uint64_t i=1;i<row;i++)
        dp[i * col] = i;
    for(uint64_t j=1;j<col;j++)
        dp[j] = j;
    
    for(uint64_t i=1; i < row; i++){
        for(uint64_t j=1;j< col; j++){
            tempind = (uint64_t)(i * col + j);
            dp[tempind] = (X[i-1]==Y[j-1]) ? dp[tempind-col-1] : dp[tempind-col-1] + 1;
            dp[tempind] = min(dp[tempind],dp[tempind-1] + 1);
            dp[tempind] = min(dp[tempind],dp[tempind- col] + 1);
        }
    }

    fill = fill_a(dp,a_X,a_Y,X,Y,row, col, a_size - 1);
    print_a(a_X,a_Y,fill,a_size);
    ret = dp[row*col - 1];
    //free(a_X);free(a_Y);free(dp);
    delete[] a_X;
    delete[] a_Y;
    delete[] dp;
    return ret;

}


int main(int argc, char* argv[]){

    uint64_t ret;

    if (argc < 3){
        cout<< "provide both testfiles for X and Y\n";
        return 0;
    }

    string Xfile, Yfile, X, Y;

    Xfile = argv[1];
    Yfile = argv[2];

    ifstream input1 (Xfile);
    ifstream input2 (Yfile);


    getline(input1 >> ws,X);
    getline(input2 >> ws,Y);
    //input1 >> X;
    //input2 >> Y;

    clock_t ct = clock();
    ct = clock();
    ret = naive_ed(X,Y);
    
    ct = clock() - ct;
  
    printf ("NaiveTime :%f :seconds, EditDistance : %llu \n", ((float)ct)/CLOCKS_PER_SEC, ret);

    input1.close();
    return ret;
}

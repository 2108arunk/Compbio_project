/*
 *   The way to run this code is 
 *   1. g++ -o basic_ed basic_ed.cpp
 *   2. ./basic_ed
 *    Reads a new file in.txt with two strings
 *    A new file output.txt is generated with allignment 
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
using namespace std;



void print_a(char *a_X,char *a_Y,uint64_t si,\
             uint64_t a_size)
{
    ofstream out_file; 
    out_file = ofstream("output.txt");
    for(int i=si+1;i < a_size; i++)
        out_file << a_X[i];
    out_file << endl;
    for(int i=si+1;i < a_size; i++)
        out_file << (((a_X[i]!='_' && a_Y[i]!='_') && (a_X[i] != a_Y[i]))?\
        '|' : ' ');
    out_file << endl;
    for(int i=si+1;i < a_size; i++)
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
    
    for(int i=1; i < row; i++){
        for(int j=1;j< col; j++){
            tempind = i * col + j;
            dp[tempind] = (X[i-1]==Y[j-1]) ? dp[tempind-col-1] : dp[tempind-col-1] + 1;
            dp[tempind] = min(dp[tempind],dp[tempind-1] + 1);
            dp[tempind] = min(dp[tempind],dp[tempind- col] + 1);
        }
    }

    printf("Edit distance is %ld\n",dp[row*col - 1]);
    fill = fill_a(dp,a_X,a_Y,X,Y,row, col, a_size - 1);
    print_a(a_X,a_Y,fill,a_size);
    free(a_X);free(a_Y);free(dp);

}
/*
 *  Main function. To run this code. Generates output.txt same as out.txt  
*/
int main(){
    ifstream input_file1,input_file2;
    string X,Y;
    clock_t t;
    input_file1 = ifstream("xaa");
    input_file2 = ifstream("xab");
    input_file1 >> X;
    input_file2 >> Y;
    naive_ed(X,Y);
    input_file1.close();
    input_file2.close();
    return 0;
}

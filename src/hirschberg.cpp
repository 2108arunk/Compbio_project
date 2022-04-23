/*
 *   The way to run this code is 
 *   1. g++ -o hirschberg hirschberg.cpp
 *   2. ./hirschberg
 *   Reads a new file in.txt with two strings
 *   A new file output.txt is generated with allignment 
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

void pretty_print(vector<char> &a_X,vector<char> &a_Y)
{
    ofstream out_file; 
    out_file = ofstream("output.txt");
    
    for(uint64_t i=0;i < a_X.size(); i++)
        out_file << a_X[i];
    out_file << endl;
    for(uint64_t i=0;i < a_X.size(); i++)
        out_file << (((a_X[i]!='_' && a_Y[i]!='_') && (a_X[i] != a_Y[i]))?\
        '|' : ' ');
    out_file << endl;
    for(uint64_t i=0;i < a_X.size(); i++)
        out_file << a_Y[i];
    
    out_file.close();
}

void find_edit1(uint64_t i_x, uint64_t j_x,uint64_t i_y, uint64_t j_y,
                vector<uint64_t>&dp, string &X, string &Y)
{
    uint64_t temp1,temp2,len1 = j_x - i_x + 1,len2 = j_y - i_y + 1,k,l;

    dp[0] = 0;
    for(k = 1; k <= len2; k++)
        dp[k] = k;

    for(k=1;k<=len1;k++)
    {
        temp1 = k-1;
        dp[0] = k;
        for(l=1;l<=len2;l++){
            temp2 = dp[l];
            dp[l] = (X[i_x + k -1]==Y[i_y + (l - 1)]) ? temp1 : 1 + min(dp[l-1],min(dp[l],\
            temp1));
            temp1 = temp2;
        }
    }
}

void find_edit2(uint64_t i_x, uint64_t j_x,uint64_t i_y, uint64_t j_y,
                vector<uint64_t>&dp, string &X, string &Y)
{
    uint64_t temp1,temp2,len1 = j_x - i_x + 1,len2 = j_y - i_y + 1,k,l;

    dp[0] = 0;
    for(k = 1; k <= len2; k++)
        dp[k] = k;

    for(k=1;k<=len1;k++)
    {
        temp1 = k-1;
        dp[0] = k;
        for(l=1;l<=len2;l++){
            temp2 = dp[l];
            dp[l] = (X[j_x - k +1]==Y[j_y - l + 1]) ? temp1 : 1 + min(dp[l-1],min(dp[l],\
            temp1));
            temp1 = temp2;
        }
    }

}
void h_recursive(vector<char> &a_X, vector<char>&a_Y,
                 string &X, string &Y,
                 uint64_t s_x,uint64_t e_x,uint64_t s_y,uint64_t e_y)
{
    uint64_t row = e_x - s_x + 1, col = e_y - s_y + 1,split = (e_x + s_x)/2,k;

    if(col==0)
    {
        for(uint64_t i = s_x; i<=e_x; i++)
        {
            a_X.push_back(X[i]);
            a_Y.push_back('_');
        }
        return;
    }
    else if(row==0)
    {
        for(uint64_t i = s_y; i<=e_y; i++)
        {
            a_X.push_back('_');
            a_Y.push_back(Y[i]);
        }
        return;
    }
    else if(row ==1)
    {
        uint64_t i;
        for(i = s_y; i<=e_y; i++)
        {
            if(X[s_x]==Y[i])
            {
                a_X.push_back(X[s_x]);
                a_Y.push_back(Y[i]);
                i++;
                break;
            }
            else
            {
                if(i==e_y)
                {
                    a_X.push_back(X[s_x]);
                    a_Y.push_back(Y[i]);
                }
                else
                {
                    a_X.push_back('_');
                    a_Y.push_back(Y[i]);
                }
            }
        }
        for(; i<=e_y; i++)
        {
            a_X.push_back('_');
            a_Y.push_back(Y[i]);
        }
        return;
    }
    else if(col == 1)
    {
        uint64_t i;
        
        for(i = s_x; i<=e_x; i++)
        {
            if(X[i]==Y[s_y])
            {
                a_X.push_back(X[i]);
                a_Y.push_back(Y[s_y]);
                i++;
                break;
            }
            else
            {
                if(i==e_x)
                {
                    a_X.push_back(X[i]);
                    a_Y.push_back(Y[s_y]);
                }
                else
                {
                    a_X.push_back(X[i]);
                    a_Y.push_back('_');
                }
            }
        }
        for(; i<=e_x; i++)
        {
            a_X.push_back(X[i]);
            a_Y.push_back('_');
        }
        return;
    }

    uint64_t ans;
    vector<uint64_t>dp1(col+1),dp2(col+1),dp3(col+1);

    find_edit1(s_x,e_x,s_y,e_y,dp1,X,Y);
    ans = dp1[col];

    find_edit1(s_x,split,s_y,e_y,dp2,X,Y);
    find_edit2(split+1,e_x,s_y,e_y,dp3,X,Y);

    for(k=0;k<=col;k++)
    {
        if(dp2[k] + dp3[col-k]== ans)
            break;
    }
    
    h_recursive(a_X,a_Y,X,Y,s_x,split,s_y, s_y + k - 1);
    h_recursive(a_X,a_Y,X,Y,split+1,e_x,s_y + k, e_y);

}
void hirschberg(string &X, string &Y)
{
    vector<char> a_X,a_Y;
    
    h_recursive(a_X,a_Y,X,Y,0,X.size()-1,0, Y.size()-1);
    pretty_print(a_X,a_Y);
}

/*
 *  Main function. To run this code. Generates output.txt same as out.txt  
*/
int main(){
    ifstream input_file;
    string X,Y;
    input_file = ifstream("in.txt");
    input_file >> X >> Y;
    hirschberg(X,Y);
    input_file.close();
    return 0;
}
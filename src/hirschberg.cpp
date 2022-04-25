/*
 *   The way to run this code is 
 *   1. g++ -o hirschberg hirschberg.cpp
 *   2. ./hirschberg
 *   Reads a new file in.txt with two strings
 *   A new file output.txt is generated with allignment 
*/
#include<iostream>
#include<fstream>
using namespace std;

void pretty_print(char *a_X, char *a_Y,uint64_t pos)
{
    ofstream out_file; 
    out_file = ofstream("output.txt");
    uint64_t ed=0;
    for(uint64_t i=0;i < pos; i++)
        out_file << a_X[i];
    out_file << endl;
    for(uint64_t i=0;i < pos; i++)
        out_file << (((a_X[i]!='_' && a_Y[i]!='_') && (a_X[i] != a_Y[i]))?\
        '|' : ' ');
    out_file << endl;
    for(uint64_t i=0;i < pos; i++)
        out_file << a_Y[i];
    for(uint64_t i =0; i<pos; i++){
	if(a_X[i]=='_' || a_Y[i] == '_' || (a_X[i]!=a_Y[i]))
		ed++;    
    }
    cout << "Edit distance is : " << ed << endl; 
    out_file.close();
}

void find_edit1(uint64_t i_x, uint64_t j_x,uint64_t i_y, uint64_t j_y,
                uint64_t split, uint64_t *dp1, uint64_t *dp2,
		string &X, string &Y)
{
    uint64_t temp1,temp2,len1 = j_x - i_x + 1,len2 = j_y - i_y + 1,k,l;

    dp1[0] = 0;
    for(k = 1; k <= len2; k++)
        dp1[k] = k;

    for(k=1;k<=len1;k++)
    {
        temp1 = k-1;
        dp1[0] = k;
        for(l=1;l<=len2;l++){
            temp2 = dp1[l];
            dp1[l] = (X[i_x + k -1]==Y[i_y + (l - 1)]) ? temp1 : 1 + min(dp1[l-1],min(dp1[l],\
            temp1));
            temp1 = temp2;
        }
	if(i_x + (k - 1) == split)
        {
                dp2[0] = k;
                for(l=1;l<=len2;l++)
                        dp2[l] = dp1[l];
        }

    }
}

void find_edit2(uint64_t i_x, uint64_t j_x,uint64_t i_y, uint64_t j_y,
                uint64_t *dp, string &X, string &Y)
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

void h_recursive(char *a_X, char *a_Y,
                 string &X, string &Y,
                 uint64_t s_x,uint64_t e_x,uint64_t s_y,uint64_t e_y, uint64_t * pos,
		 uint64_t *dp1, uint64_t *dp2, uint64_t *dp3)
{
    uint64_t row = e_x - s_x + 1, col = e_y - s_y + 1,split = (e_x + s_x)/2,k;
    if(col==0)
    {
        for(uint64_t i = s_x; i<=e_x; i++)
        {
            a_X[*pos] = X[i];
            a_Y[*pos] = '_';
	    ++*pos;
        }
        return;
    }
    else if(row==0)
    {
        for(uint64_t i = s_y; i<=e_y; i++)
        {
            a_X[*pos] = '_';
            a_Y[*pos] = Y[i];
	    ++*pos;
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
                a_X[*pos] = X[s_x];
                a_Y[*pos] = Y[i];
                i++;
		++*pos;
                break;
            }
            else
            {
                if(i==e_y)
                {
                    a_X[*pos] = X[s_x];
                    a_Y[*pos] = Y[i];
                }
                else
                {
                    a_X[*pos] = '_';
                    a_Y[*pos] = Y[i];
                }
		++*pos;
            }
        }
        for(; i<=e_y; i++)
        {
            a_X[*pos] = '_';
            a_Y[*pos] = Y[i];
	    ++*pos;
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
                a_X[*pos] = X[i];
                a_Y[*pos] = Y[s_y];
                i++;
		++*pos;
                break;
            }
            else
            {
                if(i==e_x)
                {
                    a_X[*pos] = X[i];
                    a_Y[*pos] = Y[s_y];
                }
                else
                {
                    a_X[*pos] = X[i];
                    a_Y[*pos] = '_';
                }
		++*pos;
            }
        }
        for(; i<=e_x; i++)
        {
            a_X[*pos] = X[i];
            a_Y[*pos] = '_';
	    ++*pos;
        }
        return;
    }

    uint64_t ans;

    find_edit1(s_x,e_x,s_y,e_y,split,dp1,dp2,X,Y);
    ans = dp1[col];
    find_edit2(split+1,e_x,s_y,e_y,dp3,X,Y);

    for(k=0;k<=col;k++)
    {
        if(dp2[k] + dp3[col-k]== ans)
            break;
    }
    
    h_recursive(a_X,a_Y,X,Y,s_x,split,s_y, s_y + k - 1,pos,dp1,dp2,dp3);
    h_recursive(a_X,a_Y,X,Y,split+1,e_x,s_y + k, e_y,pos,dp1,dp2,dp3);

}
void hirschberg(string &X, string &Y)
{
    uint64_t pos = 0, a_size = X.size() + Y.size();
    uint64_t *dp1 = (uint64_t *)malloc((a_size + 1) * sizeof(uint64_t));
    uint64_t *dp2 = (uint64_t *)malloc((a_size + 1) * sizeof(uint64_t));
    uint64_t *dp3 = (uint64_t *)malloc((a_size + 1) * sizeof(uint64_t));
    char *a_X = (char *)malloc(a_size * sizeof(char));
    char *a_Y = (char *)malloc(a_size * sizeof(char));
    h_recursive(a_X,a_Y,X,Y,0,X.size()-1,0, Y.size()-1, &pos, dp1,dp2,dp3);
    pretty_print(a_X,a_Y,pos);
    free(a_X);free(a_Y);free(dp1);free(dp2);free(dp3);
}

/*
 *  Main function. To run this code. Generates output.txt same as out.txt  
*/
int main(){
    ifstream input_file1, input_file2;
    string X,Y;
    //input_file1 = ifstream("xaa");
    //input_file2 = ifstream("xab");
    input_file1 = ifstream("xaa");
    input_file2 = ifstream("xab");    
    input_file1 >> X;
    input_file2 >> Y;
    hirschberg(X,Y);
    input_file1.close();
    input_file2.close();
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

// This is an Spacemoptimised implementation using n + O(1)
// Temp array of n words, two extra variables ed & prev are used
// amouting to a total complexity of n + O(1)

void printNaive(vector <vector<int>> temp, string X);
int editDistanceNaive(string &X, string &Y);
void print(vector<int> &temp);
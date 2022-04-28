#include<iostream>
#include <fstream>
using namespace std;

string permute(string &text,int percent, int alphabet_size)
{	
	string ans="";

	for(uint64_t i=0;i<text.size();i++){
		int randi=rand()%101;
		if(randi < percent)
		{
			if(randi < percent/3)
			{
				ans.push_back('a' + rand()%alphabet_size);
			}
			else if ( (randi >= percent/3) && ( randi < (2*percent/3)))
			{
				ans.push_back(text[i]);
				ans.push_back('a' + rand()%alphabet_size);
			}
		
		}
		else
		{
			ans.push_back(text[i]);
		}
	}
	return ans;
}

string generate_string(int alphabet_size,int length){
        string ans="";
        for(int i=0;i<length;i++)
                ans.push_back('a' + rand()%alphabet_size);
        return ans;

}

int main(int argc, char* argv[])
{
	if(argc != 7)
		exit(-1);
	int alphabet_size = stoi(argv[1]), text_size = stoi(argv[2]), percent = stoi(argv[3]);
        srand(time(0));
	string text = generate_string(alphabet_size, text_size),p_text;
	if(stoi(argv[6])==0)
        	p_text = permute(text,percent, alphabet_size);
	else
		p_text = generate_string(alphabet_size,text_size);
	string Xfile, Yfile;
    	Xfile = argv[4];
    	Yfile = argv[5];
	ofstream input1 (Xfile);
	ofstream input2 (Yfile);
	input1 << text;
	input2 << p_text;
	input1.close();
	input2.close();	
	return 0;
}

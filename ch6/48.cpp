/*Write the C implementation for the Huffman algorithm developed in Project 47. After it has been built,
 print the code. Then write a C program to read characters from the keyboard and convert them to your 
 Huffman code. Include a function in your program that converts Huffman code back to text. Use it to 
 verify that the code entered from the keyboard was converted correctly.*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main(){
	string line;
	fstream file;
	file.open("HW6_48.txt", ios::in);

	const int SIZE = 26;

	map<string, int> dict;
	map<string, int>::iterator it = dict.begin();
	
	string ch;
	int freq;
	int count = 0;
	if(file.is_open()){
		while(count <= SIZE){
			getline(file, line, ' ');
			ch = line;

			getline(file, line, '\n');
			freq = stoi(line);
			dict.insert(pair<string, int>(ch, freq));

			// cout << line << endl;
			count++;
		}
	}

	for (it = ++dict.begin(); it != dict.end(); ++it)
    	cout << it->first << " => " << it->second << endl;



	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "0110761_5_34.h"

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

// compare according to stock code
int cmpCode(void* g1, void* g2){
	int code1 = ((NODE*)g1)->code;
	int code2 = ((NODE*)g2)->code;
	return (code1 > code2) ? 1 : ((code1 < code2) ? -1 : 0);
}

// compare according to stock gain
int cmpGain(void* g1, void* g2){
	double gain1 = ((NODE*)g1)->gain;
	double gain2 = ((NODE*)g2)->gain;
	return (gain1 > gain2) ? 1 : ((gain1 < gain2) ? -1 : 0);
}

int cmpCodeRev(void* g1, void* g2);
int cmpGainRev(void* g1, void* g2);

int main(){
	fstream file;
	string line;
	vector<string> x;

	LIST* stocksList1 = createList(cmpCode);
	LIST* stocksList2 = createList(cmpGain);
	NODE* stockNode;
	int addResult;

	// To easily display reversely, also create two reverse-ordered list
	LIST* stocksList3 = createList(cmpCodeRev);
	LIST* stocksList4 = createList(cmpGainRev);

	file.open("stocks.txt", ios::in);
	if (file.is_open()){
		while(getline(file, line)){
			x = split(line, ' ');
			// cout << line << endl;

			stockNode = new NODE;
			stockNode->code = stoi(x[0]);
			stockNode->name = x[1];
			stockNode->invest = stod(x[2]);
			stockNode->amount = stod(x[3]);
			stockNode->price = stod(x[4]);
			stockNode->gain = stockNode->invest - stockNode->amount * stockNode->price;

			addResult = addNode(stocksList1, stockNode);
			addResult = addNode(stocksList2, stockNode);
			// total += stoi(x[i]);

			// Used to display reversely
			addResult = addNode(stocksList3, stockNode);
			addResult = addNode(stocksList4, stockNode);
		}
	}

	NODE* n = new NODE;
	int choice, count;
	cout << "4 orders could be choosed to show stocks: "<< endl;
	cout << "input '1' Arrangement in descending stock code" << endl;
	cout << "input '2' Arrangement in aescending stock code" << endl;
	cout << "input '3' Arrangement in descending stock gain" << endl;
	cout << "input '4' Arrangement in aescending stock gain" << endl;
	cout << "or input '5' to exit: " << endl;

	while(true){
		count = 0;
		cout << "\nPleas input your choice: ";
		cin >> choice;

		cout << "code\tname\tinvest\tamount\tprice\tgain\n";
		if(choice == 1){
			while(traverse(stocksList1, count, (void**) &n)){
				cout << n->code << "\t" << n->name << "\t" 
					 << n->invest << "\t" << n->amount << "\t" 
					 << n->price << "\t" << n->gain << endl; 
				count++;
			}
		}
		else if(choice == 2){
			while(traverse(stocksList3, count, (void**) &n)){
				cout << n->code << "\t" << n->name << "\t" 
					 << n->invest << "\t" << n->amount << "\t" 
					 << n->price << "\t" << n->gain << endl; 
				count++;
			}
		}
		else if(choice == 3){
			while(traverse(stocksList2, count, (void**) &n)){
				cout << n->code << "\t" << n->name << "\t" 
					 << n->invest << "\t" << n->amount << "\t" 
					 << n->price << "\t" << n->gain << endl; 
				count++;
			}
		}
		else if(choice == 4){
			while(traverse(stocksList4, count, (void**) &n)){
				cout << n->code << "\t" << n->name << "\t" 
					 << n->invest << "\t" << n->amount << "\t" 
					 << n->price << "\t" << n->gain << endl; 
				count++;
			}
		}
		else
			break;
	}


	return 0;
}


// compare according to stock code reversely
int cmpCodeRev(void* g1, void* g2){
	int code1 = ((NODE*)g1)->code;
	int code2 = ((NODE*)g2)->code;
	return (code1 > code2) ? -1 : ((code1 < code2) ? 1 : 0);
}

// compare according to stock gain reversely
int cmpGainRev(void* g1, void* g2){
	double gain1 = ((NODE*)g1)->gain;
	double gain2 = ((NODE*)g2)->gain;
	return (gain1 > gain2) ? -1 : ((gain1 < gain2) ? 1 : 0);
}
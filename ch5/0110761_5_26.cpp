#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "0110761_5_26.h"

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

int cmpGrade(void* g1, void* g2){
	int grad1 = ((NODE*)g1)->grade;
	int grad2 = ((NODE*)g2)->grade;
	return (grad1 > grad2) ? 1 : ((grad1 < grad2) ? -1 : 0);
}

int main(){
	fstream file;
	string line;

	// Students name list
	LIST* studentsList = createList(cmpGrade);
	// Students name node
	NODE* nameNode;
	// Student's grade list
	LIST* gradeList;
	// Student's grade node
	NODE* gradeNode;

	string name, temp;
	int grades[4] = {-1};
	int avg , total, size;
	int addResult;
	bool isName;
	vector<string> x;

	file.open("students.txt", ios::in);
	if (file.is_open()){
		getline(file, line);	// throw away first line (total number of students)

		while(getline(file, line)){
			total = size = avg = 0;

			nameNode = new NODE;
			x = split(line, ' ');
			nameNode->name = x[0];
			addResult = addNode(studentsList, nameNode);

			gradeList = createList(cmpGrade);;
			size = x.size();
			for(int i = 1; i < size; i++){
				gradeNode = new NODE;
				gradeNode->grade = stoi(x[i]);
				addResult = addNode(gradeList, gradeNode);
				total += stoi(x[i]);
			}

			cout << line << ", average: " << (total / size) << endl;
		}
	}

	return 0;
}
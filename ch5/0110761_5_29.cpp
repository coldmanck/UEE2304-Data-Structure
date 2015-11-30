#include <iostream>
using namespace std;

#include "0110761_5_29.h"

// compare
int cmpExp(void* g1, void* g2){
	int exp1 = ((NODE*)g1)->exp;
	int exp2 = ((NODE*)g2)->exp;
	return (exp1 > exp2) ? 1 : ((exp1 < exp2) ? -1 : 0);
}

// load data into polynomial
void loadPoly(int cof[7][2], LIST* p){
	int addResult;

	for(int i = 0; i < 7; i++){
		NODE* node = new NODE;

		node->coef = cof[i][0];
		node->exp = cof[i][1];

		addResult = addNode(p, node);
	}
}

// add p1 and p2 to p3
LIST* add(LIST* p1, LIST* p2){
	LIST* p = createList(cmpExp);
	int count1 = 0, count2 = 0, addResult1, addResult2, addResult3;
	bool ok1 = true, ok2 = true;
	NODE* n1;
	NODE* n2;

	while(!(emptyList(p1) && emptyList(p2))){		
		if(ok1){
			n1 = new NODE;
			addResult1 = traverse(p1, count1, (void**) &n1);
		}

		if(ok2){
			n2 = new NODE;
			addResult2 = traverse(p2, count2, (void**) &n2);
		}

		NODE* n3 = new NODE;
		if(addResult1 == 1 && addResult2 == 1){
			if(n1->exp == n2->exp){
				n3->exp = n1->exp;
				n3->coef = (n1->coef + n2->coef);

				count1++; count2++; 
				ok1 = true; ok2 = true;
			}
			else if(n1->exp > n2->exp){
				n3->exp = n2->exp;
				n3->coef = n2->coef;

				count2++; 
				ok1 = false; ok2 = true;
			}
			else{
				n3->exp = n1->exp;
				n3->coef = n1->coef;

				count1++; 
				ok1 = true; ok2 = false;
			}
		}
		else if(addResult1 == 1 && addResult2 != 1){
			n3->exp = n1->exp;
			n3->coef = n1->coef;

			count1++; 
			ok1 = true; ok2 = false;
		}
		else if(addResult1 != 1 && addResult2 == 1){
			n3->exp = n2->exp;
			n3->coef = n2->coef;

			count2++; 
			ok1 = false; ok2 = true;
		}
		else
			break;
		
		addResult3 = addNode(p, n3);
	}

	return p;
}

int main(){
	// initialize polynomials
	int cof1[7][2] = {{7,9}, {2,6}, {3,5}, {4,4}, {2,3}, {6,2}, {6,0}};
	int cof2[7][2] = {{-7,9}, {2,8}, {-5,7}, {2,4}, {2,3}, {9,2}, {-7,1}};

	// create list
	LIST* p1 = createList(cmpExp);
	LIST* p2 = createList(cmpExp);
	LIST* p3;

	// load data into polynomial
	loadPoly(cof1, p1);
	loadPoly(cof2, p2);
	
	// add p1 and p2 into p3
	p3 = add(p1, p2);
	
	// Show output
	NODE* n = new NODE;
	int count = 0;

	cout << "polynomial 1: ";
	while(traverse(p1, count, (void**) &n)){
		cout << n->coef << "x^" << n->exp << " + "; 
		count++;
	}

	count = 0;
	cout << "\npolynomial 2: ";
	while(traverse(p2, count, (void**) &n)){
		cout << n->coef << "x^" << n->exp << " + "; 
		count++;
	}

	count = 0;
	cout << "\npolynomial 3: ";
	while(traverse(p3, count, (void**) &n)){
		cout << n->coef << "x^" << n->exp << " + "; 
		count++;
	}
	cout << "\n";

	return 0;
}
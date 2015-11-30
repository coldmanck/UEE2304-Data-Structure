#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double squareRoot(double num, double ans, double tol);

int main(){
	int ans = 1;
	printf("square root of 125: %f\n", squareRoot(125, ans,0.01));
	printf("square root of 763: %f\n", squareRoot(763, ans,0.01));
	printf("square root of 997: %f\n", squareRoot(997, ans,0.01));


	
	return 0;
}

double squareRoot(double num, double ans, double tol){
	if(abs(pow(ans, 2) - num) < tol)
		return ans;
	else
		return squareRoot(num, (pow(ans, 2) + num)/(2*ans), tol);
}

#include <stdio.h>
#include <stdlib.h>

long factorial(int);

int main(){
	printf("factorial of 5: %ld\n", factorial(5));
	printf("factorial of 20: %ld\n", factorial(20));

	return 0;
}

long factorial(int n){
	long ans = 1;
	for(int i = n; i > 1; i--)
		ans *= i;
	return ans;
}

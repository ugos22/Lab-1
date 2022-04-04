#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[]) {
	int t = atoi(argv[1]);
	int base = atoi(argv[2]);
	int x;
	double p1, p2;

	p2 = (double) (1.0 / (1.0 + t));
	p1 = 1.0 - p2;
	printf("x = %f \np1 = %f %%\np2 = %f %%\n", base / p1, p1*100, p2*100);
}

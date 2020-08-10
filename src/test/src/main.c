#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 500
#define MIN 100

int possion(int lambda)
{
	int k = 0;
	long double p = 1.0;
	long double l = exp(-lambda);
	while (p >= l)
	{
		double f;
		f = (float) (rand() % 100);
		double u = f / 100;
		p *= u;
		k++;
	}
	return k - 1;
}

int main(int argc, char *argv[])
{
	int size, lambda;
	int sum = 0;
	char p;
	char *file = "text.txt";
	srand((unsigned) time(NULL));

	if(argc >= 2)
		file = argv[1];

	FILE *o = fopen(file, "w");

	size = MIN + rand() % (MAX - MIN);
	lambda = rand() % 127;
	printf("size: %d\tavg: %d\n", size, lambda);

	while(size--)
	{
		p = possion(lambda) % 128;
		sum += p;
		fputc(p, o);
	}
	printf("sum: %d\n", sum);

	fclose(o);

	return 0;
}

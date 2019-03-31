#include <stdio.h>
#include <stdlib.h>
#define MATSIZE 3

void MatrixMul(float A[MATSIZE][MATSIZE], float B[MATSIZE][MATSIZE], float C[MATSIZE][MATSIZE])
{
	// Fill this part
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < MATSIZE; i++)
		for (j = 0; j < MATSIZE; j++)
			C[i][j] = 0.f;

	for (i = 0; i < MATSIZE; i++)
	{
		for (j = 0; j < MATSIZE; j++)
		{
			for (k = 0; k < MATSIZE; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
			
		}
	}

}
int main()
{
	float A[MATSIZE][MATSIZE] = { {1, 0, 1}, {2, 1, 0}, {2, 2, 2} };
	float B[MATSIZE][MATSIZE] = { {2, 0, 1}, {1, 2, 0}, {1, 1, 1} };
	float C[MATSIZE][MATSIZE];
	MatrixMul(A, B, C);

	for (int i = 0; i < MATSIZE; i++) {
		for (int j = 0; j < MATSIZE; j++) {
			printf("%f ", C[i][j]);
		}
		printf("\n");
	}


	system("Pause");

	return 0;
}
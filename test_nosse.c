#include <xmmintrin.h>
#include <math.h>	
#include <stdio.h>
#include <time.h>

// 1m22sec
int main(int argc, char* argv[])
{
	printf("Starting calculation...\n");

	const int length = 64000;

	float* pResult = malloc(length * sizeof(float));

	for (int stress = 0; stress < 100000; stress++)
	{
		float xFloat = 1.0f;
		for (int i = 0; i < length; i++)
		{
			pResult[i] = sqrt(xFloat) / xFloat;
			xFloat += 1.0f;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		printf("Result[%d] = %f\n", i, pResult[i]);
	}

	return 0;
}
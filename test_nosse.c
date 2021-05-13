/*
	SSE_Tutorial
	This tutorial was written for supercomputingblog.com
	This tutorial may be freely redistributed provided this header remains intact
*/

#include <xmmintrin.h>	// Need this for SSE compiler intrinsics
#include <math.h>		// Needed for sqrt in CPU-only version
#include <stdio.h>
#include <time.h>

// 125 seconds
int main(int argc, char* argv[])
{
	printf("Starting calculation...\n");

	const int length = 64000;
	time_t bgn, end;

	// We will be calculating Y = Sin(x) / x, for x = 1->64000

	float* pResult = (float*)malloc(length * sizeof(float));

	const int SSELength = length / 4;

	// Stores time seconds
	time(&bgn);
	for (int stress = 0; stress < 100000; stress++)	// lots of stress loops so we can easily use a stopwatch
	{
		float xFloat = 1.0f;
		for (int i = 0; i < length; i++)
		{
			pResult[i] = sqrt(xFloat) / xFloat;	// Even though division is slow, there are no intrinsic functions like there are in SSE
			xFloat += 1.0f;
		}
	}
	time(&end);

	// To prove that the program actually worked
	for (int i = 0; i < 20; i++)
	{
		printf("Result[%d] = %f\n", i, pResult[i]);
	}
	printf("Time: %d", (int)(end - bgn));

	return 0;
}
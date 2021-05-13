/*
	SSE_Tutorial
	This tutorial was written for supercomputingblog.com
	This tutorial may be freely redistributed provided this header remains intact
*/

#include <xmmintrin.h>	// Need this for SSE compiler intrinsics
#include <math.h>		// Needed for sqrt in CPU-only version
#include <stdio.h>
#include <time.h>

// 18 sec
int main(int argc, char* argv[])
{
	printf("Starting calculation...\n");

	const int length = 64000;
	time_t bgn, end;

	// We will be calculating Y = Sin(x) / x, for x = 1->64000

	// If you do not properly align your data for SSE instructions, you may take a huge performance hit.
	float* pResult = (float*)_aligned_malloc(length * sizeof(float), 16);	// align to 16-byte for SSE
	__m128 x;
	__m128 xDelta = _mm_set1_ps(4.0f);		// Set the xDelta to (4,4,4,4)
	__m128* pResultSSE = (__m128*) pResult;


	const int SSELength = length / 4;

	// Stores time seconds
	time(&bgn);
	for (int stress = 0; stress < 100000; stress++)	// lots of stress loops so we can easily use a stopwatch
	{

		x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);	// Set the initial values of x to (4,3,2,1)
		for (int i = 0; i < SSELength; i++)
		{
			__m128 xSqrt = _mm_sqrt_ps(x);

			__m128 xRecip = _mm_rcp_ps(x);
			pResultSSE[i] = _mm_mul_ps(xRecip, xSqrt);

			// NOTE! Sometimes, the order in which things are done in SSE may seem reversed.
			// When the command above executes, the four floating elements are actually flipped around
			// We have already compensated for that flipping by setting the initial x vector to (4,3,2,1) instead of (1,2,3,4)

			x = _mm_add_ps(x, xDelta);	// Advance x to the next set of numbers
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
#include <xmmintrin.h>
#include <stdio.h>

// 8sec
int main(int argc, char* argv[])
{
	printf("Starting calculation...\n");

	const int length = 64000;

	float* pResult = aligned_alloc(16, length * sizeof(float));
	__m128 x;
	__m128 xDelta = _mm_set1_ps(4.0f);
	__m128* pResultSSE = (__m128*) pResult;


	const int SSELength = length / 4;

	for (int stress = 0; stress < 100000; stress++)
	{
		x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
		for (int i = 0; i < SSELength; i++)
		{
			__m128 xSqrt = _mm_sqrt_ps(x);
			pResultSSE[i] = _mm_div_ps(xSqrt, x);
			x = _mm_add_ps(x, xDelta);
		}

	}

	for (int i = 0; i < 20; i++)
	{
		printf("Result[%d] = %f\n", i, pResult[i]);
	}


	return 0;
}
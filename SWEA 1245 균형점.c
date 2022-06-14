#include <stdio.h>

int T, N;
typedef struct {
	int x;
	int m;
}MAG;
MAG mag[10];

void init()
{
	for (int i = 0; i < 10; i++)
	{
		mag[i].x = 0;
		mag[i].m = 0;
	}
}

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &mag[i].x);
	}

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &mag[i].m);
	}
}

int diff_sosu(long double a, long double b)
{
	long double temp_a = a, temp_b = b;
	int diff_a, diff_b;

	if ((int)temp_a != (int)temp_b)
	{
		if (temp_a > temp_b)	
			return 1;
		else		
			return 2;
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			temp_a -= (int)temp_a;
			temp_b -= (int)temp_b;
			temp_a *= 10;
			temp_b *= 10;
			diff_a = ((int)temp_a) % 10;
			diff_b = ((int)temp_b) % 10;

			if (diff_a != diff_b)
			{					
				if (diff_a > diff_b)
					return 1;
				else if (diff_a < diff_b)
					return 2;
			}
		}
	}
	
	return 0;
}

double solve(long double start, long double end)
{
	long double mid = (start + end) / 2;
	long double low_p = 0, high_p = 0;
	long double d;
	int cnt = 0;
	int flag = 0;

	for(int j=0;j<100;j++)
	{
		low_p = 0.0;
		high_p = 0.0;
		cnt++;

		for (int i = 0; i < N; i++)
		{
			if (mag[i].x < mid)
			{
				d = mid - mag[i].x;
				low_p += mag[i].m / (d*d);
			}
			else if (mid < mag[i].x)
			{
				d = mag[i].x - mid;
				high_p += mag[i].m / (d*d);
			}
		}
	
		flag = diff_sosu(low_p, high_p);

		switch (flag)
		{
		case 0:
			return mid;
			break;
		case 1:
			start = mid;
			mid = (start + end) / 2.0;
			break;
		case 2:
			end = mid;
			mid = (start + end) / 2.0;
			break;
		}
	}

	return mid;
}

int main(void)
{
	double result;
	scanf("%d", &T);
	
	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();
		printf("#%d", t);
		for (int i = 0; i < N - 1; i++)
		{
			result = solve(mag[i].x, mag[i+1].x);
			printf(" %.10f", result);
		}
		printf("\n");		
	}
}
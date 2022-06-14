#include <stdio.h>

int T, N, P;

void input()
{
	scanf("%d %d", &N, &P);
}


long long solve()
{
	long long result = 1;
	int dal = N / P;
	int nam = N % P;

	for (int i = 0; i < P; i++)
	{
		if (i < nam)
			result *= (long long)(dal + 1);
		else
			result *= (long long)dal;
	}

	return result;
}

int main(void)
{
	long long result;

	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		input();
		result = solve();
		printf("#%d %lld\n", t, result);
	}
}
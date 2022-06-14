#include <stdio.h>

int T, N;
long min_dist;
int cnt;

void init()
{
	min_dist = 9999999;
	cnt = 1;
}

long custom_abs(long n)
{
	return n < 0 ? -n : n;
}

void input()
{
	long dist;
	
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%ld", &dist);
		dist = custom_abs(dist);

		if (min_dist >= dist)
		{
			if (min_dist == dist)
				cnt++;
			else
				cnt = 1;

			min_dist = dist;
		}
	}
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();
		printf("#%d %d %d\n", t, min_dist, cnt);
	}
}
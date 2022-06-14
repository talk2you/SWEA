#include <stdio.h>

int T, N;
long long visit[100][21];
int num[100];

void init()
{
	for (int j = 0; j < 21; j++)
		for (int i = 0; i < 100; i++)
			visit[i][j] = 0;
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);
}

void print_visit()
{
	for (int j = 0; j <= 20; j++)
	{
		for (int i = 0; i < N; i++)
		{
			printf("%lld ", visit[i][j]);
		}
		printf("\n");
	}
	printf("----------------\n");
}

void solve()
{
	visit[0][num[0]] = 1;

	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			if (j - num[i] >= 0)
				visit[i][j] = (visit[i][j] + visit[i - 1][j - num[i]]) % 1234567891;
			if (j + num[i] <= 20)
				visit[i][j] = (visit[i][j] + visit[i - 1][j + num[i]]) % 1234567891;
		}
	}
}

int main(void)
{
	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (int test_case = 1; test_case < T + 1; test_case++)
	{
		init();
		input();
		solve();
		//print_visit();
		printf("#%d %lld\n",test_case, visit[N-2][num[N-1]]);
	}
}
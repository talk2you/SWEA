#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int T, N, K;

long long DP[1 << 15][MAX_SIZE];
char str[20][200];
int TEN[MAX_SIZE];
int M[20]; 
int L[20];



void init()
{
	memset(DP, -1, sizeof(DP));
	memset(TEN, 0, sizeof(TEN));
}

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%s", str[i]);
	
	scanf("%d", &K);
}


long long dfs(int state, int mod)
{
	long long *ret = &DP[state][mod];

	if (state == (1 << N) - 1)
	{
		if (mod == 0)
			return 1;
		else
			return 0;
	}

	if (*ret != -1)
		return *ret;

	*ret = 0;

	for (int i = 0; i < N; i++)
	{
		if (state & 1 << i)
			continue;
		*ret += dfs(state | (1 << i), ((mod*TEN[L[i]]) % K + M[i]) % K);
	}

	return *ret;
}

void solve()
{
	long long result;

	TEN[0] = 1;
	for (int i = 1; i < MAX_SIZE; i++)
		TEN[i] = TEN[i - 1] * 10 % K;

	for (int i = 0; i < N; i++)
	{
		M[i] = 0;
		L[i] = 0;
		for (int n = 0; str[i][n] != '\0'; n++)
		{
			M[i] = ((M[i] * 10) + str[i][n] - '0') % K;
			L[i]++;
		}
	}

	result = dfs(0, 0);
	printf("%lld\n", result);
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();

		printf("#%d ", t);
		solve();
	}
}
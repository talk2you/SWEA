#include <stdio.h>

int T, N;
long dummy[10000];
long sum;
long origin;
long move_cnt;

void init()
{
	sum = 0;
	origin = 0;
	move_cnt = 0;
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &dummy[i]);
		sum += dummy[i];
	}
	origin = sum / N;
}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		if (dummy[i] < origin)
		{
			move_cnt += (origin - dummy[i]);
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
		printf("#%d %d\n", test_case, move_cnt);
	}
}
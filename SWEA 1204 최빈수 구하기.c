#include <stdio.h>

#define MAX_DEG 101

int T;
char deg[MAX_DEG];
int max_cnt, max_n;

void init()
{
	for (int i = 0; i < MAX_DEG; i++)
		deg[i] = 0;
	max_cnt = 0;
	max_n = 0;
}

void input()
{
	int idx, temp;

	scanf("%d", &temp);

	for (int i = 0; i < 1000; i++)
	{
		scanf("%d", &idx);
		deg[idx]++;

		if (max_cnt <= deg[idx])
		{
			max_cnt = deg[idx];
			
			/*if(max_cnt == deg[idx] && max_n > idx)
				continue;*/

			max_n = idx;
		}
	}
}

int main(void)
{
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();

		for (int i = 0; i <= MAX_DEG; i++)
			printf("[%d] %d\n", i, deg[i]);



		printf("#%d %d\n", t, max_n);
	}
}
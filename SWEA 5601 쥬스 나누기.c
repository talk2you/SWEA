#include <stdio.h>

int T, N;

void input()
{
	scanf("%d", &N);
}

int main(void)
{
	scanf("%d", &T);

	for (int test_case = 1; test_case < T + 1; test_case++)
	{
		input();

		printf("#%d ", test_case);

		for (int i = 0; i < N; i++)
		{
			 printf("1/%d ", N);
		}
		printf("\n");
	}
}
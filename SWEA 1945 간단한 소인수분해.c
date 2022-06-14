#include <stdio.h>

int T;
long N;
int num[5];
int div_n[5] = { 2,3,5,7,11 };

void init()
{
	for (int i = 0; i < 5; i++)
		num[i] = 0;
}
void input()
{
	scanf("%d", &N);
}

// 모든 소인수분해가 아닌 5개의 숫자에 대한 소인수분해
void solve()
{
	int i = 0;
	long temp = N;

	while (1)
	{
		if (temp % div_n[i] == 0)
		{
			temp /= div_n[i];
			num[i]++;
		}
		else
		{
			i++;
			if (i >= 5)
				break;
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
		solve();
		printf("#%d %d %d %d %d %d\n", t, num[0], num[1], num[2], num[3], num[4]);
	}
}
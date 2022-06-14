#include <stdio.h>

int T, P, Q, R, S, W;

void input()
{
	scanf("%d %d %d %d %d", &P, &Q, &R, &S, &W);
}

int solve()
{
	int a, b;
	int temp;

	// A사 : 1리터당 P
	a = W * P;
	// B사 : R리터 이하 요금 Q, 이후 리터당 S
	if (W <= R)
		b = Q;
	else
	{
		b = Q;
		temp = W - R;
		b += (temp * S);
	}

	return a < b ? a : b;
}

int main(void)
{
	int tax;
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		input();
		tax = solve();

		printf("#%d %d\n", t, tax);
	}
}
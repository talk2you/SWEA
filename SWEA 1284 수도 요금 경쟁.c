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

	// A�� : 1���ʹ� P
	a = W * P;
	// B�� : R���� ���� ��� Q, ���� ���ʹ� S
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
#include <stdio.h>

int T;
long N;
char num[10];

void init()
{
	for (int i = 0; i < 10; i++)
		num[i] = 0;
}

void check_n(long n)
{
	long temp = n;
	
	while (1)
	{
		num[temp % 10] = 1;
		if (temp >= 10)
			temp /= 10;
		else
			break;
	}
}

void input()
{
	scanf("%d", &N);
}

long solve()
{
	long n = 1;
	int flag = 1;

	// n*N�� ã�������� ���ѷ���
	while (1)
	{
		// 10���� ���� �������� �ε����� ����ؼ� num�迭�� ��Ʈ������
		check_n(n*N);
		flag = 1;
		
		// num �迭�� ��� 1�� ��Ʈ�Ǹ� n*N�� ���ϰ� ����ϸ� �Լ� Ż��
		for (int i = 0; i < 10; i++)
		{
			if (num[i] == 0)
				flag = 0;
		}

		if (flag == 1)
			break;

		n++;
	}

	return n*N;
}

int main(void)
{
	long result;

	// �׽�Ʈ ���̽� Ƚ�� �Է�
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		// �ʱ�ȭ
		init();
		// �Է�
		input();
		// ���۰��
		result = solve();
		printf("#%d %d\n", t, result);
	}
}
#include <stdio.h>
#include <string.h>

int T, N;
typedef struct {
	char c;
	int n;
}ZIP;
ZIP zip[10];

void init()
{
	memset(zip, 0, sizeof(ZIP) * 10);
}

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf(" %c %d", &zip[i].c, &zip[i].n);
	}
}

void solve()
{
	int r = 0;

	// ���ڿ� 10�� ī��Ʈ �� ���� ������ְ�..
	for (int i = 0; i < N; i++)
	{
		while (1)
		{
			// �Է¹��� ������ŭ ���
			printf("%c", zip[i].c);
			zip[i].n--;

			// 10������ ���پ� �߰�
			r++;
			if (r >= 10)
			{
				printf("\n");
				r = 0;
			}
			// �� ���� Ż��
			if (zip[i].n == 0)
				break;
		}
	}
	printf("\n");
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		printf("#%d\n", t);
		init();
		input();
		solve();
	}
	return 0;
}
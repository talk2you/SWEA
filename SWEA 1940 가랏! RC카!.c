#include <stdio.h>

int T, N;
int rc_acc;
int rc_dist;

typedef struct {
	int cmd;
	int acc;
}CMD;
CMD rc_cmd[30];

void init()
{
	for (int i = 0; i < 30; i++)
	{
		rc_cmd[i].cmd = 0;
		rc_cmd[i].acc = 0;
	}
	rc_acc = 0;
	rc_dist = 0;
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		// cmd�� 0�̸� acc �� �ȹޱ�
		scanf(" %d", &rc_cmd[i].cmd);
		if (rc_cmd[i].cmd != 0)
			scanf(" %d", &rc_cmd[i].acc);
	}

}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		switch (rc_cmd[i].cmd)
		{
		// ������ ���������� ����
		case 1:
			rc_acc += rc_cmd[i].acc;
			break;
		// ������ 0���Ϸ� �������� ����
		case 2:
			rc_acc -= rc_cmd[i].acc;
			if (rc_acc < 0)
				rc_acc = 0;
			break;
		}
		// ���� ���Ӱ��� ���� �Ÿ� ����
		rc_dist += rc_acc;
	}
}

int main(void)
{
	scanf("%d", &T);
	
	for (int t = 1; t < T + 1; t++)
	{
		// ���� �ʱ�ȭ
		init();
		// �Է�
		input();
		// ���� ���
		solve();
		// ���
		printf("#%d %d\n",t, rc_dist);
	}
}
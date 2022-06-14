#include <stdio.h>
#include <string.h>

int T, N;
typedef struct {
	int a, b;
	int pre, next;
}CON;
CON con[20];
CON max_con[20];
int max_cnt;
int start_n;

// �ʱ�ȭ
void init()
{
	memset(con, -1, sizeof(CON) * 20);
	memset(max_con, -1, sizeof(CON) * 20);
	max_cnt = 0;
}

// �Է�
void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &con[i].a, &con[i].b);
}

void print_con()
{
	int next = start_n;

	while (next != -1)
	{
		printf("%d %d ", max_con[next].a, max_con[next].b);
		next = max_con[next].next;
	}
}

// DFS
void dfs(int _n, int _cnt, int _visit[20], CON _con[20])
{
	CON temp_con[20];
	int temp_cnt;
	int temp_visit[20];
	int visit_stat = 0;
	
	// ��� ���縦 �� ���� Ż���Ѵ�
	for (int i = 0; i < N; i++)
	{
		if (_visit[i] == 0)
		{
			visit_stat = 1;
			break;
		}
	}
	if (visit_stat == 0)
	{
		// �ִ�� ����� ���� ���� ����
		if (max_cnt < _cnt)
		{
			max_cnt = _cnt;
			memcpy(max_con, _con, sizeof(CON) * 20);
			
			int pre = _n;

			// ��ũ�帮��Ʈ �������� ����
			while (pre != -1)
			{
				start_n = pre;
				pre = _con[pre].pre;
			}			
		}
		return;
	}

	// ��� ���� ���鼭 �������� ������ ����
	for (int i = 0; i < N; i++)
	{
		memcpy(temp_visit, _visit, sizeof(int) * 20);
		memcpy(temp_con, _con, sizeof(CON) * 20);
		temp_cnt = _cnt;

		if (temp_visit[i] == 0)
		{
			if (con[_n].b == con[i].a)
			{
				temp_cnt++;
				temp_visit[i] = 1;
				temp_con[i].pre = _n;
				temp_con[_n].next = i;

				dfs(i, temp_cnt, temp_visit, temp_con);
			}
		}
	}
}

void solve()
{
	int cnt = 1;
	int visit[20];

	for (int i = 0; i < N; i++)
	{
		memset(visit, 0, sizeof(int) * 20);
		visit[i] = 1;
		cnt = 1;
		
		dfs(i, cnt, visit, con);
	}
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		printf("#%d ", t);
		init();
		input();
		solve();
		print_con();
		printf("\n");
	}
}
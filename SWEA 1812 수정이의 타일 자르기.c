#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 500
#define MAX_QUE 5000
int T, N;
long M;

// ����ť
typedef struct {
	int x[MAX_QUE];
	int y[MAX_QUE];
	int front, end;
	int (*push)(long, long);
	int (*pop)(long*, long*);
	int cnt;
}QUE;
QUE que;
void init_que();

int tile_cnt = 0;

// ũ�Ⱑ ū ������� ������ �켱���� ť
int heap[MAX_SIZE];
int heapSize = 0;

// ���� �ʱ�ȭ
void init()
{
	tile_cnt = 0;
	init_que();

	memset(heap, 0, sizeof(int)*MAX_SIZE);
	heapSize = 0;
}

// ����ť ���� �Լ�
int isFull()
{
	int temp = que.front - 1;
	if (temp < 0)
		temp += MAX_QUE;

	if (temp == que.end)
		return 0;
	return 1;
}

int isEmpty()
{
	if (que.front == que.end)
		return 0;
	return 1;
}

int que_push(long x, long y)
{
	if (!isFull())
		return 0;
	que.x[que.end] = x;
	que.y[que.end] = y;
	que.end++;
	que.end %= MAX_QUE;
	que.cnt++;
	return 1;
}

int que_pop(long *x, long* y)
{
	if (!isEmpty())
		return 0;
	*x = que.x[que.front];
	*y = que.y[que.front];
	que.front++;
	que.front %= MAX_QUE;
	que.cnt--;
	return 1;
}

// �켱���� ť ���� �Լ�
void init_que()
{
	memset(&que, 0, sizeof(QUE));
	que.cnt = 0;
	que.front = 0;
	que.end = 0;
	que.push = que_push;
	que.pop = que_pop;	
}

void heapInit(void)
{
	heapSize = 0;
}

int heapPush(int value)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		return 0;
	}

	heap[heapSize] = value;

	int current = heapSize;
	while (current > 0 && heap[current] > heap[(current - 1) ])
	{
		int temp = heap[(current - 1)];
		heap[(current - 1)] = heap[current];
		heap[current] = temp;
		current = (current - 1);
	}

	heapSize = heapSize + 1;

	return 1;
}

// �Է�
void input()
{
	long k;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &k);
		heapPush(k);
	}
}

// ���� �ذ�
void solve()
{
	long x, y, a;
	int cnt = 0;
	int temp_cnt = 0;
	
	// 1. �ʱ� Ÿ�� �߰� �ϸ鼭 Ÿ�� ���� ī��Ʈ ����
	que.push(M, M);
	tile_cnt = 1;

	for (int i = 0; i < N; i++)
	{
		// 2. �Է¿� ���� 2^k ��ŭ ���� ���̷� ����
		a = (long)pow(2, heap[i]);
		
		temp_cnt = que.cnt;
		cnt = 0;

		// 3. ť���� ������ ���ϴ� ũ��� �ڸ��� �ִ��� �Ǵ�
		while (que.pop(&x, &y))
		{
			// 4. ť �ѹ��� �� ���� �� Ÿ�� �߰��ϸ鼭 ���� ����
			if (temp_cnt <= cnt )
			{
				que.push(x, y);
				temp_cnt = que.cnt;

				x = M;
				y = M;
				tile_cnt++;
			}

			// 5. �ڸ��� ������ �ڸ��� ���� Ÿ�� �ΰ� ť�� �߰�
			if (x - a >= 0 && y - a >= 0)
			{
				que.push(a, y - a);
				que.push(x - a, y);
				break;
			}
			// 6. ���ڸ��� �ٽ� ť�� �����ϰ� 3���� ���ư��� �ٸ� Ÿ�� ����
			else
				que.push(x, y);
			
			cnt++;
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

		printf("#%d %d\n",t, tile_cnt);
	}
}
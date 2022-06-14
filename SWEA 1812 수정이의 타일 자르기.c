#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 500
#define MAX_QUE 5000
int T, N;
long M;

// 원형큐
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

// 크기가 큰 순서대로 저장할 우선순위 큐
int heap[MAX_SIZE];
int heapSize = 0;

// 변수 초기화
void init()
{
	tile_cnt = 0;
	init_que();

	memset(heap, 0, sizeof(int)*MAX_SIZE);
	heapSize = 0;
}

// 원형큐 관련 함수
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

// 우선순위 큐 관련 함수
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

// 입력
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

// 문제 해결
void solve()
{
	long x, y, a;
	int cnt = 0;
	int temp_cnt = 0;
	
	// 1. 초기 타일 추가 하면서 타일 개수 카운트 증가
	que.push(M, M);
	tile_cnt = 1;

	for (int i = 0; i < N; i++)
	{
		// 2. 입력에 대해 2^k 만큼 면의 길이로 결정
		a = (long)pow(2, heap[i]);
		
		temp_cnt = que.cnt;
		cnt = 0;

		// 3. 큐에서 꺼내서 원하는 크기로 자를수 있는지 판단
		while (que.pop(&x, &y))
		{
			// 4. 큐 한바퀴 다 돌면 새 타일 추가하면서 개수 증가
			if (temp_cnt <= cnt )
			{
				que.push(x, y);
				temp_cnt = que.cnt;

				x = M;
				y = M;
				tile_cnt++;
			}

			// 5. 자를수 있으면 자르고 남은 타일 두개 큐에 추가
			if (x - a >= 0 && y - a >= 0)
			{
				que.push(a, y - a);
				que.push(x - a, y);
				break;
			}
			// 6. 못자르면 다시 큐에 저장하고 3으로 돌아가서 다른 타일 꺼냄
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
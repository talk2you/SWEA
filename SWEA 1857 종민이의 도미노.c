#include <stdio.h>

#define MAX_N 2003
#define Max(a, b) ((a>b)?(a):(b))

int T, N, K;
int map[MAX_N][MAX_N];
int visit[MAX_N][MAX_N];
// 가리는 값 최고값 1000 * 5 = 5000;
int max_val;
// 출력 최고값 = 2000 * 2000 * 1000 = 4,000,000,000
unsigned int total_sum;

typedef struct {
	int n;
	int r1, c1, r2, c2;
}HEAP;
HEAP heap[30];
int heap_cnt;

void init()
{
	for (register int r = 0; r < MAX_N; r++)
		for (register int c = 0; c < MAX_N; c++)
			visit[r][c] = 0;

	for (int i = 0; i < 30; i++)
	{
		heap[i].n = 0;
		heap[i].r1 = 0;
		heap[i].c1 = 0;
		heap[i].r2 = 0;
		heap[i].c2 = 0;
	}

	heap_cnt = 0;
	max_val = 0;
	total_sum = 0;	
}

void heap_copy(HEAP *h1, HEAP *h2)
{
	h1->n = h2->n;
	h1->r1 = h2->r1;
	h1->c1 = h2->c1;
	h1->r2 = h2->r2;
	h1->c2 = h2->c2;
}

void heap_push(int n, int r1, int c1, int r2, int c2)
{
	HEAP temp;

	heap[heap_cnt].n = n;
	heap[heap_cnt].r1 = r1;
	heap[heap_cnt].c1 = c1;
	heap[heap_cnt].r2 = r2;
	heap[heap_cnt].c2 = c2;
	
	if (heap_cnt < 25)
		heap_cnt++;
	
	for (int i = heap_cnt-1; i >= 1; i--)
	{
		if (heap[i].n <= heap[i - 1].n)
			break;

		heap_copy(&temp, &heap[i]);
		heap_copy(&heap[i], &heap[i - 1]);
		heap_copy(&heap[i - 1], &temp);
	}

	if (heap_cnt >= 25)
		heap_cnt = 24;
}

void input()
{
	scanf("%d %d", &N, &K);
	
	// O(N^2)
	for (register int r = 0; r < N; r++)
		for (register int c = 0; c < N; c++)
		{
			scanf("%d", &map[r][c]);
			total_sum = total_sum + map[r][c];
		}
}

void dfs(int _sum, int _k_cnt)
{
	int wish_sum;

	if (_k_cnt >= K)
	{
		max_val = Max(_sum, max_val);
		//printf("max_val:%d\n", max_val);
		return;
	}

	for (int i = 0; i < heap_cnt; i++)
	{
		if (visit[heap[i].r1][heap[i].c1] != 0 ||
			visit[heap[i].r2][heap[i].c2] != 0)
			continue;

		// 기대치
		wish_sum = _sum;
		int k = i;
		for (int j = _k_cnt; j < K; j++)
		{
			wish_sum += heap[k].n;
			if (k < heap_cnt-1)
				k++;
		}

		// 최대값보다 기대치가 더 작으면 패스
		if (max_val >= wish_sum)
			continue;

		//printf("_sum:%d wish_sum:%d\n", _sum, wish_sum);

		visit[heap[i].r1][heap[i].c1] = 1;
		visit[heap[i].r2][heap[i].c2] = 1;

		dfs(_sum + heap[i].n, _k_cnt + 1);

		visit[heap[i].r1][heap[i].c1] = 0;
		visit[heap[i].r2][heap[i].c2] = 0;
	}
}

void solve()
{
	int list_cnt = 0;
	int val;	

	for (register int r = 0; r < N; r++)
	{
		for (register int c = 0; c < N; c++)
		{
			// 가로 모양
			if (c - 1 >= 0)
			{
				val = map[r][c - 1] + map[r][c];
				heap_push(val, r, c - 1, r, c);
			}
			// 세로 모양
			if (r - 1 >= 0)
			{
				val = map[r - 1][c] + map[r][c];
				heap_push(val, r - 1, c, r, c);
			}
		}
	}

	// DFS
	dfs(0, 0);
	
	/*for(int i=0;i<heap_cnt;i++)
		printf("%d [%d %d], [%d %d]\n", heap[i].n, heap[i].r1, heap[i].c1, heap[i].r2, heap[i].c2);*/
}

int main(void)
{
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		solve();
		printf("#%d %d\n", t, total_sum - (unsigned int)max_val);
	}
}
#include <stdio.h>
#include <string.h>
#include <math.h>

int T, N;
// 회사 -> N명의 고객집 -> 집
typedef struct {
	int x, y;
}COORD;
COORD customer[10];
COORD company, home;

typedef struct NODE{
	int x, y;
	int dist;
	int pre, next;
}NODE;

int min_dist = 99999999;

// 초기화
void init()
{
	min_dist = 99999999;
}

void print_node(NODE node[12])
{
	for(int i=0;i<12;i++)
		printf("[%d] (%d %d) >> %d, pre: %d, next: %d\n", i, node[i].x, node[i].y, node[i].dist, node[i].pre, node[i].next);
	printf("------------------\n");
}

// 입력
void input()
{
	scanf("%d", &N);
	scanf("%d %d", &company.x, &company.y);
	scanf("%d %d", &home.x, &home.y);

	for(int i=0;i<N;i++)
		scanf("%d %d", &customer[i].x, &customer[i].y);
}

void init_node(NODE node[12])
{
	memset(node, 0, sizeof(NODE)*12);

	node[0].x = company.x;
	node[0].y = company.y;
	node[11].x = home.x;
	node[11].y = home.y;
	
	for (int i = 0; i < 12; i++)
	{
		node[i].next = -1;
		node[i].pre = -1;
	}

	for (int i = 1; i <= N; i++)
	{
		node[i].x = customer[i-1].x;
		node[i].y = customer[i-1].y;
	}
}

void visit_customer(int n, int dist, int visit[12], NODE node[12])
{
	NODE temp_node[12];
	int temp_visit[12];
	int temp_dist;
	int zero_cnt = 0;

	for (int i = 1; i <=N; i++)
	{
		if (visit[i] == 0)
			zero_cnt++;
	}
	
	if (zero_cnt == 0)
	{
		memcpy(temp_node, node, sizeof(NODE) * 12);
		
		temp_node[n].next = 11;
		temp_node[11].pre = n;
		temp_node[11].dist = abs(node[n].x - node[11].x) + abs(node[n].y - node[11].y);
		temp_dist = dist + temp_node[11].dist;

		if (min_dist > temp_dist)
		{
			min_dist = temp_dist;
		}
		return;
	}

	for (int i = 1; i <= N; i++)
	{
		memcpy(temp_visit, visit, sizeof(int) * 12);
		memcpy(temp_node, node, sizeof(NODE)*12);

		if (temp_visit[i] == 0)
		{
			temp_visit[i] = 1;
			temp_node[i].dist = abs(node[n].x - node[i].x) + abs(node[n].y - node[i].y);
			temp_node[n].next = i;
			temp_node[i].pre = n;
			temp_dist = dist + temp_node[i].dist;

			if(min_dist > temp_dist)
				visit_customer(i, temp_dist, temp_visit, temp_node);
		}
	}
}

void solve()
{
	int visit[12];
	NODE node[12];	
	
	for (int i = 1; i <= N; i++)
	{
		// 초기 노드값, visit 배열 세팅
		memset(visit, 0, sizeof(int)*12);
		visit[0] = 1;
		visit[i] = 1;
		visit[11] = 1;

		init_node(node);
		node[i].dist = abs(node[0].x - node[i].x) + abs(node[0].y - node[i].y);
		node[0].next = i;
		node[i].pre = 0;
		
		visit_customer(i, node[i].dist, visit, node);
	}
}

int main(void)
{
	int idx = 0;
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();
		solve();
		
		printf("#%d %d\n",t, min_dist);
	}
}
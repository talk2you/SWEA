#include <stdio.h>
#include <string.h>
#include <math.h>

int T;
int V, E;
int A, B;

typedef struct {
	long p;
	long ch1, ch2;
}NODE;
NODE node[10000];
int node_cnt = 1;

// 초기화
void init()
{
	memset(node, -1, sizeof(NODE) * 10000);
	node_cnt = 1;
}

void print_node()
{
	for (int i = 0; i < E; i++)
		printf("[%3d] %d %d %d\n", i,node[i].p, node[i].ch1, node[i].ch2);
}

void set_node(int p, int c)
{
	if (node[p].ch1 == -1)
		node[p].ch1 = c;
	else
		node[p].ch2 = c;

	node[c].p = p;
}

// 입력
void input()
{
	int p, c;

	scanf("%d %d %d %d", &V, &E, &A, &B);
	for (int i = 0; i < E; i++)
	{
		scanf("%d %d", &p, &c);
		set_node(p, c);
	}
}

// 자식 노드방향으로 DFS
void dfs(int n)
{
	if (node[n].ch1 != -1)
	{
		node_cnt++;
		dfs(node[n].ch1);
	}
	if (node[n].ch2 != -1)
	{
		node_cnt++;
		dfs(node[n].ch2);
	}
}

// 문제 해결
int solve()
{
	int comp1 = A, comp2 = B;
	int temp_a = A , temp_b = B;
	int head = 1;

	// 부모노드로 올라가면서 같은 부모노드일때 탈출!
	while (comp1 != -1)
	{
		comp1 = node[temp_a].p;
		temp_b = B;
		comp2 = B;

		while (comp2 != -1)
		{
			comp2 = node[temp_b].p;
			
			if (node[temp_b].p == -1)
				head = temp_b;
			if (comp1 != comp2)
				temp_b = comp2;
			else
				return comp1;
		}
		temp_a = comp1;
	}

	return head;
}

int main(void)
{
	int result = 0;

	scanf("%d", &T);
	
	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();
		result = solve();
		dfs(result);

		printf("#%d %d %d\n",t, result, node_cnt);
	}
}
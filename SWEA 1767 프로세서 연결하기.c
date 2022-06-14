#include <stdio.h>

#define MAX 14

int T, N;
int map[MAX][MAX];

typedef struct {
	int r, c;
	int dir[4];
}IC;
IC ic[200];
int ic_cnt;

typedef struct {
	int r[4], c[4];
}DIR;
DIR dir = { {-1,1,0,0},{0,0,-1,1} };

long total_func = 0;
int max_onchip = 0, min_line = 99999;

void init()
{
	for (int i = 0; i < 200; i++)
	{
		ic[i].r = 0;
		ic[i].c = 0;
		ic[i].dir[0] = 0;
		ic[i].dir[1] = 0;
		ic[i].dir[2] = 0;
		ic[i].dir[3] = 0;
	}

	for (int r = 0; r < MAX; r++)
		for (int c = 0; c < MAX; c++)
			map[r][c] = 0;
		
	ic_cnt = 0;
	total_func = 0;
	max_onchip = 0;
	min_line = 99999;
}

void print_map(int dst[][MAX])
{
	for (int r = 0; r < N + 2; r++)
	{
		for (int c = 0; c < N + 2; c++)
		{
			printf("%d ", dst[r][c]);
		}
		printf("\n");
	}
	printf("--------------------------\n");
}

void print_ic()
{
	printf("ic cnt : %d\n", ic_cnt);
	for (int i = 0; i < ic_cnt; i++)
	{
		printf("ic%d [%d %d] [%d %d %d %d]\n", i, ic[i].r, ic[i].c,
			ic[i].dir[0], ic[i].dir[1], ic[i].dir[2], ic[i].dir[3]);
	}
}

void input()
{
	int match_dir = -1;
	int data;
	scanf("%d", &N);

	// º®
	for (int i = 0; i < N+2; i++)
	{
		map[0][i] = 9;
		map[N + 1][i] = 9;
		map[i][0] = 9;
		map[i][N + 1] = 9;		
	}
	
	// ¸ß½Ã³ë½º
	for (int r = 1; r < N + 1; r++)
	{
		for (int c = 1; c < N + 1; c++)
		{
			scanf("%d", &data);
			map[r][c] = data;
			if (map[r][c] == 1)
			{
				ic[ic_cnt].r = r;
				ic[ic_cnt].c = c;
				ic_cnt++;
			}
		}
	}
	
	
	for (int n = 0; n < ic_cnt; n++)
	{
		match_dir = -1;

		if (ic[n].r == 1)
			match_dir = 0;
		else if (ic[n].r == N)
			match_dir = 1;
		else if (ic[n].c == 1)
			match_dir = 2;
		else if (ic[n].c == N)
			match_dir = 3;

		if (match_dir != -1)
		{
			for (int i = 0; i < 4; i++)
				if (i != match_dir)
					ic[n].dir[i] = 1;
			continue;
		}			
	
		for (int i = 0; i < 4; i++)
		{
			int temp_r = ic[n].r;
			int temp_c = ic[n].c;

			while (1)
			{
				temp_r += dir.r[i];
				temp_c += dir.c[i];
				if (map[temp_r][temp_c] == 1)
				{
					ic[n].dir[i] = 1;
					break;
				}
				else if (map[temp_r][temp_c] == 9)
				{
					break;
				}
			}
		}
	}
}

void copy_map(int dst[][MAX], int src[][MAX])
{
	for (int r = 0; r < N + 2; r++)
		for (int c = 0; c < N + 2; c++)
			dst[r][c] = src[r][c];
}

int connect_power(int n, int i, int *cnt, int pre_map[][MAX])
{
	int r = ic[n].r, c = ic[n].c;
	int temp_cnt = *cnt;

	while (1)
	{
		total_func++;

		r += dir.r[i];
		c += dir.c[i];

		if (pre_map[r][c] == 7 || pre_map[r][c] == 1)
		{
			*cnt = temp_cnt;
			return 0;
		}

		if (r == 0 || r == N + 1 || c == 0 || c == N + 1)
			return 1;

		pre_map[r][c] = 7;	
		*cnt += 1;
	}
}

void solve(int n, int onchip, int line, int pre_map[][MAX])
{
	int temp_r, temp_c, temp_line, temp_onchip;
	int temp_map[MAX][MAX];
	int (*ptr_map)[MAX];
	int unconected = 0;

	if (n >= ic_cnt)
		return;

	if ((ic_cnt - n) + onchip < max_onchip)
		return;

	for (int i = 0; i < 4; i++)
	{
		if (ic[n].dir[i] == 0)
		{
			temp_r = ic[n].r;
			temp_c = ic[n].c;
			temp_line = line;
			temp_onchip = onchip;
			copy_map(temp_map, pre_map);

			if (connect_power(n, i, &temp_line, temp_map))
			{
				ptr_map = temp_map;
				temp_onchip++;
			}
			else
				ptr_map = pre_map;

			if (max_onchip <= temp_onchip)
			{
				if (max_onchip < temp_onchip)
				{
					min_line = temp_line;
				}

				max_onchip = temp_onchip;

				if (min_line > temp_line)
				{
					min_line = temp_line;				
				}
			}
			solve(n + 1, temp_onchip, temp_line, ptr_map);
		}
	}
	
	solve(n + 1, onchip, line, pre_map);
}

int main(void)
{
	scanf("%d", &T);

	for (int test_case = 1; test_case < T + 1; test_case++)
	{
		init();
		input();		

		solve(0, 0, 0, map);
		printf("#%d %d\n",test_case, min_line);
	}

	return 0;
}
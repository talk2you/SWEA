#include <stdio.h>
#include <string.h>

int T,N,X;
int map[22][22];
int ans;

void init()
{
	memset(map, -1, sizeof(map));
	ans = 0;
}

void input()
{
	scanf("%d %d", &N, &X);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &map[r][c]);
		}
	}
}

void solve_row()
{
	int len, n;
	int need_bridge = 0;

	for (int i = 1; i <= N; i++)
	{
		len = 1;
		n = map[i][1];
		need_bridge = 0;
		for (int j = 2; j <= N + 1; j++)
		{
			if (j == N + 1)
			{
				if (need_bridge == 0)
					ans++;
				//printf("ans:%d\n", ans);
				break;
			}

			// 다리 불필요
			if (need_bridge == 0)
			{
				if (n > map[i][j])
				{
					if (n - map[i][j] != 1)
						break;
					need_bridge = 1;
					len = 1;
					n = map[i][j];
				}
				else if (n < map[i][j])
				{
					if (map[i][j] - n != 1)
						break;

					if (len >= X)
					{
						n = map[i][j];
						len = 1;
					}
					else
						break;
				}
				else
					len++;
			}
			// 다리 필요
			else
			{
				if (n == map[i][j])
				{
					len++;
					if (len >= X)
					{
						len = 0;
						need_bridge = 0;
					}
				}
				else
				{
					//printf("fuck you\n");
					break;
				}
			}

			//printf("[%d %d] %d %d %d\n", i, j, n, len, need_bridge);
		}
	}
}

void solve_col()
{
	int len, n;
	int need_bridge = 0;

	for (int j = 1; j <= N; j++)
	{
		len = 1;
		n = map[1][j];
		need_bridge = 0;
		for (int i = 2; i <= N + 1; i++)
		{
			if (i == N + 1)
			{
				if (need_bridge == 0)
					ans++;
				//printf("ans:%d\n", ans);
				break;
			}

			// 다리 불필요
			if (need_bridge == 0)
			{
				if (n > map[i][j])
				{
					if (n - map[i][j] != 1)
						break;
					need_bridge = 1;
					len = 1;
					n = map[i][j];
				}
				else if (n < map[i][j])
				{
					if (map[i][j] - n != 1)
						break;

					if (len >= X)
					{
						n = map[i][j];
						len = 1;
					}
					else
					{
						//printf("not enough\n");
						break;
					}
				}
				else
					len++;
			}
			// 다리 필요
			else
			{
				if (n == map[i][j])
				{
					len++;
					if (len >= X)
					{
						len = 0;
						need_bridge = 0;
					}
				}
				else
				{
					//printf("fuck you\n");
					break;
				}
			}

			//printf("[%d %d] %d %d %d\n", i, j, n, len, need_bridge);
		}
	}
}

int main(void)
{
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		solve_row();
		solve_col();
		printf("#%d %d\n",t, ans);
	}
	return 0;
}
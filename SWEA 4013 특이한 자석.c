#include <stdio.h>
#include <string.h>

int T, K;

typedef struct {
	char up, right, left;
	int d[8];
	char rotate;
}GEAR;
GEAR gear[5];

typedef struct {
	int n;
	int r;
}CMD;
CMD cmd[20];
char ans = 0;

void init()
{
	memset(gear, 0, sizeof(gear));
	memset(cmd, 0, sizeof(cmd));

	for (char i = 1; i <= 4; i++)
	{
		gear[i].up = 0;
		gear[i].right = 2;
		gear[i].left = 6;
	}
	ans = 0;
}

void input()
{
	scanf("%d", &K);

	for (char i = 1; i <= 4; i++)
	{
		for (char j = 0; j < 8; j++)
		{
			scanf("%d", &gear[i].d[j]);
		}
	}

	for (char i = 0; i < K; i++)
		scanf("%d %d", &cmd[i].n, &cmd[i].r);
}

void check_gear(int src, int dst)
{
	char temp_left, temp_right;

	if (dst <= 0 || dst >= 5)
		return;

	// ¿ÞÂÊ
	if (dst < src)
	{
		//printf("%d < %d\n", src, dst);
		temp_left = gear[src].left;
		temp_right = gear[dst].right;
		if (gear[src].d[temp_left] != gear[dst].d[temp_right])
		{
			gear[dst].rotate = gear[src].rotate * -1;
			check_gear(dst, dst - 1);
		}
	}
	else
	{
		//printf("%d > %d\n", src, dst);
		temp_right = gear[src].right;
		temp_left = gear[dst].left;		
		if (gear[src].d[temp_right] != gear[dst].d[temp_left])
		{
			gear[dst].rotate = gear[src].rotate * -1;
			check_gear(dst, dst + 1);
		}
	}
}

void print_gear()
{
	for (char j = 1; j <= 4; j++)
	{
		for (int i = 0; i < 8; i++)
			printf("%d ", gear[j].d[i]);

		printf("up:%d left:%d right:%d, rotate:%d\n", gear[j].up, gear[j].left, gear[j].right, gear[j].rotate);
	}
	printf("---------------\n");
}

void rotate_gear()
{
	for (char i = 1; i <= 4; i++)
	{
		if (gear[i].rotate == 1)
		{
			gear[i].up = (gear[i].up - 1 < 0) ? 7 : gear[i].up - 1;
			gear[i].left = (gear[i].left - 1 < 0) ? 7 : gear[i].left - 1;
			gear[i].right = (gear[i].right - 1 < 0) ? 7 : gear[i].right - 1;
		}
		else if (gear[i].rotate == -1)
		{
			gear[i].up = (gear[i].up + 1 > 7) ? 0 : gear[i].up + 1;
			gear[i].left = (gear[i].left + 1 > 7) ? 0 : gear[i].left + 1;
			gear[i].right = (gear[i].right + 1 > 7) ? 0 : gear[i].right + 1;
		}

		gear[i].rotate = 0;
	}
}

void result()
{
	ans = 0;
	for (char i = 1; i <= 4; i++)
	{
		//printf("%d\n", gear[i].d[gear[i].up]);
		if (gear[i].d[gear[i].up] == 1)
		{
			ans = ans | (1 << (i - 1));
		}
	}
}

void solve()
{
	int n;

	for (char i = 0; i < K; i++)
	{
		n = cmd[i].n;
		gear[n].rotate = cmd[i].r;

		check_gear(n, n-1);
		check_gear(n, n+1);

		rotate_gear();

		//print_gear();
		result();
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
		solve();
		printf("#%d %d\n",t, ans);
	}

	return 0;
}
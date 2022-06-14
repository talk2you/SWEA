#include <stdio.h>

int T, G, N;
int flag_parallel = 1;
int result;

typedef struct {
	int x1, y1, x2, y2;
}COORD;
COORD coord[100];

typedef struct {
	double a, b;
	int inf, x;
}LINE;
LINE line[100];
int line_cnt;

void init()
{
	for (int i = 0; i < 100; i++)
	{
		line[i].a = 0.0;
		line[i].b = 0.0;
		line[i].inf = 0;
		line[i].x = 0;
	}
	line_cnt = 0;
	result = 0;
	flag_parallel = 1;
}

void input()
{
	scanf("%d %d", &G, &N);

	for (int i = 0; i < N; i++)
		scanf("%d %d %d %d", &coord[i].x1, &coord[i].y1, &coord[i].x2, &coord[i].y2);
}

void print_eq()
{
	for (int i = 0; i < line_cnt; i++)
	{
		if(line[i].inf == 1)
			printf("[%d] x=%d\n", i+1, line[i].x);
		else
			printf("[%d] a=%f, b=%f\n", i+1, line[i].a, line[i].b);
	}
	if (flag_parallel)
		printf("all paralleled\n");
}

void eq_straight()
{
	double a = 0, b = 0;
	int inf = 0, x = 0;
	int flag = 0;

	for (int i = 0; i < N; i++)
	{
		a = 0;
		b = 0;
		inf = 0;
		x = 0;
		flag = 0;

		// 수직선의 경우
		if (coord[i].x1 == coord[i].x2)
		{
			inf = 1;
			x = coord[i].x1;
		}
		// 그 이외
		else
		{
			a = (double)(coord[i].y2 - coord[i].y1) / (double)(coord[i].x2 - coord[i].x1);
			b = coord[i].y1 - a * coord[i].x1;
		}

		for (int j = 0; j < line_cnt; j++)
		{
			// 수직선
			if (inf == 1)
			{
				if (line[j].inf == 1 && line[j].x == x)
				{
					flag = 1;
					break;
				}
			}
			// 그 이외
			else
			{
				if (line[j].a == a && line[j].b == b && line[j].inf == 0)
				{
					flag = 1;
					break;
				}
			}

			// 평행 체크
			if (inf == 1)
			{
				if (line[j].inf == 0)
					flag_parallel = 0;
			}
			else
			{
				if (line[j].inf == 1)
					flag_parallel = 0;
				else
				{
					if (line[j].a != a)
						flag_parallel = 0;
				}
			}
		}

		if (flag == 0)
		{
			if (inf == 1)
			{
				line[line_cnt].inf = 1;
				line[line_cnt].x = x;
			}
			else
			{
				line[line_cnt].a = a;
				line[line_cnt].b = b;
				line[line_cnt].inf = 0;
			}
			line_cnt++;
		}
	}
}

void calc_area()
{
	int now_area;

	if (flag_parallel)
		now_area = line_cnt + 1;
	else
		now_area = line_cnt * 2;

	//printf("now %d\n", now_area);

	if (G <= now_area)
		result = 0;
	else
	{
		if (flag_parallel && G <= now_area *2)
		{
			result = 1;
		}
		else
		{
			result = (G + 1) / 2 - line_cnt;
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
		eq_straight();
		//print_eq();
		calc_area();
		printf("#%d %d\n",t, result);
	}
}
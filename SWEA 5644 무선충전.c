#include <stdio.h>
#include <string.h>
#include <math.h>

// 1 <= BC <= 4
// user = 2
// user는 (1,1), (10,10) 에서 각각 출발
// user 위치는 중복 가능, BC는 X
// 20 <= 총 이동시간 M <= 100
// 지도 크기 : 10x10

int T, M, A;
int result = 0;

typedef struct {
	int x, y;
	int charge;
	int m[100];
}USER;

typedef struct {
	int x, y;
	int coverage;
	int performance;
}BC;

typedef struct {
	int r[5];
	int c[5];
}DIR;

USER user[2] = { {1,1,0},{10,10,0} };

// X, 상, 우, 하, 좌
DIR dir = { {0,-1,0,1,0},{0,0,1,0,-1} };
BC bc[8] = { 0 };

void init()
{
	user[0].x = 1;
	user[0].y = 1;
	user[1].x = 10;
	user[1].y = 10;

	result = 0;
}

void input()
{
	scanf("%d %d", &M, &A);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &user[i].m[j]);
		}
	}

	for (int i = 0; i < A; i++)
		scanf("%d %d %d %d", &bc[i].x, &bc[i].y, &bc[i].coverage, &bc[i].performance);
}

void max_performance()
{
	int dist[2] = { 0, };
	int sum = 0;
	int max = 0;
	int temp[2] = { 0, };
	int flag1 = 0, flag2 = 0;

	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < A; j++)
		{
			dist[0] = abs(bc[i].x - user[0].x) + abs(bc[i].y - user[0].y);
			dist[1] = abs(bc[j].x - user[1].x) + abs(bc[j].y - user[1].y);

			if (dist[0] <= bc[i].coverage)
			{
				flag1 = 1;
				sum += bc[i].performance;

			}
			if (dist[1] <= bc[j].coverage)
			{
				flag2 = 1;
				sum += bc[j].performance;
			}

			if (i == j)
				sum /= 2;

			if (max < sum)
			{
				max = sum;
				if (flag1)
				{
					temp[0] = bc[i].performance;
					if (flag2 && i == j)
						temp[0] /= 2;
					//printf("u1, bc%d (%d %d) > %d, %d\n", i + 1, bc[i].x, bc[i].y, dist[0], bc[i].performance);
				}
				if (flag2)
				{
					temp[1] = bc[j].performance;
					if (flag1 && i == j)
						temp[1] /= 2;
					//printf("u2, bc%d(%d %d) > %d, %d\n", j + 1, bc[j].x, bc[j].y, dist[1], bc[j].performance);
				}
			}
			sum = 0;
			flag1 = 0;
			flag2 = 0;
		}
	}

	printf(">> %d\n", sum);
	result += (temp[0] + temp[1]);
}

void wireless_charge()
{
	int i_dir = 0;
	int cnt = 0;

	int temp[2] = { 0, };

	for (int i = 0; i <= M; i++)
	{
		//printf("t = %d, u1(%d, %d, u2(%d, %d)\n", i, user[0].x, user[0].y, user[1].x, user[1].y);

		max_performance();

		for (int k = 0; k < 2; k++)
		{
			i_dir = user[k].m[i];
			user[k].x += dir.c[i_dir];
			user[k].y += dir.r[i_dir];
		}
	}
}

int main(void)
{
	int test_case;

	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		input();

		wireless_charge();

		printf("#%d %d\n", test_case, result);
	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}
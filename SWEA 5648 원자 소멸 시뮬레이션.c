#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int T, N;
short map[2000][2000];
int total_energy;
int func_cnt;

typedef struct {
	short x, y, dir, e;
	int dead;
}ATOM;
ATOM atom[1000];

typedef struct {
	int x[4], y[4];
}DIR;
DIR dir = { {0,0,-1,1},{1,-1,0,0} };

typedef struct{
	short src, dst, rank;
}HEAP;
HEAP heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}

void init()
{
	heapInit();
	memset(atom, 0, sizeof(atom));
	memset(map, 0, sizeof(map));
	total_energy = 0;
}

short heapPush(short src, short dst, short rank)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	heap[heapSize].src = src;
	heap[heapSize].dst = dst;
	heap[heapSize].rank = rank;

	int current = heapSize;
	while (current > 0 && heap[current].rank < heap[(current - 1) / 2].rank)
	{
		HEAP temp;
		memcpy(&temp, &heap[(current - 1) / 2], sizeof(HEAP));
		memcpy(&heap[(current - 1) / 2], &heap[current], sizeof(HEAP));
		memcpy(&heap[current], &temp, sizeof(HEAP));
		//int temp = heap[(current - 1) / 2];
		//heap[(current - 1) / 2] = heap[current];
		//heap[current] = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

short heapPop(short *src, short *dst, short *rank)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*src = heap[0].src;
	*dst = heap[0].dst;
	*rank = heap[0].rank;

	heapSize = heapSize - 1;

	memcpy(&heap[0], &heap[heapSize], sizeof(HEAP));
	//heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1].rank < heap[current * 2 + 2].rank ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current].rank < heap[child].rank)
		{
			break;
		}

		HEAP temp;
		memcpy(&temp, &heap[current], sizeof(HEAP));
		memcpy(&heap[current], &heap[child], sizeof(HEAP));
		memcpy(&heap[child], &temp, sizeof(HEAP));
		
		/*int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;*/

		current = child;
	}
	return 1;
}

int Abs(int a)
{
	return a < 0 ? -a : a;
}

int Min(int a, int b)
{
	return a < b ? a : b;
}

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		scanf("%hd %hd %hd %hd", &atom[i].x, &atom[i].y, &atom[i].dir, &atom[i].e);
		atom[i].x *= 2;
		atom[i].y *= 2;
	}
}

void solve()
{
	short dist;
	int temp_x1, temp_y1, temp_x2, temp_y2;

	for (register int i = 0; i < N; i++)
	{
		for (register int j = i+1; j < N; j++)
		{
			if (i == j)
				continue;
			if (map[i][j] != 0 || map[i][j] == -1)
				continue;

			func_cnt++;

			dist = (Abs(atom[i].x - atom[j].x) + Abs(atom[i].y - atom[j].y))/2;
			temp_x1 = atom[i].x + dir.x[atom[i].dir] * dist;
			temp_y1 = atom[i].y + dir.y[atom[i].dir] * dist;
			temp_x2 = atom[j].x + dir.x[atom[j].dir] * dist;
			temp_y2 = atom[j].y + dir.y[atom[j].dir] * dist;
			
			if (temp_x1 == temp_x2 && temp_y1 == temp_y2)
			{
				map[i][j] = dist;
				heapPush(i, j, dist);
			}
		}
	}

	short src, dst;
	int temp_e;

	while (heapSize != 0)
	{
		heapPop(&src, &dst, &dist);
		temp_e = 0;
		//printf("%d %d %d\n", src, dst, dist);
		if (atom[src].dead == 0)
		{
			temp_x1 = atom[src].x + dir.x[atom[src].dir] * dist;
			temp_y1 = atom[src].y + dir.y[atom[src].dir] * dist;
			temp_e += (int)atom[src].e;
		}

		if (atom[dst].dead == 0)
		{
			temp_x2 = atom[dst].x + dir.x[atom[dst].dir] * dist;
			temp_y2 = atom[dst].y + dir.y[atom[dst].dir] * dist;
			temp_e += (int)atom[dst].e;
		}

		if (temp_x1 == temp_x2 && temp_y1 == temp_y2)
		{
			atom[dst].dead = atom[src].dead = 1;
			atom[src].x = temp_x1;
			atom[src].y = temp_y1;
			atom[dst].x = temp_x2;
			atom[dst].y = temp_y2;
			total_energy += temp_e;
		}
	}
}

void print_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}

	short src, dst, dist;

	while (heapSize != 0)
	{
		heapPop(&src, &dst, &dist);
		printf("%d %d %d\n", src, dst, dist);
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
		printf("#%d %d\n",t, total_energy);
	}
}
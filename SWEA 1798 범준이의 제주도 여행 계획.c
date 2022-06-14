#include <stdio.h>
#include <string.h>

int T, N, M;
int map[35][35];
int visit[35];

typedef struct {
	char name;
	int time;
	int happy;
}TOUR;
TOUR tour[35];

#define STACK_SIZE 100
typedef struct {
	int data[STACK_SIZE];
	int (*push)(int);
	int(*pop)();
	int tail;
}STACK;
STACK stack;
STACK max_stack;
int max_happy;
int airport;

// 스택 관련
int stack_push(int data)
{
	if (stack.tail < STACK_SIZE)
		stack.data[stack.tail++] = data;
	else
		return 1;
	return 0;
}

int stack_pop()
{
	if (stack.tail == 0)
		return 1;
	else
		return stack.data[--stack.tail];
}

void init_stack()
{
	memset(&stack, 0, sizeof(STACK));
	stack.push = stack_push;
	stack.pop = stack_pop;

	memcpy(&max_stack, &stack, sizeof(STACK));
}

// 변수 초기화
void init()
{
	init_stack();
	memset(visit, 0, sizeof(int) * 35);
	memset(map, 0, sizeof(int) * 35 * 35);
	memset(tour, 0, sizeof(TOUR) * 35);
	max_happy = 0;

}

void print_map()
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			printf("%d ", map[r][c]);
		}
		printf("\n");
	}
}

// 입력
void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r < N-1; r++)
	{
		for (int c = r + 1; c < N; c++)
		{
			// 반대로 가는 방향도 같은 시간이 걸리므로 추가로 저장
			scanf("%d", &map[r][c]);
			map[c][r] = map[r][c];
		}
	}

	for (int i = 0; i < N; i++)
	{
		scanf(" %c", &tour[i].name);

		if (tour[i].name == 'P')
			scanf("%d %d", &tour[i].time, &tour[i].happy);
		else if (tour[i].name == 'A')
			airport = i;
	}
}

// DFS
void dfs(int _n, int _day, int _time, int _happy)
{
	int temp_day, temp_time, temp_happy;

	for (int i = 0; i < N; i++)
	{
		if (_day == M - 1 && tour[i].name == 'H')
			return;

		if (_n != i)
		{
			temp_day = _day;
			temp_time = _time + map[_n][i] + tour[i].time;
			temp_happy = _happy + tour[i].happy;

			if (temp_time <= 540 && _day < M)
			{
				// 방문하지 않은곳, (H는 무한 방문)
				if (visit[i] == 0 || tour[i].name != 'P')
				{
					if (tour[i].name == 'A')
					{
						if (_day == M - 1 && max_happy < temp_happy)
						{
							// 가장 만족도가 높은 값과 길목을 저장
							max_happy = temp_happy;
							stack.push(i);
							memcpy(&max_stack, &stack, sizeof(STACK));
							stack.pop();
						}
						continue;
					}
					else if (tour[i].name == 'H')
					{
						temp_day++;
						temp_time = 0;
					}					
					
					// 길목 저장하는데는 스택 푸쉬&팝이 최고
					stack.push(i);
					visit[i] = 1;				
					dfs(i, temp_day, temp_time, temp_happy);
					stack.pop();
					visit[i] = 0;
				}
			}			
		}
	}
}

void solve()
{
	dfs(0, 0, 0, 0);
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		init();
		input();
		solve();

		printf("#%d %d ",t, max_happy);
		for (int i = 0; i < max_stack.tail; i++)
			printf("%d ", max_stack.data[i] + 1);
		printf("\n");
	}
}
#include <stdio.h>
#include <string.h>

int T;

// stat = 0 이면 정수, 1이면 분수
typedef struct {
	int stat;
	int val[2];
}SUDOKU;
SUDOKU sudoku[6][6];

typedef struct {
	int row[6];
	int col[6];
	int bnd[6];
}VISIT;
VISIT visit;

void init()
{
	memset(&visit, 0, sizeof(VISIT));
	memset(&sudoku, 0, sizeof(sudoku));
}

void input()
{
	char s[4];
	int num;

	for (register int r = 0; r < 6; r++)
	{
		for (register int c = 0; c < 6; c++)
		{
			scanf("%s", s);
			if (s[1] == '/')
			{
				sudoku[r][c].stat = 1;
				if (s[0] != '-')
				{
					num = s[0] - '0';
					sudoku[r][c].val[0] = num;
					visit.row[r] |= (1 << num);
					visit.col[c] |= (1 << num);
					visit.bnd[(c/3) + (r/2)*2] |= (1 << num);
				}
				if (s[2] != '-')
				{
					num = s[2] - '0';
					sudoku[r][c].val[1] = num;
					visit.row[r] |= (1 << num);
					visit.col[c] |= (1 << num);
					visit.bnd[(c / 3) + (r / 2) * 2] |= (1 << num);
				}
			}
			else
			{
				if (s[0] != '-')
				{
					num = s[0] - '0';
					sudoku[r][c].val[0] = num;
					visit.row[r] |= (1 << num);
					visit.col[c] |= (1 << num);
					visit.bnd[(c / 3) + (r / 2) * 2] |= (1 << num);
				}
			}
		}
	}
}

void print_map(SUDOKU _table[6][6])
{
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{
			if(_table[r][c].stat == 1)
				printf("[%d %d] ",_table[r][c].val[0], _table[r][c].val[1]);
			else
				printf("[%d]   ", _table[r][c].val[0]);
		}
		printf("\n");
	}

	printf("row\n");
	for (int i = 0; i < 6; i++)
		printf("%d ", visit.row[i]);
	printf("\n");

	printf("col\n");
	for (int i = 0; i < 6; i++)
		printf("%d ", visit.col[i]);
	printf("\n");

	printf("bundle\n");
	for (int i = 0; i < 6; i++)
		printf("%d ", visit.bnd[i]);
	printf("\n");
}

void print_result(SUDOKU _table[6][6])
{
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 6; c++)
		{
			if (_table[r][c].stat == 1)
				printf("%d/%d ", _table[r][c].val[0], _table[r][c].val[1]);
			else
				printf("%d ", _table[r][c].val[0]);
		}
		printf("\n");
	}
}

void dfs(int _r, int _c, int _n, SUDOKU _table[6][6])
{
	SUDOKU temp_table[6][6];
	int temp_r, temp_c;
	int next_r, next_c, next_n;
	int next_flag = 0;

	if (_r >= 6)
	{
		print_result(_table);
		return;
	}

	next_r = _r;
	next_c = _c + 1;
	if (next_c >= 6)
	{
		next_r++;
		next_c = 0;
	}
	next_n = _n ^ 1;


	for (int i = 1; i <= 9; i++)
	{
		memcpy(temp_table, _table, sizeof(sudoku));
		temp_r = _r;
		temp_c = _c;
		
		// 값이 없을 때
		if (temp_table[temp_r][temp_c].val[_n] == 0 && _n <= temp_table[temp_r][temp_c].stat)
		{
			if ((visit.row[temp_r] & (1 << i)) == 0 &&
				(visit.col[temp_c] & (1 << i)) == 0 &&
				(visit.bnd[(temp_c / 3) + (temp_r / 2) * 2] & (1 << i)) == 0)
			{
				visit.row[temp_r] |= (1 << i);
				visit.col[temp_c] |= (1 << i);
				visit.bnd[(temp_c / 3) + (temp_r / 2) * 2] |= (1 << i);

				temp_table[temp_r][temp_c].val[_n] = i;
				
				//print_map(temp_table);

				if (_n == 0)
				{
					if(temp_table[temp_r][temp_c].val[1] == 0)
						dfs(temp_r, temp_c, next_n, temp_table);
					else
					{
						if (temp_table[temp_r][temp_c].val[0] < temp_table[temp_r][temp_c].val[1])
							dfs(temp_r, temp_c, next_n, temp_table);
					}
				}
				else
				{
					if (temp_table[temp_r][temp_c].val[0] < temp_table[temp_r][temp_c].val[1])
						dfs(next_r, next_c, next_n, temp_table);
				}

				visit.row[temp_r] &= ~(1 << i);
				visit.col[temp_c] &= ~(1 << i);
				visit.bnd[(temp_c / 3) + (temp_r / 2) * 2] &= ~(1 << i);
			}
		}
		// 다음 셀 이동
		else
		{
			next_flag = 1;
			break;
		}
	}

	if (next_flag)
	{
		if(temp_table[temp_r][temp_c].stat == 0)
			dfs(next_r, next_c, 0, temp_table);
		else
		{
			if(_n == 0)
				dfs(temp_r, temp_c, next_n, temp_table);
			else
				dfs(next_r, next_c, next_n, temp_table);
		}
	}
}

void solve()
{	
	dfs(0, 0, 0, sudoku);
}

int main(void)
{
	setbuf(stdout, NULL);

	char buf[5000];
	FILE *fp = freopen("sample_input.txt", "r", stdin);
	fgets(buf, sizeof(buf), fp);

	scanf("%d", &T);

	for (int t = 1; t <= T; t++)
	{
		init();
		input();
		printf("#%d\n", t);
		solve();
	}

	fclose(fp);
	return 0;
}
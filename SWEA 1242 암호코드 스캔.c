#include <stdio.h>
#include <string.h>

#define MAX_KEY 500
#define MAX_DATA 500
#define MAX_TABLE 4096

typedef struct
{
	char key[MAX_KEY + 1];
	char data[MAX_DATA + 1];
}Hash;
Hash tb[MAX_TABLE];

int T, N, M;
// 1 <= N <= 2000 세로
// 1 <= M <= 500 가로
char bar_code[2000][501];
char line[2000];
char password[32];
int pw_code[8];
int ratio = 999;
int pw_sum = 0;

typedef struct {
	int n[4];
}PW_NUM;
PW_NUM pw_num[10] = { {3,2,1,1}, {2,2,2,1}, {2,1,2,2}, {1,4,1,1}, {1,1,3,2}, 
{1,2,3,1}, {1,1,1,4},{1,3,1,2}, {1,2,1,3}, {3,1,1,2} };

void init()
{
	for (int i = 0; i < 2000; i++)
		line[i] = 0;
	for (int i = 0; i < 32; i++)
		password[i] = 0;
	for (int i = 0; i < 8; i++)
		pw_code[i] = 0;
	for (int i = 0; i < 4096; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			tb[i].key[j] = 0;
			tb[i].data[j] = 0;
		}
	}

	ratio = 999;
	pw_sum = 0;
}

void print_code()
{
	for (int i = 0; i < N; i++)
	{
		printf("%s\n", bar_code[i]);
	}
}


void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
		scanf("%s", &bar_code[i][0]);
}

void decode_password(int end)
{
	int start = 0;
	int check = 1;
	int cnt = 0;
	int num = 31;
	int match_cnt = 0;
	int idx = 0;

	for (int i = end; i >= 0; i--)
	{
		if (line[i] == 1)
			start = 1;

		if (start)
		{
			if (line[i] == check)
				cnt++;
			else
			{
				check ^= 1;
				password[num--] = cnt;
				cnt = 1;
			}

			if (num == 0)
			{
				password[num] = cnt;
				break;
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			match_cnt = 0;
			for (int j = 0; j < 4; j++)
			{
				if (pw_num[k].n[j] == password[i * 4 + j])
					match_cnt++;
				else
					break;
			}
			if (match_cnt == 4)
			{
				pw_code[idx++] = k;
				break;
			}
		}
	}
}

void match_verify()
{
	int odd_sum = 0;
	int even_sum = 0;
	int result;
	int match_cnt = 0;
	int idx = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			match_cnt = 0;
			for (int j = 0; j < 4; j++)
			{
				if (pw_num[k].n[j] == password[i * 4 + j])
					match_cnt++;
				else
					break;
			}
			if (match_cnt == 4)
			{
				pw_code[idx++] = k;
				break;
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		if (i % 2 == 0)
			odd_sum += pw_code[i];
		else
			even_sum += pw_code[i];
	}

	result = odd_sum * 3 + even_sum + pw_code[7];
	
	printf("result >> %d\n", result);

	if (result % 10 == 0)
	{
		for (int i = 0; i < 8; i++)
			pw_sum += pw_code[i];
	}
}

int n_cnt = 0;
int n_switch = 1;
int n_flag = 0;
int n_idx = 31;
int verify_sum = 0;

// flag가 0이면 처음 0이 아닌 값을 발견
// 1의 개수부터 세기 시작
// flag가 1이면 이후 카운트로부터 스위칭하면서 계산
int hexTobin(char c, int bin[4])
{
	int a;
	int cnt = 3;
	int fin = 0;

	if ('0' <= c && c <= '9')			a = c - '0';
	else if ('A' <= c && c <= 'F')		a = 10 + c - 'A';

	while (a != 0)
	{
		if (a % 2 == 0) 
			bin[cnt] = 0;
		else
			bin[cnt] = 1;
		cnt--;
		a /= 2;
	}

	// 코드 변환
	for (int i = 3; i >=0 ; i--)
	{
		if (bin[i] == 1)
			n_flag = 1;

		if (n_flag && n_idx >= 0)
		{
			if (bin[i] == n_switch)
			{
				n_cnt++;
			}
			else
			{
				if (ratio > n_cnt)
					ratio = n_cnt;
				password[n_idx--] = n_cnt;
				n_switch ^= 1;
				n_cnt = 1;
				
				if (n_idx == 27)
				{
					verify_sum = password[31] + password[30] + password[29] + password[28];
				}
			}

			if (n_idx == 0)
			{
				password[0] = verify_sum - password[1] - password[2] - password[3];
				fin = 1;
			}
		}
	}

	return fin;
}


unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

int find(const char *key, char *data)
{
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;

	while (tb[h].key[0] != 0 && cnt--)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			strcpy(data, tb[h].data);
			return 1;
		}
		h = (h + 1) % MAX_TABLE;
	}
	return 0;
}

int add(const char *key, char *data)
{
	unsigned long h = hash(key);

	while (tb[h].key[0] != 0)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			return 0;
		}

		h = (h + 1) % MAX_TABLE;
	}
	strcpy(tb[h].key, key);
	strcpy(tb[h].data, data);
	return 1;
}


int hash_func(int row, int s_idx, int e_idx)
{
	char s[500];
	char return_s[500];
	int cnt = 0;
	int flag = 0;

	for (int i = s_idx; i <= e_idx; i++)
		s[cnt++] = bar_code[row][i];
	s[cnt] = '\0';
	
	flag = find(s, return_s);
	
	if (flag == 0)
		add(s, s);

	return flag;
}

void solve()
{
	int fin = 0;
	int flag = 0;
	int end_idx = 0;
	int start_idx = 0;
	int exist = 0;

	for (int i = 0; i < N; i+=5)
	{
		for (int j = M-1; j >= 0; j--)
		{		
			int bin[4] = { 0,0,0,0 };

			if (bar_code[i][j] != '0')
			{
				if(flag == 0)
					end_idx = j;
				flag = 1;				
			}
			// 이후 bin 처리
			if (flag)
			{
				fin = hexTobin(bar_code[i][j], bin);
			}

			if (fin)
			{
				start_idx = j;

				exist = hash_func(i, start_idx, end_idx);

				for (int k = 0; k < 32; k++)
					password[k] /= ratio;
				
				if (exist == 0)
				{
					match_verify();
				}

				fin = 0;
				n_cnt = 0;
				n_switch = 1;
				n_flag = 0;
				n_idx = 31;
				verify_sum = 0;
				ratio = 999;
				flag = 0;
			}
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
		solve();		

		printf("#%d %d\n",t, pw_sum);
	}
}
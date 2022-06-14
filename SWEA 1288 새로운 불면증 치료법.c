#include <stdio.h>

int T;
long N;
char num[10];

void init()
{
	for (int i = 0; i < 10; i++)
		num[i] = 0;
}

void check_n(long n)
{
	long temp = n;
	
	while (1)
	{
		num[temp % 10] = 1;
		if (temp >= 10)
			temp /= 10;
		else
			break;
	}
}

void input()
{
	scanf("%d", &N);
}

long solve()
{
	long n = 1;
	int flag = 1;

	// n*N을 찾을때까지 무한루프
	while (1)
	{
		// 10으로 나눈 나머지를 인덱스로 사용해서 num배열에 세트시켜줌
		check_n(n*N);
		flag = 1;
		
		// num 배열에 모두 1로 세트되면 n*N을 리턴값 출력하며 함수 탈출
		for (int i = 0; i < 10; i++)
		{
			if (num[i] == 0)
				flag = 0;
		}

		if (flag == 1)
			break;

		n++;
	}

	return n*N;
}

int main(void)
{
	long result;

	// 테스트 케이스 횟수 입력
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		// 초기화
		init();
		// 입력
		input();
		// 동작결과
		result = solve();
		printf("#%d %d\n", t, result);
	}
}
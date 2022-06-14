#include <stdio.h>
#include <string.h>

int T, N;
char si[100001];
char result[4];

void decoder(char str[4])
{
	int n[4];

	for (int i = 0; i < 4; i++)
	{
		// 비트연산
		if ('A' <= str[i] && str[i] <= 'Z')
			n[i] = str[i] - 'A';
		else if ('a' <= str[i] && str[i] <= 'z')
			n[i] = str[i] - 'a' + 26;
		else if ('0' <= str[i] && str[i] <= '9')
			n[i] = str[i] - '0' + 52;
		else if ('+' == str[i])
			n[i] = str[i] - '+' + 62;
		else if ('/' == str[i])
			n[i] = str[i] - '/' + 63;
	}

	result[0] = n[0] << 2;
	result[0] |= (n[1] >> 4);

	result[1] = (n[1] & 15) << 4;
	result[1] |= (n[2] >> 2);
	result[2] = (n[2] & 3) << 6;
	result[2] |= n[3];
	result[3] = '\0';
}

void input()
{
	long len;

	scanf(" %s", si);

	len = strlen(si);
	// 입력하자마자 바로 디코딩해서 출력
	for (int i = 0; i < len/4; i++)
	{
		decoder(&si[i*4]);
		printf("%s", result);
	}
	printf("\n");
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		printf("#%d ", t);
		input();
	}
}
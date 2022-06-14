#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500

int T, K;

typedef struct {
	char s[500];
}HEAP;
HEAP heap[MAX_SIZE];
HEAP str;
int heapSize = 0;

// �켱���� ť �ʱ�ȭ
void heapInit(void)
{
	memset(heap, 0, sizeof(HEAP) * MAX_SIZE);
	heapSize = 0;
}

// �� ���ڿ� ��, ó������ ������� ���ؾ��Ѵ�.
int cmp_priority_str(char s1[500], char s2[500])
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (s1[i] > s2[i])
		{
			return 1;
		}
		else if (s1[i] < s2[i])
		{
			return 2;
		}
	}
	return 0;
}

// �켱���� ť�� ������� ���ڿ� ����
int heapPush(char s[500])
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	memcpy(heap[heapSize].s, s, sizeof(char) * 500);

	int current = heapSize;
	while (current > 0 && cmp_priority_str(heap[current].s, heap[(current-1)].s) == 2)
	{
		char temp[500];
		memcpy(temp, heap[(current-1)].s, sizeof(char) * 500);
		memcpy(heap[(current-1)].s, heap[current].s, sizeof(char) * 500);
		memcpy(heap[current].s, temp, sizeof(char) * 500);
		current = (current-1);
	}

	heapSize = heapSize + 1;

	return 1;
}

void input()
{
	scanf("%d", &K);
	scanf("%s", str.s);
}

void solve()
{
	int len = strlen(str.s);

	for(int i=0;i<len;i++)
		heapPush(&str.s[i]);
}

int main(void)
{
	scanf("%d", &T);

	for (int t = 1; t < T + 1; t++)
	{
		heapInit();
		input();
		solve();

		printf("#%d %s\n", t, heap[K-1].s);
	}
}
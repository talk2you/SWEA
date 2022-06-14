#include <stdio.h>

int T, N;
int rc_acc;
int rc_dist;

typedef struct {
	int cmd;
	int acc;
}CMD;
CMD rc_cmd[30];

void init()
{
	for (int i = 0; i < 30; i++)
	{
		rc_cmd[i].cmd = 0;
		rc_cmd[i].acc = 0;
	}
	rc_acc = 0;
	rc_dist = 0;
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		// cmd가 0이면 acc 값 안받기
		scanf(" %d", &rc_cmd[i].cmd);
		if (rc_cmd[i].cmd != 0)
			scanf(" %d", &rc_cmd[i].acc);
	}

}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		switch (rc_cmd[i].cmd)
		{
		// 가속은 무제한으로 가속
		case 1:
			rc_acc += rc_cmd[i].acc;
			break;
		// 감속은 0이하로 내려가지 않음
		case 2:
			rc_acc -= rc_cmd[i].acc;
			if (rc_acc < 0)
				rc_acc = 0;
			break;
		}
		// 누적 가속값에 따라 거리 증가
		rc_dist += rc_acc;
	}
}

int main(void)
{
	scanf("%d", &T);
	
	for (int t = 1; t < T + 1; t++)
	{
		// 변수 초기화
		init();
		// 입력
		input();
		// 문제 계산
		solve();
		// 출력
		printf("#%d %d\n",t, rc_dist);
	}
}
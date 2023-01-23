#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int stop(int n, int count); // 사용자가 종료를 원하는지 여부를 확인하는 함수
int inputCheck(int input); // 입력값이 유효한지 확인하는 함수
int countBall(int input, int result); // 볼의 개수를 세는 함수
int countStrike(int input, int result); // 스트라이크의 개수를 세는 함수
float calc_result(int arr[], int count); // 사용자의 평균 게임 결과를 구하는 함수


int main()
{
	srand(time(NULL)); // 난수 생성을 위함
	int n=11, count=1, timeArr[11] = { 0, }, tryArr[11] = { 0, }, a, b, c, result, input = 0;
	time_t start, end;

	printf("================== 숫자 야구 게임 ==================\n");

	while (1) // 게임 횟수 입력
	{
		printf("게임을 몇 번 하시겠습니까? (가능 횟수 : 1회~ 10회) : ");
		scanf("%d", &n);
		if (n >= 1 && n <= 10) // 사용자가 유효한 값을 입력함
		{
			printf("\n\n================ 게임을 시작합니다! ================\n");
			break;
		}
		else printf("입력은 1~10 사이의 수만 가능합니다.\n");
	}

	for (int count = 1; count <= n; count++)
	{
		a = rand() % 9 + 1;

		while (1) // a와 b는 서로 다른 수
		{
			b = rand() % 9 + 1;
			if (a != b) break;
		}

		while (1) // a,b,c는 서로 다른 값. 
		{
			c = rand() % 9 + 1;
			if (a != c && b != c) break;
		}
		
		result = a * 100 + b * 10 + c;
		printf("컴퓨터가 정한 3자리 값을 추측해보세요. (1~9 사이의 값이 중복없이 조합되어 있습니다.)\n");
		
		time(&start); // 시작 시간 측정
		while (input != result)
		{
			printf("추측한 값을 입력하세요 : ");
			scanf("%d", &input);
			tryArr[count - 1]++;
			if (inputCheck(input) == 0) printf("입력할 수 있는 값은 세 자리 수이고, 각각 자릿수의 값들이 모두 달라야 합니다.\n");
			else
			{
				if (input == result) // 사용자가 정답을 입력한 경우
				{
					printf("---> 3스트라이크!! 정답을 입력하셨습니다. 축하합니다.\n\n");
				}
				else
				{
					int ball, strike;
					ball = countBall(input, result);
					strike = countStrike(input, result);
					if (ball == 0 && strike == 0) printf("---> 아웃\n\n");
					else printf("---> %d볼 %d스트라이크\n\n", ball, strike);
				}
			}
		}
		time(&end); // 종료 시간 측정
		timeArr[count-1] = end - start; // 한 번의 게임을 진행하는 데 소요된 시간

		printf("======== %d회차 결과 =========\n", count);
		printf("입력 횟수 : %d번	", tryArr[count-1]);
		printf("소요 시간 : %d초\n\n", timeArr[count-1]);

		if (count == n || stop(n, count) == 1) // 종료조건
		{
			printf("\n\n\n\n========= 게임을 종료합니다 =========\n");
			printf("평균 답 입력 횟수 : %.2f번\n", calc_result(tryArr, count));
			printf("평균 소모 시간 : %.2f초\n", calc_result(timeArr, count));
			printf("\n\n===프로그램을 종료합니다.===");
			break;
		}
	}
	return 0;
}

int stop(int n, int count) // 사용자가 종료를 원하는지 여부를 확인하는 함수
{
	int result;
	printf("현재 %d번 중 %d번 게임을 수행하였습니다.\n", n, count);
	printf("게임을 그만두시겠습니까? (예 : 1 / 아니오 : 0) : ");
	while (1)
	{
		scanf("%d", &result);
		if (result == 0 || result == 1) return result;
		else printf("그만두시려면 1을, 계속 하시려면 0을 입력하세요 : ");
	}
}

int inputCheck(int input) // 사용자가 유효한 값을 입력했는지 확인하는 함수
{
	if (input < 100 || input >=1000) return 0;
	else 
	{
		int a = input / 100;
		int b = (input % 100) / 100;
		int c = input % 10;
		if (a == b || b == c || a == c) return 0;
	}
	return 1;
}

int countBall(int input, int result) // 볼의 개수를 세는 함수
{
	int resultBall = 0;
	int checkarr[3] = { input / 100 , (input % 100) / 10, input % 10 };
	int resultArr[3] = { result / 100 , (result % 100) / 10, result % 10 };
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (checkarr[i] == resultArr[j] && i != j) resultBall++;
	return resultBall;
}

int countStrike(int input, int result) // 스트라이크의 개수를 세는 함수
{
	int resultStrike = 0;
	int checkarr[3] = { (input / 100) , ((input % 100) / 10), (input % 10) };
	int resultArr[3] = { (result / 100) , ((result % 100) / 10), (result % 10) };
	for (int i = 0; i < 3; i++) if (checkarr[i] == resultArr[i]) resultStrike++;
	return resultStrike;
}

float calc_result(int arr[], int count) // 평균 결과를 출력하는 함수
{
	int result = 0;
	for (int i = 0; i < count; i++) result += arr[i];
	return result / count;
}
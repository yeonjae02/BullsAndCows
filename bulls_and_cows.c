#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int stop(int n, int count); // ����ڰ� ���Ḧ ���ϴ��� ���θ� Ȯ���ϴ� �Լ�
int inputCheck(int input); // �Է°��� ��ȿ���� Ȯ���ϴ� �Լ�
int countBall(int input, int result); // ���� ������ ���� �Լ�
int countStrike(int input, int result); // ��Ʈ����ũ�� ������ ���� �Լ�
float calc_result(int arr[], int count); // ������� ��� ���� ����� ���ϴ� �Լ�


int main()
{
	srand(time(NULL)); // ���� ������ ����
	int n=11, count=1, timeArr[11] = { 0, }, tryArr[11] = { 0, }, a, b, c, result, input = 0;
	time_t start, end;

	printf("================== ���� �߱� ���� ==================\n");

	while (1) // ���� Ƚ�� �Է�
	{
		printf("������ �� �� �Ͻðڽ��ϱ�? (���� Ƚ�� : 1ȸ~ 10ȸ) : ");
		scanf("%d", &n);
		if (n >= 1 && n <= 10) // ����ڰ� ��ȿ�� ���� �Է���
		{
			printf("\n\n================ ������ �����մϴ�! ================\n");
			break;
		}
		else printf("�Է��� 1~10 ������ ���� �����մϴ�.\n");
	}

	for (int count = 1; count <= n; count++)
	{
		a = rand() % 9 + 1;

		while (1) // a�� b�� ���� �ٸ� ��
		{
			b = rand() % 9 + 1;
			if (a != b) break;
		}

		while (1) // a,b,c�� ���� �ٸ� ��. 
		{
			c = rand() % 9 + 1;
			if (a != c && b != c) break;
		}
		
		result = a * 100 + b * 10 + c;
		printf("��ǻ�Ͱ� ���� 3�ڸ� ���� �����غ�����. (1~9 ������ ���� �ߺ����� ���յǾ� �ֽ��ϴ�.)\n");
		
		time(&start); // ���� �ð� ����
		while (input != result)
		{
			printf("������ ���� �Է��ϼ��� : ");
			scanf("%d", &input);
			tryArr[count - 1]++;
			if (inputCheck(input) == 0) printf("�Է��� �� �ִ� ���� �� �ڸ� ���̰�, ���� �ڸ����� ������ ��� �޶�� �մϴ�.\n");
			else
			{
				if (input == result) // ����ڰ� ������ �Է��� ���
				{
					printf("---> 3��Ʈ����ũ!! ������ �Է��ϼ̽��ϴ�. �����մϴ�.\n\n");
				}
				else
				{
					int ball, strike;
					ball = countBall(input, result);
					strike = countStrike(input, result);
					if (ball == 0 && strike == 0) printf("---> �ƿ�\n\n");
					else printf("---> %d�� %d��Ʈ����ũ\n\n", ball, strike);
				}
			}
		}
		time(&end); // ���� �ð� ����
		timeArr[count-1] = end - start; // �� ���� ������ �����ϴ� �� �ҿ�� �ð�

		printf("======== %dȸ�� ��� =========\n", count);
		printf("�Է� Ƚ�� : %d��	", tryArr[count-1]);
		printf("�ҿ� �ð� : %d��\n\n", timeArr[count-1]);

		if (count == n || stop(n, count) == 1) // ��������
		{
			printf("\n\n\n\n========= ������ �����մϴ� =========\n");
			printf("��� �� �Է� Ƚ�� : %.2f��\n", calc_result(tryArr, count));
			printf("��� �Ҹ� �ð� : %.2f��\n", calc_result(timeArr, count));
			printf("\n\n===���α׷��� �����մϴ�.===");
			break;
		}
	}
	return 0;
}

int stop(int n, int count) // ����ڰ� ���Ḧ ���ϴ��� ���θ� Ȯ���ϴ� �Լ�
{
	int result;
	printf("���� %d�� �� %d�� ������ �����Ͽ����ϴ�.\n", n, count);
	printf("������ �׸��νðڽ��ϱ�? (�� : 1 / �ƴϿ� : 0) : ");
	while (1)
	{
		scanf("%d", &result);
		if (result == 0 || result == 1) return result;
		else printf("�׸��ν÷��� 1��, ��� �Ͻ÷��� 0�� �Է��ϼ��� : ");
	}
}

int inputCheck(int input) // ����ڰ� ��ȿ�� ���� �Է��ߴ��� Ȯ���ϴ� �Լ�
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

int countBall(int input, int result) // ���� ������ ���� �Լ�
{
	int resultBall = 0;
	int checkarr[3] = { input / 100 , (input % 100) / 10, input % 10 };
	int resultArr[3] = { result / 100 , (result % 100) / 10, result % 10 };
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (checkarr[i] == resultArr[j] && i != j) resultBall++;
	return resultBall;
}

int countStrike(int input, int result) // ��Ʈ����ũ�� ������ ���� �Լ�
{
	int resultStrike = 0;
	int checkarr[3] = { (input / 100) , ((input % 100) / 10), (input % 10) };
	int resultArr[3] = { (result / 100) , ((result % 100) / 10), (result % 10) };
	for (int i = 0; i < 3; i++) if (checkarr[i] == resultArr[i]) resultStrike++;
	return resultStrike;
}

float calc_result(int arr[], int count) // ��� ����� ����ϴ� �Լ�
{
	int result = 0;
	for (int i = 0; i < count; i++) result += arr[i];
	return result / count;
}
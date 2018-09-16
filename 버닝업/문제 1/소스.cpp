#define CHANGE_LINE printf("\n");
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct Array
{
	int num[4][4];
};

void multi(Array*, Array*);
void plus(Array*, Array*);
void minus(Array*, Array*);
void det(Array);
void convert(Array*);
void initial(Array*);

int main()
{
	char command;
	Array A, B;

	initial(&A);

	while (1) {
		printf("명령어를 입력하시오");
		CHANGE_LINE
			scanf(" %c", &command);
		switch (command) {
		case 'M':
		case 'm':
			initial(&B);
			multi(&A, &B);
			break;
		case 'A':
		case 'a':
			initial(&B);
			plus(&A, &B);
			break;
		case 'D':
		case 'd':
			initial(&B);
			minus(&A, &B);
			break;
		case 'R':
		case 'r':
			det(A);
			break;
		case 'H':
		case 'h':
			convert(&A);
			break;
		case 'E':
		case 'e':
			return 0;
			break;
		default:
			printf("잘못된 명령어");
			CHANGE_LINE
				break;
		}
		fflush(stdin);
	}
	/*
	for (int i = 0; i < 9; ++i) {
		printf("%d", A.num[i / 3][i % 3]);
		if(i%3==2)
			CHANGE_LINE
	}
	*/
}

void multi(Array* A, Array* B) {
	Array tmp_A;
	for (int i = 0; i < 9; ++i) {
		tmp_A.num[i / 3][i % 3] = A->num[i / 3][i % 3];
	}
	/*
	for (int i = 0; i < 3; ++i) {
		A->num[i % 3][0] = tmp_A.num[0][0] * B->num[0][i % 3] + tmp_A.num[0][1] * B->num[1][i % 3] + tmp_A.num[0][2] * B->num[2][i % 3];
		A->num[i % 3][1] = tmp_A.num[1][0] * B->num[0][i % 3] + tmp_A.num[1][1] * B->num[1][i % 3] + tmp_A.num[1][2] * B->num[2][i % 3];
		A->num[i % 3][2] = tmp_A.num[2][0] * B->num[0][i % 3] + tmp_A.num[2][1] * B->num[1][i % 3] + tmp_A.num[2][2] * B->num[2][i % 3];
	}
	*/
	A->num[0][0] = tmp_A.num[0][0] * B->num[0][0] + tmp_A.num[0][1] * B->num[1][0] + tmp_A.num[0][2] * B->num[2][0];
	A->num[0][1] = tmp_A.num[0][0] * B->num[0][1] + tmp_A.num[0][1] * B->num[1][1] + tmp_A.num[0][2] * B->num[2][1];
	A->num[0][2] = tmp_A.num[0][0] * B->num[0][2] + tmp_A.num[0][1] * B->num[1][2] + tmp_A.num[0][2] * B->num[2][2];
	A->num[1][0] = tmp_A.num[1][0] * B->num[0][0] + tmp_A.num[1][1] * B->num[1][0] + tmp_A.num[1][2] * B->num[2][0];
	A->num[1][1] = tmp_A.num[1][0] * B->num[0][1] + tmp_A.num[1][1] * B->num[1][1] + tmp_A.num[1][2] * B->num[2][1];
	A->num[1][2] = tmp_A.num[1][0] * B->num[0][2] + tmp_A.num[1][1] * B->num[1][2] + tmp_A.num[1][2] * B->num[2][2];
	A->num[2][0] = tmp_A.num[2][0] * B->num[0][0] + tmp_A.num[2][1] * B->num[1][0] + tmp_A.num[2][2] * B->num[2][0];
	A->num[2][1] = tmp_A.num[2][0] * B->num[0][1] + tmp_A.num[2][1] * B->num[1][1] + tmp_A.num[2][2] * B->num[2][1];
	A->num[2][2] = tmp_A.num[2][0] * B->num[0][2] + tmp_A.num[2][1] * B->num[1][2] + tmp_A.num[2][2] * B->num[2][2];
	
	// 첫번째 줄
	for (int i = 0; i < 3; ++i)
		printf("%d", tmp_A.num[0][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[0][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[0][i % 3]);
	CHANGE_LINE

		// 두번째 줄
		for (int i = 0; i < 3; ++i)
			printf("%d", tmp_A.num[1][i % 3]);
	printf(" * ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[1][i % 3]);
	printf(" = ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[1][i % 3]);
	CHANGE_LINE

		// 세번째 줄
		for (int i = 0; i < 3; ++i)
			printf("%d", tmp_A.num[2][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[2][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[2][i % 3]);
	CHANGE_LINE
}

void plus(Array* A,Array* B) {
	Array tmp_A;
	for (int i = 0; i < 9; ++i) {
		tmp_A.num[i / 3][i % 3] = A->num[i / 3][i % 3];
	}

	for (int i = 0; i < 9; ++i) {
		A->num[i / 3][i % 3] = A->num[i / 3][i % 3] + B->num[i / 3][i % 3];
	}

	// 첫번째 줄
	for (int i = 0; i < 3; ++i)
		printf("%d", tmp_A.num[0][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[0][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[0][i % 3]);
	CHANGE_LINE

	// 두번째 줄
	for (int i = 0; i < 3; ++i)
		printf("%d", tmp_A.num[1][i % 3]);
	printf(" + ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[1][i % 3]);
	printf(" = ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[1][i % 3]);
	CHANGE_LINE

	// 세번째 줄
	for (int i = 0; i < 3; ++i)
		printf("%d", tmp_A.num[2][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[2][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[2][i % 3]);
	CHANGE_LINE
}

void minus(Array* A, Array* B) {
	Array tmp_A;
	for (int i = 0; i < 9; ++i) {
		tmp_A.num[i / 3][i % 3] = A->num[i / 3][i % 3];
	}

	for (int i = 0; i < 9; ++i) {
		A->num[i / 3][i % 3] = A->num[i / 3][i % 3] - B->num[i / 3][i % 3];
	}

	// 첫번째 줄
	for (int i = 0; i < 3; ++i)
		printf("%d", tmp_A.num[0][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[0][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[0][i % 3]);
	CHANGE_LINE

		// 두번째 줄
		for (int i = 0; i < 3; ++i)
			printf("%d", tmp_A.num[1][i % 3]);
	printf(" - ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[1][i % 3]);
	printf(" = ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[1][i % 3]);
	CHANGE_LINE

		// 세번째 줄
		for (int i = 0; i < 3; ++i)
			printf("%d", tmp_A.num[2][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", B->num[2][i % 3]);
	printf("   ");
	for (int i = 0; i < 3; ++i)
		printf("%d", A->num[2][i % 3]);
	CHANGE_LINE
}

void det(Array A) {
	int a,b,c;
	a = ((A.num[1][1] * A.num[2][2]) - (A.num[1][2] * A.num[2][1]))*A.num[0][0];
	b = ((A.num[1][0] * A.num[2][2]) - (A.num[1][2] * A.num[2][0]))*(-1 * A.num[0][1]);
	c = ((A.num[1][0] * A.num[2][1]) - (A.num[1][1] * A.num[2][0]))*A.num[0][2];

	// 첫번째 줄
	for (int i = 0; i < 3; ++i)
		printf("%d", A.num[0][i % 3]);
	CHANGE_LINE

	// 두번째 줄
		for (int i = 0; i < 3; ++i)
			printf("%d", A.num[1][i % 3]);
	printf(" = ");

		printf("%d", a+b+c);
	CHANGE_LINE

	// 세번째 줄
		for (int i = 0; i < 3; ++i)
			printf("%d", A.num[2][i % 3]);
	CHANGE_LINE
}

void convert(Array* A) {
	for (int i = 0; i < 3; ++i) {
		A->num[i][3] = 0;
		A->num[3][i] = 0;
	}
	A->num[3][3] = 1;

	for (int i = 0; i < 16; ++i) {
		printf("%d", A->num[i / 4][i % 4]);
		if (i % 4 == 3)
			CHANGE_LINE
	}
}

void initial(Array* A) {
	for (int i = 0; i < 16; ++i)
		A->num[i/4][i%4] = rand() % 2;
}

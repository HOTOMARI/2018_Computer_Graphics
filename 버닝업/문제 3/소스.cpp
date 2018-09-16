#define CHANGE_LINE printf("\n");

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

int miro[25][25];
int critical = 0;

void initial();
void make_miro();

int main()
{
	srand(time(NULL));
	while (1) {
		system("cls");
		initial();
		make_miro();

			for (int i = 0; i < 25; ++i) {
				for (int j = 0; j < 25; ++j) {
					if (miro[i][j])
						printf("бс");
					else printf("бр");
				}
				CHANGE_LINE
			}
		
	
		if ('q' == getch())
			return 0;
	}
}
void initial() {
	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 25; ++j)
			miro[i][j] = 0;
	miro[0][0] = 1;
}
void make_miro() {
	int arrow = 1;	
	int before = -1;
	int stack = 0;
	int X = 0, Y = 0;
	int err = 0;

	while (1) {
			arrow = rand() % 2;
		switch (arrow) {
		case 0:
			if (Y >= 24) {
				err++;
				break;
			}

			if (stack >= 2&&before==1) {
				err++;
				break;
			}
			if (before == 3)
				stack = 0;
			if (rand() % 25 == 1&&Y>5&&stack==0&&critical<=1500) {
				if (miro[Y-1][X] == 1 || miro[Y-2][X] == 1 || miro[Y-3][X] == 1|| miro[Y - 1][X-1] == 1 || miro[Y - 2][X-1] == 1 || miro[Y - 3][X-1] == 1
					|| miro[Y - 1][X + 1] == 1 || miro[Y - 2][X + 1] == 1 || miro[Y - 3][X + 1] == 1) {
					err++;
					break;
				}
				for (int i = 0; i < 3; ++i) {
					Y--;
					miro[Y][X] = 1;
				}
				stack = 1;
			}
			else {
				if (miro[Y + 1][X] == 1 || miro[Y + 2][X] == 1  || miro[Y + 1][X - 1] == 1 || miro[Y + 2][X - 1] == 1 
					|| miro[Y + 1][X + 1] == 1 || miro[Y + 2][X + 1] == 1 ) {
					err++;
					break;
				}
					for (int i = 0; i < 2; ++i) {
					Y++;
					miro[Y][X] = 1;
					if (X == 24 && Y == 24) {
						break;
					}
				}
			}
			before = 1;
			stack++;
			break;
		case 1:
			if (X >= 24) {
				break;
				err++;
			}
			
			if (stack >= 2&&before==3) {
				err++;
				break;
			}
			if (before == 1)
				stack = 0;
			if (rand() % 25 == 1 && X>5 && stack == 0&&critical<=1500) {
				if (miro[Y][X-1] == 1|| miro[Y][X-2] == 1|| miro[Y][X-3] == 1|| miro[Y-1][X - 1] == 1 || miro[Y-1][X - 2] == 1 || miro[Y-1][X - 3] == 1
					|| miro[Y + 1][X - 1] == 1 || miro[Y + 1][X - 2] == 1 || miro[Y + 1][X - 3] == 1) {
					err++;
					break;
				}
				for (int i = 0; i < 3; ++i) {
					X--;
					miro[Y][X] = 1;
				}
				stack = 1;
			}
			else {
				if (miro[Y][X + 1] == 1 || miro[Y][X + 2] == 1  || miro[Y - 1][X + 1] == 1 || miro[Y - 1][X + 2] == 1 
					|| miro[Y + 1][X + 1] == 1 || miro[Y + 1][X + 2] == 1 ) {
					err++;
					break;
				}
					for (int i = 0; i < 2; ++i) {
					X++;
					miro[Y][X] = 1;
					if (X == 24 && Y == 24) {
						break;
					}
				}
			}
			before = 3;
			stack++;
			break;
		}
		if (err >= 100) {

			initial();
			before = -1;
			stack = 0;
			X = 0, Y = 0;
			err = 0;
			printf("making...");
			critical++;
			system("cls");
		
		}
		if (X == 24 && Y == 24) {
			break;
		}
	}
}
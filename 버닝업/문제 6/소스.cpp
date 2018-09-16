#include<stdio.h>
#include<Windows.h>

#define CHANGE_LINE printf("\n");

struct Shape {
	int x1, x2, y1, y2;
	int type;
};

Shape shape;

int board[30][30];
char command;

void initialize();
void draw_shape();
void print_board();

int main() {
	bool first = true;

	initialize();
	while (1) {
		system("cls");
		while (first) {
			printf("도형 선택 (1-사각형): ");
			scanf(" %d", &shape.type);
			printf("도형 좌표 입력: ");
			scanf("%d %d %d %d", &shape.x1, &shape.y1, &shape.x2, &shape.y2);
			if (shape.type != 1) {
				printf("잘못된 도형\n");
			}
			else if (shape.x1 < 1 || shape.x2 < 1 || shape.y1 < 1 || shape.y2 < 1
				|| shape.x1 > 30 || shape.x2 > 30 || shape.y1 > 30 || shape.y2 > 30
				|| shape.x1 >= shape.x2 || shape.y1 >= shape.y2) {
				printf("잘못된 크기\n");
			}
			else {
				draw_shape();
				first = false;
			}
			system("cls");
		}
		print_board();
		printf("명령어 입력: ");
		scanf(" %c",&command);
		switch (command)
		{
		case 'x':
			if (shape.x2 == 30) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.x1++;
				shape.x2++;
				initialize();
				draw_shape();
			}
			break;
		case 'X':
			if (shape.x1 == 1) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.x1--;
				shape.x2--;
				initialize();
				draw_shape();
			}
			break;
		case 'y':
			if (shape.y2 == 30) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.y1++;
				shape.y2++;
				initialize();
				draw_shape();
			}
			break;
		case 'Y':
			if (shape.y1 == 1) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.y1--;
				shape.y2--;
				initialize();
				draw_shape();
			}
			break;
		case 's':
			if (shape.x2 == 30) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.x2++;
				initialize();
				draw_shape();
			}
			if (shape.y2 == 30) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.y2++;
				initialize();
				draw_shape();
			}
			break;
		case 'S':
			if (shape.x2 - 1 == shape.x1) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.x2--;
				initialize();
				draw_shape();
			}
			if (shape.y2 - 1 == shape.y1) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.y2--;
				initialize();
				draw_shape();
			}
			break;
		case 'i':
			if (shape.x2 == 30) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.x2++;
				initialize();
				draw_shape();
			}
			break;
		case 'j':
			if (shape.x2 - 1 == shape.x1) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.x2--;
				initialize();
				draw_shape();
			}
			break;
		case 'k':
			if (shape.y2 == 30) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.y2++;
				initialize();
				draw_shape();
			}
			break;
		case 'l':
			if (shape.y2-1 == shape.y1) {
				printf("ERROR!\n");
				Sleep(1500);
			}
			else {
				shape.y2--;
				initialize();
				draw_shape();
			}
			break;
		case 'r':
			first = true;
			initialize();
			break;
		default:
			break;
		}
	}
}

void initialize() {
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			board[j][i] = 0;
		}
	}
}

void draw_shape() {
	for (int i = -1; i < shape.y2 - shape.y1; ++i) {
		for (int j = -1; j < shape.x2 - shape.x1; ++j) {
			board[i + shape.y1][j + shape.x1] = 1;
		}
	}
}

void print_board() {
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			if (board[i][j] == 0)
				printf("□");
			else printf("■");
		}
		CHANGE_LINE
	}
}
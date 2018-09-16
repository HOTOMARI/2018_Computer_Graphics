#define CHANGE_LINE printf("\n");

#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<Windows.h>

struct List {
	int x, y, z;
	float length;
	bool chk = false;
};

List list[10];
char command;
int x, y, z;

void print_list();

int main() {
	while (1) {
		fflush(stdin);
		print_list();
		CHANGE_LINE
		printf("명령 입력: ");
		scanf(" %c", &command);
		switch (command) {
		case '+':
			scanf("%d %d %d", &x, &y, &z);
			for (int i = 9; i >= 0; --i) {
				if (list[i].chk == true) {
					list[i+1].x = x;
					list[i+1].y = y;
					list[i+1].z = z;
					list[i+1].length = sqrt((x * x) + (y * y) + (z * z));
					list[i+1].chk = true;
					break;
				}
				if (list[0].chk == false&&i==0) {
					list[0 ].x = x;
					list[0 ].y = y;
					list[0 ].z = z;
					list[0 ].length = sqrt((x * x) + (y * y) + (z * z));
					list[0 ].chk = true;
					break;
				}
			}
			break;
		case '-':
			for (int i = 9; i >= 0; --i) {
				if (list[i].chk) {
					list[i].chk = false;
					break;
				}
			}
			break;
		case 'e':
			scanf("%d %d %d", &x, &y, &z);
			for (int i = 9; i > 0; --i) {
				list[i] = list[i - 1];
			}
			//for (int i = 0; i < 10; ++i) {
			//	if (list[i].chk) {
			//		if (i == 0) {
						
							list[0 ].x = x;
							list[0 ].y = y;
							list[0 ].z = z;
							list[0 ].length = sqrt((x * x) + (y * y) + (z * z));
							list[0 ].chk = true;
							break;
						
				//	}
				//	list[i-1].x = x;
				//	list[i-1].y = y;
				//	list[i-1].z = z;
				//	list[i-1].length = sqrt((x * x) + (y * y) + (z * z));
				//	list[i - 1].chk=true;
				//	break;
				//}
			//}
			break;
		case 'd':
			for (int i = 0; i < 10; ++i) {
				if (list[i].chk) {
					list[i].chk = false;
					break;
				}
			}
			break;
		case 'l':
			int count;
			count = -1;
			for (int i = 0; i < 10; ++i)
				if (list[i].chk)
					count++;
			CHANGE_LINE
			printf(" length of list: %d", count);
			Sleep(1500);
			break;
		case 'c':
			for (int i = 0; i < 10; ++i)
				list[i].chk = false;
			break;
		case 'm':
			float max;
			max = 0;
			for (int i = 0; i < 10; ++i) {
				if (list[i].chk&&list[i].length > max)
					max = list[i].length;
			}
			CHANGE_LINE
			for (int i = 0; i < 10; ++i)
				if (list[i].length == max)
					printf("%d %d %d", list[i].x, list[i].y, list[i].z);
			Sleep(1500);
			break;
		case 'n':
			float min;
			min = 999999;
			for (int i = 0; i < 10; ++i) {
				if (list[i].chk&&list[i].length < min)
					min = list[i].length;
			}
			CHANGE_LINE
				for (int i = 0; i < 10; ++i)
					if (list[i].length == min&&list[i].chk==true)
						printf("%d %d %d", list[i].x, list[i].y, list[i].z);
			Sleep(1500);
			break;
		case 'q':
			return 0;
			break;
		default:
			printf("잘못된 명령어\n");
			Sleep(1500);
			break;
		}	
		system("cls");
	}
}

void print_list() {
	for (int i = 9; i >= 0; --i) {
		printf("%d ", i);
		if (list[i].chk)
			printf("%d %d %d %f", list[i].x, list[i].y, list[i].z, list[i].length);
		CHANGE_LINE
	}
}
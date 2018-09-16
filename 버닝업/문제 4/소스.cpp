#include<stdio.h>
#define CHANGE_LINE printf("\n");

struct Vect {
	int x, y, z;
};

int main() {
	Vect vect[2];
	char command;

	printf("input vector1 x y z : ");
	scanf("%d %d %d", &vect[0].x, &vect[0].y, &vect[0].z);
	printf("input vector2 x y z : ");
	scanf("%d %d %d", &vect[1].x, &vect[1].y, &vect[1].z);

	while (1) {
		printf("명령 입력: ");
		scanf(" %c", &command);
		switch (command)
		{
		case '+':
			printf("(%d, %d, %d)+(%d, %d, %d)=(%d, %d, %d)",
				vect[0].x, vect[0].y, vect[0].z, vect[1].x, vect[1].y, vect[1].z,
				vect[0].x + vect[1].x, vect[0].y + vect[1].y, vect[0].z + vect[1].z);
			break;
		case '-':
			printf("(%d, %d, %d)-(%d, %d, %d)=(%d, %d, %d)",
				vect[0].x, vect[0].y, vect[0].z, vect[1].x, vect[1].y, vect[1].z,
				vect[0].x - vect[1].x, vect[0].y - vect[1].y, vect[0].z - vect[1].z);
			break;
		case 'd':
		case 'D':
			printf("(%d, %d, %d)@(%d, %d, %d)=%d",
				vect[0].x, vect[0].y, vect[0].z, vect[1].x, vect[1].y, vect[1].z,
				vect[0].x*vect[1].x + vect[0].y*vect[1].y + vect[0].z*vect[1].z);
			break;
		case 'C':
		case 'c':
			printf("(%d, %d, %d)*(%d, %d, %d)=(%d, %d, %d)",
				vect[0].x, vect[0].y, vect[0].z, vect[1].x, vect[1].y, vect[1].z,
				vect[0].y*vect[1].z - vect[0].z*vect[1].y,
				vect[0].z*vect[1].x - vect[0].x*vect[1].z,
				vect[0].x*vect[1].y - vect[0].y*vect[1].x);
			break;
		case 'l':
		case 'L':
			printf("root(%d, %d, %d)=root(%d),root(%d, %d, %d)=root(%d)",
				vect[0].x, vect[0].y, vect[0].z, vect[0].x*vect[0].x+ vect[0].y*vect[0].y+ vect[0].z*vect[0].z,
				vect[1].x, vect[1].y, vect[1].z, vect[1].x*vect[1].x + vect[1].y*vect[1].y+ vect[1].z*vect[1].z);
			break;
		case 'q':
		case 'Q':
			return 0;
			break;
		default:
			printf("잘못된 명령어\n");
			break;
		}
		CHANGE_LINE
	}
}
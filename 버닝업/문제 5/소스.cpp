#include<stdio.h>
#include<math.h>
#include<Windows.h>

#define CHANGE_LINE printf("\n");

struct Shape {
	float x1, x2, y1, y2;
	int type;	// 1 사각형 2 원
};

Shape shape[2];

bool collide_rec_rec();
bool collide_cir_cir();
bool collide_rec_cir();
bool IsPointInCircle(float , float, float, float, float);

int main() {
	char command;
	bool first = true;
	while (first) {
		printf("Input Shape Combination: ");
		scanf(" %c", &command);
		CHANGE_LINE
		printf("Shape 1: ");
		scanf("%f %f %f %f", &shape[0].x1, &shape[0].y1, &shape[0].x2, &shape[0].y2);
		printf("Shape 2: ");
		scanf("%f %f %f %f", &shape[1].x1, &shape[1].y1, &shape[1].x2, &shape[1].y2);
		switch (command) {
		case '1':
			shape[0].type = 1;
			shape[1].type = 1;
			first = false;
			break;
		case '2':
			shape[0].type = 2;
			shape[1].type = 2;
			first = false;
			break;
		case '3':
			shape[0].type = 1;
			shape[1].type = 2;
			first = false;
			break;
		default:
			printf("ERROR\n");
			break;
		}
		for (int i = 0; i < 2; ++i) {
			if (shape[i].x1 < 0 || shape[i].x2 < 0 || shape[i].y1 < 0 || shape[i].y2 < 0
				|| shape[i].x1 >= shape[i].x2 || shape[i].y1 >= shape[i].y2) {
				printf("Shape %d 잘못된 크기\n", i + 1);
				first = true;
			}
		}
		for (int i = 0; i < 2; ++i) {
			if (shape[i].type==2 && (shape[i].x2 - shape[i].x1  != shape[i].y2 - shape[i].y1)) {
				printf("Shape %d 잘못된 크기\n", i + 1);
				first = true;
			}
		}
	}
	while (1) {
		printf("command: ");
		scanf(" %c", &command);
		switch (command) {
		case 'a':
			if (shape[1].x1 > 60) {
				shape[1].x1 -= 60;
				shape[1].x2 -= 60;
			}
			else {
				printf("ERROR\n");
			}
			break;
		case 'd':
			shape[1].x1 += 60;
			shape[1].x2 += 60;
			break;
		case 's':
			shape[1].y1 += 60;
			shape[1].y2 += 60;
			break;
		case 'w':
			if (shape[1].y1 > 60) {
				shape[1].y1 -= 60;
				shape[1].y2 -= 60;
			}
			else {
				printf("ERROR\n");
			}
			break;
		default:
			printf("ERROR\n");
			break;
		}
		for (int i = 0; i < 2; ++i) {
			printf("Shape %d: (%.0f, %.0f) (%.0f, %.0f)\n", i + 1, shape[i].x1, shape[i].y1, shape[i].x2, shape[i].y2);
		}
		if (shape[0].type == 1 && shape[1].type == 1) {
			if (collide_rec_rec()) {
				printf("Rectangle 1 & Rectangle 2 colide!!\n");
			}
		}
		else if (shape[0].type == 2 && shape[1].type == 2) {
			if (collide_cir_cir()) {
				printf("Circle 1 & Circle 2 colide!!\n");
			}
		}
		else if (shape[0].type == 1 && shape[1].type == 2) {
			if (collide_rec_cir()) {
				printf("Rectangle 1 & Circle 2 colide!!\n");
			}
		}
	}
}

bool collide_rec_rec() {
	if (shape[0].x1<shape[1].x2&&shape[0].y1<shape[1].y2
		&&shape[0].x2>shape[1].x1&&shape[0].y2>shape[1].y1)
		return true;
	else return false;
}

bool collide_cir_cir() {
	float cx[2], cy[2];
	float r[2];
	for (int i = 0; i < 2; ++i) {
		cx[i] = shape[i].x1 + ((shape[i].x2 - shape[i].x1) / 2);
		cx[i] = shape[i].y1 + ((shape[i].y2 - shape[i].y1) / 2);
		r[i] = (shape[i].x2 - shape[i].x1) / 2;
	}
	if ((cx[1]-cx[0])*(cx[1] - cx[0])+ (cy[1] - cy[0])*(cy[1] - cy[0])<=(r[0]+r[1])*(r[0] + r[1]))
		return true;
	return false;
}

bool collide_rec_cir() {
	float cx, cy, cr;
	Shape rcEx;

	cx = shape[1].x1 + ((shape[1].x2 - shape[1].x1) / 2);
	cy = shape[1].y1 + ((shape[1].y2 - shape[1].y1) / 2);
	cr = (shape[1].x2 - shape[1].x1) / 2;

	rcEx.x1 = shape[0].x1 - cr;
	rcEx.y1 = shape[0].y1 - cr;
	rcEx.x2 = shape[0].x2 + cr;
	rcEx.y2 = shape[0].y2 + cr;

	if ((rcEx.x1 <= cx && rcEx.x2 >= cx) && (rcEx.y2 >= cy && rcEx.y1 <= cy)) {
		return true;
	}
	else {
		if (IsPointInCircle(cx, cy, cr, shape[0].x1, shape[0].y1)) {
			return true;
		}
		if (IsPointInCircle(cx, cy, cr, shape[0].x1, shape[0].y2)) {
			return true;
		}
		if (IsPointInCircle(cx, cy, cr, shape[0].x2, shape[0].y1)) {
			return true;
		}
		if (IsPointInCircle(cx, cy, cr, shape[0].x2, shape[0].y2)) {
			return true;
		}
		return false;
	}
}
	
bool IsPointInCircle(float cx, float cy, float cr, float px, float py) {        // 포인트 인 서클
	float Dx = cx - px;
	float Dy = cy - py;

	float length = sqrt(Dx * Dx + Dy * Dy);

	if (length > cr) {
		return false;
	}
	return true;
}
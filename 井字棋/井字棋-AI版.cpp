#include<easyx.h>

#define EMPTY 0
#define PLAYER 1
#define AI -1

int DATA[3][3];  //棋盘数据
ExMessage msg;

void initData();
int setSetting();
void drawData();
void drawPlate();
int nowPlayer();
void getData();
int checkWin(int player);
int checkDraw();
void gameOver(int* flag);
int minMax(int player);
void aiMove();

int main() {
	int runFlag = setSetting();
	initData();
	BeginBatchDraw();
	while (runFlag) {
		cleardevice();
		drawPlate();
		getData();
		drawData();
		FlushBatchDraw();
		gameOver(&runFlag);
	}
	EndBatchDraw();
	return 0;
}


void initData() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			DATA[i][j] = EMPTY;
}

int setSetting() {
	initgraph(600, 600);//200
	setlinestyle(PS_SOLID, 5);
	setbkcolor(CYAN);
	return 1;
}
void drawData() {
	int x, y;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (DATA[i][j] == PLAYER) circle(200 * j + 100, 200 * i + 100, 80);
			else if (DATA[i][j] == AI) {
				setlinecolor(YELLOW);
				line(200 * j + 20, 200 * i + 20, 200 * (j + 1) - 20, 200 * (i + 1) - 20);
				line(200 * j + 20, 200 * (i + 1) - 20, 200 * (j + 1) - 20, 200 * i + 20);
				setlinecolor(WHITE);
			}
		}
}

void drawPlate() {
	setlinecolor(BLACK);
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	setlinecolor(WHITE);
}

int nowPlayer() {
	static int now = -1;
	now = -now;
	if (now == -1) aiMove();
	return now;
}

void getData() {
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			int x, y;
			x = msg.x / 200;
			y = msg.y / 200;
			if (DATA[y][x] == EMPTY) 
				if (nowPlayer() == 1) DATA[y][x] = PLAYER;
		}
	}
}

int checkWin(int player) {
	for (int i = 0; i < 3; i++) {
		if (DATA[i][0] == player && DATA[i][1] == player && DATA[i][2] == player) return 1;
		if (DATA[0][i] == player && DATA[1][i] == player && DATA[2][i] == player) return 1;
	}
	if (DATA[0][0] == player && DATA[1][1] == player && DATA[2][2] == player) return 1;
	if (DATA[2][0] == player && DATA[1][1] == player && DATA[0][2] == player) return 1;
	return 0;
}

int checkDraw() {
	int flag = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (DATA[i][j] == EMPTY) flag = 0;
	return flag;
}

void gameOver(int* flag) {
	const wchar_t* t = NULL;
	if (checkWin(PLAYER)) {
		*flag = 0;
		t = L"玩家获胜!!!";
	}
	if (checkWin(AI)) {
		*flag = 0;
		t = L"AI获胜!!!";
	}
	if (checkDraw()) {
		*flag = 0;
		t = L"本局平局!!!";
	}
	if (!(*flag)) MessageBox(GetHWnd(), t, _T("游戏结束"), MB_OK);
}

int minMax(int player) {
	if (checkWin(PLAYER)) return -10;
	if (checkWin(AI)) return 10;
	if (checkDraw()) return 0;

	int bestScore = (player == AI) ? -100 : 100;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (DATA[i][j] == EMPTY) {
				DATA[i][j] = player;
				int score = minMax(-player);
				DATA[i][j] = EMPTY;
				if (player == AI) bestScore = (bestScore > score) ? bestScore : score;
				else bestScore = (bestScore < score) ? bestScore : score;
			}
		}
	return bestScore;
}

void aiMove() {
	int bestScore = -100;
	int bestMove[2] = { 0, 0 };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (DATA[i][j] == EMPTY) {
				DATA[i][j] = AI;
				int score = minMax(PLAYER);
				DATA[i][j] = EMPTY;
				if (score > bestScore) {
					bestScore = score;
					bestMove[0] = i;
					bestMove[1] = j;
				}

			}
		}
	DATA[bestMove[0]][bestMove[1]] = AI;
	drawData();
	//ai实际移动
}

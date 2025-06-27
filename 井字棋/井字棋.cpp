#include<easyx.h>

char gameData[3][3];  //棋盘数据
ExMessage msg;


//初始化棋盘数据
void initData(char data[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			data[i][j] = '-';
}

void drawData(char data[3][3]) {
	int x, y;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (data[i][j] == 'o') circle(200 * j + 100, 200 * i + 100, 80);
			else if (data[i][j] == 'x') {
				line(200 * j + 20, 200 * i + 20, 200 *(j + 1) - 20, 200 * (i + 1) - 20);
				line(200 * j + 20, 200 * (i + 1) - 20, 200 * (j + 1) - 20, 200 * i + 20);
			}
		}
}

void drawPlate() {
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

bool nowPlayer() {
	static bool now = true;
	now = !now;
	return now;
}

void getData(char data[3][3]) {
	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {
			int x, y;
			x = msg.x / 200;
			y = msg.y / 200;
			if (data[y][x] == '-') {
				if (nowPlayer()) data[y][x] = 'x';
				else data[y][x] = 'o';
			}
		}
	}
}

char checkWin(char data[3][3]) {
	char who[2] = { 'x', 'o' };
	for (int i = 0; i < 2; i++) {
		if (data[0][0] == who[i] && data[0][1] == who[i] && data[0][2] == who[i]) return who[i];
		if (data[1][0] == who[i] && data[1][1] == who[i] && data[1][2] == who[i]) return who[i];
		if (data[2][0] == who[i] && data[2][1] == who[i] && data[2][2] == who[i]) return who[i];
		if (data[0][0] == who[i] && data[1][0] == who[i] && data[2][0] == who[i]) return who[i];
		if (data[0][1] == who[i] && data[1][1] == who[i] && data[2][1] == who[i]) return who[i];
		if (data[0][2] == who[i] && data[1][2] == who[i] && data[2][2] == who[i]) return who[i];
		if (data[0][0] == who[i] && data[1][1] == who[i] && data[2][2] == who[i]) return who[i];
		if (data[2][0] == who[i] && data[1][1] == who[i] && data[0][2] == who[i]) return who[i];
	}
	int count = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (data[i][j] != '-') count++;
	if (count == 9) return 'p';
	return '-';
}

int main() {
	initgraph(600, 600);//200
	setlinestyle(PS_SOLID, 5);
	initData(gameData);
	BeginBatchDraw();
	while (1) {
		cleardevice();
		drawPlate();
		getData(gameData);
		drawData(gameData);
		FlushBatchDraw();
		if (checkWin(gameData) != '-') {
			if (checkWin(gameData) == 'o')
				MessageBox(GetHWnd(), _T("玩家O获胜"), _T("游戏结束"), MB_OK);
			else if (checkWin(gameData) == 'x')
				MessageBox(GetHWnd(), _T("玩家X获胜"), _T("游戏结束"), MB_OK);
			else MessageBox(GetHWnd(), _T("平局了"), _T("游戏结束"), MB_OK);
			break;
		}
	}
	EndBatchDraw();
}

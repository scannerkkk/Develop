//ͷ�ļ��ϼ�
#pragma region
#include "atlbase.h"
#include "atlstr.h"
#include <iostream>
#include <stdio.h>
//����ͼ�ο��ļ�
#include <easyx.h>
//����windows���ļ�
#include <Windows.h>
//���������ļ�
#include <mmsystem.h>
#include <conio.h>
#include <stack>
#include <map>
#include <string>
//����winmm.lib
#pragma comment(lib,"winmm.lib")
#pragma endregion
//��������ϼ�
#pragma region
//ÿ�����ӵĿ��
#define GRID_W 25
//��������ϵļ�����
#define INTERVAL (4 * 25)
//���̳���
#define ROW 15
//���̿��
#define COL 15
//�������̵ĵ÷����
#define OTHER 0//0,�������Ͳ�����
#define R_DRAW 3//ɱ�����
#define R_WHITE 4
#define R_BLACK 5
#define WIN 1//100000,��Ӯ
#define LOSE 2//-10000000
#define FLEX4 3//50000,�׻�4
#define flex4 4//-80000
#define BLOCK4 5//400
#define block4 6//-80000
#define FLEX3 7//400
#define flex3 8//-8000
#define BLOCK3 9//20
#define block3 10//-40
#define FLEX2 11//20
#define flex2 12//-40
#define BLOCK2 13//1
#define block2 14//-2
#define FLEX1 15//1
#define flex1 16//-2
using namespace std;
//���嵱ǰ����״̬��AI����ר��
int VisChess[ROW][COL];
int Chess[ROW][COL];
//6Ԫ���ж����� 0�������ӣ�1����ڷ���2����׷���3����߽�
int scoreBoard[4][4][4][4][4][4];
//�����ܻ���
int scoreBBS;
//����ڷ�����
int scoreblack = 100;
//����׷�����
int scorewhite = 100;
//������Һ�AI����
int f = 1;
//����оֿ���״̬
bool eG = false;
//���巵��״̬
bool returngame2 = true, returngame1 = true, returngame3 = true;
//����״̬����
enum class Status { None, Black, White };
//������Ҳ���״̬����
struct node {
	int x = 0;//��ǰ����Ŀ�������
	int y = 0;//��ǰ����Ŀ��������
	bool isShow = false;//�Ƿ���ʾ�����
	//��굱ǰ���������Ӧ���±�
	int row = 0;
	int col = 0;
	//����״̬
	Status chessPlayer = Status::Black;
}op;
struct evaluation {
	long long score;
	int result;
	long long stat[20];//��ɱ��
};
struct QPoint {
	int x;
	int y;
};
struct POinTS {
	QPoint pos[10];//0������ߣ�9�������
	long long score[10];
};
struct undo {
	int x;
	int y;
};
//�������ջ��
stack <undo> white;
stack <undo> black;
//����AI����״S̬����
struct aiNode{ int x;
int y; 
int ans; }aiOperation;
#pragma endregion
//���̲����ϼ�
#pragma region
//�Ʒֺ���
void OutputScore(int player,int sc)
{
	char s[10010] = {0};
	int  c = 0;
	int num = sc;
	while (num) {
		num /= 10;
		c++;
	}
	if (sc == 0)
		s[c++] = '0';
	while (sc) {
		int d = sc % 10;
		s[--c] = char(d + 48);
		sc = sc / 10;
	}
	if(player == 1)
		MessageBox(GetHWnd(), s, "�ڷ��Ƿ���", MB_OK);
	else
		MessageBox(GetHWnd(), s, "�׷��Ƿ���", MB_OK);
}
//�������
int popChess(stack <undo> &s)
{
	if (s.empty()) {
		return 0;
	}
	else {
		undo v = s.top();
		s.pop();
		Chess[v.x][v.y] = int(Status::None);
		return 1;
	}
}
//���ջ������
void clearStack(stack <undo>& s)
{
	s = stack <undo>();
}
//�ж���������
bool judgeFullchess()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			if (!Chess[i][j])
				return false;
	return true;
}
//�������
void flushCheckerBoard()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			Chess[i][j] = int(Status::None);
}
//�ж�Ӯ��
bool judgeWinner(int sx, int sy)
{
	int mx[8] = { 1,-1,1,-1,0,0,1,-1 };
	int my[8] = { -1,1,1,-1,1,-1,0,0 };
	for (int i = 0; i < 4; i++) {
		int cnt = 1;
		int dx = sx;
		int dy = sy;
		while (1) {
			dx = mx[i * 2] + dx;
			dy = my[i * 2] + dy;
			if (dx < 0 || dx >= 15 || dy < 0 || dy >= 15)
				break;
			if (Chess[dx][dy] != int(op.chessPlayer))
				break;
			cnt++;
		}
		dx = sx;
		dy = sy;
		while (1) {
			dx = mx[i * 2 + 1] + dx;
			dy = my[i * 2 + 1] + dy;
			if (dx < 0 || dx >= 15 || dy < 0 || dy >= 15)
				break;
			if (Chess[dx][dy] != int(op.chessPlayer))
				break;
			cnt++;
		}
		if (cnt >= 5)
			return true;
	}
	return false;
}
//��������
void drawCheckerBoard()
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	for (int i = 0; i < 15; i++) {
		//��������
		line(INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL, INTERVAL + i * GRID_W);
		line(INTERVAL + i * GRID_W, INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL);
	}
	//����������ʽ
	setlinestyle(PS_SOLID, 3);
	//���ƾ��󣬼ӿ����
	rectangle(INTERVAL, INTERVAL, INTERVAL + GRID_W * 14, INTERVAL + GRID_W * 14);
	//��������ѡ���
	if (op.isShow) {//��ֹ�����̻���ʾ�����
		setlinecolor(BLUE);
		rectangle(op.x - 12, op.y - 12, op.x + 12, op.y + 12);
	}
	//��������
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			switch (Chess[i][j]) {
			case 0:break;
			case 1:
				setfillcolor(BLACK);
				solidcircle(i * GRID_W + INTERVAL, j * GRID_W + INTERVAL, 10);
				break;//���������ʵ�������෴
			case 2:
				setfillcolor(WHITE);
				solidcircle(i * GRID_W + INTERVAL, j * GRID_W + INTERVAL, 10);
				break;//���������ʵ�������෴
			default:
				break;
			}
		}
}
#pragma endregion
//�оֲ����ϼ�
#pragma region
void endGame1()
{
	Chess[4][3] = 2;
	Chess[4][6] = 1;
	Chess[5][4] = 1;
	Chess[5][5] = 2;
	Chess[5][6] = 2;
	Chess[6][3] = 1;
	Chess[6][6] = 1;
	Chess[6][7] = 2;
	Chess[7][4] = 2;
	Chess[7][5] = 1;
	Chess[7][6] = 1;
	Chess[7][7] = 2;
	Chess[8][5] = 1;
	Chess[9][4] = 2;
	Chess[9][5] = 2;
	Chess[10][6] = 1;
	op.chessPlayer = Status::Black;
}
void endGame2()
{
	Chess[8][1] = 2;
	Chess[8][2] = 1;
	Chess[8][3] = 2;
	Chess[8][6] = 2;
	Chess[8][7] = 1;
	Chess[8][8] = 1;
	Chess[8][10] = 1;
	Chess[5][5] = 2;
	Chess[6][7] = 2;
	Chess[6][9] = 1;
	Chess[7][5] = 1;
	Chess[7][9] = 2;
	Chess[9][3] = 2;
	Chess[9][6] = 1;
	Chess[9][5] = 1;
	Chess[9][7] = 2;
	Chess[9][9] = 2;
	Chess[9][11] = 2;
	Chess[10][3] = 1;
	Chess[10][5] = 2;
	Chess[10][8] = 1;
	Chess[11][4] = 1;
	Chess[11][6] = 1;
	Chess[11][7] = 2;
	Chess[11][8] = 2;
	Chess[11][9] = 1;
	Chess[11][10] = 2;
	Chess[12][5] = 2;
	Chess[12][6] = 1;
	Chess[13][3] = 1;
	op.chessPlayer = Status::Black;
}
void endGame3()
{
	Chess[1][11] = 2;
	Chess[2][7] = 1;
	Chess[2][9] = 2;
	Chess[2][10] = 1;
	Chess[3][7] = 1;
	Chess[3][8] = 2;
	Chess[3][9] = 1;
	Chess[3][10] = 1;
	Chess[4][7] = 2;
	Chess[4][8] = 1;
	Chess[4][9] = 2;
	Chess[4][11] = 2;
	Chess[5][6] = 1;
	Chess[5][7] = 2;
	Chess[5][8] = 1;
	Chess[5][9] = 2;
	Chess[6][7] = 2;
	Chess[6][9] = 1;
	Chess[6][10] = 2;
	Chess[6][11] = 1;
	Chess[7][6] = 2;
	Chess[7][7] = 1;
	Chess[7][8] = 1;
	Chess[7][10] = 1;
	Chess[8][7] = 2;
	Chess[8][11] = 1;
	Chess[9][11] = 2;
	Chess[9][12] = 2;
	op.chessPlayer = Status::Black;
}
void endGame4()
{
	Chess[3][8] = 2;
	Chess[3][11] = 2;
	Chess[4][9] = 1;
	Chess[4][10] = 1;
	Chess[4][11] = 2;
	Chess[5][8] = 2;
	Chess[5][10] = 1;
	Chess[5][9] = 1;
	Chess[5][11] = 1;
	Chess[6][9] = 1;
	Chess[6][8] = 1;
	Chess[6][10] = 2;
	Chess[6][11] = 1;
	Chess[7][8] = 1;
	Chess[7][9] = 2;
	Chess[8][7] = 1;
	Chess[8][8] = 2;
	Chess[8][9] = 2;
	Chess[9][6] = 2;
	Chess[9][8] = 2;
	op.chessPlayer = Status::Black;
}
void endGame5()
{
	Chess[5][3] = 1;
	Chess[5][4] = 2;
	Chess[7][3] = 1;
	Chess[6][4] = 1;
	Chess[6][7] = 2;
	Chess[6][8] = 2;
	Chess[6][9] = 2;
	Chess[6][12] = 1;
	Chess[7][5] = 1;
	Chess[7][7] = 1;
	Chess[7][9] = 1;
	Chess[7][12] = 2;
	Chess[8][7] = 2;
	Chess[8][8] = 2;
	Chess[8][9] = 1;
	Chess[8][12] = 2;
	Chess[9][7] = 1;
	Chess[9][9] = 1;
	Chess[9][12] = 1;
	Chess[10][7] = 2;
	Chess[10][8] = 2;
	Chess[10][9] = 2;
	Chess[10][12] = 1;
	op.chessPlayer = Status::Black;
}
//�����ȡ�о�
void chooseEndgame()
{
	int key;
	key = rand() % 5 + 1;
	if (key == 1)
		endGame1();
	else if (key == 2)
		endGame2();
	else if (key == 3)
		endGame3();
	else if (key == 4)
		endGame4();
	else if (key == 5)
		endGame5();
}
#pragma endregion
//���Ϻϼ�
#pragma region
//��������
void bkmusic()
{
	mciSendString("open ./bkmusic.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", NULL, 0, NULL);
}
//����ͼƬ
void bkimage()
{
	//˫�����ͼ ������������������ͼ����˸
	BeginBatchDraw();
	IMAGE img_bk;//����ͼƬ����
	loadimage(&img_bk, "./checkerboard.jpg", 0, 0);
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(30, 10, "����");
	outtextxy(460, 200, "----");
	outtextxy(460, 215, "����");
	outtextxy(495, 215, "|");
	outtextxy(455, 215, "|");
	outtextxy(460, 230, "----");

	outtextxy(460, 235, "----");
	outtextxy(460, 250, "����");
	outtextxy(495, 250, "|");
	outtextxy(455, 250, "|");
	outtextxy(460, 265, "----");

	outtextxy(460, 270, "----");
	outtextxy(460, 285, "���");
	outtextxy(495, 285, "|");
	outtextxy(455, 285, "|");
	outtextxy(460, 300, "----");

	outtextxy(15, 460, "----");
	outtextxy(15, 475, "����");
	outtextxy(50, 475, "|");
	outtextxy(10, 475, "|");
	outtextxy(15, 490, "----");
}
//�˵�����
void menumusic()
{
	mciSendString("open ./menumusic.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", NULL, 0, NULL);
}
//�˵�����ͼƬ
void menuImage()
{
	IMAGE img_menubk;//����ͼƬ����
	loadimage(&img_menubk, "./menubk.jpg", 0, 0);
	putimage(0, 0, &img_menubk);
}
#pragma endregion
//��Ϸʵ�ֺϼ�
#pragma region
//������
void mouseEvent()
{
	//����һ����Ϣ�ṹ�����
	ExMessage msg;
	//��ȡ�����Ϣ
	if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSEֻ��Ҫ�����Ϣ
		//����
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 460 && msg.x <= 490 && msg.y >= 250 && msg.y < 280) {
				//���������
				clearStack(white);
				clearStack(black);
				MessageBox(GetHWnd(), "Win", op.chessPlayer == Status::White ? "�ڷ�" : "�׷�", MB_OK);
				MessageBox(GetHWnd(), "���¿�ʼ", "���ֺڷ�����", MB_OK);
				//����״̬ת��
				op.chessPlayer = Status::Black;
				flushCheckerBoard();
				return;
			}
			else if(msg.x >= 460 && msg.x <= 490 && msg.y >= 285 && msg.y < 315) {
				//���������
				clearStack(white);
				clearStack(black);
				MessageBox(GetHWnd(), "���¿�ʼ", "ƽ��", MB_OK);
				MessageBox(GetHWnd(), "", "���ֺڷ�����", MB_OK);
				//����״̬ת��
				op.chessPlayer = Status::Black;
				flushCheckerBoard();
				return;
			}
			else if(msg.x >= 460 && msg.x <= 490 && msg.y >= 215 && msg.y < 245) {
				//�ж��Ƿ����
				int check = 0;
				if (op.chessPlayer == Status::Black)
					check = popChess(white);
				else
					check = popChess(black);
				//���û�л���
				if (!check) {
					MessageBox(GetHWnd(), "����û������Ŷ>0<", "", MB_OK);
					return;
				}
				//����״̬ת��
				op.chessPlayer = (op.chessPlayer == Status::Black ? Status::White : Status::Black);
				drawCheckerBoard();
				FlushBatchDraw();
				return;
			}
			else if (msg.x >= 10 && msg.x <= 50 && msg.y >= 460 && msg.y < 490) {
				if (!returngame1)
					returngame1 = true;
				if (!returngame2)
					returngame2 = true;
				if (!returngame3)
					returngame3 = true;
				return;
			}
		}
		//����У׼(�Զ��۽���������ĳ���������)
		op.isShow = false;
		int intervalGridx = msg.x % GRID_W;
		int intervalGridy = msg.y % GRID_W;
		int gridx, gridy;
		//У׼x����
		if (intervalGridx <= GRID_W / 2)
			gridx = (msg.x / GRID_W) * GRID_W;
		else
			gridx = (msg.x / GRID_W + 1) * GRID_W;
		//У׼y����
		if (intervalGridy <= GRID_W / 2)
			gridy = (msg.y / GRID_W) * GRID_W;
		else
			gridy = (msg.y / GRID_W + 1) * GRID_W;
		//�ж��Ƿ�Խ������
		if (gridx < INTERVAL || gridy < INTERVAL ||
			gridx > INTERVAL + GRID_W * 14 || gridy > INTERVAL + GRID_W * 14)
			return;
		op.isShow = true;
		op.row = (gridx - INTERVAL) / GRID_W;
		op.col = (gridy - INTERVAL) / GRID_W;
		op.x = gridx;
		op.y = gridy;
		//�������
		if (msg.message == WM_LBUTTONDOWN && Chess[op.row][op.col] == 0) {
			//����״̬���
			Chess[op.row][op.col] = int(op.chessPlayer);
			if (op.chessPlayer == Status::Black)
				black.push({ op.row,op.col });
			else
				white.push({ op.row,op.col });
			drawCheckerBoard();
			FlushBatchDraw();
			//�ж�Ӯ��
			if (!eG && judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", op.chessPlayer == Status::White ? "�׷�" : "�ڷ�", MB_OK);
				MessageBox(GetHWnd(), "���¿�ʼ", op.chessPlayer == Status::White ? "���ֺڷ�����" : "���ְ׷�����", MB_OK);
				//�������ջ��
				clearStack(white);
				clearStack(black);
				flushCheckerBoard();
				if (op.chessPlayer == Status::White) {
					scorewhite += 10;
					scoreblack -= 10;
					if (scoreblack < 0)
						scoreblack = 0;
					OutputScore(1, scoreblack);
					OutputScore(2, scorewhite);
				}
				else {
					scoreblack += 10;
					scorewhite -= 10;
					if (scorewhite < 0)
						scorewhite = 0;
					OutputScore(1, scoreblack);
					OutputScore(2, scorewhite);
				}
			}
			//�о�״̬
			else if(eG && judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", op.chessPlayer == Status::White ? "�׷�" : "�ڷ�", MB_OK);
				MessageBox(GetHWnd(), "���¿�ʼ", op.chessPlayer == Status::Black ? "���ֺڷ�����" : "���ְ׷�����", MB_OK);
				flushCheckerBoard();
				if (op.chessPlayer == Status::White) {
					scorewhite += 10;
					scoreblack -= 10;
					if (scoreblack < 0)
						scoreblack = 0;
					OutputScore(1, scoreblack);
					OutputScore(2, scorewhite);
				}
				else {
					scoreblack += 10;
					scorewhite -= 10;
					if (scorewhite < 0)
						scorewhite = 0;
					OutputScore(1, scoreblack);
					OutputScore(2, scorewhite);
				}
				chooseEndgame();
				//�������ջ��
				clearStack(white);
				clearStack(black);
				return;
			}
			//����״̬ת��
			op.chessPlayer = (op.chessPlayer == Status::Black ? Status::White : Status::Black);
		}
		//��������
		if (judgeFullchess()) {
			MessageBox(GetHWnd(), "����", "���¿�ʼ", MB_OK);
			//�������ջ��
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
		}
	}
}
//��ʼ������
void InitBoardScore()
{
	memset(scoreBoard, 0, sizeof(scoreBoard));
	//����5,aiӮ
	scoreBoard[2][2][2][2][2][2] = WIN;
	scoreBoard[2][2][2][2][2][0] = WIN;
	scoreBoard[0][2][2][2][2][2] = WIN;
	scoreBoard[2][2][2][2][2][1] = WIN;
	scoreBoard[1][2][2][2][2][2] = WIN;
	scoreBoard[3][2][2][2][2][2] = WIN;//�߽翼��
	scoreBoard[2][2][2][2][2][3] = WIN;
	//����5,ai��
	scoreBoard[1][1][1][1][1][1] = LOSE;
	scoreBoard[1][1][1][1][1][0] = LOSE;
	scoreBoard[0][1][1][1][1][1] = LOSE;
	scoreBoard[1][1][1][1][1][2] = LOSE;
	scoreBoard[2][1][1][1][1][1] = LOSE;
	scoreBoard[3][1][1][1][1][1] = LOSE;
	scoreBoard[1][1][1][1][1][3] = LOSE;
	//�׻�4
	scoreBoard[0][2][2][2][2][0] = FLEX4;
	//�ڻ�4
	scoreBoard[0][1][1][1][1][0] = flex4;
	//�׻�3
	scoreBoard[0][2][2][2][0][0] = FLEX3;
	scoreBoard[0][0][2][2][2][0] = FLEX3;
	scoreBoard[0][2][0][2][2][0] = FLEX3;
	scoreBoard[0][2][2][0][2][0] = FLEX3;
	//�ڻ�3
	scoreBoard[0][1][1][1][0][0] = flex3;
	scoreBoard[0][0][1][1][1][0] = flex3;
	scoreBoard[0][1][0][1][1][0] = flex3;
	scoreBoard[0][1][1][0][1][0] = flex3;
	//�׻�2
	scoreBoard[0][2][2][0][0][0] = FLEX2;
	scoreBoard[0][2][0][2][0][0] = FLEX2;
	scoreBoard[0][2][0][0][2][0] = FLEX2;
	scoreBoard[0][0][2][2][0][0] = FLEX2;
	scoreBoard[0][0][2][0][2][0] = FLEX2;
	scoreBoard[0][0][0][2][2][0] = FLEX2;
	//�ڻ�2
	scoreBoard[0][1][1][0][0][0] = flex2;
	scoreBoard[0][1][0][1][0][0] = flex2;
	scoreBoard[0][1][0][0][1][0] = flex2;
	scoreBoard[0][0][1][1][0][0] = flex2;
	scoreBoard[0][0][1][0][1][0] = flex2;
	scoreBoard[0][0][0][1][1][0] = flex2;
	//�׻�1
	scoreBoard[0][2][0][0][0][0] = FLEX1;
	scoreBoard[0][0][2][0][0][0] = FLEX1;
	scoreBoard[0][0][0][2][0][0] = FLEX1;
	scoreBoard[0][0][0][0][2][0] = FLEX1;
	//�ڻ�1
	scoreBoard[0][1][0][0][0][0] = flex1;
	scoreBoard[0][0][1][0][0][0] = flex1;
	scoreBoard[0][0][0][1][0][0] = flex1;
	scoreBoard[0][0][0][0][1][0] = flex1;
	//����ѭ��ö�ٻ�û�г�ʼ�������ͣ�2����ai��1�������
	for(int p1 = 0;p1 < 4;p1++)
		for (int p2 = 0; p2 < 3; p2++)
			for (int p3 = 0; p3 < 3; p3++)
				for (int p4 = 0; p4 < 3; p4++)
					for (int p5 = 0; p5 < 3; p5++)
						for (int p6 = 0; p6 < 4; p6++) {
							//ͳ������������Ӻ��ұ���������
							//lx������������Ӹ�����rx�����ұ������Ӹ���
							//ly������������Ӹ�����ry�����ұ������Ӹ���
							int lx, ly, rx, ry;
							lx = ly = rx = ry = 0;
							if (p1 == 1)
								lx++;
							else if (p1 == 2)
								ly++;

							if (p2 == 1){
								lx++; 
								rx++;
							}
							else if (p2 == 2) {
								ly++;
								ry++;
							}

							if (p3 == 1) {
								lx++;
								rx++;
							}
							else if (p3 == 2) {
								ly++;
								ry++;
							}

							if (p4 == 1) {
								lx++;
								rx++;
							}
							else if (p4 == 2) {
								ly++;
								ry++;
							}

							if (p5 == 1) {
								lx++;
								rx++;
							}
							else if (p5 == 2) {
								ly++; 
								ry++;
							}

							if (p6 == 1)
								rx++;
							else if (p6 == 2)
								ry++;

							//�߽����
							if (p1 == 3 || p6 == 3) {
								//��߽����
								if (p1 == 3 && p6 != 3) {
									//�׳������
									if (rx == 0 && ry == 4) 
										if(scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK4;

									//�ڳ������
									if (ry == 0 && rx == 4)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block4;

									//������
									if (rx == 0 && ry == 3) 
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK3;

									//������
									if (ry == 0 && rx == 3)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block3;
									
									//���߶�
									if (rx == 0 && ry == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK2;

									//���߶�
									if (ry == 0 && rx == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block2;
									//�׵�һ
									if(rx == 0 && ry == 1)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = FLEX1;

									//�ڵ�һ
									if (rx == 1 && ry == 0)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = flex1;
								}
								//�ұ߽����
								else if (p6 == 3 && p1 != 3) {
									//�׳�4���
									if (lx == 0 && ly == 4)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK4;

									//�ڳ������
									if (ly == 0 && lx == 4)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block4;

									//������
									if (lx == 0 && ly == 3)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block3;

									//������
									if (ly == 0 && lx == 3)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK3;

									//���߶�
									if (lx == 0 && ly == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block2;

									//���߶�
									if (ly == 0 && lx == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK2;

									//�׵�һ
									if (lx == 0 && ly == 1)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = FLEX1;

									//�ڵ�һ
									if (lx == 1 && ly == 0)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = flex1;
								}
							}
							//�ޱ߽����
							else {
								//�׳������
								if ((lx == 0 && ly == 4) || (rx == 0 && ry == 4))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK4;

								//�ڳ������
								if ((ly == 0 && lx == 4) || (ry == 0 && rx == 4))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = block4;

								//������
								if ((lx == 0 && ly == 3) || (rx == 0 && ry == 3))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK3;

								//������
								if ((ly == 0 && lx == 3) || (ry == 0 && rx == 3))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = block3;

								//���߶�
								if ((lx == 0 && ly == 2) || (rx == 0 && ry == 2))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK2;

								//���߶�
								if ((ly == 0 && lx == 2) || (ry == 0 && rx == 2))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = block2;

								//�׵�һ
								if ((lx == 0 && ly == 1) || (rx == 0 && ry == 1))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = FLEX1;

								//�ڵ�һ
								if ((lx == 1 && ly == 0) || (rx == 1 && ry == 0))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = flex1;
							}
						}
}
//HardAI��ֺ���
evaluation evaluate(int chess[ROW][COL])
{
	int w[17] = {0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3};
	//���ĸ������� ����0  ����1  ���Խ��ߣ�2  �ζԽ��ߣ�3
	int QiXing[4][17];
	int CopyChess[ROW + 2][COL + 2];
	memset(QiXing, 0, sizeof(QiXing));
	//��������̳�ʼ���߽�
	for (int i = 0; i < 17; i++)
		CopyChess[i][0] = 3;
	//���ϱ����̳�ʼ���߽�
	for (int i = 0; i < 17; i++)
		CopyChess[0][i] = 3;
	//���ұ����̳�ʼ���߽�
	for (int i = 0; i < 17; i++)
		CopyChess[i][16] = 3;
	//���±����̳�ʼ���߽�
	for (int i = 0; i < 17; i++)
		CopyChess[16][i] = 3;
	
	//���Ƶ�ǰ����
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			CopyChess[i + 1][j + 1] = chess[i][j];

	//�����̺����� bug?
	for(int i = 0;i <= 16;i++)
		for (int j = 0; j < 12; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i][j + 1]][CopyChess[i][j + 2]][CopyChess[i][j + 3]][CopyChess[i][j + 4]][CopyChess[i][j + 5]];
			QiXing[0][q]++;
		}

	//������������
	for (int i = 0; i < 12; i++)
		for (int j = 0; j <= 16; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i + 1][j]][CopyChess[i + 2][j]][CopyChess[i + 3][j]][CopyChess[i + 4][j]][CopyChess[i + 5][j]];
			QiXing[1][q]++;
		}

	//���������Խ��ߴ��
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i + 1][j + 1]][CopyChess[i + 2][j + 2]][CopyChess[i + 3][j + 3]][CopyChess[i + 4][j + 4]][CopyChess[i + 5][j + 5]];
			QiXing[2][q]++;
		}

	//�����̴ζԽ��ߴ��
	for (int i = 0; i < 12; i++)
		for (int j = 5; j <= 16; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i + 1][j - 1]][CopyChess[i + 2][j - 2]][CopyChess[i + 3][j - 3]][CopyChess[i + 4][j - 4]][CopyChess[i + 5][j - 5]];
			QiXing[3][q]++;
		}
	
	//��ʼ����
	int score = 0;
	evaluation eval;
	memset(eval.stat, 0, sizeof(eval.stat));
	for (int i = 1; i < 17; i++) {
		score += (QiXing[0][i] + QiXing[1][i] + QiXing[2][i] + QiXing[3][i]) * w[i];
		int cnt = (QiXing[0][i] + QiXing[1][i] + QiXing[2][i] + QiXing[3][i]);
		if (i == WIN)eval.stat[WIN] = cnt;
		else if (i == LOSE)eval.stat[LOSE] = cnt;
		else if (i == FLEX4)eval.stat[FLEX4] = cnt;
		else if (i == BLOCK4)eval.stat[BLOCK4] = cnt;
		else if (i == FLEX3)eval.stat[FLEX3] = cnt;
	}
	eval.result = R_DRAW;
	if (eval.stat[WIN] > 0)
		eval.result = R_WHITE;
	else if (eval.stat[LOSE] > 0)
		eval.result = R_BLACK;
	eval.score = score;
	return eval;
}
//��AI��������
void judgeRobotValue(int robotNum, int empty, int sx, int sy)
{
	int cnt = 0;
	//һ��
	if (robotNum == 0)
		cnt = 5;
	//����
	else if (robotNum == 1)
		cnt = 10;
	//����
	else if (robotNum == 2) {
		//����
		if (empty == 1)
			cnt = 25;
		//����
		else if (empty == 2)
			cnt = 50;
	}
	//����
	else if (robotNum == 3) {
		//����
		if (empty == 1)
			cnt = 55;
		//����
		else if (empty == 2)
			cnt = 300;
	}
	//����
	else if (robotNum >= 4)
		cnt = 30000;
	if (cnt > aiOperation.ans) {
		aiOperation.x = sx;
		aiOperation.y = sy;
		aiOperation.ans = cnt;
	}
}
//�������������
void judgePersonValue(int personNum,int empty,int sx,int sy)
{
	int cnt = 0;
	//����
	if (personNum == 1) {
		cnt = 10;
	}
	//����
	else if (personNum == 2) {
		//����
		if (empty == 1)
			cnt = 30;
		//����
		else if (empty == 2)
			cnt = 40;
	}
	//����
	else if (personNum == 3) {
		//����
		if (empty == 1)
			cnt = 60;
		//����
		else if (empty == 2)
			cnt = 200;
	}
	//����
	else if (personNum >= 4)
		cnt = 20000;
	if (cnt > aiOperation.ans) {
		aiOperation.x = sx;
		aiOperation.y = sy;
		aiOperation.ans = cnt;
	}
}
//�жϿ��������λ��
POinTS canPoints(int CurrentChess[ROW][COL])
{
	//����ֲ��������
	bool visBoard[ROW][COL];
	int  score[ROW][COL];
	POinTS goodPints;
	memset(visBoard, 0, sizeof(visBoard));
	for (int i = 0; i < 10; i++)
		goodPints.pos[i].x = 0,goodPints.pos[i].y = 0;
	//ÿ���ǿյ㸽��8����������3�����,Ҳ�������п�������
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (CurrentChess[i][j] != int(Status::None)) {
				for (int k = -3; k <= 3; k++) {
					if (i + k >= 0 && i + k < 15) {
						visBoard[i + k][j] = true;
						if (j + k >= 0 && j + k < 15) visBoard[i + k][j + k] = true;
						if (j - k >= 0 && j - k < 15) visBoard[i + k][j - k] = true;
					}
					if (j + k >= 0 && j + k < 15) {
						/*if (i + k >= 0 && i + k < 15) visBoard[i + k][j + k] = true;
						if (i - k >= 0 && i - k < 15) visBoard[i - k][j + k] = true;*/
						visBoard[i][j + k] = true;
					}
				}
			}
		}
	}
	//�ж�ÿ�����ߵ�ķ���
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			score[i][j] = -INT_MAX;
			if (CurrentChess[i][j] == int(Status::None) && visBoard[i][j]) {
				CurrentChess[i][j] = int(Status::White);//?bug?
				score[i][j] = evaluate(CurrentChess).score;
				CurrentChess[i][j] = int(Status::None);
			}
		}
	}
	//ѡ��ʮ�����п����ߵĵ�
	for (int k = 0; k < 10; k++) {
		int mincost = -INT_MAX;
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (score[i][j] > mincost) {
					mincost = score[i][j];
					QPoint temp;
					temp.x = i;
					temp.y = j;
					goodPints.pos[k] = temp;
				}
			}
		}
		goodPints.score[k] = mincost;
		score[goodPints.pos[k].x][goodPints.pos[k].y] = -INT_MAX;//�������һ��,������һ���λ�úͷ���
	}
	return goodPints;
}
//���Ƶ�ǰ����
void cpBoard(int lastBoard[ROW][COL],int curBoard[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			lastBoard[i][j] = curBoard[i][j];
}
//��ת����������ɫ
void reverseBoard(int CurrentChess[ROW][COL], int rBoard[15][15])
{
	for(int i =  0;i < ROW;i++)
		for (int j = 0; j < COL; j++) {
			if (CurrentChess[i][j] == 1)
				rBoard[i][j] = 2;
			else if(CurrentChess[i][j] == 2)
				rBoard[i][j] = 1;
		}
}
//AI alpha-beta
int AiHard(int depth, int alpha, int beta,int chess[ROW][COL])
{
	//�ײ��ʱ��
	evaluation gameresult = evaluate(chess);
	if (depth == 0 || gameresult.result != R_DRAW) {
		if(gameresult.result != R_DRAW)
			return gameresult.score;
		if (depth == 0) {
			POinTS P;
			P = canPoints(chess);//������ѵĿ�������λ��
			return P.score[0];//�������λ�ö�Ӧ����߷�
		}
		
	}
	//Ai����
	else if (depth % 2 == 0) {
		POinTS P;
		int sameBoard[ROW][COL];
		cpBoard(sameBoard, chess);
		P = canPoints(sameBoard);
		for (int i = 0; i < 10; i++) {
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::White);//ģ�⼺������
			int score = AiHard(depth - 1, alpha, beta,sameBoard);
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::None);//���ݻ�ԭ����
			if (score > alpha) {
				alpha = score;
				if (depth == 6) {//�Ǹ�ż������,�������������
					aiOperation.x = P.pos[i].x;
					aiOperation.y = P.pos[i].y;
				}
			}
			if (alpha >= beta) return alpha;//��֦
		}
	}
	//ģ����Ҳ��� 
	else {
		int rBoard[ROW][COL];
		reverseBoard(Chess, rBoard);
		POinTS P;
		P = canPoints(rBoard);//�Ҷ��ں��ӵ����λ��,��Ҫ�����̲�ͬ��ɫ��ת,��ΪcanPoint�����ɫ�������λ��
		int sameBoard[ROW][COL];
		cpBoard(sameBoard, chess);
		for (int i = 0; i < 10; i++ ) {
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::Black);//ģ��з�����
			int score = AiHard(depth - 1, alpha, beta,sameBoard);//ʹ��longlong���·���ը��
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::None);//���ݻ�ԭ����
			if (score < beta)beta = score;
			if (alpha >= beta) return beta;//��֦
		}
	}
}
//��ʼ����AI
void initAI()
{
	aiOperation.ans = 0;
	aiOperation.x = 0;
	aiOperation.y = 0;
	int mx[8] = { 1,-1,1,-1,0,0,1,-1 };
	int my[8] = { -1,1,1,-1,1,-1,0,0 };
	//����ҽ������� ����Ǻ���
	for(int i = 0;i < ROW;i++)
		for (int j = 0; j < COL; j++) {
			int sx = i, sy = j;
			int empty,personNum,robotNum;
			if (!Chess[sx][sy]) {
				int dx = sx, dy = sy;
				for (int k = 0; k < 4; k++) {
					personNum = 0;
					robotNum = 0;
					empty = 0;
					//�ж��������
					dx = sx, dy = sy;
					for (int z = 0; z < 5;z++) {
						dx = dx + mx[2 * k];
						dy = dy + my[2 * k];
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//����AI���Ӿ��˳�
						if (Chess[dx][dy] == 2) {
							break;
						}
						//�ո�����˳�
						if (Chess[dx][dy] == 0) {
							empty++;
							break;
						}
						personNum++;
					}
					dx = sx,dy = sy;
					for (int z = 0; z < 5;z++) {
						dx = dx + mx[2 * k + 1];
						dy = dy + my[2 * k + 1];
						//Խ������˳�
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//����AI���Ӿ��˳�
						if (Chess[dx][dy] == 2) {
							break;
						}
						//�����ո��˳�
						if (Chess[dx][dy] == 0) {
							empty++;
							break;
						}
						personNum++;
					}
					judgePersonValue(personNum,empty,sx,sy);
					//��ʼ������״̬
					empty = 0;
					dx = sx,dy = sy;
					//�ж�AI����
					for (int z = 0; z < 5;z++) {
						dx = dx + mx[2 * k];
						dy = dy + my[2 * k];
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//����������Ӿ��˳�
						if (Chess[dx][dy] == 1) {
							break;
						}
						//�ո�����˳�
						if (Chess[dx][dy] == 0) {
							empty++;
							break;
						}
						robotNum++;
					}
					dx = sx,dy = sy;
					for (int z = 0; z < 5;z++) {
						dx = dx + mx[2 * k + 1];
						dy = dy + my[2 * k + 1];
						//Խ������˳�
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//����������Ӿ��˳�
						if (Chess[dx][dy] == 1) {
							break;
						}
						//�����ո��˳�
						if (Chess[dx][dy] == 0) {
							empty++;
							break;
						}
						robotNum++;
					}
					judgeRobotValue(robotNum, empty, sx, sy);
				}
			}
		}
}
//��AI
void aiEvent1()
{
	if (f == -1) {
		initAI();
		//AIѡ�����ʾ
		op.isShow = false;
		op.row = aiOperation.x;
		op.col = aiOperation.y;
		op.x = op.row * GRID_W + INTERVAL;
		op.y = op.col * GRID_W + INTERVAL;
		//AI����
		if (Chess[op.row][op.col] == 0) {
			//����״̬���
			Chess[op.row][op.col] = 2;
			white.push({ op.row,op.col });
			drawCheckerBoard();
			FlushBatchDraw();
			//�ж�Ӯ��
			if (judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", "AI", MB_OK);
				MessageBox(GetHWnd(), "���¿�ʼ", "�����������", MB_OK);
				clearStack(white);
				clearStack(black);
				flushCheckerBoard();
				//������˻���2��
				scoreBBS -= 2;
				if (scoreBBS < 0)
					scoreBBS = 0;
				OutputScore(1,scoreBBS);
			}
			//����״̬ת��
			op.chessPlayer = Status::Black;
			f = 1;
		}
		//��������
		if (judgeFullchess()) {
			MessageBox(GetHWnd(), "����", "���¿�ʼ", MB_OK);
			clearStack(white);
			clearStack(black);
			op.chessPlayer = Status::Black;
			f = 1;
			flushCheckerBoard();
		}
	}
	else {
		//����һ����Ϣ�ṹ�����
		ExMessage msg;
		//��ȡ�����Ϣ
		if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSEֻ��Ҫ�����Ϣ
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= 460 && msg.x <= 490 && msg.y >= 250 && msg.y < 280) {
					//���������
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "Win", "AI", MB_OK);
					MessageBox(GetHWnd(), "���¿�ʼ", "�����������", MB_OK);
					//����״̬ת��
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 285 && msg.y < 315) {
					//���������
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "���¿�ʼ", "ƽ��", MB_OK);
					MessageBox(GetHWnd(), "", "���ֺڷ�����", MB_OK);
					//����״̬ת��
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 215 && msg.y < 245) {
					//�ж��Ƿ����
					int check = 0;
					check = popChess(black);
					check = popChess(white);
					//���û�л���
					if (!check) {
						MessageBox(GetHWnd(), "����û������Ŷ>0<", "", MB_OK);
						return;
					}
					drawCheckerBoard();
					FlushBatchDraw();
					return;
				}
				else if (msg.x >= 10 && msg.x <= 50 && msg.y >= 460 && msg.y < 490) {
					if (!returngame1)
						returngame1 = true;
					if (!returngame2)
						returngame2 = true;
					if (!returngame3)
						returngame3 = true;
					return;
				}
			}
			//����У׼(�Զ��۽���������ĳ���������)
			op.isShow = false;
			int intervalGridx = msg.x % GRID_W;
			int intervalGridy = msg.y % GRID_W;
			int gridx, gridy;
			//У׼x����
			if (intervalGridx <= GRID_W / 2)
				gridx = (msg.x / GRID_W) * GRID_W;
			else
				gridx = (msg.x / GRID_W + 1) * GRID_W;
			//У׼y����
			if (intervalGridy <= GRID_W / 2)
				gridy = (msg.y / GRID_W) * GRID_W;
			else
				gridy = (msg.y / GRID_W + 1) * GRID_W;
			//�ж��Ƿ�Խ������
			if (gridx < INTERVAL || gridy < INTERVAL ||
				gridx > INTERVAL + GRID_W * 14 || gridy > INTERVAL + GRID_W * 14)
				return;
			op.isShow = true;
			op.row = (gridx - INTERVAL) / GRID_W;
			op.col = (gridy - INTERVAL) / GRID_W;
			op.x = gridx;
			op.y = gridy;
			//�������
			if (msg.message == WM_LBUTTONDOWN && Chess[op.row][op.col] == 0) {
				//����״̬���
				Chess[op.row][op.col] = 1;
				black.push({ op.row,op.col });
				drawCheckerBoard();
				FlushBatchDraw();
				//�ж�Ӯ��
				if (judgeWinner(op.row, op.col)) {
					MessageBox(GetHWnd(), "Win", "���", MB_OK);
					MessageBox(GetHWnd(), "���¿�ʼ", "�����������", MB_OK);
					clearStack(white);
					clearStack(black);
					op.chessPlayer = Status::Black;
					f = 1;
					flushCheckerBoard();
					//Ӯ���˻���5��
					scoreBBS += 5;
					OutputScore(1, scoreBBS);
					return;
				}
				//����״̬ת��
				op.chessPlayer = Status::White;
				f = -1;
			}
			//��������
			if (judgeFullchess()) {
				MessageBox(GetHWnd(), "����", "���¿�ʼ", MB_OK);
				clearStack(white);
				clearStack(black);
				op.chessPlayer = Status::Black;
				f = 1;
				flushCheckerBoard();
			}
		}
	}
}
//����AI
void aiEvent2()
{
	if (f == -1) {
		AiHard(6, -INT_MAX, INT_MAX, Chess);
		//AIѡ�����ʾ
		op.isShow = false;
		op.row = aiOperation.x;
		op.col = aiOperation.y;
		op.x = op.row * GRID_W + INTERVAL;
		op.y = op.col * GRID_W + INTERVAL;
		//AI����
		if (Chess[op.row][op.col] == 0) {
			//����״̬���
			Chess[op.row][op.col] = 2;
			white.push({ op.row,op.col });
			drawCheckerBoard();
			FlushBatchDraw();
			//�ж�Ӯ��
			if (judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", "AI", MB_OK);
				MessageBox(GetHWnd(), "���¿�ʼ", "�����������", MB_OK);
				clearStack(white);
				clearStack(black);
				flushCheckerBoard();
				//��������˻���5��
				scoreBBS -= 5;
				if (scoreBBS < 0)
					scoreBBS = 0;
				OutputScore(1,scoreBBS);
			}
			//����״̬ת��
			op.chessPlayer = Status::Black;
			f = 1;
		}
		//��������
		if (judgeFullchess()) {
			MessageBox(GetHWnd(), "����", "���¿�ʼ", MB_OK);
			clearStack(white);
			clearStack(black);
			op.chessPlayer = Status::Black;
			f = 1;
			flushCheckerBoard();
		}
	}
	else {
		//����һ����Ϣ�ṹ�����
		ExMessage msg;
		//��ȡ�����Ϣ
		if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSEֻ��Ҫ�����Ϣ
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= 460 && msg.x <= 490 && msg.y >= 250 && msg.y < 280) {
					//���������
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "Win", "AI", MB_OK);
					MessageBox(GetHWnd(), "���¿�ʼ", "�����������", MB_OK);
					//����״̬ת��
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 285 && msg.y < 315) {
					//���������
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "���¿�ʼ", "ƽ��", MB_OK);
					MessageBox(GetHWnd(), "", "���ֺڷ�����", MB_OK);
					//����״̬ת��
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 215 && msg.y < 245) {
					//�ж��Ƿ����
					int check = 0;
					check = popChess(black);
					check = popChess(white);	
					//���û�л���
					if (!check) {
						MessageBox(GetHWnd(), "����û������Ŷ>0<", "", MB_OK);
						return;
					}
					drawCheckerBoard();
					FlushBatchDraw();
					return;
				}
				else if (msg.x >= 10 && msg.x <= 50 && msg.y >= 460 && msg.y < 490) {
					if (!returngame1)
						returngame1 = true;
					if (!returngame2)
						returngame2 = true;
					if (!returngame3)
						returngame3 = true;
					return;
				}
			}
			//����У׼(�Զ��۽���������ĳ���������)
			op.isShow = false;
			int intervalGridx = msg.x % GRID_W;
			int intervalGridy = msg.y % GRID_W;
			int gridx, gridy;
			//У׼x����
			if (intervalGridx <= GRID_W / 2)
				gridx = (msg.x / GRID_W) * GRID_W;
			else
				gridx = (msg.x / GRID_W + 1) * GRID_W;
			//У׼y����
			if (intervalGridy <= GRID_W / 2)
				gridy = (msg.y / GRID_W) * GRID_W;
			else
				gridy = (msg.y / GRID_W + 1) * GRID_W;
			//�ж��Ƿ�Խ������
			if (gridx < INTERVAL || gridy < INTERVAL ||
				gridx > INTERVAL + GRID_W * 14 || gridy > INTERVAL + GRID_W * 14)
				return;
			op.isShow = true;
			op.row = (gridx - INTERVAL) / GRID_W;
			op.col = (gridy - INTERVAL) / GRID_W;
			op.x = gridx;
			op.y = gridy;
			//�������
			if (msg.message == WM_LBUTTONDOWN && Chess[op.row][op.col] == 0) {
				//����״̬���
				Chess[op.row][op.col] = 1;
				black.push({ op.row,op.col });
				drawCheckerBoard();
				FlushBatchDraw();
				//�ж�Ӯ��
				if (judgeWinner(op.row, op.col)) {
					MessageBox(GetHWnd(), "Win", "���", MB_OK);
					MessageBox(GetHWnd(), "���¿�ʼ", "�����������", MB_OK);
					clearStack(white);
					clearStack(black);
					op.chessPlayer = Status::Black;
					f = 1;
					flushCheckerBoard();
					//Ӯ�����˻���20��
					scoreBBS += 20;
					OutputScore(1,scoreBBS);
					return;
				}
				//����״̬ת��
				op.chessPlayer = Status::White;
				f = -1;
			}
			//��������
			if (judgeFullchess()) {
				MessageBox(GetHWnd(), "����", "���¿�ʼ", MB_OK);
				clearStack(white);
				clearStack(black);
				op.chessPlayer = Status::Black;
				f = 1;
				flushCheckerBoard();
			}
		}
	}
}
#pragma endregion
//��Ϸģʽ�ϼ�
#pragma region
//˫�˶�ս
void gameMode1()
{
	bkmusic();
	returngame1 = false;
	BeginBatchDraw();
	while (1)
	{
		//����
		cleardevice();
		//����ͼƬ
		bkimage();
		//��������
		drawCheckerBoard();
		//������
		mouseEvent();
		//ˢ��
		FlushBatchDraw();
		//�ж��Ƿ񷵻�
		if (returngame1 == true) {
			//����
			cleardevice();
			//MessageBox(GetHWnd(), "welcome !", "hello", MB_OK);
			op.chessPlayer = Status::Black;
			f = 1;
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
			//���¿�ʼ�Ʒ�
			scoreblack = 100;
			scorewhite = 100;
			return;
		}
	}
	//������ͼ
	EndBatchDraw();
}
//���˻�ģʽ
void AIgameMode1()
{
	bkmusic();
	returngame2 = false;
	BeginBatchDraw();
	while (1)
	{
		//����
		cleardevice();
		//����ͼƬ
		bkimage();
		//��������
		drawCheckerBoard();
		//�˻�����
		aiEvent1();
		//ˢ��
		FlushBatchDraw();
		if (returngame2 == true) {
			//����
			cleardevice();
			//MessageBox(GetHWnd(), "welcome !", "hello", MB_OK);
			op.chessPlayer = Status::Black;
			f = 1;
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
			return;
		}
	}
	//������ͼ
	EndBatchDraw();
}
//�����˻�ģʽ
void AIgameMode2()
{
	InitBoardScore();
	bkmusic();
	BeginBatchDraw();
	returngame2 = false;
	while (1)
	{
		//����
		cleardevice();
		//����ͼƬ
		bkimage();
		//��������
		drawCheckerBoard();
		//�˻�����
		aiEvent2();
		//ˢ��
		FlushBatchDraw();
		if (returngame2 == true) {
			//����
			cleardevice();
			//MessageBox(GetHWnd(), "welcome !", "hello", MB_OK);
			op.chessPlayer = Status::Black;
			f = 1;
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
			return;
		}
	}
	//������ͼ
	EndBatchDraw();
}
//�˻��˵�
void Aimenu()
{
	menuImage();
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(50, 15, "����");
	outtextxy(190, 220, "1.��ģʽ");
	outtextxy(190, 270, "2.����ģʽ");
	settextcolor(BLUE);
	settextstyle(30, 10, "����");
	outtextxy(15, 460, "----");
	outtextxy(15, 475, "����");
	outtextxy(50, 475, "|");
	outtextxy(10, 475, "|");
	outtextxy(15, 490, "----");
}
//�˻���ս
void gameMode2()
{
	Aimenu();
	//��ȡ�����Ϣ
	ExMessage msg1;
	int gridx, gridy;
	BeginBatchDraw();
	while (1) {
		Aimenu();
		FlushBatchDraw();
		if (peekmessage(&msg1, EM_MOUSE)) {//EM_MOUSEֻ��Ҫ�����Ϣ
			op.isShow = true;
			if (msg1.message == WM_LBUTTONDOWN) {
				gridx = msg1.x;
				gridy = msg1.y;
				if (gridx >= 170 && gridx <= 420 && gridy >= 220 && gridy < 270)
					AIgameMode1();
				else if (gridx >= 170 && gridx <= 420 && gridy >= 270 && gridy < 320)
					AIgameMode2();
				else if (gridx >= 10 && gridx <= 50 && gridy >= 460 && gridy < 490) 
					return;
			}
		}
		//��ռƷ���
		scoreBBS = 0;
	}
	EndBatchDraw();
}
//�о�
void gameMode3()
{
	bkmusic();
	//�����о�ģʽ
	eG = true;
	returngame3 = false;
	chooseEndgame();
	BeginBatchDraw();
	while (1)
	{
		//����
		cleardevice();
		//����ͼƬ
		bkimage();
		//��������
		drawCheckerBoard();
		//������
		mouseEvent();
		//ˢ��
		FlushBatchDraw();
		//�Ƿ񷵻�
		if (returngame3 == true) {
			//����
			cleardevice();
			op.chessPlayer = Status::Black;
			f = 1;
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
			eG = false;
			//���¿�ʼ�Ʒ�
			scoreblack = 100;
			scorewhite = 100;
			return;
		}
	}
	//������ͼ
	EndBatchDraw();
}
#pragma endregion
//��Ϸָ���ϼ�
#pragma region
//��Ϸģʽ
void bkwords()
{
	// ���ñ���Ϊ͸��
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(50, 15, "����");
	outtextxy(190, 120, "  ��Ϸ�˵�");
	outtextxy(190, 170, "1.˫�˶�ս");
	outtextxy(190, 220, "2.�˻���ս");
	outtextxy(190, 270, "3.�о�ģʽ");
	outtextxy(190, 320, "4.�˳���Ϸ");
}
void gameMode()
{//��ȡ�����Ϣ
	ExMessage msg;
	int gridx, gridy;
	menumusic();
	BeginBatchDraw();
	while (1) {
		menuImage();
		bkwords();
		FlushBatchDraw();
		if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSEֻ��Ҫ�����Ϣ
			op.isShow = true;
			if (msg.message == WM_LBUTTONDOWN) {
				gridx = msg.x;
				gridy = msg.y;
				if (gridx >= 170 && gridx <= 420 && gridy >= 170 && gridy < 220)
					gameMode1();
				else if (gridx >= 170 && gridx <= 420 && gridy >= 220 && gridy < 270)
					gameMode2();
				else if (gridx >= 170 && gridx <= 420 && gridy >= 270 && gridy < 320)
					gameMode3();
				else if (gridx >= 170 && gridx <= 420 && gridy >= 270 && gridy < 370)
					return;
			}
		}
	}
	//������ͼ
	EndBatchDraw();
}
//��ʼ�˵�
void menu()
{
	gameMode();
}
#pragma endregion
//���������
#pragma region
int main()
{
	initgraph(529, 529);//��������
	menu();
	return 0;
}
#pragma endregion
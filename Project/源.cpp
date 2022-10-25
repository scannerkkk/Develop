//头文件合集
#pragma region
#include "atlbase.h"
#include "atlstr.h"
#include <iostream>
#include <stdio.h>
//加载图形库文件
#include <easyx.h>
//加载windows库文件
#include <Windows.h>
//加载音乐文件
#include <mmsystem.h>
#include <conio.h>
#include <stack>
#include <map>
#include <string>
//加载winmm.lib
#pragma comment(lib,"winmm.lib")
#pragma endregion
//人物操作合集
#pragma region
//每个格子的宽度
#define GRID_W 25
//定义左和上的间隔宽度
#define INTERVAL (4 * 25)
//棋盘长度
#define ROW 15
//棋盘宽度
#define COL 15
//定义棋盘的得分情况
#define OTHER 0//0,其他棋型不考虑
#define R_DRAW 3//杀棋情况
#define R_WHITE 4
#define R_BLACK 5
#define WIN 1//100000,白赢
#define LOSE 2//-10000000
#define FLEX4 3//50000,白活4
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
//定义当前棋盘状态，AI走棋专用
int VisChess[ROW][COL];
int Chess[ROW][COL];
//6元组判断棋型 0代表无子，1代表黑方，2代表白方，3代表边界
int scoreBoard[4][4][4][4][4][4];
//定义总积分
int scoreBBS;
//定义黑方积分
int scoreblack = 100;
//定义白方积分
int scorewhite = 100;
//定义玩家和AI操作
int f = 1;
//定义残局开启状态
bool eG = false;
//定义返回状态
bool returngame2 = true, returngame1 = true, returngame3 = true;
//定义状态种类
enum class Status { None, Black, White };
//定义玩家操作状态集合
struct node {
	int x = 0;//当前操作目标横坐标
	int y = 0;//当前操作目标纵坐标
	bool isShow = false;//是否显示下棋框
	//鼠标当前所在数组对应的下标
	int row = 0;
	int col = 0;
	//棋手状态
	Status chessPlayer = Status::Black;
}op;
struct evaluation {
	long long score;
	int result;
	long long stat[20];//存杀棋
};
struct QPoint {
	int x;
	int y;
};
struct POinTS {
	QPoint pos[10];//0分数最高，9分数最低
	long long score[10];
};
struct undo {
	int x;
	int y;
};
//定义悔棋栈区
stack <undo> white;
stack <undo> black;
//定义AI操作状S态集合
struct aiNode{ int x;
int y; 
int ans; }aiOperation;
#pragma endregion
//棋盘操作合集
#pragma region
//计分函数
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
		MessageBox(GetHWnd(), s, "黑方记分牌", MB_OK);
	else
		MessageBox(GetHWnd(), s, "白方记分牌", MB_OK);
}
//悔棋操作
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
//清空栈区函数
void clearStack(stack <undo>& s)
{
	s = stack <undo>();
}
//判断棋盘满棋
bool judgeFullchess()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			if (!Chess[i][j])
				return false;
	return true;
}
//清空棋盘
void flushCheckerBoard()
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			Chess[i][j] = int(Status::None);
}
//判断赢棋
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
//绘制棋盘
void drawCheckerBoard()
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	for (int i = 0; i < 15; i++) {
		//绘制线条
		line(INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL, INTERVAL + i * GRID_W);
		line(INTERVAL + i * GRID_W, INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL);
	}
	//设置线条样式
	setlinestyle(PS_SOLID, 3);
	//绘制矩阵，加宽外框
	rectangle(INTERVAL, INTERVAL, INTERVAL + GRID_W * 14, INTERVAL + GRID_W * 14);
	//绘制下棋选择框
	if (op.isShow) {//防止出棋盘还显示下棋框
		setlinecolor(BLUE);
		rectangle(op.x - 12, op.y - 12, op.x + 12, op.y + 12);
	}
	//绘制棋子
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			switch (Chess[i][j]) {
			case 0:break;
			case 1:
				setfillcolor(BLACK);
				solidcircle(i * GRID_W + INTERVAL, j * GRID_W + INTERVAL, 10);
				break;//矩阵坐标和实际坐标相反
			case 2:
				setfillcolor(WHITE);
				solidcircle(i * GRID_W + INTERVAL, j * GRID_W + INTERVAL, 10);
				break;//矩阵坐标和实际坐标相反
			default:
				break;
			}
		}
}
#pragma endregion
//残局操作合集
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
//随机抽取残局
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
//材料合集
#pragma region
//背景音乐
void bkmusic()
{
	mciSendString("open ./bkmusic.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", NULL, 0, NULL);
}
//背景图片
void bkimage()
{
	//双缓冲绘图 让数据批量处理，不让图像闪烁
	BeginBatchDraw();
	IMAGE img_bk;//创建图片对象
	loadimage(&img_bk, "./checkerboard.jpg", 0, 0);
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(30, 10, "楷体");
	outtextxy(460, 200, "----");
	outtextxy(460, 215, "悔棋");
	outtextxy(495, 215, "|");
	outtextxy(455, 215, "|");
	outtextxy(460, 230, "----");

	outtextxy(460, 235, "----");
	outtextxy(460, 250, "认输");
	outtextxy(495, 250, "|");
	outtextxy(455, 250, "|");
	outtextxy(460, 265, "----");

	outtextxy(460, 270, "----");
	outtextxy(460, 285, "求和");
	outtextxy(495, 285, "|");
	outtextxy(455, 285, "|");
	outtextxy(460, 300, "----");

	outtextxy(15, 460, "----");
	outtextxy(15, 475, "返回");
	outtextxy(50, 475, "|");
	outtextxy(10, 475, "|");
	outtextxy(15, 490, "----");
}
//菜单音乐
void menumusic()
{
	mciSendString("open ./menumusic.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", NULL, 0, NULL);
}
//菜单背景图片
void menuImage()
{
	IMAGE img_menubk;//创建图片对象
	loadimage(&img_menubk, "./menubk.jpg", 0, 0);
	putimage(0, 0, &img_menubk);
}
#pragma endregion
//游戏实现合集
#pragma region
//鼠标操作
void mouseEvent()
{
	//定义一个消息结构体变量
	ExMessage msg;
	//获取鼠标消息
	if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSE只需要鼠标消息
		//认输
		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= 460 && msg.x <= 490 && msg.y >= 250 && msg.y < 280) {
				//清空棋子区
				clearStack(white);
				clearStack(black);
				MessageBox(GetHWnd(), "Win", op.chessPlayer == Status::White ? "黑方" : "白方", MB_OK);
				MessageBox(GetHWnd(), "重新开始", "下轮黑方先手", MB_OK);
				//棋手状态转换
				op.chessPlayer = Status::Black;
				flushCheckerBoard();
				return;
			}
			else if(msg.x >= 460 && msg.x <= 490 && msg.y >= 285 && msg.y < 315) {
				//清空棋子区
				clearStack(white);
				clearStack(black);
				MessageBox(GetHWnd(), "重新开始", "平局", MB_OK);
				MessageBox(GetHWnd(), "", "下轮黑方先手", MB_OK);
				//棋手状态转换
				op.chessPlayer = Status::Black;
				flushCheckerBoard();
				return;
			}
			else if(msg.x >= 460 && msg.x <= 490 && msg.y >= 215 && msg.y < 245) {
				//判断是否悔棋
				int check = 0;
				if (op.chessPlayer == Status::Black)
					check = popChess(white);
				else
					check = popChess(black);
				//如果没有悔棋
				if (!check) {
					MessageBox(GetHWnd(), "您还没有下棋哦>0<", "", MB_OK);
					return;
				}
				//棋手状态转换
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
		//坐标校准(自动聚焦到棋盘上某个点的中心)
		op.isShow = false;
		int intervalGridx = msg.x % GRID_W;
		int intervalGridy = msg.y % GRID_W;
		int gridx, gridy;
		//校准x坐标
		if (intervalGridx <= GRID_W / 2)
			gridx = (msg.x / GRID_W) * GRID_W;
		else
			gridx = (msg.x / GRID_W + 1) * GRID_W;
		//校准y坐标
		if (intervalGridy <= GRID_W / 2)
			gridy = (msg.y / GRID_W) * GRID_W;
		else
			gridy = (msg.y / GRID_W + 1) * GRID_W;
		//判断是否越出棋盘
		if (gridx < INTERVAL || gridy < INTERVAL ||
			gridx > INTERVAL + GRID_W * 14 || gridy > INTERVAL + GRID_W * 14)
			return;
		op.isShow = true;
		op.row = (gridx - INTERVAL) / GRID_W;
		op.col = (gridy - INTERVAL) / GRID_W;
		op.x = gridx;
		op.y = gridy;
		//左击下棋
		if (msg.message == WM_LBUTTONDOWN && Chess[op.row][op.col] == 0) {
			//棋盘状态标记
			Chess[op.row][op.col] = int(op.chessPlayer);
			if (op.chessPlayer == Status::Black)
				black.push({ op.row,op.col });
			else
				white.push({ op.row,op.col });
			drawCheckerBoard();
			FlushBatchDraw();
			//判断赢棋
			if (!eG && judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", op.chessPlayer == Status::White ? "白方" : "黑方", MB_OK);
				MessageBox(GetHWnd(), "重新开始", op.chessPlayer == Status::White ? "下轮黑方先手" : "下轮白方先手", MB_OK);
				//清空棋子栈区
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
			//残局状态
			else if(eG && judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", op.chessPlayer == Status::White ? "白方" : "黑方", MB_OK);
				MessageBox(GetHWnd(), "重新开始", op.chessPlayer == Status::Black ? "下轮黑方先手" : "下轮白方先手", MB_OK);
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
				//清空棋子栈区
				clearStack(white);
				clearStack(black);
				return;
			}
			//棋手状态转换
			op.chessPlayer = (op.chessPlayer == Status::Black ? Status::White : Status::Black);
		}
		//满棋的情况
		if (judgeFullchess()) {
			MessageBox(GetHWnd(), "和棋", "重新开始", MB_OK);
			//清空棋子栈区
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
		}
	}
}
//初始化棋型
void InitBoardScore()
{
	memset(scoreBoard, 0, sizeof(scoreBoard));
	//白连5,ai赢
	scoreBoard[2][2][2][2][2][2] = WIN;
	scoreBoard[2][2][2][2][2][0] = WIN;
	scoreBoard[0][2][2][2][2][2] = WIN;
	scoreBoard[2][2][2][2][2][1] = WIN;
	scoreBoard[1][2][2][2][2][2] = WIN;
	scoreBoard[3][2][2][2][2][2] = WIN;//边界考虑
	scoreBoard[2][2][2][2][2][3] = WIN;
	//黑连5,ai输
	scoreBoard[1][1][1][1][1][1] = LOSE;
	scoreBoard[1][1][1][1][1][0] = LOSE;
	scoreBoard[0][1][1][1][1][1] = LOSE;
	scoreBoard[1][1][1][1][1][2] = LOSE;
	scoreBoard[2][1][1][1][1][1] = LOSE;
	scoreBoard[3][1][1][1][1][1] = LOSE;
	scoreBoard[1][1][1][1][1][3] = LOSE;
	//白活4
	scoreBoard[0][2][2][2][2][0] = FLEX4;
	//黑活4
	scoreBoard[0][1][1][1][1][0] = flex4;
	//白活3
	scoreBoard[0][2][2][2][0][0] = FLEX3;
	scoreBoard[0][0][2][2][2][0] = FLEX3;
	scoreBoard[0][2][0][2][2][0] = FLEX3;
	scoreBoard[0][2][2][0][2][0] = FLEX3;
	//黑活3
	scoreBoard[0][1][1][1][0][0] = flex3;
	scoreBoard[0][0][1][1][1][0] = flex3;
	scoreBoard[0][1][0][1][1][0] = flex3;
	scoreBoard[0][1][1][0][1][0] = flex3;
	//白活2
	scoreBoard[0][2][2][0][0][0] = FLEX2;
	scoreBoard[0][2][0][2][0][0] = FLEX2;
	scoreBoard[0][2][0][0][2][0] = FLEX2;
	scoreBoard[0][0][2][2][0][0] = FLEX2;
	scoreBoard[0][0][2][0][2][0] = FLEX2;
	scoreBoard[0][0][0][2][2][0] = FLEX2;
	//黑活2
	scoreBoard[0][1][1][0][0][0] = flex2;
	scoreBoard[0][1][0][1][0][0] = flex2;
	scoreBoard[0][1][0][0][1][0] = flex2;
	scoreBoard[0][0][1][1][0][0] = flex2;
	scoreBoard[0][0][1][0][1][0] = flex2;
	scoreBoard[0][0][0][1][1][0] = flex2;
	//白活1
	scoreBoard[0][2][0][0][0][0] = FLEX1;
	scoreBoard[0][0][2][0][0][0] = FLEX1;
	scoreBoard[0][0][0][2][0][0] = FLEX1;
	scoreBoard[0][0][0][0][2][0] = FLEX1;
	//黑活1
	scoreBoard[0][1][0][0][0][0] = flex1;
	scoreBoard[0][0][1][0][0][0] = flex1;
	scoreBoard[0][0][0][1][0][0] = flex1;
	scoreBoard[0][0][0][0][1][0] = flex1;
	//六个循环枚举还没有初始化的棋型，2代表ai，1代表玩家
	for(int p1 = 0;p1 < 4;p1++)
		for (int p2 = 0; p2 < 3; p2++)
			for (int p3 = 0; p3 < 3; p3++)
				for (int p4 = 0; p4 < 3; p4++)
					for (int p5 = 0; p5 < 3; p5++)
						for (int p6 = 0; p6 < 4; p6++) {
							//统计左边五格的棋子和右边五格的棋子
							//lx代表左边五格黑子个数，rx代表右边五格黑子个数
							//ly代表左边五格白子个数，ry代表右边五格白子个数
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

							//边界情况
							if (p1 == 3 || p6 == 3) {
								//左边界情况
								if (p1 == 3 && p6 != 3) {
									//白冲四情况
									if (rx == 0 && ry == 4) 
										if(scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK4;

									//黑冲四情况
									if (ry == 0 && rx == 4)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block4;

									//白眠三
									if (rx == 0 && ry == 3) 
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK3;

									//黑眠三
									if (ry == 0 && rx == 3)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block3;
									
									//白眠二
									if (rx == 0 && ry == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK2;

									//黑眠二
									if (ry == 0 && rx == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block2;
									//白单一
									if(rx == 0 && ry == 1)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = FLEX1;

									//黑单一
									if (rx == 1 && ry == 0)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = flex1;
								}
								//右边界情况
								else if (p6 == 3 && p1 != 3) {
									//白冲4情况
									if (lx == 0 && ly == 4)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK4;

									//黑冲四情况
									if (ly == 0 && lx == 4)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block4;

									//白眠三
									if (lx == 0 && ly == 3)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block3;

									//黑眠三
									if (ly == 0 && lx == 3)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK3;

									//白眠二
									if (lx == 0 && ly == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = block2;

									//黑眠二
									if (ly == 0 && lx == 2)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK2;

									//白单一
									if (lx == 0 && ly == 1)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = FLEX1;

									//黑单一
									if (lx == 1 && ly == 0)
										if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
											scoreBoard[p1][p2][p3][p4][p5][p6] = flex1;
								}
							}
							//无边界情况
							else {
								//白冲四情况
								if ((lx == 0 && ly == 4) || (rx == 0 && ry == 4))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK4;

								//黑冲四情况
								if ((ly == 0 && lx == 4) || (ry == 0 && rx == 4))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = block4;

								//白眠三
								if ((lx == 0 && ly == 3) || (rx == 0 && ry == 3))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK3;

								//黑眠三
								if ((ly == 0 && lx == 3) || (ry == 0 && rx == 3))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = block3;

								//白眠二
								if ((lx == 0 && ly == 2) || (rx == 0 && ry == 2))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = BLOCK2;

								//黑眠二
								if ((ly == 0 && lx == 2) || (ry == 0 && rx == 2))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = block2;

								//白单一
								if ((lx == 0 && ly == 1) || (rx == 0 && ry == 1))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = FLEX1;

								//黑单一
								if ((lx == 1 && ly == 0) || (rx == 1 && ry == 0))
									if (scoreBoard[p1][p2][p3][p4][p5][p6] == 0)
										scoreBoard[p1][p2][p3][p4][p5][p6] = flex1;
							}
						}
}
//HardAI打分函数
evaluation evaluate(int chess[ROW][COL])
{
	int w[17] = {0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3};
	//给四个方向打分 横向：0  竖向：1  主对角线：2  次对角线：3
	int QiXing[4][17];
	int CopyChess[ROW + 2][COL + 2];
	memset(QiXing, 0, sizeof(QiXing));
	//给左边棋盘初始化边界
	for (int i = 0; i < 17; i++)
		CopyChess[i][0] = 3;
	//给上边棋盘初始化边界
	for (int i = 0; i < 17; i++)
		CopyChess[0][i] = 3;
	//给右边棋盘初始化边界
	for (int i = 0; i < 17; i++)
		CopyChess[i][16] = 3;
	//给下边棋盘初始化边界
	for (int i = 0; i < 17; i++)
		CopyChess[16][i] = 3;
	
	//复制当前棋盘
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			CopyChess[i + 1][j + 1] = chess[i][j];

	//给棋盘横向打分 bug?
	for(int i = 0;i <= 16;i++)
		for (int j = 0; j < 12; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i][j + 1]][CopyChess[i][j + 2]][CopyChess[i][j + 3]][CopyChess[i][j + 4]][CopyChess[i][j + 5]];
			QiXing[0][q]++;
		}

	//给棋盘纵向打分
	for (int i = 0; i < 12; i++)
		for (int j = 0; j <= 16; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i + 1][j]][CopyChess[i + 2][j]][CopyChess[i + 3][j]][CopyChess[i + 4][j]][CopyChess[i + 5][j]];
			QiXing[1][q]++;
		}

	//给棋盘主对角线打分
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i + 1][j + 1]][CopyChess[i + 2][j + 2]][CopyChess[i + 3][j + 3]][CopyChess[i + 4][j + 4]][CopyChess[i + 5][j + 5]];
			QiXing[2][q]++;
		}

	//给棋盘次对角线打分
	for (int i = 0; i < 12; i++)
		for (int j = 5; j <= 16; j++) {
			int q = scoreBoard[CopyChess[i][j]][CopyChess[i + 1][j - 1]][CopyChess[i + 2][j - 2]][CopyChess[i + 3][j - 3]][CopyChess[i + 4][j - 4]][CopyChess[i + 5][j - 5]];
			QiXing[3][q]++;
		}
	
	//开始估分
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
//对AI落子评分
void judgeRobotValue(int robotNum, int empty, int sx, int sy)
{
	int cnt = 0;
	//一连
	if (robotNum == 0)
		cnt = 5;
	//二连
	else if (robotNum == 1)
		cnt = 10;
	//三连
	else if (robotNum == 2) {
		//死三
		if (empty == 1)
			cnt = 25;
		//活三
		else if (empty == 2)
			cnt = 50;
	}
	//连四
	else if (robotNum == 3) {
		//死四
		if (empty == 1)
			cnt = 55;
		//活四
		else if (empty == 2)
			cnt = 300;
	}
	//连五
	else if (robotNum >= 4)
		cnt = 30000;
	if (cnt > aiOperation.ans) {
		aiOperation.x = sx;
		aiOperation.y = sy;
		aiOperation.ans = cnt;
	}
}
//对玩家落子评分
void judgePersonValue(int personNum,int empty,int sx,int sy)
{
	int cnt = 0;
	//连二
	if (personNum == 1) {
		cnt = 10;
	}
	//连三
	else if (personNum == 2) {
		//死三
		if (empty == 1)
			cnt = 30;
		//活三
		else if (empty == 2)
			cnt = 40;
	}
	//连四
	else if (personNum == 3) {
		//死四
		if (empty == 1)
			cnt = 60;
		//活四
		else if (empty == 2)
			cnt = 200;
	}
	//连五
	else if (personNum >= 4)
		cnt = 20000;
	if (cnt > aiOperation.ans) {
		aiOperation.x = sx;
		aiOperation.y = sy;
		aiOperation.ans = cnt;
	}
}
//判断可以下棋的位置
POinTS canPoints(int CurrentChess[ROW][COL])
{
	//定义局部标记数组
	bool visBoard[ROW][COL];
	int  score[ROW][COL];
	POinTS goodPints;
	memset(visBoard, 0, sizeof(visBoard));
	for (int i = 0; i < 10; i++)
		goodPints.pos[i].x = 0,goodPints.pos[i].y = 0;
	//每个非空点附近8个方向延伸3个深度,也就是最有可能落子
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
	//判断每个可走点的分数
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
	//选出十个最有可能走的点
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
		score[goodPints.pos[k].x][goodPints.pos[k].y] = -INT_MAX;//清除掉上一点,计算下一点的位置和分数
	}
	return goodPints;
}
//复制当前棋盘
void cpBoard(int lastBoard[ROW][COL],int curBoard[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			lastBoard[i][j] = curBoard[i][j];
}
//翻转棋盘棋子颜色
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
	//底层的时候
	evaluation gameresult = evaluate(chess);
	if (depth == 0 || gameresult.result != R_DRAW) {
		if(gameresult.result != R_DRAW)
			return gameresult.score;
		if (depth == 0) {
			POinTS P;
			P = canPoints(chess);//生成最佳的可能落子位置
			return P.score[0];//返回最佳位置对应的最高分
		}
		
	}
	//Ai操作
	else if (depth % 2 == 0) {
		POinTS P;
		int sameBoard[ROW][COL];
		cpBoard(sameBoard, chess);
		P = canPoints(sameBoard);
		for (int i = 0; i < 10; i++) {
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::White);//模拟己方落子
			int score = AiHard(depth - 1, alpha, beta,sameBoard);
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::None);//回溯还原落子
			if (score > alpha) {
				alpha = score;
				if (depth == 6) {//是个偶数即可,用来找最佳落子
					aiOperation.x = P.pos[i].x;
					aiOperation.y = P.pos[i].y;
				}
			}
			if (alpha >= beta) return alpha;//剪枝
		}
	}
	//模拟玩家操作 
	else {
		int rBoard[ROW][COL];
		reverseBoard(Chess, rBoard);
		POinTS P;
		P = canPoints(rBoard);//找对于黑子的最佳位置,需要将棋盘不同颜色反转,因为canPoint是求白色方的最佳位置
		int sameBoard[ROW][COL];
		cpBoard(sameBoard, chess);
		for (int i = 0; i < 10; i++ ) {
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::Black);//模拟敌方落子
			int score = AiHard(depth - 1, alpha, beta,sameBoard);//使用longlong是怕分数炸掉
			sameBoard[P.pos[i].x][P.pos[i].y] = int(Status::None);//回溯还原落子
			if (score < beta)beta = score;
			if (alpha >= beta) return beta;//剪枝
		}
	}
}
//初始化简单AI
void initAI()
{
	aiOperation.ans = 0;
	aiOperation.x = 0;
	aiOperation.y = 0;
	int mx[8] = { 1,-1,1,-1,0,0,1,-1 };
	int my[8] = { -1,1,1,-1,1,-1,0,0 };
	//对玩家进行评分 玩家是黑子
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
					//判断玩家落子
					dx = sx, dy = sy;
					for (int z = 0; z < 5;z++) {
						dx = dx + mx[2 * k];
						dy = dy + my[2 * k];
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//碰到AI棋子就退出
						if (Chess[dx][dy] == 2) {
							break;
						}
						//空格情况退出
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
						//越界情况退出
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//碰到AI棋子就退出
						if (Chess[dx][dy] == 2) {
							break;
						}
						//碰到空格退出
						if (Chess[dx][dy] == 0) {
							empty++;
							break;
						}
						personNum++;
					}
					judgePersonValue(personNum,empty,sx,sy);
					//初始化搜索状态
					empty = 0;
					dx = sx,dy = sy;
					//判断AI落子
					for (int z = 0; z < 5;z++) {
						dx = dx + mx[2 * k];
						dy = dy + my[2 * k];
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//碰到玩家棋子就退出
						if (Chess[dx][dy] == 1) {
							break;
						}
						//空格情况退出
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
						//越界情况退出
						if (dx < 0 || dy < 0 || dx >= 15 || dy >= 15)
							break;
						//碰到玩家棋子就退出
						if (Chess[dx][dy] == 1) {
							break;
						}
						//碰到空格退出
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
//简单AI
void aiEvent1()
{
	if (f == -1) {
		initAI();
		//AI选择框不显示
		op.isShow = false;
		op.row = aiOperation.x;
		op.col = aiOperation.y;
		op.x = op.row * GRID_W + INTERVAL;
		op.y = op.col * GRID_W + INTERVAL;
		//AI下棋
		if (Chess[op.row][op.col] == 0) {
			//棋盘状态标记
			Chess[op.row][op.col] = 2;
			white.push({ op.row,op.col });
			drawCheckerBoard();
			FlushBatchDraw();
			//判断赢棋
			if (judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", "AI", MB_OK);
				MessageBox(GetHWnd(), "重新开始", "下轮玩家先手", MB_OK);
				clearStack(white);
				clearStack(black);
				flushCheckerBoard();
				//输给简单人机减2分
				scoreBBS -= 2;
				if (scoreBBS < 0)
					scoreBBS = 0;
				OutputScore(1,scoreBBS);
			}
			//棋手状态转换
			op.chessPlayer = Status::Black;
			f = 1;
		}
		//满棋的情况
		if (judgeFullchess()) {
			MessageBox(GetHWnd(), "和棋", "重新开始", MB_OK);
			clearStack(white);
			clearStack(black);
			op.chessPlayer = Status::Black;
			f = 1;
			flushCheckerBoard();
		}
	}
	else {
		//定义一个消息结构体变量
		ExMessage msg;
		//获取鼠标消息
		if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSE只需要鼠标消息
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= 460 && msg.x <= 490 && msg.y >= 250 && msg.y < 280) {
					//清空棋子区
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "Win", "AI", MB_OK);
					MessageBox(GetHWnd(), "重新开始", "下轮玩家先手", MB_OK);
					//棋手状态转换
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 285 && msg.y < 315) {
					//清空棋子区
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "重新开始", "平局", MB_OK);
					MessageBox(GetHWnd(), "", "下轮黑方先手", MB_OK);
					//棋手状态转换
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 215 && msg.y < 245) {
					//判断是否悔棋
					int check = 0;
					check = popChess(black);
					check = popChess(white);
					//如果没有悔棋
					if (!check) {
						MessageBox(GetHWnd(), "您还没有下棋哦>0<", "", MB_OK);
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
			//坐标校准(自动聚焦到棋盘上某个点的中心)
			op.isShow = false;
			int intervalGridx = msg.x % GRID_W;
			int intervalGridy = msg.y % GRID_W;
			int gridx, gridy;
			//校准x坐标
			if (intervalGridx <= GRID_W / 2)
				gridx = (msg.x / GRID_W) * GRID_W;
			else
				gridx = (msg.x / GRID_W + 1) * GRID_W;
			//校准y坐标
			if (intervalGridy <= GRID_W / 2)
				gridy = (msg.y / GRID_W) * GRID_W;
			else
				gridy = (msg.y / GRID_W + 1) * GRID_W;
			//判断是否越出棋盘
			if (gridx < INTERVAL || gridy < INTERVAL ||
				gridx > INTERVAL + GRID_W * 14 || gridy > INTERVAL + GRID_W * 14)
				return;
			op.isShow = true;
			op.row = (gridx - INTERVAL) / GRID_W;
			op.col = (gridy - INTERVAL) / GRID_W;
			op.x = gridx;
			op.y = gridy;
			//左击下棋
			if (msg.message == WM_LBUTTONDOWN && Chess[op.row][op.col] == 0) {
				//棋盘状态标记
				Chess[op.row][op.col] = 1;
				black.push({ op.row,op.col });
				drawCheckerBoard();
				FlushBatchDraw();
				//判断赢棋
				if (judgeWinner(op.row, op.col)) {
					MessageBox(GetHWnd(), "Win", "玩家", MB_OK);
					MessageBox(GetHWnd(), "重新开始", "下轮玩家先手", MB_OK);
					clearStack(white);
					clearStack(black);
					op.chessPlayer = Status::Black;
					f = 1;
					flushCheckerBoard();
					//赢简单人机加5分
					scoreBBS += 5;
					OutputScore(1, scoreBBS);
					return;
				}
				//棋手状态转换
				op.chessPlayer = Status::White;
				f = -1;
			}
			//满棋的情况
			if (judgeFullchess()) {
				MessageBox(GetHWnd(), "和棋", "重新开始", MB_OK);
				clearStack(white);
				clearStack(black);
				op.chessPlayer = Status::Black;
				f = 1;
				flushCheckerBoard();
			}
		}
	}
}
//困难AI
void aiEvent2()
{
	if (f == -1) {
		AiHard(6, -INT_MAX, INT_MAX, Chess);
		//AI选择框不显示
		op.isShow = false;
		op.row = aiOperation.x;
		op.col = aiOperation.y;
		op.x = op.row * GRID_W + INTERVAL;
		op.y = op.col * GRID_W + INTERVAL;
		//AI下棋
		if (Chess[op.row][op.col] == 0) {
			//棋盘状态标记
			Chess[op.row][op.col] = 2;
			white.push({ op.row,op.col });
			drawCheckerBoard();
			FlushBatchDraw();
			//判断赢棋
			if (judgeWinner(op.row, op.col)) {
				MessageBox(GetHWnd(), "Win", "AI", MB_OK);
				MessageBox(GetHWnd(), "重新开始", "下轮玩家先手", MB_OK);
				clearStack(white);
				clearStack(black);
				flushCheckerBoard();
				//输给困难人机减5分
				scoreBBS -= 5;
				if (scoreBBS < 0)
					scoreBBS = 0;
				OutputScore(1,scoreBBS);
			}
			//棋手状态转换
			op.chessPlayer = Status::Black;
			f = 1;
		}
		//满棋的情况
		if (judgeFullchess()) {
			MessageBox(GetHWnd(), "和棋", "重新开始", MB_OK);
			clearStack(white);
			clearStack(black);
			op.chessPlayer = Status::Black;
			f = 1;
			flushCheckerBoard();
		}
	}
	else {
		//定义一个消息结构体变量
		ExMessage msg;
		//获取鼠标消息
		if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSE只需要鼠标消息
			if (msg.message == WM_LBUTTONDOWN) {
				if (msg.x >= 460 && msg.x <= 490 && msg.y >= 250 && msg.y < 280) {
					//清空棋子区
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "Win", "AI", MB_OK);
					MessageBox(GetHWnd(), "重新开始", "下轮玩家先手", MB_OK);
					//棋手状态转换
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 285 && msg.y < 315) {
					//清空棋子区
					clearStack(white);
					clearStack(black);
					MessageBox(GetHWnd(), "重新开始", "平局", MB_OK);
					MessageBox(GetHWnd(), "", "下轮黑方先手", MB_OK);
					//棋手状态转换
					op.chessPlayer = Status::Black;
					flushCheckerBoard();
					return;
				}
				else if (msg.x >= 460 && msg.x <= 490 && msg.y >= 215 && msg.y < 245) {
					//判断是否悔棋
					int check = 0;
					check = popChess(black);
					check = popChess(white);	
					//如果没有悔棋
					if (!check) {
						MessageBox(GetHWnd(), "您还没有下棋哦>0<", "", MB_OK);
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
			//坐标校准(自动聚焦到棋盘上某个点的中心)
			op.isShow = false;
			int intervalGridx = msg.x % GRID_W;
			int intervalGridy = msg.y % GRID_W;
			int gridx, gridy;
			//校准x坐标
			if (intervalGridx <= GRID_W / 2)
				gridx = (msg.x / GRID_W) * GRID_W;
			else
				gridx = (msg.x / GRID_W + 1) * GRID_W;
			//校准y坐标
			if (intervalGridy <= GRID_W / 2)
				gridy = (msg.y / GRID_W) * GRID_W;
			else
				gridy = (msg.y / GRID_W + 1) * GRID_W;
			//判断是否越出棋盘
			if (gridx < INTERVAL || gridy < INTERVAL ||
				gridx > INTERVAL + GRID_W * 14 || gridy > INTERVAL + GRID_W * 14)
				return;
			op.isShow = true;
			op.row = (gridx - INTERVAL) / GRID_W;
			op.col = (gridy - INTERVAL) / GRID_W;
			op.x = gridx;
			op.y = gridy;
			//左击下棋
			if (msg.message == WM_LBUTTONDOWN && Chess[op.row][op.col] == 0) {
				//棋盘状态标记
				Chess[op.row][op.col] = 1;
				black.push({ op.row,op.col });
				drawCheckerBoard();
				FlushBatchDraw();
				//判断赢棋
				if (judgeWinner(op.row, op.col)) {
					MessageBox(GetHWnd(), "Win", "玩家", MB_OK);
					MessageBox(GetHWnd(), "重新开始", "下轮玩家先手", MB_OK);
					clearStack(white);
					clearStack(black);
					op.chessPlayer = Status::Black;
					f = 1;
					flushCheckerBoard();
					//赢困难人机加20分
					scoreBBS += 20;
					OutputScore(1,scoreBBS);
					return;
				}
				//棋手状态转换
				op.chessPlayer = Status::White;
				f = -1;
			}
			//满棋的情况
			if (judgeFullchess()) {
				MessageBox(GetHWnd(), "和棋", "重新开始", MB_OK);
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
//游戏模式合集
#pragma region
//双人对战
void gameMode1()
{
	bkmusic();
	returngame1 = false;
	BeginBatchDraw();
	while (1)
	{
		//清屏
		cleardevice();
		//加载图片
		bkimage();
		//绘制棋盘
		drawCheckerBoard();
		//鼠标操作
		mouseEvent();
		//刷新
		FlushBatchDraw();
		//判断是否返回
		if (returngame1 == true) {
			//清屏
			cleardevice();
			//MessageBox(GetHWnd(), "welcome !", "hello", MB_OK);
			op.chessPlayer = Status::Black;
			f = 1;
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
			//重新开始计分
			scoreblack = 100;
			scorewhite = 100;
			return;
		}
	}
	//结束绘图
	EndBatchDraw();
}
//简单人机模式
void AIgameMode1()
{
	bkmusic();
	returngame2 = false;
	BeginBatchDraw();
	while (1)
	{
		//清屏
		cleardevice();
		//加载图片
		bkimage();
		//绘制棋盘
		drawCheckerBoard();
		//人机操作
		aiEvent1();
		//刷新
		FlushBatchDraw();
		if (returngame2 == true) {
			//清屏
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
	//结束绘图
	EndBatchDraw();
}
//困难人机模式
void AIgameMode2()
{
	InitBoardScore();
	bkmusic();
	BeginBatchDraw();
	returngame2 = false;
	while (1)
	{
		//清屏
		cleardevice();
		//加载图片
		bkimage();
		//绘制棋盘
		drawCheckerBoard();
		//人机操作
		aiEvent2();
		//刷新
		FlushBatchDraw();
		if (returngame2 == true) {
			//清屏
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
	//结束绘图
	EndBatchDraw();
}
//人机菜单
void Aimenu()
{
	menuImage();
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(50, 15, "楷体");
	outtextxy(190, 220, "1.简单模式");
	outtextxy(190, 270, "2.困难模式");
	settextcolor(BLUE);
	settextstyle(30, 10, "楷体");
	outtextxy(15, 460, "----");
	outtextxy(15, 475, "返回");
	outtextxy(50, 475, "|");
	outtextxy(10, 475, "|");
	outtextxy(15, 490, "----");
}
//人机对战
void gameMode2()
{
	Aimenu();
	//获取鼠标消息
	ExMessage msg1;
	int gridx, gridy;
	BeginBatchDraw();
	while (1) {
		Aimenu();
		FlushBatchDraw();
		if (peekmessage(&msg1, EM_MOUSE)) {//EM_MOUSE只需要鼠标消息
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
		//清空计分牌
		scoreBBS = 0;
	}
	EndBatchDraw();
}
//残局
void gameMode3()
{
	bkmusic();
	//开启残局模式
	eG = true;
	returngame3 = false;
	chooseEndgame();
	BeginBatchDraw();
	while (1)
	{
		//清屏
		cleardevice();
		//加载图片
		bkimage();
		//绘制棋盘
		drawCheckerBoard();
		//鼠标操作
		mouseEvent();
		//刷新
		FlushBatchDraw();
		//是否返回
		if (returngame3 == true) {
			//清屏
			cleardevice();
			op.chessPlayer = Status::Black;
			f = 1;
			clearStack(white);
			clearStack(black);
			flushCheckerBoard();
			eG = false;
			//重新开始计分
			scoreblack = 100;
			scorewhite = 100;
			return;
		}
	}
	//结束绘图
	EndBatchDraw();
}
#pragma endregion
//游戏指引合集
#pragma region
//游戏模式
void bkwords()
{
	// 设置背景为透明
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(50, 15, "楷体");
	outtextxy(190, 120, "  游戏菜单");
	outtextxy(190, 170, "1.双人对战");
	outtextxy(190, 220, "2.人机对战");
	outtextxy(190, 270, "3.残局模式");
	outtextxy(190, 320, "4.退出游戏");
}
void gameMode()
{//获取鼠标消息
	ExMessage msg;
	int gridx, gridy;
	menumusic();
	BeginBatchDraw();
	while (1) {
		menuImage();
		bkwords();
		FlushBatchDraw();
		if (peekmessage(&msg, EM_MOUSE)) {//EM_MOUSE只需要鼠标消息
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
	//结束绘图
	EndBatchDraw();
}
//开始菜单
void menu()
{
	gameMode();
}
#pragma endregion
//主程序入口
#pragma region
int main()
{
	initgraph(529, 529);//创建窗口
	menu();
	return 0;
}
#pragma endregion
//引入头文件
#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")

//声明Bottom按键结构体
typedef struct Bottom
{
	int x1, y1, x2, y2, m;
}BTM;
//声明函数
//界面函数
void StartMenu();		//游戏开始界面	1模式选择 2游戏说明 3游戏设置
void MoudleMenu();		//模式选择界面	1双人对战 2人机对战 3联网对战
void ChooseMoudle();	//选择模式
void Introduce(MOUSEMSG m);		//游戏说明界面
void SetMenu();			//游戏设置界面	棋盘，棋子，背景音乐，图片
void PauseMenu();		//游戏暂停界面	1继续游戏 2游戏存档 3返回主界面
void GameOver(int win);		//游戏结束画面	胜利/失败画面；1再来一局；2主界面（开始界面） 
void GMDouble();		//双人对战
void GMRebot();			//人机对战
void GMConNet();		//联网对战

//绘制部件
void DrawGobang();		//绘制棋盘
void DrawBottom(int x1, int y1, BTM *btm, int m , LPCTSTR words);			//按键
void DrawBottom(int x1, int y1, BTM *btm, LPCTSTR words);
void DrawBottom(int x1, int y1, LPCTSTR words);
void DrawSwitch(int x1, int x2, int y1, int y2, char[20]);			//开关
bool isClickSwitch();
void Choose();			//选择
void MousePoint();		//按键特效



//SetMenu()子函数
void SetBoradSize();		//设置棋盘大小
void SetBoradShape();		//设置棋盘形状
void SetBGImage(LPCTSTR SBGIPath);		//设置背景图片
void SetBGMusic();			//设置背景音乐
void SetPieceSize(int r);	//设置圆棋大小
void SetPieceShape();		//设置棋子形状	圆形 椭圆形 矩形 梯形 菱形 三角形
void SetRecord();			//设置自动存档

//游戏逻辑算法函数
void PlayChess(MOUSEMSG m, int* f);		//下棋并判断输赢
int judgewin(int a, int b);	//判断输赢 赢就返回1，没有就返回0，游戏继续；
void GameRecord(int WR);	//游戏存取档 WR为1则存档，为2则读档
void Repentance();			//按键悔棋


//声明全局变量
int InterfaceWidth = 1000;
int InterfaceHeight = 650;
const int BoardX=15, BoardY=15;
int board[BoardX][BoardY] = { 0 };	//0表示没有下棋的状态
int x, y;							//坐标

LPCTSTR startBGIPath;				//	startBGIPath = L"背景1.jpg";
//char SBGIPath  ;
int gameMoudle = 0;


struct Bottom back;
BTM b1;
bool isClickBottom(BTM b, MOUSEMSG m1);
bool isGameOver = false;

//主函数
int main()
{
	while (1) {

		StartMenu();
		ChooseMoudle();
		
	}
}


//函数定义

void MousePoint()		//鼠标点击特效
{
	MOUSEMSG m1;//鼠标指针

	m1 = GetMouseMsg();//获取一条鼠标消息

	for (int i = 0; i <= 10; i++)
	{
		setrop2(R2_NOTXORPEN);		//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
		setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
		circle(m1.x, m1.y, 2 * i);  
		Sleep(25);					//停顿25ms
		circle(m1.x, m1.y, 2 * i);  //抹去刚刚画的圆
	}
	setrop2(R2_COPYPEN);
	FlushMouseMsgBuffer();//清空鼠标消息缓存区	
}

void StartMenu()
{
	LPCTSTR sbgi = L"背景1.jpg" ;
	SetBGImage(sbgi);	//startBGIPath = L"背景1.jpg";
	
	IMAGE BG_Start;
	MOUSEMSG msg;

	mciSendString(L"open timi.mp3", 0, 0, 0);	//打开音乐
	mciSendString(L"play timi.mp3", 0, 0, 0);	//播放音乐
	//Sleep(3000);
	initgraph(InterfaceWidth, InterfaceHeight);
	cleardevice();
	loadimage(&BG_Start,startBGIPath);		//loadimage(NULL, L"背景1.jpg");
	putimage(0, 0, &BG_Start);

	settextstyle(60, 30, _T("隶书"));
	settextcolor(DARKGRAY);
	setbkmode(TRANSPARENT);
	outtextxy(200, 100, L"欢迎来到欢乐五子棋!");
	settextstyle(40, 20, _T("楷体"));
	setlinecolor(LIGHTGRAY);
	setfillstyle(BS_NULL);
	fillroundrect(330, 245, 610, 330, 20, 20);
	outtextxy(370, 270, L"1.选择模式");
	fillroundrect(330, 345, 610, 430, 20, 20);
	outtextxy(370, 370, L"2.游戏说明");
	fillroundrect(330, 445, 610, 530, 20, 20);
	outtextxy(370, 470, L"3.游戏设置");
	FlushBatchDraw();
	gameMoudle = 0;
	isGameOver = false;
	while (1)
	{
		msg = GetMouseMsg();
		
		if (msg.x > 330 && msg.y > 245 && msg.x < 610 && msg.y < 330)	//选择模式
		{
			settextstyle(40, 20, _T("楷体"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			outtextxy(370, 270, L"1.选择模式");
			if (msg.mkLButton)
			{
				MousePoint();
				closegraph();
				FlushMouseMsgBuffer();	//清空鼠标消息缓存区
				MoudleMenu();			//进入选择模式
				break;
			}
		}
		else if (msg.x > 330 && msg.y > 345 && msg.x < 610 && msg.y < 430)	//游戏说明
		{
			settextstyle(40, 20, _T("楷体"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 345, 610, 430, 20, 20);
			outtextxy(370, 370, L"2.游戏说明");

			if(msg.mkLButton)
			{
				MousePoint();
				FlushMouseMsgBuffer();	//清空鼠标消息缓存区
				Introduce(msg);		//进入游戏说明
				break;
			}
		}
		else if (msg.x > 330 && msg.y > 445 && msg.x < 610 && msg.y < 530)	//退出游戏
		{
			settextstyle(40, 20, _T("楷体"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 445, 610, 530, 20, 20);
			outtextxy(370, 470, L"3.游戏设置");
			if (msg.mkLButton)
			{
				MousePoint();
				FlushMouseMsgBuffer();	//清空鼠标消息缓存区
				SetMenu();				//进入游戏设置
				break;
			}
		}
		else
		{
			if (msg.mkLButton)
				MousePoint();
			settextcolor(DARKGRAY);
			settextstyle(40, 20, _T("楷体"));
			outtextxy(370, 270, L"1.选择模式");
			outtextxy(370, 370, L"2.游戏说明");
			outtextxy(370, 470, L"3.游戏设置");
			setlinecolor(LIGHTGRAY);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			fillroundrect(330, 345, 610, 430, 20, 20);
			fillroundrect(330, 445, 610, 530, 20, 20);

		}
	}
	mciSendString(L"close timi.mp3", 0, 0, 0);	//停放音乐
}

void ChooseMoudle()			//选择模式
{
	switch (gameMoudle) {
	case 1://双人对战
		GMDouble();
		break;
	case 2://人机对战

		break;
	case 3://联网对战

		break;
	default:
		//请重新选择
		break;
	}
}


void MoudleMenu()
{

	IMAGE BG_Start;
	MOUSEMSG msg;

	initgraph(InterfaceWidth, InterfaceHeight);
	cleardevice();
	loadimage(&BG_Start, startBGIPath);		//loadimage(NULL, L"背景1.jpg");
	putimage(0, 0, &BG_Start);

	settextstyle(60, 30, _T("隶书"));
	settextcolor(DARKGRAY);
	setbkmode(TRANSPARENT); 
	outtextxy(250, 100, L"请选择游戏模式!");
	settextstyle(40, 20, _T("楷体"));
	setlinecolor(LIGHTGRAY);
	setfillstyle(BS_NULL);
	fillroundrect(330, 245, 610, 330, 20, 20);
	outtextxy(370, 270, L"1.双人对战");
	fillroundrect(330, 345, 610, 430, 20, 20);
	outtextxy(370, 370, L"2.人机对战");
	fillroundrect(330, 445, 610, 530, 20, 20);
	outtextxy(370, 470, L"3.联网对战");
	settextcolor(BLUE);
	BTM back1;
	DrawBottom(10, 10, &back1, 10, L"返回");
	FlushBatchDraw();

	//FlushMouseMsgBuffer();//清空鼠标消息缓存区
	while (1)
	{
		FlushMouseMsgBuffer();//清空鼠标消息缓存区
		msg = GetMouseMsg();

		if (msg.mkLButton)
			MousePoint();
		if (msg.x > 330 && msg.y > 245 && msg.x < 610 && msg.y < 330)	//1.双人对战
		{
			settextstyle(40, 20, _T("楷体"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			outtextxy(370, 270, L"1.双人对战");
			if (msg.mkLButton)
			{
				//MousePoint();
				closegraph();			//结束选择模式，进入双人对战
				gameMoudle = 1;
				FlushMouseMsgBuffer();	//清空鼠标消息缓存区	
				break;
			}

		}
		else if (msg.x > 330 && msg.y > 345 && msg.x < 610 && msg.y < 430)	//2.人机对战
		{
			settextstyle(40, 20, _T("楷体"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 345, 610, 430, 20, 20);
			outtextxy(370, 370, L"2.人机对战");

			if (msg.mkLButton)
			{
				MousePoint();
				gameMoudle = 2;
				FlushMouseMsgBuffer();
				break;
			}
		}
		else if (msg.x > 330 && msg.y > 445 && msg.x < 610 && msg.y < 530)	//3.联网对战
		{
			settextstyle(40, 20, _T("楷体"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 445, 610, 530, 20, 20);
			outtextxy(370, 470, L"3.联网对战");
			if (msg.mkLButton)
			{
				MousePoint();
				gameMoudle = 3;
				FlushMouseMsgBuffer();
				exit(0);
			}
		}
		else if(isClickBottom(back1,msg) == 1)
		{
			//测试 outtextxy(100, 100, L"click");
			//FlushMouseMsgBuffer();
			break;	//-->StartMenu();	
		}
		else
		{
			
			
			//isClickBottom(back1);
			settextcolor(DARKGRAY);
			settextstyle(40, 20, _T("楷体"));
			outtextxy(370, 270, L"1.双人对战");
			outtextxy(370, 370, L"2.人机对战");
			outtextxy(370, 470, L"3.联网对战");
			setlinecolor(LIGHTGRAY);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			fillroundrect(330, 345, 610, 430, 20, 20);
			fillroundrect(330, 445, 610, 530, 20, 20);
			
		}
	}
}

void Introduce(MOUSEMSG m)
{
	IMAGE bgp;
	initgraph(InterfaceWidth, InterfaceHeight);
	//cleardevice();
	setbkmode(TRANSPARENT);
	loadimage(&bgp, L"yxsm.jpg");
	BeginBatchDraw();
	putimage(0, 0, &bgp, SRCCOPY);

	settextstyle(25, 12, _T("隶书"));
	setfillstyle(BS_NULL);
	settextcolor(BLUE);
	BTM back;
	DrawBottom(10, 10, &back, L"返回");
	EndBatchDraw();

	FlushBatchDraw();

	while (1)
	{
		int backY = isClickBottom(back,m);
		
		 if (backY == 1)
		 {
			 break;//-->StartMenu();
		}
		
	}
}


void SetMenu()
{

}

void PauseMenu()
{

}

void GameOver(int win)
{
	if (win == 5)
	{
		isGameOver = true;
		settextcolor(RED);
		fillroundrect(248, 453, 752, 602, 20, 20);
		setfillcolor(LIGHTCYAN);
		fillroundrect(250, 455, 750, 600, 20, 20);
		settextstyle(70, 40, _T("隶书"));
		outtextxy(350, 465, L"游戏结束");
		while (1)
		{
			BTM backstartmenu, restart;
			settextstyle(30, 20, _T("隶书"));
			DrawBottom(325, 550, &backstartmenu, 10, L"结束游戏");
			DrawBottom(525, 550, &restart, 10, L"再来一局");
			MOUSEMSG m2;
			m2 = GetMouseMsg();
			
			if (isClickBottom(backstartmenu, m2) == 1)
			{
				break;
			}
			if (isClickBottom(restart, m2) == 1)
			{
				FlushMouseMsgBuffer();
				GMDouble();
				break;
			}
			if (m2.mkLButton)
			{
				MousePoint();
			}
		}
	}
}

void DrawGobang()
{
	setlinecolor(LIGHTGRAY);
	line(600,8,600,650);		// 画分割线
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0, m = 30;
	for (int lineN = 1; lineN <= 15; lineN++)
	{
		//MousePoint();
		
		setlinecolor(BLUE);
		settextstyle(20, 10, _T("Times New Roman"));
		//for (int x1, y1, x2, y2;)
		x1 = m * lineN, y1 = m, x2 = m * lineN, y2 = m * 15;	//竖线
		line(x1,y1,x2,y2);
		//outtextxy(m*lineN, m-5,(char)lineN);
		x1 = m, y1 = m * lineN, x2 = m * 15, y2 = m * lineN;	//横线
		line(x1, y1, x2, y2);
		//outtextxy(m-5, m*lineN, (char)lineN);
		int s = (lineN - 7) * (lineN - 7);
		Sleep(3*s);
	}
	int wx = 470, wy = 16;
	settextcolor(LIGHTGRAY);
	settextstyle(80, 40, _T("隶书"));
	outtextxy(wx, wy, L"欢"); wy += 90;
	outtextxy(wx, wy, L"乐"); wy += 90;
	outtextxy(wx, wy, L"五"); wy += 90;
	outtextxy(wx, wy, L"子"); wy += 90;
	outtextxy(wx, wy, L"棋");

	settextstyle(25, 12, _T("隶书"));
	DrawBottom(800, 40, &b1, 10, L"游戏快乐!");
}

void GMDouble()
{
	IMAGE bgp;
	initgraph(InterfaceWidth, InterfaceHeight);
	setbkmode(TRANSPARENT);
	loadimage(&bgp, L"yxsm.jpg");
	
	putimage(0, 0, &bgp, SRCCOPY);
	settextstyle(25, 12, _T("隶书"));
	setfillstyle(BS_NULL);
	settextcolor(BLUE);
	//DrawBottom(10, 10, L"返回");
	int f = 0;  
	for (int ix = 0; ix < BoardX; ix++)		
		for (int jy = 0; jy < BoardY; jy++)
			board[ix][jy] = 0;
		
	DrawGobang();

	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			MousePoint(); 
			//测试	outtextxy(f*10, f*10, L"FF"); 
			f += 1;
			PlayChess(m,&f);
			if (isGameOver)
			{
				isGameOver = false;
				break;
			}
		}

		/*if (isClickBottom(b1) == 1)
		{
			MoudleMenu();
			break;
		}*/
	}
}

void GMRebot()
{

}

void GMConNet()
{

}
//不用
void DrawBottom(int x1, int y1,LPCTSTR words)
{
	Bottom btms;
	int m1 = textwidth(words);
	int n = textwidth(words) / (10* _tcslen(words));
	int x2 = x1 + textwidth(words) + n;
	int y2 = y1 + textheight(words) + n;
	btms.x1 = x1 - n;
	btms.y1 = y1 - n;
	btms.x2 = x2;
	btms.y2 = y2;
	setfillstyle(BS_NULL);
	outtextxy(x1,y1,words);
	fillroundrect(x1-n,y1-n, x2, y2,20,20);
	
}
//
void DrawBottom(int x1, int y1, BTM *btm, LPCTSTR words)
{
	int m1 = textwidth(words);
	int n = textwidth(words) / (10 * _tcslen(words));
	int x2 = x1 + textwidth(words) + n;
	int y2 = y1 + textheight(words) + n;
	btm->x1 = x1 - n;
	btm->y1 = y1 - n;
	btm->x2 = x2;
	btm->y2 = y2;
	setfillstyle(BS_NULL);
	outtextxy(x1, y1, words);
	fillroundrect(x1 - n, y1 - n, x2, y2, 20, 20);
}


void DrawBottom(int x1, int y1, BTM *btm, int m, LPCTSTR words)
{
	int m1 = textwidth(words);
	int x2 = x1 + textwidth(words) + m;
	int y2 = y1 + textheight(words) + m;
	
	btm->x1 = (x1 - m);
	btm->y1 = y1 - m;
	btm->x2 = x2;
	btm->y2 = y2;
	btm->m = m;
	setfillstyle(BS_NULL);
	outtextxy(x1, y1, words);
	fillroundrect(x1 - m, y1 - m, x2, y2, 20, 20);
}

bool isClickBottom(BTM b, MOUSEMSG m1)
{
	//MOUSEMSG m1;
	//back = b;
	m1 = GetMouseMsg();
	if (m1.x > b.x1 && m1.y > b.y1 && m1.x < b.x2 && m1.y < b.y2)
	{
		setlinecolor(RED);
		setfillstyle(BS_NULL);
		fillroundrect(b.x1, b.y1, b.x2, b.y2, 20, 20);
		//测试 outtextxy(b.x2,b.y2, L"inclickbtm");
		if (m1.mkLButton)
		{
			//测试 outtextxy(200, 200, L"isclickbtm");
			MousePoint();
			return 1;
		}
	}
	else
	{
		//测试 outtextxy(b.x1,b.y1, L"notclickbtm");
		setlinecolor(DARKGRAY);
		setfillstyle(BS_NULL);
		fillroundrect(b.x1, b.y1, b.x2, b.y2, 20, 20);
		return 0;
	}
	FlushMouseMsgBuffer();
	return 0;
}

void Choose()
{

}

void PlayChess(MOUSEMSG m, int *f)
{
	//setfillcolor(RED);
	*f % 2 == 1 ? setfillcolor(RED) : setfillcolor(YELLOW);
	setfillstyle(BS_SOLID);
	if (m.x > 25 && m.y > 25 && m.x < 455 && m.y < 455)
	{
		int px = (int)((m.x / 30.0) + 0.5);
		int py = (int)((m.y / 30.0) + 0.5);
		int win1 = 0, win2 = 0, win3 = 0, win4 = 0;
		if (board[px][py] == 0)
		{
			board[px][py] = (*f % 2)+1;
			solidcircle(px * 30, py * 30, 13);
			
			for (int i = 1; i <= 10; i++)	//判断输赢
			{
				(board[px][py - 6 + i] == (*f % 2) + 1) ? win1++ : win1 = 0;
				GameOver(win1);
				(board[px - 6 + i][py] == (*f % 2) + 1) ? win2++ : win2 = 0;
				GameOver(win2);
				(board[px - 6 + i][py - 6 + i] == (*f % 2) + 1) ? win3++ : win3 = 0;
				GameOver(win3);
				(board[px + 6 - i][py - 6 + i] == (*f % 2) + 1) ? win4++ : win4 = 0;
				GameOver(win4);
			}
		}
		else
		{
			setrop2(R2_NOTXORPEN);
			outtextxy(200, 600, L"此处有棋，请重新下棋");
			*f -= 1;
			Sleep(2000);
			outtextxy(200, 600, L"此处有棋，请重新下棋");
			setrop2(R2_COPYPEN);
			/*HWND hwnd;
			MessageBox(hwnd,)*/
		}
	}
	else
	{
		*f -= 1;
	}
}

void DrawSwitch(int x1, int x2, int y1, int y2, char[20])
{

}

void SetBoradSize()
{

}

void SetBoradShape()
{

}

void SetBGImage(LPCTSTR SBGIPath)
{
	startBGIPath = SBGIPath;
}

void SetBGMusic()
{

}

void SetPieceSize(int r)
{

}

void SetPieceShape()
{

}

void SetRecord()
{

}

void pash(int a, int b)
{

}

int judgewin(int a, int b)
{
	int win = 0;
	for (int i = 1; i <= 10; i++)
	{
		(board[a][b - 6 + i] == 1) ? win++ : win = 0;
		if (win == 5)
		{
			settextcolor(RED);
			settextstyle(50, 30, _T("隶书"));
			outtextxy(200, 300, L"游戏结束");
		}
	}
	return 0;
}

void GameRecord(int WR)
{

}

void Repentance()
{

}


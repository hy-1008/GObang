//����ͷ�ļ�
#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include <conio.h>
#pragma comment(lib,"winmm.lib")

//����Bottom�����ṹ��
typedef struct Bottom
{
	int x1, y1, x2, y2, m;
}BTM;
//��������
//���溯��
void StartMenu();		//��Ϸ��ʼ����	1ģʽѡ�� 2��Ϸ˵�� 3��Ϸ����
void MoudleMenu();		//ģʽѡ�����	1˫�˶�ս 2�˻���ս 3������ս
void ChooseMoudle();	//ѡ��ģʽ
void Introduce(MOUSEMSG m);		//��Ϸ˵������
void SetMenu();			//��Ϸ���ý���	���̣����ӣ��������֣�ͼƬ
void PauseMenu();		//��Ϸ��ͣ����	1������Ϸ 2��Ϸ�浵 3����������
void GameOver(int win);		//��Ϸ��������	ʤ��/ʧ�ܻ��棻1����һ�֣�2�����棨��ʼ���棩 
void GMDouble();		//˫�˶�ս
void GMRebot();			//�˻���ս
void GMConNet();		//������ս

//���Ʋ���
void DrawGobang();		//��������
void DrawBottom(int x1, int y1, BTM *btm, int m , LPCTSTR words);			//����
void DrawBottom(int x1, int y1, BTM *btm, LPCTSTR words);
void DrawBottom(int x1, int y1, LPCTSTR words);
void DrawSwitch(int x1, int x2, int y1, int y2, char[20]);			//����
bool isClickSwitch();
void Choose();			//ѡ��
void MousePoint();		//������Ч



//SetMenu()�Ӻ���
void SetBoradSize();		//�������̴�С
void SetBoradShape();		//����������״
void SetBGImage(LPCTSTR SBGIPath);		//���ñ���ͼƬ
void SetBGMusic();			//���ñ�������
void SetPieceSize(int r);	//����Բ���С
void SetPieceShape();		//����������״	Բ�� ��Բ�� ���� ���� ���� ������
void SetRecord();			//�����Զ��浵

//��Ϸ�߼��㷨����
void PlayChess(MOUSEMSG m, int* f);		//���岢�ж���Ӯ
int judgewin(int a, int b);	//�ж���Ӯ Ӯ�ͷ���1��û�оͷ���0����Ϸ������
void GameRecord(int WR);	//��Ϸ��ȡ�� WRΪ1��浵��Ϊ2�����
void Repentance();			//��������


//����ȫ�ֱ���
int InterfaceWidth = 1000;
int InterfaceHeight = 650;
const int BoardX=15, BoardY=15;
int board[BoardX][BoardY] = { 0 };	//0��ʾû�������״̬
int x, y;							//����

LPCTSTR startBGIPath;				//	startBGIPath = L"����1.jpg";
//char SBGIPath  ;
int gameMoudle = 0;


struct Bottom back;
BTM b1;
bool isClickBottom(BTM b, MOUSEMSG m1);
bool isGameOver = false;

//������
int main()
{
	while (1) {

		StartMenu();
		ChooseMoudle();
		
	}
}


//��������

void MousePoint()		//�������Ч
{
	MOUSEMSG m1;//���ָ��

	m1 = GetMouseMsg();//��ȡһ�������Ϣ

	for (int i = 0; i <= 10; i++)
	{
		setrop2(R2_NOTXORPEN);		//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
		setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
		circle(m1.x, m1.y, 2 * i);  
		Sleep(25);					//ͣ��25ms
		circle(m1.x, m1.y, 2 * i);  //Ĩȥ�ոջ���Բ
	}
	setrop2(R2_COPYPEN);
	FlushMouseMsgBuffer();//��������Ϣ������	
}

void StartMenu()
{
	LPCTSTR sbgi = L"����1.jpg" ;
	SetBGImage(sbgi);	//startBGIPath = L"����1.jpg";
	
	IMAGE BG_Start;
	MOUSEMSG msg;

	mciSendString(L"open timi.mp3", 0, 0, 0);	//������
	mciSendString(L"play timi.mp3", 0, 0, 0);	//��������
	//Sleep(3000);
	initgraph(InterfaceWidth, InterfaceHeight);
	cleardevice();
	loadimage(&BG_Start,startBGIPath);		//loadimage(NULL, L"����1.jpg");
	putimage(0, 0, &BG_Start);

	settextstyle(60, 30, _T("����"));
	settextcolor(DARKGRAY);
	setbkmode(TRANSPARENT);
	outtextxy(200, 100, L"��ӭ��������������!");
	settextstyle(40, 20, _T("����"));
	setlinecolor(LIGHTGRAY);
	setfillstyle(BS_NULL);
	fillroundrect(330, 245, 610, 330, 20, 20);
	outtextxy(370, 270, L"1.ѡ��ģʽ");
	fillroundrect(330, 345, 610, 430, 20, 20);
	outtextxy(370, 370, L"2.��Ϸ˵��");
	fillroundrect(330, 445, 610, 530, 20, 20);
	outtextxy(370, 470, L"3.��Ϸ����");
	FlushBatchDraw();
	gameMoudle = 0;
	isGameOver = false;
	while (1)
	{
		msg = GetMouseMsg();
		
		if (msg.x > 330 && msg.y > 245 && msg.x < 610 && msg.y < 330)	//ѡ��ģʽ
		{
			settextstyle(40, 20, _T("����"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			outtextxy(370, 270, L"1.ѡ��ģʽ");
			if (msg.mkLButton)
			{
				MousePoint();
				closegraph();
				FlushMouseMsgBuffer();	//��������Ϣ������
				MoudleMenu();			//����ѡ��ģʽ
				break;
			}
		}
		else if (msg.x > 330 && msg.y > 345 && msg.x < 610 && msg.y < 430)	//��Ϸ˵��
		{
			settextstyle(40, 20, _T("����"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 345, 610, 430, 20, 20);
			outtextxy(370, 370, L"2.��Ϸ˵��");

			if(msg.mkLButton)
			{
				MousePoint();
				FlushMouseMsgBuffer();	//��������Ϣ������
				Introduce(msg);		//������Ϸ˵��
				break;
			}
		}
		else if (msg.x > 330 && msg.y > 445 && msg.x < 610 && msg.y < 530)	//�˳���Ϸ
		{
			settextstyle(40, 20, _T("����"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 445, 610, 530, 20, 20);
			outtextxy(370, 470, L"3.��Ϸ����");
			if (msg.mkLButton)
			{
				MousePoint();
				FlushMouseMsgBuffer();	//��������Ϣ������
				SetMenu();				//������Ϸ����
				break;
			}
		}
		else
		{
			if (msg.mkLButton)
				MousePoint();
			settextcolor(DARKGRAY);
			settextstyle(40, 20, _T("����"));
			outtextxy(370, 270, L"1.ѡ��ģʽ");
			outtextxy(370, 370, L"2.��Ϸ˵��");
			outtextxy(370, 470, L"3.��Ϸ����");
			setlinecolor(LIGHTGRAY);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			fillroundrect(330, 345, 610, 430, 20, 20);
			fillroundrect(330, 445, 610, 530, 20, 20);

		}
	}
	mciSendString(L"close timi.mp3", 0, 0, 0);	//ͣ������
}

void ChooseMoudle()			//ѡ��ģʽ
{
	switch (gameMoudle) {
	case 1://˫�˶�ս
		GMDouble();
		break;
	case 2://�˻���ս

		break;
	case 3://������ս

		break;
	default:
		//������ѡ��
		break;
	}
}


void MoudleMenu()
{

	IMAGE BG_Start;
	MOUSEMSG msg;

	initgraph(InterfaceWidth, InterfaceHeight);
	cleardevice();
	loadimage(&BG_Start, startBGIPath);		//loadimage(NULL, L"����1.jpg");
	putimage(0, 0, &BG_Start);

	settextstyle(60, 30, _T("����"));
	settextcolor(DARKGRAY);
	setbkmode(TRANSPARENT); 
	outtextxy(250, 100, L"��ѡ����Ϸģʽ!");
	settextstyle(40, 20, _T("����"));
	setlinecolor(LIGHTGRAY);
	setfillstyle(BS_NULL);
	fillroundrect(330, 245, 610, 330, 20, 20);
	outtextxy(370, 270, L"1.˫�˶�ս");
	fillroundrect(330, 345, 610, 430, 20, 20);
	outtextxy(370, 370, L"2.�˻���ս");
	fillroundrect(330, 445, 610, 530, 20, 20);
	outtextxy(370, 470, L"3.������ս");
	settextcolor(BLUE);
	BTM back1;
	DrawBottom(10, 10, &back1, 10, L"����");
	FlushBatchDraw();

	//FlushMouseMsgBuffer();//��������Ϣ������
	while (1)
	{
		FlushMouseMsgBuffer();//��������Ϣ������
		msg = GetMouseMsg();

		if (msg.mkLButton)
			MousePoint();
		if (msg.x > 330 && msg.y > 245 && msg.x < 610 && msg.y < 330)	//1.˫�˶�ս
		{
			settextstyle(40, 20, _T("����"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 245, 610, 330, 20, 20);
			outtextxy(370, 270, L"1.˫�˶�ս");
			if (msg.mkLButton)
			{
				//MousePoint();
				closegraph();			//����ѡ��ģʽ������˫�˶�ս
				gameMoudle = 1;
				FlushMouseMsgBuffer();	//��������Ϣ������	
				break;
			}

		}
		else if (msg.x > 330 && msg.y > 345 && msg.x < 610 && msg.y < 430)	//2.�˻���ս
		{
			settextstyle(40, 20, _T("����"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 345, 610, 430, 20, 20);
			outtextxy(370, 370, L"2.�˻���ս");

			if (msg.mkLButton)
			{
				MousePoint();
				gameMoudle = 2;
				FlushMouseMsgBuffer();
				break;
			}
		}
		else if (msg.x > 330 && msg.y > 445 && msg.x < 610 && msg.y < 530)	//3.������ս
		{
			settextstyle(40, 20, _T("����"));
			settextcolor(RED);
			setlinecolor(BROWN);
			setfillstyle(BS_NULL);
			fillroundrect(330, 445, 610, 530, 20, 20);
			outtextxy(370, 470, L"3.������ս");
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
			//���� outtextxy(100, 100, L"click");
			//FlushMouseMsgBuffer();
			break;	//-->StartMenu();	
		}
		else
		{
			
			
			//isClickBottom(back1);
			settextcolor(DARKGRAY);
			settextstyle(40, 20, _T("����"));
			outtextxy(370, 270, L"1.˫�˶�ս");
			outtextxy(370, 370, L"2.�˻���ս");
			outtextxy(370, 470, L"3.������ս");
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

	settextstyle(25, 12, _T("����"));
	setfillstyle(BS_NULL);
	settextcolor(BLUE);
	BTM back;
	DrawBottom(10, 10, &back, L"����");
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
		settextstyle(70, 40, _T("����"));
		outtextxy(350, 465, L"��Ϸ����");
		while (1)
		{
			BTM backstartmenu, restart;
			settextstyle(30, 20, _T("����"));
			DrawBottom(325, 550, &backstartmenu, 10, L"������Ϸ");
			DrawBottom(525, 550, &restart, 10, L"����һ��");
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
	line(600,8,600,650);		// ���ָ���
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0, m = 30;
	for (int lineN = 1; lineN <= 15; lineN++)
	{
		//MousePoint();
		
		setlinecolor(BLUE);
		settextstyle(20, 10, _T("Times New Roman"));
		//for (int x1, y1, x2, y2;)
		x1 = m * lineN, y1 = m, x2 = m * lineN, y2 = m * 15;	//����
		line(x1,y1,x2,y2);
		//outtextxy(m*lineN, m-5,(char)lineN);
		x1 = m, y1 = m * lineN, x2 = m * 15, y2 = m * lineN;	//����
		line(x1, y1, x2, y2);
		//outtextxy(m-5, m*lineN, (char)lineN);
		int s = (lineN - 7) * (lineN - 7);
		Sleep(3*s);
	}
	int wx = 470, wy = 16;
	settextcolor(LIGHTGRAY);
	settextstyle(80, 40, _T("����"));
	outtextxy(wx, wy, L"��"); wy += 90;
	outtextxy(wx, wy, L"��"); wy += 90;
	outtextxy(wx, wy, L"��"); wy += 90;
	outtextxy(wx, wy, L"��"); wy += 90;
	outtextxy(wx, wy, L"��");

	settextstyle(25, 12, _T("����"));
	DrawBottom(800, 40, &b1, 10, L"��Ϸ����!");
}

void GMDouble()
{
	IMAGE bgp;
	initgraph(InterfaceWidth, InterfaceHeight);
	setbkmode(TRANSPARENT);
	loadimage(&bgp, L"yxsm.jpg");
	
	putimage(0, 0, &bgp, SRCCOPY);
	settextstyle(25, 12, _T("����"));
	setfillstyle(BS_NULL);
	settextcolor(BLUE);
	//DrawBottom(10, 10, L"����");
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
			//����	outtextxy(f*10, f*10, L"FF"); 
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
//����
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
		//���� outtextxy(b.x2,b.y2, L"inclickbtm");
		if (m1.mkLButton)
		{
			//���� outtextxy(200, 200, L"isclickbtm");
			MousePoint();
			return 1;
		}
	}
	else
	{
		//���� outtextxy(b.x1,b.y1, L"notclickbtm");
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
			
			for (int i = 1; i <= 10; i++)	//�ж���Ӯ
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
			outtextxy(200, 600, L"�˴����壬����������");
			*f -= 1;
			Sleep(2000);
			outtextxy(200, 600, L"�˴����壬����������");
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
			settextstyle(50, 30, _T("����"));
			outtextxy(200, 300, L"��Ϸ����");
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


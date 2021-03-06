/*贪吃蛇Dome2.1  最后编辑于12.30 机实验16余鑫 16105050133*/
//运行环境：WIN10,VS2010
/*用到了：数组，指针，动态内存分配，结构体等知识及WINDOWS的部分API*/
/*         
除了光标设置函数SetConsoleCursorPosition是通过网络查询所得，其他均为原创
*/
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>	//包含清屏函数的头文件
#include<time.h>

typedef struct
{
	int length[10];
	int speed[10];
}RankingListTypeDef;	//排行榜数据记录

typedef struct
{
	char number[12];
	char name[10];
	char class_[15];
}AuthorInfoTypeDef;

int N=20;	//棋盘大小
int SPEED=150;	//运动周期
int LENGTH_MAX=50;	//定义最大蛇身长度
int LENGTH_TARGET=40;	//定义长度目标值

RankingListTypeDef Ranking_List={0};
AuthorInfoTypeDef AuthorInfo={{"16105050133"},{"余鑫"},{"机实验16"}};	

void gotoxy(int x,int y)	//定义gotoxy函数
{ 
	COORD coord; 
	coord.X=x; 
	coord.Y=y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);	//光标定位到xy
}


void Ranking_Ascend(int *a,int len);
void Ranking_Descend(int *a,int len);

int Gameing_Patience(void);	//耐心模式
int Gameing_Speed(void);	//速度挑战
void Seting(void);	//设置
void Ranking_Patience(void);
void Ranking_Speed(void);
void Rank_Patience_Clear(void);
void Rank_Speed_Clear(void);
void Author_Info_Printf(void);
void Visit_Github(void);

int main()
{
	int choice=0;

	while(1)
	{
		system("cls");	//清屏
		printf("\n");
		printf("\n");
		printf(" ----------贪吃蛇Dome2.1---------\n");
		printf("                            --余鑫\n");
		printf("1.开始游戏-耐心挑战\n2.开始游戏-手速比拼\n3.设置\n4.耐心排行榜\n5.速度排行榜\n6.清空耐心排行榜\n7.清空速度排行榜\n8.退出游戏\n9.作者信息\n10.访问Github查看源代码\n");
		scanf("%d",&choice);

		switch (choice)
		{
		case 0:
			{
				printf("请输入正确的选择！\n按任意键返回");
				getch();
				break;
			}
		case 1:
			{
				static short rank_length_count=0;
				rank_length_count=rank_length_count>10?0:rank_length_count;	//大于10则归0	循环记录
				Ranking_List.length[rank_length_count++]=Gameing_Patience();
				break;
			}
		case 2:
			{
				static short rank_speed_count=0;
				rank_speed_count=rank_speed_count>10?0:rank_speed_count;	//大于10则归0	循环记录
				Ranking_List.speed[rank_speed_count++]=Gameing_Speed();
				break;
			}
		case 3:
			{
				Seting();
				break;
			}
		case 4:
			{
				Ranking_Patience();
				break;
			}
		case 5:
			{
				Ranking_Speed();
				break;
			}
		case 6:
			{
				Rank_Patience_Clear();
				break;
			}
		case 7:
			{
				Rank_Speed_Clear();
				break;
			}
		case 8:
			{
				return 0;
				break;
			}
		case 9:
			{
				Author_Info_Printf();
				break;
			}
		case 10:
			{
				Visit_Github();
				break;
			}
		default:
			{
				printf("请输入正确的选择！\n按任意键返回");
				getch();
				break;
			}
		}
	}

	
	////////////////////////////////////////////

	////////////////////////////////////////////
	return 0;
}


void Seting(void)
{
	system("cls");
	printf("设置棋盘大小（单位为全角,建议不超过28，全屏随意）：\n速度模式下棋盘会限制在30以内\n");
	scanf("%d",&N);
}


void Ranking_Patience(void)
{
	system("cls");
	int out_temp[10];
	for(int i=0;i<10;i++)
	{
		out_temp[i]=Ranking_List.length[i];
	}
	Ranking_Ascend(out_temp,10);
	printf("\n------------耐心排行榜-------------");
	for(int i=0;i<9;i++)
	{
		printf("\n%d.................................%d",i+1,out_temp[i]);
	}
	printf("\n%d.................................%d",9,out_temp[9]);
	printf("\n按任意键返回");
	getch();
}


void Ranking_Speed(void)
{
	system("cls");
	int out_temp[10];
	for(int i=0;i<10;i++)
	{
		out_temp[i]=Ranking_List.speed[i];
	}
	Ranking_Descend(out_temp,10);	//降序排反应速度
	printf("\n------------反应时间排行榜-------------");
	for(int i=0;i<9;i++)
	{
		printf("\n%d.................................%d",i+1,out_temp[i]);
	}
	printf("\n%d.................................%d",9,out_temp[9]);
	printf("\n按任意键返回");
	getch();
}


void Rank_Patience_Clear(void)
{
	system("cls");
	for(int i=0;i<10;i++)
	{
		Ranking_List.length[i]=0;
	}
	printf("-----已清除耐心排行榜-----\n按任意键返回");
	getch();
}

void Rank_Speed_Clear(void)
{
	system("cls");
	for(int i=0;i<10;i++)
	{
		Ranking_List.speed[i]=0;
	}
	printf("-----已清除手速排行榜-----\n按任意键返回");
	getch();
}


void Author_Info_Printf(void)
{
	system("cls");
	printf(" ----------贪吃蛇Dome2.1---------");
	printf("\n姓名：%s",AuthorInfo.name);
	printf("\n班级：%s",AuthorInfo.class_);
	printf("\n学号：%s",AuthorInfo.number);
	printf("\n\n\n\t\t按任意键返回");
	getch();
}


void Visit_Github(void)
{
	system("cls");
	system("explorer https://github.com/yx19981001/Retro_Snaker");
	printf("已使用默认浏览器打开\n如电脑无法自动打开浏览器，请手动访问：\nhttps://github.com/yx19981001/Retro_Snaker");
	getch();
}


int Gameing_Patience(void)	
{
	SPEED=150;
	///////////////////////////////////////////////////////


	srand(time(0));
	int c=0;	//键盘输入变量
	int x=3;
	int i;	//定义临时循环变量
	int ri,li,r,l;
	int length=6;	//定义蛇身长度变量
	int v[2]={0,1};	//定义并速度变量向右


	int R_Init[7]={2,2,2,2,2,2,2};	//行坐标初始化数值
	int L_Init[7]={7,6,5,4,3,2,1};	//列坐标初始化数值
	int* R=(int*)malloc(LENGTH_MAX*sizeof(int));	//为其分配动态内存，当作数组来用
	int* L=(int*)malloc(LENGTH_MAX*sizeof(int));	//这样可以初始化自定义数组
	for(int i=0;i<7;i++)
	{
		R[i]=R_Init[i];
		L[i]=L_Init[i];
	}


	int food[2];	//定义食物坐标
	food[0]=rand()%(N-2)+1;	//初始化随机行坐标
	food[1]=rand()%(N-2)+1;	//初始化随机列坐标
	char board[100][100];	//定义棋盘二维数组

	for(i=0;i<N;i++)	//定义上下边界
	{
		board[(N-1)][i]='-';
		board[0][i]='-';
	}

	for(i=0;i<N;i++)	//定义左右边界
	{
		board[i][0]='|';
		board[i][(N-1)]='|';
	}

	system("cls");
	printf("\n");
	printf("\n");
	printf("----------贪吃蛇Dome2.1---------\n");
	printf("                            --余鑫\n");
	printf("小提示：\nW控制上 S控制下 A控制左 D控制右\n目标：吃到更多的食物\n");
	printf("\n     按下任意键开始游戏");
	getch();

	system("cls");	//清屏

		while(1)
	{



		if(R[0]==0||R[0]==(N-1)||L[0]==0||L[0]==(N-1))	//判断是否触碰到边界
		{
			gotoxy(5,10);	//移动光标到指定位置（中间）
			printf("\n           吃到墙啦\n           最终长度：%d\n           即将退出本局\n",length);
			goto a;
		}


		for(ri=1;ri<N-1;ri++)
			for(li=1;li<N-1;li++)
				board[ri][li]=' ';	//	定义棋盘内圈为英文空格（外圈为边界）

		board[food[0]][food[1]]='$';	//在棋盘中插入食物$

		for(i=0;i<length;i++)
		{
			r=R[i];
			l=L[i];
			board[r][l]='*';	//在棋盘中插入蛇身*
		}



		gotoxy(1,1);	
		for(ri=0;ri<N;ri++)	//数组内容最终输出
		{
			printf("\n");
			for(li=0;li<N;li++)
				printf("%c ",board[ri][li]);
		}


		Sleep(SPEED);	
		c=0;	
		if(_kbhit()!=0)	//当没有输入时跳过getch语句以让程序流畅进行
		{
			c=getch();
		}

		while(_kbhit()!=0)	//手动读取清除键盘缓冲区内容
		{
			i=getch();
		}

		switch(c)	//通过读取键盘字符对速度变量的赋值
		{
		case 119:	//上键键值
			v[0]=-1;
			v[1]=0;
		break;
		case 97:	//左键键值
			v[0]=0;
			v[1]=-1;
		break;
		case 100:	//右键键值
			v[0]=0;
			v[1]=1;
		break;
		case 115:	//下键键值
			v[0]=1;
			v[1]=0;
		break;
		}


		if((R[0]==food[0])&&(L[0]==food[1]))	//判断是否吃到食物
		{
			length++;	
			srand(time(0));	
			food[0]=rand()%(N-2)+1;	
			food[1]=rand()%(N-2)+1;	
		}



		if(length==LENGTH_MAX)
		{
			gotoxy(5,10);	//移动光标到指定位置（中间）
			printf("给你的耐心一个赞，游戏已通关\n--后续更多版本敬请期待\n");
			goto a;	
		}

		for(i=length;i>=2;i--)	//蛇身前进
		{
			R[i-1]=R[i-2];
			L[i-1]=L[i-2];
		}

		R[0]=R[0]+v[0];//蛇头前进
		L[0]=L[1]+v[1];

		for(i=1;i<length;i++)
		{
			if((R[0]==R[i])&&(L[0]==L[i]))	//检查蛇头是否与蛇身重合
			{
				gotoxy(5,10);	
				printf("你吃到自己了-_-|，游戏结束 - 最终长度是%d\n",length);
				goto a;
			}
		}

	}

	a:printf("\n\n           ");	//这个，调整最后一句话出现的位置，无功能作用
	system("pause");	//暂停一下画面
	//////////////////////////////////////////////////////

	free(R);
	free(L);

	return length;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Gameing_Speed(void)	//速度挑战
{
	SPEED=150;
	///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
	int N_temp=N;	//储存记录外部设置棋盘大小
	N=N>30?30:N;;	//限制大小30以内


	srand(time(0));
	int c=0;	//键盘输入变量
	int x=3;
	int i;	//定义临时循环变量
	int ri,li,r,l;
	int length=6;	//定义蛇身长度变量
	int v[2]={0,1};	//定义并速度变量向右


	int R_Init[7]={2,2,2,2,2,2,2};	//行坐标初始化数值
	int L_Init[7]={7,6,5,4,3,2,1};	//列坐标初始化数值
	int* R=(int*)malloc(LENGTH_MAX*sizeof(int));	//为其分配动态内存，当作数组来用
	int* L=(int*)malloc(LENGTH_MAX*sizeof(int));	//这样可以初始化自定义数组
	for(int i=0;i<7;i++)
	{
		R[i]=R_Init[i];
		L[i]=L_Init[i];
	}


	int food[2];	//定义食物坐标
	food[0]=rand()%(N-2)+1;	//初始化随机行坐标
	food[1]=rand()%(N-2)+1;	//初始化随机列坐标
	char board[100][100];	//定义棋盘二维数组

	for(i=0;i<N;i++)	//定义上下边界
	{
		board[(N-1)][i]='-';
		board[0][i]='-';
	}

	for(i=0;i<N;i++)	//定义左右边界
	{
		board[i][0]='|';
		board[i][(N-1)]='|';
	}

	system("cls");
	printf("\n");
	printf("\n");
	printf("----------贪吃蛇Dome2.1---------\n");
	printf("                            --余鑫\n");
	printf("小提示：\nW控制上 S控制下 A控制左 D控制右\n目标：在越来越快的游戏速度下吃到食物\n");
	printf("\n     按下任意键开始游戏");
	getch();

	system("cls");	//清屏

		while(1)
	{

		if(R[0]==0||R[0]==(N-1)||L[0]==0||L[0]==(N-1))	//判断是否触碰到边界
		{
			gotoxy(5,10);	//移动光标到指定位置（中间）
			printf("\n          吃到墙啦\n          最终反应时间：%d\n          即将退出本局\n",SPEED);
			goto a;
		}


		for(ri=1;ri<N-1;ri++)
			for(li=1;li<N-1;li++)
				board[ri][li]=' ';	//	定义棋盘内圈为英文空格（外圈为边界）

		board[food[0]][food[1]]='$';	//在棋盘中插入食物$

		for(i=0;i<length;i++)
		{
			r=R[i];
			l=L[i];
			board[r][l]='*';	//在棋盘中插入蛇身*
		}



		gotoxy(1,1);	//定位(清屏)函数
		for(ri=0;ri<N;ri++)	//数组内容最终输出
		{
			printf("\n");
			for(li=0;li<N;li++)
				printf("%c ",board[ri][li]);
		}

		if(SPEED!=0)
		Sleep(SPEED);	
		c=0;	
		if(_kbhit()!=0)	//当没有输入时跳过getch语句以让程序流畅进行
		{
			c=getch();	
		}

		while(_kbhit()!=0)	//手动读取清除键盘缓冲区内容
		{
			i=getch();
		}

		switch(c)	//通过读取键盘字符对速度变量的赋值
		{
		case 119:	//上键键值
			v[0]=-1;
			v[1]=0;
		break;
		case 97:	//左键键值
			v[0]=0;
			v[1]=-1;
		break;
		case 100:	//右键键值
			v[0]=0;
			v[1]=1;
		break;
		case 115:	//下键键值
			v[0]=1;
			v[1]=0;
		break;
		}


		if((R[0]==food[0])&&(L[0]==food[1]))	//判断是否吃到食物
		{
			SPEED=SPEED>10?(SPEED-10):SPEED;	//对速度的条件赋值
			SPEED=(SPEED<=10&&SPEED>3)?4:SPEED;	//对速度的条件赋值
			SPEED=SPEED==4?1:SPEED;	//对速度的条件赋值
			SPEED=SPEED==1?0:SPEED;
			length++;	
			srand(time(0));	
			food[0]=rand()%(N-2)+1;	
			food[1]=rand()%(N-2)+1;	
		}



		if(length==LENGTH_MAX)
		{
			gotoxy(5,10);	//移动光标到指定位置（中间）
			printf("   给你的耐心一个赞，游戏已通关\n   --后续更多版本敬请期待\n");
			goto a;	
		}

		for(i=length;i>=2;i--)	//蛇身前进
		{
			R[i-1]=R[i-2];
			L[i-1]=L[i-2];
		}

		R[0]=R[0]+v[0];//蛇头前进
		L[0]=L[1]+v[1];

		for(i=1;i<length;i++)
		{
			if((R[0]==R[i])&&(L[0]==L[i]))	//检查蛇头是否与蛇身重合
			{
				gotoxy(5,10);	
				printf("你吃到自己了-_-|，游戏结束 - 最终反应时间是%d\n",SPEED);
				goto a;	
			}
		}

	}

	a:printf("\n\n           ");	//这个，调整最后一句话出现的位置，无功能作用
	system("pause");	//暂停一下画面
	//////////////////////////////////////////////////////

	free(R);
	free(L);
	N=N_temp;	//将储存的外部设置值还原
	return SPEED==0?0:SPEED;
	///////////////////////////////////////////////////////////

}




void Ranking_Ascend(int *a,int len)	//升序函数
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			if(*(a+j)<*(a+j+1))
			{
				int b=*(a+j);
				*(a+j)=*(a+j+1);
				*(a+j+1)=b;
			}
		}
	}
}

void Ranking_Descend(int *a,int len)	//降序函数
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			if(*(a+j)!=0&&*(a+j+1)!=0)	//对速度排行榜0升序，非零降序的特殊处理
			{
				if(*(a+j)>*(a+j+1))
				{
					int b=*(a+j);
					*(a+j)=*(a+j+1);
					*(a+j+1)=b;
				}
			}
			else
			{
				if(*(a+j)<*(a+j+1))
				{
					int b=*(a+j);
					*(a+j)=*(a+j+1);
					*(a+j+1)=b;
				}
			}
		}
	}
}




/*
比赛规则：
1、十二人参加，比赛两轮，一轮淘汰赛，二轮决赛
2、选手编号10001-10012
3、分组比赛，每组6人，抽签分组
4、十个评委，去掉最低最高分，求平均分
5、每组淘汰最后三人，进入下一轮，前三胜出
6、比赛过后显示晋级选手的信息

程序功能：
1、开始演讲比赛：完成流程
2、查看往届记录：查看前三结果，每次比赛记录到文件中，文件名用.csv
3、清空比赛记录：清空文件数据
4、退出比赛程序：退出当前程序
*/

#include<iostream>
#include<ctime>
#include"speakingManager.h"
using namespace std;

int main()
{
	SpeakingManager sm;
	srand((unsigned int)time(NULL));
	int iSel = 0;
	while (true)
	{
		sm.showMenu();
		cin >> iSel;
		switch (iSel)
		{
		case 1:
			sm.startCompetition();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 4:
			sm.exitSystem();
			break;
		default:
			system("pause");
			system("cls");
			break;
		}
	}
	return 1;
}
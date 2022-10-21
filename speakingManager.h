#pragma once
#include<iostream>
#include<vector>
#include"speaker.h"
#include<map>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<string>
using namespace std;

class SpeakingManager
{
public:
	SpeakingManager();
	~SpeakingManager();
	//显示菜单
	void showMenu();
	//退出
	void exitSystem();
	//创建人员
	void createSpeaker();
	//初始化容器和属性
	void initSpeak();
	//开始比赛流程
	void startCompetition();
	//抽签
	void randSort();
	//比赛
	void speakingContest();
	//显示晋级成员
	void showScore();
	//保存分数
	void saveRecord();
	//读数据
	void loadRecord();
	//判断文件是否为空
	bool fileIsEmpty;
	//存放往届记录的容器
	map<int, vector<string>> m_Record;
	//显示往届成绩
	void showRecord();
	//清空记录
	void clearRecord();
	//第一轮
	vector<int>v1;
	//第一轮晋级
	vector<int>v2;
	//胜出的选手
	vector<int>vVictory;
	//存放编号以及对应具体选手容器
	map<int, Speaker>m_Speaker;
	//存放比赛轮数
	int m_Index;
};


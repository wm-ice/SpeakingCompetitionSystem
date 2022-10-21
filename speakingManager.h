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
	//��ʾ�˵�
	void showMenu();
	//�˳�
	void exitSystem();
	//������Ա
	void createSpeaker();
	//��ʼ������������
	void initSpeak();
	//��ʼ��������
	void startCompetition();
	//��ǩ
	void randSort();
	//����
	void speakingContest();
	//��ʾ������Ա
	void showScore();
	//�������
	void saveRecord();
	//������
	void loadRecord();
	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	//��������¼������
	map<int, vector<string>> m_Record;
	//��ʾ����ɼ�
	void showRecord();
	//��ռ�¼
	void clearRecord();
	//��һ��
	vector<int>v1;
	//��һ�ֽ���
	vector<int>v2;
	//ʤ����ѡ��
	vector<int>vVictory;
	//��ű���Լ���Ӧ����ѡ������
	map<int, Speaker>m_Speaker;
	//��ű�������
	int m_Index;
};


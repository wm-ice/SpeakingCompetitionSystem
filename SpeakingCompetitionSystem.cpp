/*
��������
1��ʮ���˲μӣ��������֣�һ����̭�������־���
2��ѡ�ֱ��10001-10012
3�����������ÿ��6�ˣ���ǩ����
4��ʮ����ί��ȥ�������߷֣���ƽ����
5��ÿ����̭������ˣ�������һ�֣�ǰ��ʤ��
6������������ʾ����ѡ�ֵ���Ϣ

�����ܣ�
1����ʼ�ݽ��������������
2���鿴�����¼���鿴ǰ�������ÿ�α�����¼���ļ��У��ļ�����.csv
3����ձ�����¼������ļ�����
4���˳����������˳���ǰ����
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
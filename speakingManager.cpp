#include"speakingManager.h"


SpeakingManager::SpeakingManager()
{
	//��ʼ������������
	this->initSpeak();
	//����ѡ��
	this->createSpeaker();
	//������������
	this->loadRecord();
}

SpeakingManager::~SpeakingManager()
{

}

void SpeakingManager::showMenu()
{
	cout << "�˵���" << endl;
	cout << "1����ʼ�ݽ�����" << endl;
	cout << "2���鿴�����¼��" << endl;
	cout << "3����ձ�����¼��" << endl;
	cout << "4���˳���������" << endl;
	cout << "������������ţ�";
}

void SpeakingManager::exitSystem()
{
	int iTmp = 0;
	cout << "�Ƿ�ȷ���˳���1����    2����";
	cin >> iTmp;
	if (iTmp == 2)
	{
		return;
	}
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}
void SpeakingManager::initSpeak()
{
	//���
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}
void SpeakingManager::createSpeaker()
{
	string nameTmp = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "ѡ��";
		name += nameTmp[i];
		Speaker sp;
		sp.name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeakingManager::startCompetition()
{
	cout << endl;
	cout << "********��ʼ�ݽ�����********" << endl;
	//�齱
	this->randSort();
	//����
	this->speakingContest();
	//��ʾ�������
	this->showScore();
	//�ڶ��ֱ�����ʼ
	this->m_Index++;
	//��ǩ
	this->randSort();
	//����
	this->speakingContest();
	//��ʾ�������
	this->showScore();
	//�����¼
	this->saveRecord();
	//���ñ�������ȡ��¼
	//��ʼ������������
	this->initSpeak();
	//����ѡ��
	this->createSpeaker();
	//������������
	this->loadRecord();

	cout << "���α���������" << endl;
	system("pause");
	system("cls");
}
void SpeakingManager::randSort()
{
	cout << "��"<<this->m_Index<<"�ֱ����齱˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		//�������0000000
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
		{
			cout << (*it)  << " ";
		}
		cout << endl;
	}
	else
	{
		//�������
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
		{
			cout << (*it) << " ";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
}

void SpeakingManager::speakingContest()
{
	//׼����ʱ�������С��ɼ�(���ճɼ�����
	multimap<double, int, greater<double>> groupScore;
	int iNum = 0;//ÿ����һ��
	cout << "��"<<this->m_Index<<"����ʽ������ʼ��" << endl;
	//����ѡ�ֵ�����
	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		iNum++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score =( rand() % 401 + 600)/10.f; //600~1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//��ƽ���ַŵ�map������
		this->m_Speaker[*it] .m_Score[this->m_Index-1] = avg;
		groupScore.insert(make_pair(avg, *it));
		if (iNum %6==0)
		{
			cout << "��" << iNum / 6 << "С��������Σ�" << endl;
			int iCount = 0;//ȡ��ǰ����
			for (multimap<double, int, greater<double>>::iterator mp = groupScore.begin();
				mp != groupScore.end(); mp++)
			{
				cout << "��ţ�" << mp->second << " ������" << this->m_Speaker[mp->second].name
					<< " ƽ���֣�" << this->m_Speaker[mp->second].m_Score[this->m_Index-1] << endl;
				if (iCount < 3)
				{
					if (this->m_Index == 1)
					{
						v2.push_back(mp->second);
					}
					else
					{
						vVictory.push_back(mp->second);
					}
					iCount++;
				}
			}
			groupScore.clear();//С������Ҫ���
		}
	}
	cout << "��" << this->m_Index << "�ֱ�������" << endl;
	system("pause");
}
void SpeakingManager::showScore()
{
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	cout << "��" << this->m_Index << "�ֽ�����Ա��Ϣ���£�" << endl;
	for (vector<int>::iterator vit = v.begin(); vit != v.end(); vit++)
	{
		cout << "��ţ�" << *vit << "  ������" << m_Speaker[*vit].name << "  �ɼ���" << m_Speaker[*vit].m_Score[m_Index - 1] <<endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}
void SpeakingManager::saveRecord()
{
	ofstream ofs;
	//׷�ӷ�ʽд�ļ�
	ofs.open("speakingCompetition.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼����ɹ���" << endl;
	fileIsEmpty = false;
}
//������
void SpeakingManager::loadRecord()
{
	ifstream ifs;
	//���ļ�
	ifs.open("speakingCompetition.csv", ios::in );
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż���
	string data;
	int index = 0;
	while (ifs >> data)
	{
		//10005,88.65,10002,86.7125,10006,85.0125,
		//����","��λ��
		int pos = -1;
		//���ҵ���ʼλ��
		int start = 0;
		vector<string>v;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			start = pos + 1;
			v.push_back(temp);
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void SpeakingManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "û����������" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "��ɼ���"<<endl;
		cout << "�ھ����Ϊ��" << this->m_Record[i][0] << "  ����Ϊ��" << this->m_Record[i][1] << endl;
		cout << "�Ǿ����Ϊ��" << this->m_Record[i][2] << "  ����Ϊ��" << this->m_Record[i][3] << endl;
		cout << "�������Ϊ��" << this->m_Record[i][4] << "  ����Ϊ��" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}
void SpeakingManager::clearRecord()
{
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int iSel = 0;
	cin >> iSel;
	if (iSel==1)
	{
		//�ļ�������ɾ�������´������ļ�
		ofstream ofs("speakingCompetition.csv", ios::trunc);
		ofs.close();
		//��ʼ������������
		this->initSpeak();
		//����ѡ��
		this->createSpeaker();
		//������������
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
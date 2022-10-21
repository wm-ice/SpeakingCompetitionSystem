#include"speakingManager.h"


SpeakingManager::SpeakingManager()
{
	//初始化容器和属性
	this->initSpeak();
	//创建选手
	this->createSpeaker();
	//加载往届数据
	this->loadRecord();
}

SpeakingManager::~SpeakingManager()
{

}

void SpeakingManager::showMenu()
{
	cout << "菜单：" << endl;
	cout << "1、开始演讲比赛" << endl;
	cout << "2、查看往届记录：" << endl;
	cout << "3、清空比赛记录：" << endl;
	cout << "4、退出比赛程序" << endl;
	cout << "请输入以上序号：";
}

void SpeakingManager::exitSystem()
{
	int iTmp = 0;
	cout << "是否确认退出？1、是    2、否：";
	cin >> iTmp;
	if (iTmp == 2)
	{
		return;
	}
	cout << "欢迎下次使用" << endl;
	exit(0);
}
void SpeakingManager::initSpeak()
{
	//清空
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
		string name = "选手";
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
	cout << "********开始演讲比赛********" << endl;
	//抽奖
	this->randSort();
	//比赛
	this->speakingContest();
	//显示晋级结果
	this->showScore();
	//第二轮比赛开始
	this->m_Index++;
	//抽签
	this->randSort();
	//比赛
	this->speakingContest();
	//显示晋级结果
	this->showScore();
	//保存记录
	this->saveRecord();
	//重置比赛，获取记录
	//初始化容器和属性
	this->initSpeak();
	//创建选手
	this->createSpeaker();
	//加载往届数据
	this->loadRecord();

	cout << "本次比赛结束！" << endl;
	system("pause");
	system("cls");
}
void SpeakingManager::randSort()
{
	cout << "第"<<this->m_Index<<"轮比赛抽奖顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		//随机排序0000000
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
		{
			cout << (*it)  << " ";
		}
		cout << endl;
	}
	else
	{
		//随机排序
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
	//准备临时容器存放小组成绩(按照成绩排序）
	multimap<double, int, greater<double>> groupScore;
	int iNum = 0;//每六人一组
	cout << "第"<<this->m_Index<<"轮正式比赛开始：" << endl;
	//比赛选手的容器
	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		iNum++;
		//评委打分
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
		//将平均分放到map容器中
		this->m_Speaker[*it] .m_Score[this->m_Index-1] = avg;
		groupScore.insert(make_pair(avg, *it));
		if (iNum %6==0)
		{
			cout << "第" << iNum / 6 << "小组比赛名次：" << endl;
			int iCount = 0;//取走前三名
			for (multimap<double, int, greater<double>>::iterator mp = groupScore.begin();
				mp != groupScore.end(); mp++)
			{
				cout << "编号：" << mp->second << " 姓名：" << this->m_Speaker[mp->second].name
					<< " 平均分：" << this->m_Speaker[mp->second].m_Score[this->m_Index-1] << endl;
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
			groupScore.clear();//小组容器要清空
		}
	}
	cout << "第" << this->m_Index << "轮比赛结束" << endl;
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
	cout << "第" << this->m_Index << "轮晋级成员信息如下：" << endl;
	for (vector<int>::iterator vit = v.begin(); vit != v.end(); vit++)
	{
		cout << "编号：" << *vit << "  姓名：" << m_Speaker[*vit].name << "  成绩：" << m_Speaker[*vit].m_Score[m_Index - 1] <<endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}
void SpeakingManager::saveRecord()
{
	ofstream ofs;
	//追加方式写文件
	ofs.open("speakingCompetition.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录保存成功！" << endl;
	fileIsEmpty = false;
}
//读数据
void SpeakingManager::loadRecord()
{
	ifstream ifs;
	//读文件
	ifs.open("speakingCompetition.csv", ios::in );
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件清空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符放回来
	string data;
	int index = 0;
	while (ifs >> data)
	{
		//10005,88.65,10002,86.7125,10006,85.0125,
		//查找","的位置
		int pos = -1;
		//查找的起始位置
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
		cout << "没有往届数据" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届成绩："<<endl;
		cout << "冠军编号为：" << this->m_Record[i][0] << "  分数为：" << this->m_Record[i][1] << endl;
		cout << "亚军编号为：" << this->m_Record[i][2] << "  分数为：" << this->m_Record[i][3] << endl;
		cout << "季军编号为：" << this->m_Record[i][4] << "  分数为：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}
void SpeakingManager::clearRecord()
{
	cout << "是否确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int iSel = 0;
	cin >> iSel;
	if (iSel==1)
	{
		//文件存在则删除并重新创建新文件
		ofstream ofs("speakingCompetition.csv", ios::trunc);
		ofs.close();
		//初始化容器和属性
		this->initSpeak();
		//创建选手
		this->createSpeaker();
		//加载往届数据
		this->loadRecord();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
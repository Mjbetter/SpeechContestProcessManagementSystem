#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech(); 
	//创建12名选手
	this->createSpeaker();
	//加载往届的记录
	this->loadRecord();
}

void SpeechManager::main_interface() {
	cout << "      欢迎参加演讲比赛      " << endl;
	cout << "      1.开始演讲比赛        " << endl;
	cout << "      2.查看往届的记录      " << endl;
	cout << "      3.清空比赛记录        " << endl;
	cout << "      0.退出比赛程序        " << endl;
	cout << "      请输入选择的序号：";
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::initSpeech() {
	//容器都置空
	this->speaker_numbers.clear();
	this->first_winners_numbers.clear();
	this->speaker_victory.clear();
	this->m_speaker.clear();
	this->m_record.clear();
	//初始化比赛轮数
	this->m_index = 1;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker speaker(name,i);
		for (int j = 0; j < 2; j++) {
			speaker.m_Score[j] = 0;
		}
		//创建选手的编号
		this->speaker_numbers.push_back(i + 10001);
		//选手编号以及对应选手 放入到map容器中
		this->m_speaker.insert(make_pair(i + 10001, speaker));

	}
}

void SpeechManager::speechDraw() {
	cout << "-----------第" << this->m_index << "轮比赛选手正在抽签-----------" << endl;
	cout << "" << endl;
	cout << "抽签后的演讲顺序如下:" << endl;

	if (this->m_index == 1) {
		//第一轮比赛
		random_shuffle(this->speaker_numbers.begin(), this->speaker_numbers.end());
		for (auto it : this->speaker_numbers) {
			cout << it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(this->first_winners_numbers.begin(), this->first_winners_numbers.end());
		for (auto it : this->first_winners_numbers) {
			cout << it << " ";
		}
		cout << endl;
	}
}

void SpeechManager::speechContent(){
	cout << "-------------第" << this->m_index << "轮比赛正式开始-------------" << endl;
	//准备临时容器，存放临时成绩
	multimap<double, int, greater<double>>groupScore;
	//记录人员个数 6人一组
	int num = 0;
	vector<int>speaker_src;//比赛选手容器
	if (this->m_index == 1) {
		speaker_src = this->speaker_numbers;
	}
	else {
		speaker_src = this->first_winners_numbers;
	}
	//遍历所有选手进行比赛
	for (auto &it : speaker_src) {
		num++;
		//评委打分
		deque<double>score_d;
		//cout << "编号为" << it << "的选手得分如下" << endl;
		for (int i = 0; i < 10; i++) {
			double score =(rand() % 401 + 600)/10.f;//600~1000;
			//cout << score << " ";
			score_d.push_back(score);
		}
		//cout << endl;
		sort(score_d.begin(), score_d.end(),greater<double>());
		score_d.pop_front();//去除最高分
		score_d.pop_back();//去除最低分
		double sum = accumulate(score_d.begin(),score_d.end(),0.0f);//总分
		double aver = sum / (double)score_d.size();//平均分
		//将平均分放入到map容器中
		this->m_speaker[it].m_Score[this->m_index-1] = aver;
		//将打分的数据放入到临时的小组
		groupScore.insert(make_pair(aver,it));//（得分，编号）
		//每6人去出前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (auto &i : groupScore) {
				cout << "编号：" << i.second << " 姓名:" << this->m_speaker[i.second].speaker_Name << "  分数：" << i.first << endl;
			}
			//取走前三名
			int count = 0;
			for (auto& i : groupScore) {
				count++;
				if (count > 3) break;
				if (this->m_index == 1) {
					this->first_winners_numbers.push_back(i.second);
				}
				else {
					this->speaker_victory.push_back(i.second);
				}
			}
			groupScore.clear();
		}
		//打印平均分
		//cout << "编号为：" << it << "   姓名为：" << this->m_speaker[it].speaker_Name << "的选手得分： " << aver << endl;
	}
	cout << "-------------第" << this->m_index << "轮比赛结束-------------" << endl;
}

void SpeechManager::printWinners(vector<int>& p) {
	cout << "-------------第" << this->m_index << "轮比赛晋级结果如下------------" << endl;
	for (auto it : p) {
		cout << "编号:" << it << "  姓名:" << this->m_speaker[it].speaker_Name << "  成绩:" << this->m_speaker[it].m_Score[this->m_index] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加的方式写文件
	//将每个选手的数据写入文件中
	for (auto& it : this->speaker_victory) {
		ofs << it << "," << this->m_speaker[it].speaker_Name << "," << this->m_speaker[it].m_Score[1] << ",";
	}
	ofs << endl;
	//关闭
	ofs.close();
	cout << "保存完成" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::startSpeech() {
	//第一轮比赛开始
	this->m_index = 1;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContent();
	//3.显示晋级结果
	this->printWinners(this->first_winners_numbers);
	this->main_interface();
	//第二轮开始比赛
	this->m_index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContent();
	//3.显示最终结果
	this->printWinners(this->speaker_victory);
	//保存结果
	this->saveRecord();
	cout << "本届比赛完成！！！" << endl;
	//重置比赛
	//初始化属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//获取往届记录
	this->loadRecord();
	system("pause");
	system("cls");
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符，放回来
	string data;
	int index = 0;
	while (ifs >> data) {
		int pos = -1;//查到逗号位置的变量
		int start = 0;
		vector<string>v;//存放9个string字符串
		while (true) {
			pos = data.find(',',start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件不存在或者文件为空！" << endl;
	}
	for (auto& i : this->m_record) {
		cout << "-----------第" << i.first+1 << "比赛的结果-----------" << endl;
		cout << "冠军编号：" << i.second[0] << " 冠军姓名:" << i.second[1] << " 冠军得分：" << i.second[2] << endl;
		cout << "亚军编号：" << i.second[3] << " 亚军姓名:" << i.second[4] << " 亚军得分：" << i.second[5] << endl;
		cout << "季军编号：" << i.second[6] << " 季军姓名:" << i.second[7] << " 季军得分：" << i.second[8] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "是否确认要清空文件数据" << endl;
	cout << "1.确认" << endl;
	cout << "2.否认" << endl;
	int choice = 0;
	while (cin >> choice) {
		if (choice == 1 || choice == 2) {
			break;
		}
	}
	if (choice == 1) {
		ofstream ofs;
		//确认清空
		ofs.open("speech.csv", ios::trunc);
		ofs.close();
		//初始化属性
		this->initSpeech();
		//创建选手
		this->createSpeaker();
		//获取往届记录
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}
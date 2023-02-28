#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include "speaker.h"
#include <deque>
#include <numeric>
#include <string>
#include <fstream>

using namespace std;

//设计演讲比赛的管理类
class SpeechManager {
public:
	//构造函数
	SpeechManager();
	//主界面
	void main_interface();
	//退出功能
	void exitSystem();
	//初始化容器和属性
	void initSpeech();
	//创建选手
	void createSpeaker();
	//比赛流程控制
	void startSpeech();
	//比赛抽签
	void speechDraw();
	//比赛函数
	void speechContent();
	//打印结果
	void printWinners(vector<int>&p);
	//保存结果
	void saveRecord();
	//查看往届记录
	void loadRecord();
	//展示往届记录
	void showRecord();
	//清空记录功能实现
	void clearRecord();
	//析构函数
	~SpeechManager();

	//成员属性
	//保存第一轮比赛选手编号
	vector<int>speaker_numbers;
	//第一轮晋级选手编号
	vector<int>first_winners_numbers;
	//胜出前三名选手编号容器
	vector<int>speaker_victory;
	//存放编号以及对应具体选手容器
	map<int, Speaker>m_speaker;
	//往届记录
	map<int, vector<string>>m_record;
	//文件是否存在
	bool fileIsEmpty;
	//存放比赛轮数
	int m_index;

};

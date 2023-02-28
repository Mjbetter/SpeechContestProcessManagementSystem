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

//����ݽ������Ĺ�����
class SpeechManager {
public:
	//���캯��
	SpeechManager();
	//������
	void main_interface();
	//�˳�����
	void exitSystem();
	//��ʼ������������
	void initSpeech();
	//����ѡ��
	void createSpeaker();
	//�������̿���
	void startSpeech();
	//������ǩ
	void speechDraw();
	//��������
	void speechContent();
	//��ӡ���
	void printWinners(vector<int>&p);
	//������
	void saveRecord();
	//�鿴�����¼
	void loadRecord();
	//չʾ�����¼
	void showRecord();
	//��ռ�¼����ʵ��
	void clearRecord();
	//��������
	~SpeechManager();

	//��Ա����
	//�����һ�ֱ���ѡ�ֱ��
	vector<int>speaker_numbers;
	//��һ�ֽ���ѡ�ֱ��
	vector<int>first_winners_numbers;
	//ʤ��ǰ����ѡ�ֱ������
	vector<int>speaker_victory;
	//��ű���Լ���Ӧ����ѡ������
	map<int, Speaker>m_speaker;
	//�����¼
	map<int, vector<string>>m_record;
	//�ļ��Ƿ����
	bool fileIsEmpty;
	//��ű�������
	int m_index;

};

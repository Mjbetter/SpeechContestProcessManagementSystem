#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Speaker {
public:
	Speaker(string name, int age);
	Speaker();
	string speaker_Name;
	int speaker_Age;
	double m_Score[2];//最多有两轮分数
};
#include <iostream>
#include "speechManager.h"
#include <ctime>
using namespace std;

int main() {
	//添加随机数种子
	srand((unsigned int)time(NULL));
	//创建管理类对象
	SpeechManager sm;
	int num = 0;
	while (1) {
		system("cls");
		sm.main_interface();
		cin >> num;
		switch (num) {
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			return 0;
		default:
			system("cls");
			break;
		}
	}
	system("pause"); 
	return 0;
}
#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech(); 
	//����12��ѡ��
	this->createSpeaker();
	//��������ļ�¼
	this->loadRecord();
}

void SpeechManager::main_interface() {
	cout << "      ��ӭ�μ��ݽ�����      " << endl;
	cout << "      1.��ʼ�ݽ�����        " << endl;
	cout << "      2.�鿴����ļ�¼      " << endl;
	cout << "      3.��ձ�����¼        " << endl;
	cout << "      0.�˳���������        " << endl;
	cout << "      ������ѡ�����ţ�";
}

void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::initSpeech() {
	//�������ÿ�
	this->speaker_numbers.clear();
	this->first_winners_numbers.clear();
	this->speaker_victory.clear();
	this->m_speaker.clear();
	this->m_record.clear();
	//��ʼ����������
	this->m_index = 1;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker speaker(name,i);
		for (int j = 0; j < 2; j++) {
			speaker.m_Score[j] = 0;
		}
		//����ѡ�ֵı��
		this->speaker_numbers.push_back(i + 10001);
		//ѡ�ֱ���Լ���Ӧѡ�� ���뵽map������
		this->m_speaker.insert(make_pair(i + 10001, speaker));

	}
}

void SpeechManager::speechDraw() {
	cout << "-----------��" << this->m_index << "�ֱ���ѡ�����ڳ�ǩ-----------" << endl;
	cout << "" << endl;
	cout << "��ǩ����ݽ�˳������:" << endl;

	if (this->m_index == 1) {
		//��һ�ֱ���
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
	cout << "-------------��" << this->m_index << "�ֱ�����ʽ��ʼ-------------" << endl;
	//׼����ʱ�����������ʱ�ɼ�
	multimap<double, int, greater<double>>groupScore;
	//��¼��Ա���� 6��һ��
	int num = 0;
	vector<int>speaker_src;//����ѡ������
	if (this->m_index == 1) {
		speaker_src = this->speaker_numbers;
	}
	else {
		speaker_src = this->first_winners_numbers;
	}
	//��������ѡ�ֽ��б���
	for (auto &it : speaker_src) {
		num++;
		//��ί���
		deque<double>score_d;
		//cout << "���Ϊ" << it << "��ѡ�ֵ÷�����" << endl;
		for (int i = 0; i < 10; i++) {
			double score =(rand() % 401 + 600)/10.f;//600~1000;
			//cout << score << " ";
			score_d.push_back(score);
		}
		//cout << endl;
		sort(score_d.begin(), score_d.end(),greater<double>());
		score_d.pop_front();//ȥ����߷�
		score_d.pop_back();//ȥ����ͷ�
		double sum = accumulate(score_d.begin(),score_d.end(),0.0f);//�ܷ�
		double aver = sum / (double)score_d.size();//ƽ����
		//��ƽ���ַ��뵽map������
		this->m_speaker[it].m_Score[this->m_index-1] = aver;
		//����ֵ����ݷ��뵽��ʱ��С��
		groupScore.insert(make_pair(aver,it));//���÷֣���ţ�
		//ÿ6��ȥ��ǰ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С���������" << endl;
			for (auto &i : groupScore) {
				cout << "��ţ�" << i.second << " ����:" << this->m_speaker[i.second].speaker_Name << "  ������" << i.first << endl;
			}
			//ȡ��ǰ����
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
		//��ӡƽ����
		//cout << "���Ϊ��" << it << "   ����Ϊ��" << this->m_speaker[it].speaker_Name << "��ѡ�ֵ÷֣� " << aver << endl;
	}
	cout << "-------------��" << this->m_index << "�ֱ�������-------------" << endl;
}

void SpeechManager::printWinners(vector<int>& p) {
	cout << "-------------��" << this->m_index << "�ֱ��������������------------" << endl;
	for (auto it : p) {
		cout << "���:" << it << "  ����:" << this->m_speaker[it].speaker_Name << "  �ɼ�:" << this->m_speaker[it].m_Score[this->m_index] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ�
	//��ÿ��ѡ�ֵ�����д���ļ���
	for (auto& it : this->speaker_victory) {
		ofs << it << "," << this->m_speaker[it].speaker_Name << "," << this->m_speaker[it].m_Score[1] << ",";
	}
	ofs << endl;
	//�ر�
	ofs.close();
	cout << "�������" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::startSpeech() {
	//��һ�ֱ�����ʼ
	this->m_index = 1;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContent();
	//3.��ʾ�������
	this->printWinners(this->first_winners_numbers);
	this->main_interface();
	//�ڶ��ֿ�ʼ����
	this->m_index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContent();
	//3.��ʾ���ս��
	this->printWinners(this->speaker_victory);
	//������
	this->saveRecord();
	cout << "���������ɣ�����" << endl;
	//���ñ���
	//��ʼ������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//��ȡ�����¼
	this->loadRecord();
	system("pause");
	system("cls");
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ����Ż���
	string data;
	int index = 0;
	while (ifs >> data) {
		int pos = -1;//�鵽����λ�õı���
		int start = 0;
		vector<string>v;//���9��string�ַ���
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
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	}
	for (auto& i : this->m_record) {
		cout << "-----------��" << i.first+1 << "�����Ľ��-----------" << endl;
		cout << "�ھ���ţ�" << i.second[0] << " �ھ�����:" << i.second[1] << " �ھ��÷֣�" << i.second[2] << endl;
		cout << "�Ǿ���ţ�" << i.second[3] << " �Ǿ�����:" << i.second[4] << " �Ǿ��÷֣�" << i.second[5] << endl;
		cout << "������ţ�" << i.second[6] << " ��������:" << i.second[7] << " �����÷֣�" << i.second[8] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "�Ƿ�ȷ��Ҫ����ļ�����" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int choice = 0;
	while (cin >> choice) {
		if (choice == 1 || choice == 2) {
			break;
		}
	}
	if (choice == 1) {
		ofstream ofs;
		//ȷ�����
		ofs.open("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ������
		this->initSpeech();
		//����ѡ��
		this->createSpeaker();
		//��ȡ�����¼
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}
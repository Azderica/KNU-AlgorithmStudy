#include <iostream>
#include <string>
#include <queue>
using namespace std;

int solution(string s);
int main() {
	string temp;
	cin >> temp;
	cout << solution(temp);

}
int solution(string s) {
	int answer = 99999;
	int string_length = 0;
	
	queue <string> comp;
	string temp;
	string count_string;
	vector <string> result;

	int count = 1; // �̰� � ������
	for (int token = 1; token < s.size(); token++) {

			for (int i = 0; i < s.size() ; i = i + token) {
				comp.push(s.substr(i, token));
			}
			while (!comp.empty()) {
				temp = comp.front();
				comp.pop();
				while (!comp.empty()) {
					if (temp.compare(comp.front()) != 0) // �����ʴ�
					{
						break;
					}
					comp.pop();
					count++;
				}
				if (count > 1) {
					//���⼭ string to temp
					count_string=to_string(count);
					result.push_back(count_string);
				}
				result.push_back(temp);
				count = 1;
			}
			//vector ũ�� ����ϰ� vector �� queue �ʱ�ȭ
			for (int i = 0; i < result.size(); i++) {
				string_length += result[i].size();
			}
			if (answer > string_length) {
				answer = string_length;
			}
			string_length = 0;
			result.clear();
			result.resize(0);
	}
	return answer;
}

/*#include <string>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int solution(string s) {
	int answer = 99999;
	int string_length = 0;
	
	queue <string> comp;
	string temp;
	string count_string;
	vector <string> result;

	int count = 1; // �̰� � ������
	for (int token = 1; token < s.size(); token++) {

			for (int i = 0; i < s.size() ; i = i + token) {
				comp.push(s.substr(i, token));
			}
			while (!comp.empty()) {
				temp = comp.front();
				comp.pop();
				while (!comp.empty()) {
					if (temp.compare(comp.front()) != 0) // �����ʴ�
					{
						break;
					}
					comp.pop();
					count++;
				}
				if (count > 1) {
					//���⼭ string to temp
					count_string=to_string(count);
					result.push_back(count_string);
				}
				result.push_back(temp);
				count = 1;
			}
			//vector ũ�� ����ϰ� vector �� queue �ʱ�ȭ
			for (int i = 0; i < result.size(); i++) {
				string_length += result[i].size();
			}
			if (answer > string_length) {
				answer = string_length;
			}
			string_length = 0;
			result.clear();
			result.resize(0);
	}
	return answer;
}*/
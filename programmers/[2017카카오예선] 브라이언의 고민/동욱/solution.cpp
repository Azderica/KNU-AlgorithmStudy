#include <string>
#include <iostream>
#include <ctype.h> //isupper����Ҷ��
#include <vector>
using namespace std;

bool isUsed[26];
string Sentence;
string answer = "";
int rule1(int start_index, char curAlphabet,char curRule2Alphabet) {//ù° ���ڰ� �빮�� ���� �ҹ��� �빮�� �ݺ�
	answer += Sentence[start_index];
	curAlphabet = Sentence[start_index + 1];
	if (isupper(curAlphabet)) {//��Ģ1���� 2��°���ڰ� �빮���ΰ��
		for (int i = 1; i < Sentence.size() - start_index; i++) {
			if (isupper(Sentence[start_index + i])) {//����� ���°��
				answer += Sentence[start_index + i];
			}
			else {
				return start_index + i - 1;
			}
		}
	}
	if (isUsed[curAlphabet - 'a']) {//��������϶�
		answer = "invalid";
		return 0;
	}
	isUsed[curAlphabet - 'a'] = true; //��� ó��
	int small_cnt = 0;
	for (int i = 1; i < Sentence.size() - start_index; i++) {
		if (i % 2 == 0) { //�빮�ڳ��;ߵ�
			if (isupper(Sentence[start_index + i])) {//����� ���°��
				answer += Sentence[start_index + i];
			}
			else {//�ҹ��� ���ö�
				if (isUsed[Sentence[start_index + i]-'a']) {//����� ���ö�
					answer = "invalid";
					return 0;
				}
				return start_index + i - 1; //������ index ��ȯ
			}
		}
		else {// �ҹ��� ���;ߵ� ����� ������ �׳� ��� 
			if (isupper(Sentence[start_index + i])) {//�빮�� �ǳ��°��
				if (small_cnt == 1) {
					if (isupper(Sentence[start_index + i+1])) {
						isUsed[curAlphabet - 'a'] = false;
						answer.pop_back();
						return start_index;
					}
				}
				return start_index + i - 1;
			
			}
			else {
				if (Sentence[start_index + i] != curAlphabet) {//�ٸ� ��ȣ�� ���ڱ� ���°��
					if (isUsed[Sentence[start_index + i]-'a']) {//�����ȣ
						answer = "invalid";
						return 0;
					}
					else {
						if(small_cnt==1&&curRule2Alphabet==NULL){
							isUsed[curAlphabet - 'a'] = false;
							answer.pop_back();
							return start_index;
						}
						return start_index + i - 1;
					}
				}
				else {
					small_cnt++;
				}
			}
			
			
		}
	}
	return Sentence.size();
}
int rule2(int i, char curAlphabet) {//ù° ���ڰ� �ҹ��ڸ� �� �빮�� �����ٰ� �ҹ���
	i++;//���� ���ں��� Ȯ���ص��Ǽ�
	int small_cnt = 1;
	for (; i < Sentence.size(); i++) {
		if (!isupper(Sentence[i])) {//�ҹ���
			if (Sentence[i] != curAlphabet) { //�ٸ��ҹ��� ���ö�
				if (small_cnt != 1||answer.size()<=0) {
					answer = "invalid";
					return 0;
				}
				else {//��Ģ 2�� �ѹ��� �����ϼ��� �ִ�.
					if (!isUsed[Sentence[i]-'a']) {
						answer.pop_back();
						isUsed[curAlphabet - 'a'] = false;
						i = rule1(i-1, NULL,curAlphabet);
						if (Sentence[i + 1] == curAlphabet) {
							isUsed[curAlphabet - 'a'] = true;
							return i + 1;
						}
						else {
							answer = "invalid";
							return 0;
						}
					}
				}
					
			}
			else {
				return i-1;
			}
			
		}
		else {//�빮��
			answer += Sentence[i];
		}
	}
}

string solution(string sentence) {
	for (int i = 0; i < 26; i++)
		isUsed[i] = false;
	Sentence = sentence;
	answer = "";
	if (sentence.find(" ") != string::npos) {
		answer = "invalid";
		return answer;
	}
	for (int i = 0; i < sentence.size(); i++) {
		if (isupper(sentence[i])) {//1�̸� �빮�� 0�̸�ҹ���
			i = rule1(i,NULL,NULL);
			if (i==0) {
				return answer;
			}
		}
		else {//�ҹ���
			int idx = sentence[i] - 'a';
			if (!isUsed[idx]) {
				isUsed[idx] = true;
				i=rule2(i,sentence[i]);
				if (i==0) {
					return answer;
				}
			}
		}
		if(answer.size()>0 && answer[answer.size()-1]!=' ')
			answer += " ";
	}
	if (answer.size() <= 0) {
		return "invalid";
	}
	while (answer[answer.size() - 1] == ' ') {
		answer.pop_back();
		if (answer.size() <= 0) {
			return "invalid";
		}
	}
		
	
	return answer;
}

int main() {
	vector<string> v;
	v.push_back("HaEaLaLaObWORLDb");
	v.push_back("SpIpGpOpNpGJqOqA");
	v.push_back("AxAxAxAoBoBoB");
	v.push_back("abHELLObaWORLD");
	v.push_back("HaEaLaLaOWaOaRaLaD");
	v.push_back("aHELLOWORLDa");
	v.push_back("HaEaLaLObWORLDb"); //
	v.push_back("aHbEbLbLbOacWdOdRdLdDc");
	v.push_back("aBcAadDeEdvAvlElmEEEEm");
	v.push_back("AcAcABaBaB");//���� 2���� �ɼ��ִ�.
	v.push_back("AxAxAxABcBcBcB");
	v.push_back("AaABbBCcC");
	v.push_back("HELLOWORLD");
	v.push_back("AAAaBaAbBBBBbCcBdBdBdBcCeBfBeGgGGjGjGRvRvRvRvRvR");
	v.push_back("a");
	v.push_back("A");
	v.push_back("aA");
	v.push_back("Aa");
	v.push_back("bTxTxTaTxTbkABaCDk");
	v.push_back("TxTxTxbAb");
	v.push_back("HaEaLaLaObWORLDbSpIpGpOpNpGJqOqAdGcWcFcDdeGfWfLeoBBoAAAAxAxAxAA");
	v.push_back("AxAxAxA");
	v.push_back("AA");
	v.push_back("oBBoA");
	v.push_back("aGbWbFbDakGnWnLk");
	v.push_back("A B");
	for (int i = 0; i < v.size(); i++) {
		cout <<i<<" : '"+v[i]<< endl;
		cout << "' -> " << "'" + solution(v[i]) + "'" << endl;
	}

}
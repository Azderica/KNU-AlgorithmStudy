#include    <iostream>
#include    <string>
#include    <vector>
#include    <deque>
#include    <algorithm>
using namespace std;

bool isFinished(vector<int> dist, deque<int> weakList, int cnt) {
	sort(dist.begin(), dist.end());
	
	do {
		int start = 0;
		for (int i = 0, j=start; i < cnt; i++) {
			// i�� ��� ��ȣ, j�� �� ����� �� �� �ִ� ������� ��ġ
			int possibleDist = weakList[start] + dist[i];
			while (j < weakList.size()) {
				if (weakList[j] <= possibleDist)
					j++;		// �� ���������� �� ����
				else {
					start = j;	// ���� ������� �ñ�
					break;
				}
			}
			// ��������� �� �� ���
			if (j == weakList.size()) {
				return true;
			}
		}
	} while (next_permutation(dist.begin(), dist.end()));

	return false;
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	deque<int> weakList;

	// ������� ������ 0
	if (weak.size() == 0)
		return 0;

	// ��� ���� �ø��鼭 Ȯ��
	for (int i = 1; i <= dist.size(); i++) {                 // ��� ��
		// weak list ����
		for (int j = 0; j < weak.size(); j++)
			weakList.push_back(weak[j]);
		for (int j = 0; j < weak.size(); j++) {

			// �ش� ������� �ذ�Ǹ� ����
			if (isFinished(dist, weakList, i))
				return i;

			int key = weakList.front();
			weakList.pop_front();
			weakList.push_back(key + n);
		}
		weakList.clear();
	}
	return -1;
}

int main() {
	cout << solution(12, { 1, 5, 6, 10 }, { 1, 2, 3, 4 }) << "\n";
	cout << solution(12, { 1, 3, 4, 9, 10 }, { 3, 5, 7 }) << "\n";
}
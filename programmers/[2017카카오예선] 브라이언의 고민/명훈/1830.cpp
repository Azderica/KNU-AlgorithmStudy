#include	<iostream>
#include	<string>
#include	<string.h>
#include	<set>
using namespace std;

bool visited[26];
set<string> ans;

void dfs(string sentence, int cnt) {
	// end state, 
	if (cnt == 0) {
		//cout << sentence << "\n";
		ans.insert(sentence);
		return;
	}
	
	for (int i = 0; i < 26; i++) {
		// �ҹ��� ���ĺ�(������)�� �ִ� ���
		if (visited[i]) {
			string res = "";
			char ad_key = 'a' + i;
			int ad_key_start = sentence.find(ad_key);
			
			int t_count = 0;
			for (int j = ad_key_start; j < sentence.length(); j++) {
				// ����Ű ���� Ȯ��
				if (sentence[j] == ad_key)
					t_count++;
			}

			// ���� ����Ű�� 2���� �ƴϸ� ������ �������� 1
			int ad_pattern = 0;
			if (t_count != 2)
				ad_pattern = 1;
			else
				ad_pattern = 2;		// 2���� ��� ������ �������� 2�� ����.
			// �پ� �ִ� ���� ����.

			if (ad_pattern == 1) {
				// ���� ���� 1���� ���
				if (ad_key_start != 1) {
					// ������ 1�� ��ġ�� �ƴ� ��쿡�� �տ� ��ĭ�� �־���Ѵ� �ʿ�� ����.
					res += sentence.substr(0, ad_key_start - 2);	//
					if(sentence[ad_key_start - 2] != ' ')
						res += " ";
				}
				// ù��° �� ���ְ�
				res += sentence[ad_key_start - 1];
				// �� �ڷ� ������ �ֵ� ����ܾ� ���� �� ���ֱ�.
				int j;
				for (j = ad_key_start; j < sentence.length(); j+= 2) {
					if (sentence[j] == ad_key)
						res += sentence[j + 1];
					else
						break;
				}
				// ���� j�� ��ġ���� ������ �����ֱ�.
				if (j != sentence.length()) {
					if(sentence[j] != ' ')
						res += " ";
					res += sentence.substr(j);
				}
			}
			else {
				// ���� ���� 2���� ���
				if (ad_key_start != 0) {
					// ���� ��ġ�� 0�� �ƴ� ���, ���� ����� �� �����ش�.
					res += sentence.substr(0, ad_key_start);
					if(sentence[ad_key_start - 1] != ' ')
						res += " ";
				}
				int j;
				for (j = ad_key_start + 1; j < sentence.length(); j++) {
					if (sentence[j] != ad_key)	// ����Ű�� �ƴϸ� ��
						res += sentence[j];
					else						// ����Ű�� ������ ��ž
						break;
				}
				// j�� ���� �ƴ� ���
				if (j != sentence.length() - 1) {
					if(sentence[j+1] != ' ')
						res += " ";
					res += sentence.substr(j + 1);
				}
			}
			
			// check
			//cout << ad_pattern << " " << res << "\n";

			visited[i] = false;
			dfs(res, cnt - 1);
			visited[i] = true;
		}
	}
}

string solution(string sentence) {
    // initialize
	int ad_count = 0;
	ans.clear();
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < sentence.length(); i++){
		if (sentence[i] >= 'a' && sentence[i] <= 'z')
			visited[(sentence[i] - 'a')] = true;
		if (sentence[i] == ' ')	// �߸��� input
			return "invalid";
	}
		
	for (int i = 0; i < 26; i++)
		if (visited[i])
			ad_count++;

	// solution
	dfs(sentence, ad_count);

	// output
	if (ans.size() != 1)
		return "invalid";
	else {
		string ans_str = *(ans.begin());
		if (ans_str.find("  ") != string::npos)
			return "invalid";
		return ans_str;
	}
}

int main() {
	cout << solution("HaEaLaLaObWORLDb") << "\n";
	cout << solution("SpIpGpOpNpGJqOqA") << "\n";
	cout << solution("AxAxAxAoBoBoB") << "\n";
}
#include	<iostream>
#include	<algorithm>
using namespace std;

#define MAX 10

struct horse {
	int id;		// �� �ѹ�
	int loc;	// ���� ��ġ
	bool arrived;
};

int board_len[4] = { 21, 8, 7, 8 };
int board[4][22] = {
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 0},
	{10, 13, 16, 19, 25, 30, 35, 40, 0},
	{20, 22, 24, 25, 30, 35, 40, 0},
	{30, 28, 27, 26, 25, 30, 35, 40, 0}
};

int dice[MAX];
int order[MAX];
int max_score = -1;

bool isInBoard(horse Horse[4], int idx) {
	if (Horse[idx].loc < board_len[Horse[idx].id])
		return true;
	return false;
}

int getCross(horse Horse[4], int idx) {
	if (Horse[idx].id == 0) {
		if (Horse[idx].loc == 5 || Horse[idx].loc == 10 || Horse[idx].loc == 15)
			return Horse[idx].loc / 5;
		else
			return 0;
	}
	return 0;
}

bool isAnyHorse(horse Horse[4], int idx) {
	for (int i = 0; i < 4; i++) {
		if (i != idx) {
			// �������� ���� ���
			if (board[Horse[idx].id][Horse[idx].loc] == board[Horse[i].id][Horse[i].loc]) {
				if (Horse[idx].id == Horse[i].id)
					return true;		// �ƿ� ��ΰ� ��ġ�� ���
				else if (Horse[idx].loc >= board_len[Horse[idx].id] - 4 && Horse[i].loc >= board_len[Horse[i].id] - 4)
					return true;		// ��ΰ� ��ġ�� �Ķ��� 4ĭ(25, 30, 35, 40)���� ������ ��� 
				else
					return false;
			}
		}
	}
	return false;
}

void dfs(int cnt) {
	if (cnt == 10) {
		// ���� �ڵ�
		horse Horse[4];
		int score = 0;
		for (int i = 0; i < 4; i++)	// init
			Horse[i] = { 0, 0, false };

		for (int i = 0; i < 10; i++) {
			int idx = order[i];		// idx �� i��° ������ ��
			int move = dice[i];		// move �� i��°�� ������ ĭ
			if (isInBoard(Horse, idx)) {	// �ʾȿ� �ִ� ��츸
				Horse[idx].loc += move;
				
				if (!isInBoard(Horse, idx)) {	// �ۿ� �������� ���, ����ó��
					Horse[idx].arrived = true;
					Horse[idx].loc = board_len[Horse[idx].id];
				}
				score += board[Horse[idx].id][Horse[idx].loc];

				// ��ΰ� �ٲ�� ��� üũ
				int new_id = getCross(Horse, idx);
				if (new_id) {
					Horse[idx].id = new_id;
					Horse[idx].loc = 0;
				}

				// ���࿡ ������ ���ߴµ� ��ġ�� ��찡 ������ �ٷ� ����
				if (!Horse[idx].arrived && isAnyHorse(Horse, idx))
					return;
			}
			else
				return;
		}
		max_score = max(max_score, score);
		return;
	}

	for (int i = 0; i < 4; i++) {
		order[cnt] = i;
		dfs(cnt + 1);
	}
}


int main() {
	// input
	for (int i = 0; i < MAX; i++)
		scanf("%d", &dice[i]);

	// solution
	dfs(0);

	// output
	cout << max_score << "\n";
	return 0;
}
#include	<iostream>
#include	<deque>
#include	<map>
using namespace std;

#define MAX 100 + 1

enum {BLANK, SNAKE, APPLE};
pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };	// R, D, L, U
int N, K, L;
int board[MAX][MAX];
deque<pair<int, int>> snake;
map<int, char> comm;

int main() {
	// input
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int r, c;
		scanf("%d %d", &r, &c);
		board[r][c] = APPLE;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int t, d;
		scanf("%d %c", &t, &d);
		comm.insert({ t, d });
	}

	// solution
	board[1][1] = SNAKE;
	snake.push_back({ 1, 1 });

	int answer = 0, d = 0;
	while (true) {
		answer++;
		// y, x�� ���� ��ġ
		
		int nextY = snake[0].first + dir[d].first;
		int nextX = snake[0].second + dir[d].second;

		// ���� �����ų�, �ڱ� ���� ���� ���. ����
		if (nextY < 1 || nextY > N || nextX < 1 || nextX > N || board[nextY][nextX] == SNAKE) {
			break;
		}

		// ���� ��ġ�� ����� �ƴϸ� ���� ����
		if (board[nextY][nextX] != APPLE) {
			pair<int, int> tail = snake[snake.size() - 1];
			snake.pop_back();
			board[tail.first][tail.second] = BLANK;
		}

		// ����
		board[nextY][nextX] = SNAKE;
		snake.push_front({ nextY, nextX });

		// ���� �ٲٱ�
		if (comm.find(answer) != comm.end()) {	// ã�� ���
			if (comm.find(answer)->second == 'L')
				d = (d + 3) % 4;
			else
				d = (d + 1) % 4;
		}
	}

	// output
	cout << answer << "\n";

	return 0;
}
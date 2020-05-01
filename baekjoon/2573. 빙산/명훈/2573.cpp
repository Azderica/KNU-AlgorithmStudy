#include	<iostream>
#include	<queue>
#include	<algorithm>
using namespace std;

// static
const int MAX = 300;
const pair<int, int> dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
// variable
int board[MAX][MAX], cpyboard[MAX][MAX];
int N, M;
int answer;					// year

bool visited[MAX][MAX];
queue<pair<int, int>> q;

// ������ üũ
bool isInRange(int y, int x) {
	if (y < 0 || y > N || x < 0 || x > M)
		return false;
	return true;
}

// ���� ������Ʈ
void updateGlacier() {
	// origin -> cpy
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpyboard[i][j] = board[i][j];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j]) {
				int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int nextY = i + dir[d].first;
					int nextX = j + dir[d].second;
					
					// �������̰� �ֺ��� �ٴ��� ���
					if (isInRange(nextY, nextX) && board[nextY][nextX] == 0) {
						cnt++;
					}
				}

				if (cpyboard[i][j] >= cnt)
					cpyboard[i][j] -= cnt;
				else
					cpyboard[i][j] = 0;
			}
		}
	}

	// cpy -> origin
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board[i][j] = cpyboard[i][j];
}


// ���ϰ� �ΰ��� �и��Ǿ� ������ ����
bool isSeperated() {
	bool isOne = false;		// �Ѱ����� üũ
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// ���ϰ� �ƴ� ���
			if (board[i][j] && !visited[i][j]) {
				if (!isOne) {
					q.push({ i, j });
					visited[i][j] = true;
					isOne = true;

					while (!q.empty()) {
						int curY = q.front().first;
						int curX = q.front().second;
						q.pop();

						for (int d = 0; d < 4; d++) {
							int nextY = curY + dir[d].first;
							int nextX = curX + dir[d].second;

							if (isInRange(nextY, nextX) && board[nextY][nextX] && !visited[nextY][nextX]) {
								q.push({ nextY, nextX });
								visited[nextY][nextX] = true;
							}
						}
					}
				}
				else
					return true;	// �ι�° ����� �ִ� ���	
			}
		}
	}
	return false;
}

// ���ϰ� ������  true
bool isNoGlacier() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j])
				return false;
	return true;
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	// solution
	while (true) {
		answer++;

		updateGlacier();

		// check code
	/*	cout << answer << "\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				printf("%d ", board[i][j]);
			cout << "\n";
		}*/

		if (isSeperated()) {
			break;
		}
		if (isNoGlacier()) {
			answer = 0;
			break;
		}
	}

	// output
	cout << answer << "\n";
	return 0;
}
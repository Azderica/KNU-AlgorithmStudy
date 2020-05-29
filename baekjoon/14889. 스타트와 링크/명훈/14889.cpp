#include	<iostream>
#include	<vector>
#include	<algorithm>
#include	<limits.h>
using namespace std;

const int MAX = 20 + 1;

int N;
int board[MAX][MAX];
int ans = INT_MAX;

int getTeamScore(vector<int> v) {
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			sum += board[v[i]][v[j]];
			sum += board[v[j]][v[i]];
		}
	}
	return sum;
}

int main() {
	// input
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &board[i][j]);

	// solution
	vector<int> ind;
	for (int i = 0; i < N / 2; i++) {
		ind.push_back(0);
		ind.push_back(1);
	}
	sort(ind.begin(), ind.end());
	
	//	combination
	do {
		vector<int> team1, team2;
		// make team 
		for (int i = 0; i < ind.size(); i++) {
			if (ind[i] == 1)
				team1.push_back(i);
			else
				team2.push_back(i);
		}

		// get Team Sum
		int teamScore_1 = getTeamScore(team1);
		int teamScore_2 = getTeamScore(team2);

		if (ans > abs(teamScore_1 - teamScore_2))
			ans = abs(teamScore_1 - teamScore_2);
	} while (next_permutation(ind.begin(), ind.end()));

	// output
	cout << ans << "\n";

	return 0;
}
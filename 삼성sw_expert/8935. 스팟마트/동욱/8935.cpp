#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int numN;
int numM;
int N[3001];
int M[101];
int dp[3001][101][101][2];

bool cmp_desc(const int a, const int b) {
	return a > b;
}


int findMaxResult(int iterN, int iter_selectedM, int iter_passM, int selected) {
	//��
	if (iterN >= numN && (iter_selectedM + iter_passM) >= numM)
		return 0;
	int &result = dp[iterN][iter_selectedM][iter_passM][selected]; //result�� ��Ī
	if (result != 0) //�̹̰���Ѱ�
		return result;
	if (selected) {//���Ⱑ ���õ�����
		if (iterN < numN) { //�ڿ� ���þ��ϰ� �ڿ� N�ö�
			result = max(result, findMaxResult(iterN + 1, iter_selectedM, iter_passM, 0));
		}
		if ((iter_selectedM + iter_passM) < numM) {//�ڿ� ���þ��ϰ� �ڿ� M�ö�
			result = max(result, findMaxResult(iterN, iter_selectedM, iter_passM + 1, 0));
		}
	}
	else {//���Ⱑ ���� �ȵ�����
		if (iterN < numN) {//�ڿ� N�ö�
			//�ڿ� ����
			result = max(result, N[iterN] + findMaxResult(iterN + 1, iter_selectedM, iter_passM, 1));
			//�ڿ� ���þ���
			result = max(result, findMaxResult(iterN + 1, iter_selectedM, iter_passM, 0));
		}
		if ((iter_selectedM + iter_passM) < numM) {//�ڿ� M�ö�
			//�ڿ� ����
			result = max(result, M[iter_selectedM] + findMaxResult(iterN, iter_selectedM + 1, iter_passM, 1));
			//�ڿ� ���þ���
			result = max(result, findMaxResult(iterN, iter_selectedM, iter_passM + 1, 0));
		}
	}
	return result;
}

int Testcase() {

	scanf("%d", &numN);
	for (int i = 0; i < numN; i++) {
		scanf("%d", &N[i]);
	}
	scanf("%d", &numM);
	for (int i = 0; i < numM; i++) {
		scanf("%d", &M[i]);
	}
	for (int i = 0; i <=numN; i++) {
		for (int j = 0; j <= numM; j++) {
			for (int k = 0; k <= numM; k++) {
				dp[i][j][k][0] = dp[i][j][k][1] = 0;
			}
		}
	}
	sort(M, M + numM, cmp_desc);
	return findMaxResult(0, 0, 0, 0);
}

int main() {
	int testcase;
	freopen("input.txt", "r", stdin);
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		printf("#%d %d\n", t, Testcase());
	}
}
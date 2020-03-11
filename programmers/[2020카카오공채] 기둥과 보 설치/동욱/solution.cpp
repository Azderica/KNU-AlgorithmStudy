#include <string>
#include <vector>
#include <iostream>

#define PILLAR 0
#define BEAM 1
#define DESTROY 0
#define BUILD 1
using namespace std;

vector<vector<vector<bool>>> structure;

bool existPillar(int x, int y, int n) {
	if (x<0 || y<0 || x>n || y>n)
		return false;
	return structure[x][y][PILLAR];
}
bool existBeam(int x, int y, int n) {
	if(x<0 || y<0 || x>n || y>n)
		return false;
	return structure[x][y][BEAM];
}

bool canMaintainBeam(int x, int y, int n) {
	if (existPillar(x, y - 1, n) || existPillar(x + 1, y - 1, n))//�����Ѱ��� ����� �ִ� ���
		return true;
	if (existBeam(x - 1, y, n) && existBeam(x + 1, y, n))// ���� ���� ������ ��ο� �Ѵ�������
		return true;
	return false;
}
bool canMaintainPillar(int x, int y, int n) {
	if (y == 0) //�ٴ�
		return true;
	//���� �Ǵ� �����ʿ� �����ְų� �ٷξƷ��� ����� �ִ� ���
	if (existBeam(x - 1, y, n) || existBeam(x, y, n) || existPillar(x, y - 1, n))
		return true;
	return false;
}

bool canDestroyBeam(int x, int y, int n) {
	if (existBeam(x, y, n)) {
		structure[x][y][BEAM]=false;
		if (existPillar(x, y, n)) {//���� ���ʳ��� ����� �ִ°��
			if (!canMaintainPillar(x, y, n)) {
				structure[x][y][BEAM] = true;
				return false;
			}
		}
		if (existPillar(x + 1, y, n)) {//���� �����ʳ��� ����� �ִ°��
			if (!canMaintainPillar(x + 1, y, n)) {
				structure[x][y][BEAM] = true;
				return false;
			}
		}
		if (existBeam(x - 1, y, n)) {// ���� ���ʿ� ���� �ִ� ���
			if (!canMaintainBeam(x - 1, y, n)) {
				structure[x][y][BEAM] = true;
				return false;
			}	
		}
		if (existBeam(x + 1, y, n)) {// ���� �����ʿ� ���� �ִ°��
			if (!canMaintainBeam(x + 1, y, n)) {
				structure[x][y][BEAM] = true;
				return false;
			}
		}
	}
	return true;
}



bool canDestroyPillar(int x, int y, int n) {
	if (existPillar(x, y, n)) {
		structure[x][y][PILLAR] = false;
		if (existPillar(x, y + 1, n)) {//���� ����� ������
			if (!canMaintainPillar(x,y+1,n)) {
				structure[x][y][PILLAR] = true;
				return false;
			}
				
		}
		if (existBeam(x - 1, y + 1, n)) {//���� ���� ���� ������
			if (!canMaintainBeam(x - 1, y + 1, n)) {
				structure[x][y][PILLAR] = true;
				return false;
			}
		}
		if (existBeam(x, y + 1, n)) {//���������� ���� ������
			if (!canMaintainBeam(x, y + 1, n)) {
				structure[x][y][PILLAR] = true;
				return false;
			}
		}
	}
	return true;
}

bool canBuildBeam(int x, int y, int n) {
	if (existPillar(x, y - 1, n) || existPillar(x + 1, y - 1, n)) //���� ���κ��� �����
		return true;
	else if (existBeam(x - 1, y, n) && existBeam(x + 1, y, n)) // ���� ���κ��� �ٸ����� ���ÿ���
		return true;
	return false;
}

bool canBuildPillar(int x, int y, int n) {
	if (y == 0)//�ٴ��϶�
		return true;
	else if (existBeam(x - 1, y, n) || existBeam(x, y, n))//���� ���� ������ ������
		return true;
	else if (existPillar(x, y - 1, n))//�Ǵٸ� ����� �϶�
		return true;
	return false;
}

void destroyBeam(int x, int y, int n){
	if (canDestroyBeam(x, y, n))
		structure[x][y][BEAM] = false;
}

void destroyPillar(int x, int y, int n) {
	if (canDestroyPillar(x, y, n)) {
		structure[x][y][PILLAR] = false;
	}
}

void buildBeam(int x, int y, int n) {
	if (canBuildBeam(x, y, n)) {
		structure[x][y][BEAM] = true;
	}
}

void buildPillar(int x, int y,int n) {
	if (canBuildPillar(x, y, n)) {
		structure[x][y][PILLAR] = true;
	}
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	structure.assign(n + 1, vector <vector<bool>>(n + 1, vector<bool>(2, false)));

	for (int i = 0; i < build_frame.size(); i++) {
		if (build_frame[i][2] == PILLAR) {//���
			if (build_frame[i][3] == DESTROY) {//����
				destroyPillar(build_frame[i][0], build_frame[i][1],n);
			}
			else {//��ġ
				buildPillar(build_frame[i][0], build_frame[i][1],n);
			}
		}
		else {//��
			if (build_frame[i][3] == DESTROY) {//����
				destroyBeam(build_frame[i][0], build_frame[i][1],n);
			}
			else {//��ġ
				buildBeam(build_frame[i][0], build_frame[i][1],n);
			}
		}
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < 2; k++) {
				if (structure[i][j][k])
					answer.push_back({ i,j,k });
			}
		}
	}
	return answer;
}

int main() {
	//vector<vector<int>> result = solution(5, { {1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},{5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1} });
	vector<vector<int>> result = solution(5, { {0,0,0,1},{2,0,0,1},{4,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{2,0,0,0},{1,1,1,0},{2,2,0,1} });

	for (int i = 0; i < result.size(); i++) {
		printf("[");
		for (int j = 0; j < result[i].size(); j++) {
			cout << result[i][j] << " ";
		}
		printf("]\n");
	}

}
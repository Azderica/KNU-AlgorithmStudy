#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct paper {
	int row;
	int col;
	int state;
};

vector <paper> init;
vector <paper> used;

int arr[10][10];
int visit[10][10];
bool comp(paper& x, paper& y);
void check_arr(int row, int col, int state);
int check5_5(int row, int col);
int check4_4(int row, int col);
int check3_3(int row, int col);
int check2_2(int row, int col);
int check1_1(int row, int col);
void main() {
	paper temp;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> arr[i][j];
			visit[i][j] = arr[i][j];
			if (arr[i][j] == 1) {
				temp.row = i;
				temp.col = j;
				temp.state = 0;
				init.push_back(temp);
			}
		}
	}
	sort(init.begin(), init.end(), comp);
	init.back();
}
bool comp(paper& x, paper& y) {
	if (x.row == y.row) {
		return x.col > y.col;
	}
	else {
		return x.row > y.row;
	}
}
//visit �� 1,2,3,4,5�� ����������
// init ���� use �� �� �� �̹� visit �Ǿ������� state 9�� push ���� count �� ������  ----
// ����ī��Ʈ�� ������ stack ���� ���, ���� ī��Ʈ�� �ٽ� ���������� ���� use���� ���� ���� �� ������ ���� �ٽ� init  // use�� 5�� �ȴٸ� �� ������ ���� ��� ������? --
//  use���� state �� 5�̸� �ٽ� init ���� case �� 6�̰��� ����ī��Ʈ �÷��ߵ� ;  ���� 9��� count ����ī��Ʈ�� �ȹٲ�  --
// ������ �����ų� 0�̰ų�( �̰� used�� �尡�ִ°� ���� �˻� )
void check_arr(int row, int col,int state) {
	paper temp;
	temp.row = row;
	temp.col = col;
	temp.state = state + 1;
	switch (temp.state) {
	case 1:
		if (check1_1(row, col) > 0) {
			used.push_back(temp);
		}
		break;
	case 2:
		if (check2_2(row, col) > 0) {
			used.push_back(temp);
		}
		break;
	case 3:
		if (check3_3(row, col) > 0) {
			used.push_back(temp);
		}
		break;
	case 4:
		if (check4_4(row, col) > 0) {
			used.push_back(temp);
		}
		break;
	case 5:
		if (check5_5(row, col) > 0) {
			used.push_back(temp);
		}
		break;
	}
}
int check5_5(int row, int col) {
	if (row + 4 >= 10) {
		return -1;
	}
	else if (col + 4 >= 10) {
		return -1;
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (visit[row+i][col+j] == 0) {
					return -1;
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				visit[row + i][col + j] = 0;
			}
		}
		return 1;
	}
}
int check4_4(int row, int col) {
	if (row + 3 >= 10) {
		return -1;
	}
	else if (col + 3 >= 10) {
		return -1;
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (visit[row+i][col+j] == 0) {
					return -1;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				visit[row + i][col + j] = 0;
			}
		}
		return 1;
	}
}
int check3_3(int row, int col) {
	if (row + 2 >= 10) {
		return -1;
	}
	else if (col + 2 >= 10) {
		return -1;
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (visit[row+i][col+j] == 0) {
					return -1;
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				visit[row + i][col + j] = 0;
			}
		}
		return 1;
	}
}
int check2_2(int row, int col) {
	if (row + 1 >= 10) {
		return -1;
	}
	else if (col + 1 >= 10) {
		return -1;
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (visit[row+i][col+j] == 0) {
					return -1;
				}
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				visit[row + i][col + j] = 0;
			}
		}
		return 1;
	}
}

int check1_1(int row, int col) {

	if (visit[row][col] == 0) {
			return -1;
	}
	visit[row][col] = 0;
	return 1;
}
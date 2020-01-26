#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct MapInfo {
	int nutriment;
	vector<int> trees;
}MapInfo;

int row_dir[8] = { -1,-1,-1,0,0,1,1,1 };
int col_dir[8] = { -1,0,1,-1,1,-1,0,1 };

int map_size, num_trees, year;

MapInfo Map[11][11];
int nutriments[11][11];
int dead_tree[11][11];

void Winter() {
	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			Map[i][j].nutriment += nutriments[i][j];
		}
	}
}

void Fall() {
	for (int r = 1; r <= map_size; r++) {
		for (int c = 1; c <= map_size; c++) {
			for (int t = 0; t < Map[r][c].trees.size(); t++) {
				if (Map[r][c].trees[t] % 5 == 0) {
					for (int i = 0; i < 8; i++) {
						int next_row = r + row_dir[i];
						int next_col = c + col_dir[i];
						if (next_row >= 1 && next_col >= 1 && next_row <= map_size && next_col <= map_size) {
							Map[next_row][next_col].trees.push_back(1);
							num_trees++; //��������
						}
					}
				}
			}

		}
	}
}

void Summer() {//�������� ����ֱ�
	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			if (dead_tree[i][j] != 0) {
				Map[i][j].nutriment += dead_tree[i][j];
				dead_tree[i][j] = 0;
			}	
		}
	}
}

void Spring() {
	//������ �ڽ��� ���̸�ŭ ��и԰� ���� 1����
	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			if (!Map[i][j].trees.empty()) {//������ ����
				sort(Map[i][j].trees.begin(), Map[i][j].trees.end());//���̾�ź��� ���� ��������
				for (int k = 0; k < Map[i][j].trees.size(); k++) {
					if (Map[i][j].trees[k] <= Map[i][j].nutriment) { //����ټ�������
						Map[i][j].nutriment -= Map[i][j].trees[k];//��иԱ�
						Map[i][j].trees[k]++;//��������
					}
					else {//��� ���ٶ�
						int cnt = 0;
						for (; k < Map[i][j].trees.size(); k++) {
							dead_tree[i][j] += (Map[i][j].trees[k] / 2);
							cnt++;
						}
						for (int t = 0; t < cnt; t++) {
							Map[i][j].trees.pop_back();
							num_trees--; //��������
						}
						break;
					}
				}
			}
		}
	}
	//����� �������� ���̰� ���
}

int main() {
	scanf("%d %d %d", &map_size, &num_trees, &year);

	for (int i = 1; i <= map_size; i++) {
		for (int j = 1; j <= map_size; j++) {
			scanf("%d", &nutriments[i][j]);
			Map[i][j].nutriment = 5; //�ʱⰪ�� 5
		}
	}
	for (int i = 0; i < num_trees; i++) {
		int r, c, age;
		scanf("%d %d %d", &r, &c, &age);
		Map[r][c].trees.push_back(age);
	}

	for (int i = 0; i < year; i++) {
		Spring();
		Summer();
		Fall();
		Winter();
	}
	printf("%d", num_trees);
}
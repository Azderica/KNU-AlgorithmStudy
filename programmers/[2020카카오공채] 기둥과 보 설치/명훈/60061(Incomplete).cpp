#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MAX 100 + 1
#define PILLAR  0
#define FLOOR   1
#define BOTH    2

int board[MAX][MAX];
pair<int, int> dir[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

bool isInRange(int y, int x, int n) {
    if (y < 0 || y > n || x < 0 || x > n)
        return false;
    return true;
}

// �Ǽ� �������� Ȯ��
bool isValidBuild(int n, int x, int y, int btype) {
    if (btype == FLOOR) {     // "��"
        // ���� �����̳� ������ �� �߿� �ϳ��� ����� ���
        if ((y >= 1 && board[y - 1][x] % 2 == PILLAR) || (isInRange(y - 1, x + 1, n) && board[y - 1][x + 1] % 2 == PILLAR))
            return true;
        // ���� ������ ���� ���
        if ((x >= 1 && board[y][x - 1] >= FLOOR) && (x < n && board[y][x + 1] >= FLOOR))
            return true;
        // �� �ܿ��� �׻� ����
        return false;
    }
    else {                   // "���"
        // ����� �ٴڿ� �ִ� ���
        if (y == 0)
            return true;
        // ����� �Ʒ��� ���� ���
        if (board[y][x] >= FLOOR || (x >= 1 && board[y][x - 1] >= FLOOR))
            return true;
        // ����� �Ʒ��� ����� ���
        if (y >= 1 && board[y - 1][x] % 2 == PILLAR)
            return true;
        // �� �ܿ��� �׻� ����
        return false;
    }
}

// ���� �������� Ȯ�� �� ����
void BuildDelete(int n, int x, int y, int btype) {
    if (btype == FLOOR) {     // "��"
        int tmp = board[y][x];  // ���� ���� ��� �����ϰ�
        if (tmp == BOTH)        // ������ ���·� �����ϰ�
            board[y][x] = PILLAR;
        else if (tmp == FLOOR && btype == FLOOR)
            board[y][x] = -1;
        else
            return;
        // ���� ���� �κ� �������� �� Ȯ��
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // �� �ֺ��� �ٽ� ���� �� ���ٸ� ����
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // ���� ������ �κ� �������� �� Ȯ��
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + 1 + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // �� �ֺ��� �ٽ� ���� �� ���ٸ� ����
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // �����ϹǷ� ������ �κ��� �����ؼ� return
        return;
    }
    else {               // "���"
        int tmp = board[y][x];  // ���� ���� ��� �����ϰ�
        if (tmp == BOTH)        // ������ ���·� �����ϰ�
            board[y][x] = FLOOR;
        else if (tmp == PILLAR && btype == PILLAR)
            board[y][x] = -1;
        else
            return;
        // ���� �Ʒ��� �κ� �������� �� Ȯ��
        for (int d = 0; d < 4; d++) {
            int nextY = y + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // �� �ֺ��� �ٽ� ���� �� ���ٸ� ����
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // ���� ���� �κ� �������� �� Ȯ��
        for (int d = 0; d < 4; d++) {
            int nextY = y + 1 + dir[d].first;
            int nextX = x + dir[d].second;
            if (isInRange(nextY, nextX, n) && board[nextY][nextX] != -1) {
                // �� �ֺ��� �ٽ� ���� �� ���ٸ� ����
                if (board[nextY][nextX] == BOTH) {
                    if (!isValidBuild(n, nextX, nextY, 0) || !isValidBuild(n, nextX, nextY, 0)) {
                        board[y][x] = tmp;
                        return;
                    }
                }
                if (!isValidBuild(n, nextX, nextY, board[nextY][nextX])) {
                    board[y][x] = tmp;
                    return;
                }
            }
        }
        // �����ϹǷ� ������ �κ��� �����ؼ� return
        return;
    }
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    // solution
    vector<vector<int>> ans;
    memset(board, -1, sizeof(board));
    for (int i = 0; i < build_frame.size(); i++) {
        vector<int> b_l = build_frame[i];

        if (b_l[3] == 1) {        // insert
            if (isValidBuild(n, b_l[0], b_l[1], b_l[2])) {
                if (board[b_l[1]][b_l[0]] == -1)
                    board[b_l[1]][b_l[0]] = b_l[2];
                else if (b_l[2] != board[b_l[1]][b_l[0]])
                    board[b_l[1]][b_l[0]] = 2;      // ������ ���
            }
        }
        else {                   // delete
            BuildDelete(n, b_l[0], b_l[1], b_l[2]);
        }
    }

    // make answer
    for (int j = 0; j <= n; j++) {
        for (int i = 0; i <= n; i++) {
            if (board[i][j] != -1) {
                vector<int> ans_line;
                if (board[i][j] == BOTH) {
                    ans_line.push_back(j);
                    ans_line.push_back(i);
                    ans_line.push_back(0);
                    ans.push_back(ans_line);
                    ans_line.clear();
                    ans_line.push_back(j);
                    ans_line.push_back(i);
                    ans_line.push_back(1);
                    ans.push_back(ans_line);
                }
                else {
                    ans_line.push_back(j);
                    ans_line.push_back(i);
                    ans_line.push_back(board[i][j]);
                    ans.push_back(ans_line);
                }
            }
        }
    }
    return ans;
}

int main(int argc, const char* argv[]) {
    //vector<vector<int>> res1 = solution(5, {{1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},{5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1}});
    //for(int i=0; i<res1.size(); i++)
        //printf("%d %d %d\n", res1[i][0], res1[i][1], res1[i][2]);

    vector<vector<int>> res2 = solution(5, { {0,0,0,1},{2,0,0,1},{4,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{2,0,0,0},{1,1,1,0},{2,2,0,1} });
    for (int i = 0; i < res2.size(); i++)
        printf("%d %d %d\n", res2[i][0], res2[i][1], res2[i][2]);


    return 0;
}
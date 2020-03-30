#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <limits.h>
#define OPERAND 0
#define BRACKET 1
#define PLUS 3
#define MINUS 3
#define MUL 2
using namespace std;

typedef struct Formula {
	char symbol;
	int num;
	int priority;//��ȣ : 1, * : 2, +,- :3 
	Formula(char s, int p) { symbol = s; priority = p; }
	Formula(int n) { num = n; priority = 0; }
}Formula;

int formula_size;
int max_result=INT_MIN;

int cal(int a, int b, Formula oper) {
	switch (oper.symbol)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	default:
		cout << "error";
		return 0;
	}
}

vector<Formula> InfixToPostfix(vector<Formula> infix) {
	vector<Formula> postfix;
	stack<Formula> s;
	for (int i = 0; i < formula_size; i++) {
		if (infix[i].priority == OPERAND) {// �ǿ�����
			postfix.push_back(infix[i]);
		}
		else { //������
			while (!s.empty() && s.top().priority <= infix[i].priority) {//������ ����ų�, ���� ž���� �켱������ ���� ��ǲ�϶����� pop
				postfix.push_back(s.top());
				s.pop();
			}
			s.push(infix[i]);
		}
	}
	while (!s.empty()) {
		postfix.push_back(s.top());
		s.pop();
	}

	return postfix;
}
int postfixToResult(vector<Formula> postfix) {//�������� -> ���
	stack<Formula> s;
	int result = 0;
	for (int i = 0; i < formula_size; i++) {
		if (postfix[i].priority == OPERAND) {//�ǿ�����
			s.push(postfix[i]);
		}
		else {// ������
			int operand1 = s.top().num;
			s.pop();
			int operand2 = s.top().num;
			s.pop();
			result = cal(operand2, operand1, postfix[i]);
			s.push(result);
		}
	}
	return s.top().num;
}

int calculateFormula(vector<Formula> infix) {
	vector<Formula> postfix = InfixToPostfix(infix);
	int result = postfixToResult(postfix);
	return result;
}
void dfs(int idx, vector<Formula> formula) {
	if (idx >= formula.size()) {
		//����ϱ�
		int result = calculateFormula(formula);
		max_result = max(max_result, result);
		return;
	}
	if (idx >=3 && formula[idx - 2].priority==1) {//���� �����ڿ� ��ȣ�� �������
		dfs(idx + 2, formula);
	}
	else {
		dfs(idx + 2, formula);
		formula[idx].priority = 1;
		dfs(idx + 2, formula);
	}

}

int main() {
	vector<Formula> formula;
	string s;
	cin >> formula_size;
	cin >> s;
	for (int i = 0; i < formula_size; i++) {
		if (i % 2 == 0) {//operand
			formula.push_back(Formula(s[i]-'0'));
		} 
		else {//Oper
			int prior;
			if (s[i] == '*')
				prior = MUL;
			else
				prior = 3;
			formula.push_back(Formula(s[i], prior));
		}
	}
	dfs(1, formula);
	printf("%d\n", max_result);
}
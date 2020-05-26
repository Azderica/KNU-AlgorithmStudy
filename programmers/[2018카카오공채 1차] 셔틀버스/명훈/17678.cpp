#include    <iostream>
#include    <string>
#include    <vector>
#include    <algorithm>
using namespace std;

const int HOUR = 60;

typedef struct Bus {
	int time;
	vector<int> guest;
};

// int -> string , time format change 
string changeTimeIntToString(int time) {
	int hour = time / 60;
	int minute = time % 60;
	string res = "";
	if (hour < 10) {
		res += "0";
		res += (hour + '0');
	}
	else {
		res += (hour / 10 + '0');
		res += (hour % 10 + '0');
	}
	res += ":";
	if (minute < 10) {
		res += "0";
		res += (minute + '0');
	}
	else {
		res += (minute / 10 + '0');
		res += (minute % 10 + '0');
	}
	return res;
}

// string -> int , time format change 
int changeTimeStringToInt(string time) {
	return atoi(time.substr(0, 2).c_str()) * HOUR + atoi(time.substr(3, 2).c_str());
}


// n, t -> list<int> , make bus time list
vector<Bus> getBusTime(int n, int t) {
	vector<Bus> busTime(n);
	int startBusTime = 9 * HOUR;

	for (int i = 0; i < n; i++) {
		busTime[i].time = startBusTime;
		startBusTime += t;
	}
	return busTime;
}

string solution(int n, int t, int m, vector<string> timetable) {
	string answer = "";
	vector<int> guestTimeTable;
	vector<Bus> busTable(n);

	// format change and sort timetable
	for (int i = 0; i < timetable.size(); i++) {
		guestTimeTable.push_back(changeTimeStringToInt(timetable[i]));
	}
	sort(guestTimeTable.begin(), guestTimeTable.end());

	// make bus time list
	busTable = getBusTime(n, t);

	// �մ��� ������ �¿��, �ش� ������ �ִ� m������� �¿��.
	for (int guestIndex = 0; guestIndex < guestTimeTable.size(); guestIndex++) {
		for (int busIndex = 0; busIndex < busTable.size(); busIndex++) {
			if (guestTimeTable[guestIndex] <= busTable[busIndex].time && busTable[busIndex].guest.size() < m) {
				busTable[busIndex].guest.push_back(guestTimeTable[guestIndex]);
				break;
			}
		}
	}

	// ������ ������ �մ��� �ִ��ѵ� ���� ������ ��� Ÿ��
	if (busTable[n - 1].guest.size() < m) {
		answer = changeTimeIntToString(busTable[n - 1].time);
	}
	else {	//������ ������ �մ��� �ִ��ѵ����� ũ��, �� ������ ����� ���� ������ ����
		int lastGuest = busTable[n - 1].guest.size() - 1;
		answer = changeTimeIntToString(busTable[n - 1].guest[lastGuest] - 1);
	}


	//for (int i = 0; i < busTable.size(); i++) {
	//	cout << busTable[i].time << ": ";
	//	for (int j = 0; j < busTable[i].guest.size(); j++)
	//		cout << busTable[i].guest[j] << " ";
	//	cout << "\n";
	//}
	//cout << "\n";

	// ������ ���
	//answer = changeTimeIntToString(validBusTime[validBusTime.size() - 1]);

	return answer;
}

int main() {

	cout << solution(1, 1, 5, { "08:00", "08:01", "08:02", "08:03" }) << endl;
	cout << solution(2, 10, 2, { "09:10", "09:09", "08:00" }) << endl;
	cout << solution(2, 1, 2, { "09:00", "09:00", "09:00", "09:00" }) << endl;
	cout << solution(1, 1, 5, { "00:01", "00:01", "00:01", "00:01", "00:01" }) << endl;
	cout << solution(1, 1, 1, { "23:59" }) << endl;
	cout << solution(10, 60, 45, { "23:59", "23:59", "23:59", "23:59", "23:59",
		"23:59", "23:59", "23:59", "23:59", "23:59",
		"23:59", "23:59", "23:59", "23:59", "23:59" }) << endl;

	return 0;
}
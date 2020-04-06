#include    <iostream>
#include    <string>
#include    <vector>
#include    <sstream>
using namespace std;

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter)) {
        internal.push_back(temp);
    }
    return internal;
}

string changeMelody(string str) {
    string res(str);
    size_t start_pos = 0;
    while ((start_pos = res.find("A#", start_pos)) != string::npos) {
        res.replace(start_pos, 2, "1");
        start_pos += 1;
    }
    start_pos = 0;
    while ((start_pos = res.find("C#", start_pos)) != string::npos) {
        res.replace(start_pos, 2, "3");
        start_pos += 1;
    }
    start_pos = 0;
    while ((start_pos = res.find("D#", start_pos)) != string::npos) {
        res.replace(start_pos, 2, "4");
        start_pos += 1;
    }
    start_pos = 0;
    while ((start_pos = res.find("F#", start_pos)) != string::npos) {
        res.replace(start_pos, 2, "6");
        start_pos += 1;
    }
    start_pos = 0;
    while ((start_pos = res.find("G#", start_pos)) != string::npos) {
        res.replace(start_pos, 2, "7");
        start_pos += 1;
    }
    return res;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "";
    int answer_time = 0;
    string re_m = changeMelody(m);
    int music_length = (int)re_m.length();
    //cout << "\n" << re_m << "\n";

    for (int i = 0; i < musicinfos.size(); i++) {
        string music_info = musicinfos[i];
        vector<string> music_list = split(music_info, ',');

        int start_time = stoi(music_list[0].substr(0, 2)) * 60 + stoi(music_list[0].substr(3, 2));
        int end_time = stoi(music_list[1].substr(0, 2)) * 60 + stoi(music_list[1].substr(3, 2));
        int radio_time = end_time - start_time;             // ���� �� ����ð�
        string re_melody = changeMelody(music_list[3]);
        int radio_part_time = re_melody.length();       // ��ε� �ð�

        // radio music �� �������� �귯���� ��ü ��ε�
        string radio_music = "";
        int t1 = radio_time / radio_part_time;
        int t2 = radio_time % radio_part_time;
        for (int j = 0; j < t1; j++)
            radio_music += re_melody;
        radio_music += re_melody.substr(0, t2);

        //cout << radio_music << "\n";

        // ã�� ���
        if (radio_music.find(re_m) != string::npos) {
            if (answer.length() == 0) {     // ������ ���
                answer = music_list[2];
                answer_time = radio_time;
            }
            else {              // �ִ� ���
                if (radio_time > answer_time) {
                    answer = music_list[2];
                    answer_time = radio_time;
                }
            }
        }
    }

    if (answer.length() == 0)
        answer = "(None)";

    return answer;
}

int main() {
    string ans = "";
    ans = solution("ABCDEFG", { "12:00,12:14,HELLO,CDEFGAB", "13:00,13:05,WORLD,ABCDEF" });
    cout << ans << "\n";

    ans = solution("CC#BCC#BCC#BCC#B", { "03:00,03:30,FOO,CC#B", "04:00,04:08,BAR,CC#BCC#BCC#B" });
    cout << ans << "\n";

    ans = solution("ABC", { "12:00,12:14,HELLO,C#DEFGAB", "13:00,13:05,WORLD,ABCDEF" });
    cout << ans << "\n";

    return 0;
}
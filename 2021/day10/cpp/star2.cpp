#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <deque>
#include <vector>
#include <map>


using namespace std;


long long line_score(string line)
{
        long long points = 0;
        deque<char> chunks;
        map<char, int> score_map = {
                { '(', 1 },
                { '[', 2 },
                { '{', 3 },
                { '<', 4 },
        };

        for (char& c : line) {
                if (c == '(' || c == '[' || c == '{' || c == '<') {
                        chunks.push_back(c);
                } else if (c == ')' && chunks.back() == '(') {
                        chunks.pop_back();
                } else if (c == ']' && chunks.back() == '[') {
                        chunks.pop_back();
                } else if (c == '}' && chunks.back() == '{') {
                        chunks.pop_back();
                } else if (c == '>' && chunks.back() == '<') {
                        chunks.pop_back();
                } else {
                        return 0;
                }
        }

        for (char& c : chunks) {
                points *= 5;
                points += score_map[chunks.back()];
                chunks.pop_back();
        }

        return points;
}


int main(int argc, char *argv[])
{
        ifstream infile;
        string line;
        char c;
        vector<long long> scores;

        infile.open(argv[1]);

        while (getline(infile, line)) {
                long long score = line_score(line);
                if (score > 0) {
                        scores.push_back(score);
                }
        }

        sort(scores.begin(), scores.end());

        cout << scores[scores.size()/2] << endl;

        return 0;
}

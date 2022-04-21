#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <map>


using namespace std;


char check_line(string line)
{
        deque<char> chunks;

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
                        return c;
                }
        }

        return 0;
}


int main(int argc, char *argv[])
{
        ifstream infile;
        string line;
        char c;
        int error_score = 0;
        map<char, int> score_map = {
                { ')', 3 },
                { ']', 57 },
                { '}', 1197 },
                { '>', 25137 },
        };

        infile.open(argv[1]);

        while (getline(infile, line)) {
                c = check_line(line);
                if (c != 0) {
                        error_score += score_map[c];
                }
        }
        cout << error_score << endl;

        return 0;
}

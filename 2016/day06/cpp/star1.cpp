#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        string message;
        std::vector<std::map<char, int> > posLetterCounts; /* letter counts for each position */

        inFile.open(argv[1]);

        getline(inFile, line);
        for (const char & c : line) {
                std::map<char, int> letterCounts;
                auto emplace_pair = letterCounts.emplace(c, 0);
                emplace_pair.first->second += 1;
                posLetterCounts.push_back(letterCounts);
        }

        while (getline(inFile, line)) {
                int pos = 0;
                for (const char & c : line) {
                        auto emplace_pair = posLetterCounts[pos++].emplace(c, 0);
                        emplace_pair.first->second += 1;
                }
        }

        for (const auto & letterCounts : posLetterCounts) {
                auto x = std::max_element(
                    letterCounts.begin(), letterCounts.end(),
                    [](const pair<int, int> &p1, const pair<int, int> &p2) {
                      return p1.second < p2.second;
                    });
                message.push_back(x->first);
        }

        cout << "The error-corrected version of the message is " << message << "." << endl;

        return 0;
}

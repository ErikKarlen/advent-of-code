#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int realIdSum = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                std::map<char, int> letterCounts;
                size_t last = 0;
                size_t next = line.find_first_of("0123456789");
                string letters = line.substr(last, next - last);
                for (const auto & c : letters) {
                        if (c != '-') {
                                auto emplace_pair = letterCounts.emplace(c, 0);
                                emplace_pair.first->second += 1;
                        }
                }

                last = next;
                next = line.find("[");
                int id = stoi(line.substr(last, next - last));

                string checksum = line.substr(next + 1, 5);

                vector<pair<char, int>> countLetterList;
                for (const auto & pair : letterCounts) {
                        countLetterList.push_back({ pair.first, pair.second });
                }

                auto cmp = [](std::pair<char,int> const & a, std::pair<char,int> const & b) 
                { 
                        return a.second != b.second ?  a.second > b.second : a.first < b.first;
                };
                sort(countLetterList.begin(), countLetterList.end(), cmp);
                //sort(countLetterList.rbegin(), countLetterList.rend());

                stringstream ss;
                for (int i = 0; i < 5; ++i) {
                        ss << countLetterList[i].first;
                        //cout << countLetterList[i].first << ": " << countLetterList[i].second << endl;
                }

                if (checksum == ss.str()) {
                        realIdSum += id;
                }

                //for (const auto & pair : letterCounts) {
                //        cout << pair.first << ": " << pair.second << endl;
                //}
                //cout << "five: " << ss.str() << ", check: " << checksum << endl;

        }

        cout << "The sum of the sector IDs of the real rooms is " << realIdSum << "." << endl;

        return 0;
}

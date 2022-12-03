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
        int product = 0;
        vector<string> logs;
        map<int, int> idToTotalSleepTime;
        map<int, map<int, int>> idToSleepTimes;
        int id, sleepStart;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                logs.push_back(line);
        }
        sort(logs.begin(), logs.end());

        for (const auto & log : logs) {
                size_t start = log.find('#');
                if (start != string::npos) {
                        size_t end = log.find(' ', start);
                        id = stoi(log.substr(start + 1, end - start));
                } else if (log.find("falls asleep") != string::npos) {
                        sleepStart = stoi(log.substr(15, 2));
                } else if (log.find("wakes up") != string::npos) {
                        int sleepEnd = stoi(log.substr (15, 2));
                        int sleepTime = sleepEnd - sleepStart;
                        auto emplace_pair = idToTotalSleepTime.emplace(id, 0);
                        emplace_pair.first->second += sleepTime;
                        for (int i = sleepStart; i < sleepEnd; ++i) {
                                auto emplace_pair = idToSleepTimes[id].emplace(i, 0);
                                emplace_pair.first->second += 1;
                        }
                }
        }
        int minute = 0;
        int minuteCount = 0;
        int bestId = 0;
        for (const auto & idSleep : idToSleepTimes) {
                id = idSleep.first;
                for (const auto & pair : idToSleepTimes[id]) {
                        if (pair.second > minuteCount) {
                                minuteCount = pair.second;
                                minute = pair.first;
                                bestId = id;
                        }
                }
        }

        product = bestId * minute;

        cout << "The ID of the chosen guard multiplied by the minute chosen is "
                << product << "." << endl;

        return 0;
}

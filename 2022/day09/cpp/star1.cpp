#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        pair<int, int> headPos{ 0, 0 };
        pair<int, int> tailPos{ 0, 0 };
        set<pair<int, int>> tailVisited = { tailPos };
        map<char, pair<int, int>> direction{
                { 'L', { -1, 0} },
                { 'U', { 0, 1} },
                { 'R', { 1, 0} },
                { 'D', { 0, -1} }
        };

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                int dx = direction[line.front()].first;
                int dy = direction[line.front()].second;
                int numSteps = stoi(line.substr(2));
                for (int i = 0; i < numSteps; ++i) {
                        pair<int, int> step = { dx, dy };
                        headPos.first += step.first;
                        headPos.second += step.second;
                        //cout << headPos.first << ", " << headPos.second << endl;
                        if (abs(headPos.first - tailPos.first) > 1 || abs(headPos.second - tailPos.second) > 1) {
                                tailPos.first = headPos.first - dx;
                                tailPos.second = headPos.second - dy;
                                //cout << "head: " << headPos.first << "," << headPos.second << endl;
                                //cout << "tail: " << tailPos.first << "," << tailPos.second << endl;
                                tailVisited.insert(tailPos);
                        }
                }
        }

        cout << "The number of positions the tail of the rope visits at least "
                << "once is " << tailVisited.size() << "." << endl;

        return 0;
}

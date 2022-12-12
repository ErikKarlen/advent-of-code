#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <vector>


using namespace std;

map<pair<int, int>, int> heightMap;
pair<int, int> endPos;

struct ComparePaths {
        bool operator()(vector<pair<int, int>> const& p1, vector<pair<int, int>> const& p2)
        {
                int dx1 = abs(p1.back().first - endPos.first);
                int dy1 = abs(p1.back().second - endPos.second);
                int dx2 = abs(p2.back().first - endPos.first);
                int dy2 = abs(p2.back().second - endPos.second);
                if (heightMap[p1.back()] != heightMap[p2.back()]) {
                        return heightMap[p1.back()] < heightMap[p2.back()];
                }
                if (p1.size() != p2.size()) {
                      return p1.size() < p2.size();
                }
                return dx1 + dy1 > dx2 + dy2;
        }
};

void drawPath(vector<pair<int, int>> path)
{
        set<pair<int, int>> s(path.begin(), path.end());
        for (int row = 0; row < 41; ++row) {
                for (int col = 0; col < 64; ++col) {
                        if (s.count({ row, col })) {
                                cout << "#";
                        } else {
                                cout << ".";
                        }
                }
                cout << endl;
        }
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        priority_queue<vector<pair<int, int>>, vector<vector<pair<int, int>>>, ComparePaths> todoPaths;
        set<vector<pair<int, int>>> possiblePaths;
        vector<pair<int, int>> bestPath;
        int row = 0, col;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                col = 0;
                for (const auto & c : line){
                        heightMap[{ row, col }] = (int)c;
                        if (c == 'S') {
                                todoPaths.push({ { row, col } });
                                heightMap[{ row, col }] = (int)'a';
                        }
                        else if (c == 'E') {
                                endPos = { row, col };
                                heightMap[{ row, col }] = (int)'z';
                        }
                        col++;
                }
                row++;
        }

        int minLength = 500;
        int numLoops = 0;
        //todoPaths.pop();
        //todoPaths.push({ { 4, 45 } });

        while (!todoPaths.empty()) {
                vector<pair<int, int>> path = todoPaths.top();
                pair<int, int> pos = path.back();
                todoPaths.pop();

                if (path.size() + abs(pos.first - endPos.first) + abs(pos.second - endPos.second) > minLength) {
                        continue;
                }
                if (!possiblePaths.empty() && heightMap[pos] < heightMap[*(path.end() - 2)]) {
                        continue;
                }
                set<pair<int, int>> checkedPos(path.begin(), path.end());

                //cout << todoPaths.size() << endl;
                //cout << path.size() << endl;
                //cout << ++numLoops << endl;

                //for (const auto & p : path) {
                //        cout << "(" << p.first << "," << p.second << "), ";
                //}
                //cout << endl;

                vector<pair<int, int>> newPositions = {
                        { pos.first - 1, pos.second },
                        { pos.first + 1, pos.second },
                        { pos.first, pos.second - 1 },
                        { pos.first, pos.second + 1 }
                };
                for (const auto & p : newPositions) {
                        vector<pair<int, int>> newPath(path);
                        newPath.push_back(p);
                        if (newPath.size() + abs(pos.first - endPos.first) + abs(pos.second - endPos.second)<  minLength
                        && heightMap.count(p)
                        && (heightMap[p] == heightMap[pos] + 1 || heightMap[p] == heightMap[pos] || heightMap[p] == (int)'i')
                        && !checkedPos.count(p)
                        && todoPaths.size() < 100000) {
                                todoPaths.push(newPath);
                        }
                }
                if (pos == endPos) {
                        possiblePaths.insert(path);
                        drawPath(path);
                        cout << endl << endl;
                        if (minLength > path.size()) {
                                minLength = path.size();
                        }
                }
        }

        bestPath = *possiblePaths.begin();
        for (const auto & p : possiblePaths) {
                //cout << p.size() << endl;
                if (p.size() < bestPath.size()) {
                        bestPath = p;
                }
        }

        cout << "The fewest steps required to move from your current position "
                << "to the location that should get the best signal is "
                << bestPath.size() - 1 << endl;

        return 0;
}

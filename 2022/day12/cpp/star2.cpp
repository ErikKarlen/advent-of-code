#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <vector>


using namespace std;


void drawDistances(map<pair<int, int>, int> distanceToStart, int numRows, int numCols)
{
        for (int row = 0; row < numRows; ++row) {
                for (int col = 0; col < numCols; ++col) {
                        if (distanceToStart[{ row, col }] < 1000) {
                                cout << distanceToStart[{ row, col }] % 10;
                        } else {
                                cout << ".";
                        }
                }
                cout << endl;
        }
        cout << endl;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        map<pair<int, int>, int> heightMap;
        map<pair<int, int>, int> distanceToStart;
        set<pair<int, int>> checked;
        pair<int, int> endPos;
        int row = 0, col, minSteps = 1000;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                col = 0;
                for (const auto & c : line){
                        heightMap[{ row, col }] = (int)c;
                        distanceToStart[{ row, col }] = 10000;
                        if (c == 'S') {
                                //distanceToStart[{ row, col }] = 0;
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

        /*
         * Only checking first column in every row because all the 'b's are in
         * the second column so the best position has to be in the first column
         */
        for (int r = 0; r < row; ++r) {
                /* Reset distances */
                checked.clear();
                for (int i = 0; i < row; ++i) {
                        for (int j = 0; j < col; ++j) {
                                distanceToStart[{ i, j }] = 10000;
                        }
                }
                distanceToStart[{ r, 0 }] = 0;

                /* Dijkstra's */
                while (!checked.count(endPos)) {
                        pair<int, int> pos = (*distanceToStart.begin()).first;
                        for (const auto & posDistance : distanceToStart) {
                                if (checked.count(pos)) {
                                        pos = posDistance.first;
                                } else if (!checked.count(posDistance.first) && posDistance.second < distanceToStart[pos]) {
                                        pos = posDistance.first;
                                }
                        }

                        checked.insert(pos);

                        vector<pair<int, int>> newPositions = {
                                { pos.first - 1, pos.second },
                                { pos.first + 1, pos.second },
                                { pos.first, pos.second - 1 },
                                { pos.first, pos.second + 1 }
                        };
                        for (const auto & p : newPositions) {
                                if (heightMap.count(p) && heightMap[p] <= heightMap[pos] + 1 && !checked.count(p)) {
                                        if (distanceToStart[p] > distanceToStart[pos] + 1) {
                                                distanceToStart[p] = distanceToStart[pos] + 1;
                                        }
                                }
                        }

                        //drawDistances(distanceToStart, row, col);
                }

                //cout << distanceToStart[endPos] << endl;
                if (distanceToStart[endPos] < minSteps) {
                        minSteps = distanceToStart[endPos];
                }
        }

        cout << "The fewest steps required to move starting from any square with "
                << "elevation 'a' to the location that should get the best signal "
                << "is " << minSteps << "." << endl;

        return 0;
}

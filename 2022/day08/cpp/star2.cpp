#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;

int numberOfLowerTrees(int maxHeight, vector<int> treeLine)
{
        int numTrees = 0;
        for (const auto height : treeLine) {
                //cout << height << endl;
                numTrees++;
                if (height >= maxHeight) {
                        break;
                }
        }

        return numTrees;
}

long long calculateScenicScore(map<pair<int, int>, int> trees, int row, int col, int numRows, int numCols)
{
        vector<int> treeLine;
        int scenicScore = 1;
        int r, c;

        /* trees above */
        for (r = row - 1; r >= 0; --r) {
                treeLine.push_back(trees[{ r, col }]);
        }
        scenicScore *= numberOfLowerTrees(trees[{ row, col }], treeLine);

        /* trees below */
        treeLine.clear();
        for (r = row + 1; r < numRows; ++r) {
                treeLine.push_back(trees[{ r, col }]);
        }
        scenicScore *= numberOfLowerTrees(trees[{ row, col }], treeLine);

        /* trees left */
        treeLine.clear();
        for (c = col - 1; c >= 0; --c) {
                treeLine.push_back(trees[{ row, c }]);
        }
        scenicScore *= numberOfLowerTrees(trees[{ row, col }], treeLine);

        /* trees above */
        treeLine.clear();
        for (c = col + 1; c < numCols; ++c) {
                treeLine.push_back(trees[{ row, c }]);
        }
        scenicScore *= numberOfLowerTrees(trees[{ row, col }], treeLine);

        return scenicScore;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        map<pair<int, int>, int> trees; // coord to height
        map<pair<int, int>, int> scores; // coord to score
        int row, col, numRows, numCols;
        long long maxScenicScore = 0;

        inFile.open(argv[1]);

        row = 0;
        while (getline(inFile, line)) {
                col = 0;
                for (const auto & c : line) {
                        trees[{ row, col }] = c - '0';
                        col++;
                }
                row++;
        }
        numRows = row;
        numCols = col;

        for (row = 1; row < numRows - 1; ++row) {
                for (col = 1; col < numCols - 1; ++col) {
                        long long scenicScore = calculateScenicScore(trees, row, col, numRows, numCols);
                        scores[{ row, col }] = scenicScore;
                        if (scenicScore > maxScenicScore) {
                                maxScenicScore = scenicScore;
                        }
                }
        }

        //for (row = 0; row < numRows; ++row) {
        //        for (col = 0; col < numCols; ++col) {
        //                cout << trees[{ row, col }];
        //        }
        //        cout << endl;
        //}

        //for (row = 0; row < numRows; ++row) {
        //        for (col = 0; col < numCols; ++col) {
        //                if (scores.count({ row, col })) {
        //                        cout << scores[{ row, col }];
        //                } else {
        //                        cout << '0';
        //                }
        //        }
        //        cout << endl;
        //}

        cout << "The highest scenic score possible for any tree is " << maxScenicScore
                << "." << endl;

        return 0;
}

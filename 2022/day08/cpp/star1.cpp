#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;


set<pair<int, int>> lineVisibility(map<pair<int, int>, int> trees, vector<pair<int, int>> treeLine)
{
        set<pair<int, int>> visibleTrees;
        int height = -1;

        for (const auto & tree : treeLine) {
                if (trees[tree] > height) {
                        height = trees[tree];
                        visibleTrees.insert(tree);
                        if (height == 9) {
                                break;
                        }
                }
        }
        return visibleTrees;
}


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        map<pair<int, int>, int> trees; // coord to height
        set<pair<int, int>> visibleTrees, visibleLine;
        int row, col, numRows, numCols;
        vector<pair<int, int>> treeLine;

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

        /* looking from top */
        for (col = 0; col < numCols; ++col) {
                treeLine.clear();
                for (row = 0; row < numRows; ++row) {
                        treeLine.push_back({ row, col });
                }
                visibleLine = lineVisibility(trees, treeLine);
                visibleTrees.insert(visibleLine.begin(), visibleLine.end());
        }

        /* looking from bottom */
        for (col = 0; col < numCols; ++col) {
                treeLine.clear();
                for (row = numRows - 1; row >= 0; --row) {
                        treeLine.push_back({ row, col });
                }
                visibleLine = lineVisibility(trees, treeLine);
                visibleTrees.insert(visibleLine.begin(), visibleLine.end());
        }

        /* looking from right */
        for (row = 0; row < numRows; ++row) {
                treeLine.clear();
                for (col = 0; col < numCols; ++col) {
                        treeLine.push_back({ row, col });
                }
                visibleLine = lineVisibility(trees, treeLine);
                visibleTrees.insert(visibleLine.begin(), visibleLine.end());
        }

        /* looking from right */
        for (row = 0; row < numRows; ++row) {
                treeLine.clear();
                for (col = numCols - 1; col >= 0; --col) {
                        treeLine.push_back({ row, col });
                }
                visibleLine = lineVisibility(trees, treeLine);
                visibleTrees.insert(visibleLine.begin(), visibleLine.end());
        }
        //cout << visibleTrees(trees, treeLine) << endl;

        for (const auto & tree : visibleTrees) {
                cout << tree.first << ", " << tree.second << endl;
        }

        for (row = 0; row < numRows; ++row) {
                for (col = 0; col < numCols; ++col) {
                        cout << trees[{ row, col }];
                }
                cout << endl;
        }

        cout << "There are " << visibleTrees.size() << " visible from outside the grid." << endl;

        return 0;
}

#include <iostream>
#include <fstream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        set<pair<int, int>> trees;
        int numHitTrees;
        int x, y = 0;
        int width = 0, height = 0;
        set<pair<int, int>> slopes;
        long long numHitTreesProduct = 1;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                x = 0;
                for (const auto & c : line) {
                        if (c == '#') {
                                trees.insert({x, y});
                        }
                        x++;
                }
                width = x > width ? x : width;
                y++;
        }
        height = y;

        slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

        for (const auto & slope : slopes) {
                numHitTrees = 0;
                x = 0;
                for (y = 0; y < height; y += slope.second) {
                        if (trees.find({x % width, y}) != trees.end()) {
                                numHitTrees++;
                        }
                        x += slope.first;
                }
                numHitTreesProduct *= numHitTrees;
        }

        cout << "If you multiply together the number of trees encountered on each "
                << "of the listed slopes you get " << numHitTreesProduct << "." << endl;

        return 0;
}

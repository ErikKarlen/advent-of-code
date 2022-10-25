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
        int numHitTrees = 0;
        int x, y = 0;
        int width = 0, height = 0;

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

        x = 0;
        for (y = 0; y < height; ++y) {
                if (trees.find({x % width, y}) != trees.end()) {
                        numHitTrees++;
                }
                x += 3;
        }

        cout << "I would encounter a total of " << numHitTrees << " trees." << endl;

        return 0;
}

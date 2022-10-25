#include <iostream>
#include <fstream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        pair<int, int> pos = {0, 0};
        set<pair<int, int>> visited = { pos };

        inFile.open(argv[1]);

        getline(inFile, line);

        for (const char dir : line) {
                if (dir == '^') {
                        pos.second += 1;
                } else if (dir == '>') {
                        pos.first += 1;
                } else if (dir == 'v') {
                        pos.second -= 1;
                } else if (dir == '<') {
                        pos.first -= 1;
                }
                visited.insert(pos);
        }

        cout << "A total of " << visited.size() << " houses receive at least one present." << endl;

        return 0;
}

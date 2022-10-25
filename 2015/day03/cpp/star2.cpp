#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        pair<int, int> santaPos = {0, 0};
        pair<int, int> roboSantaPos = {0, 0};
        set<pair<int, int>> santaVisited = { santaPos };
        set<pair<int, int>> roboSantaVisited = { roboSantaPos };
        set<pair<int, int>> bothVisited = {};
        bool santasTurn = true;

        inFile.open(argv[1]);

        getline(inFile, line);

        for (const char dir : line) {
                if (santasTurn && dir == '^') {
                        santaPos.second += 1;
                } else if (santasTurn && dir == '>') {
                        santaPos.first += 1;
                } else if (santasTurn && dir == 'v') {
                        santaPos.second -= 1;
                } else if (santasTurn && dir == '<') {
                        santaPos.first -= 1;
                } else if (dir == '^') {
                        roboSantaPos.second += 1;
                } else if (dir == '>') {
                        roboSantaPos.first += 1;
                } else if (dir == 'v') {
                        roboSantaPos.second -= 1;
                } else if (dir == '<') {
                        roboSantaPos.first -= 1;
                }
                santaVisited.insert(santaPos);
                roboSantaVisited.insert(roboSantaPos);
                santasTurn = !santasTurn;
        }

        bothVisited.insert(santaVisited.begin(), santaVisited.end());
        bothVisited.insert(roboSantaVisited.begin(), roboSantaVisited.end());

        cout << "A total of " << bothVisited.size()
                << " houses receive at least one present." << endl;

        return 0;
}

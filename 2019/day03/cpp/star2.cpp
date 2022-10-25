#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int shortestWireLength;
        vector<vector<pair<int, int>>> wiresVector;
        vector<set<pair<int, int>>> wiresSet;
        vector<pair<int, int>> intersections;

        inFile.open(argv[1]);

        for (int i = 0; i < 2; ++i) {
                getline(inFile, line);
                size_t last = 0;
                size_t next = line.find(',');
                int xPos = 0, yPos = 0;
                vector<string> instructions;

                while (next != string::npos) {
                        string instruction = line.substr(last, next - last);
                        instructions.push_back(instruction);
                        last = next + 1;
                        next = line.find(',', last);
                }
                instructions.push_back(line.substr(last, next - last));

                wiresVector.push_back({});

                for (const auto & instruction : instructions) {
                        char dir = instruction[0];
                        int length = stoi(instruction.substr(1));
                        int dx = 0, dy = 0;

                        if (dir == 'U') {
                                dy = 1;
                        } else if (dir == 'R') {
                                dx = 1;
                        } else if (dir == 'D') {
                                dy = -1;
                        } else if (dir == 'L') {
                                dx = -1;
                        }

                        for (int x = xPos; x != xPos + dx * length; x += dx) {
                                wiresVector[i].push_back({ x + dx, yPos });
                        }

                        for (int y = yPos; y != yPos + dy * length; y += dy) {
                                wiresVector[i].push_back({ xPos, y + dy });
                        }

                        xPos += dx * length;
                        yPos += dy * length;
                }
        }

        for (const auto & v : wiresVector) {
                wiresSet.push_back(set(v.begin(), v.end()));
        }

        set_intersection(
                wiresSet[0].begin(), wiresSet[0].end(),
                wiresSet[1].begin(), wiresSet[1].end(),
                inserter(intersections, intersections.begin())
        );

        shortestWireLength = 10000000;
        for (const auto & coord : intersections) {
                size_t wireLength1 = find(wiresVector[0].begin(), wiresVector[0].end(), coord) - wiresVector[0].begin() + 1;
                size_t wireLength2 = find(wiresVector[1].begin(), wiresVector[1].end(), coord) - wiresVector[1].begin() + 1;
                int wireLength = wireLength1 + wireLength2;
                if (wireLength < shortestWireLength) {
                        shortestWireLength = wireLength;
                }
        }

        cout << "The fewest combined steps the wires must take to reach an intersection is "
                << shortestWireLength << "." << endl;

        return 0;
}

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
        int shortestDistance;
        vector<set<pair<int, int>>> wires;
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

                wires.push_back({});

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
                                wires[i].insert({ x + dx, yPos });
                        }

                        for (int y = yPos; y != yPos + dy * length; y += dy) {
                                wires[i].insert({ xPos, y + dy });
                        }

                        xPos += dx * length;
                        yPos += dy * length;
                }
        }

        set_intersection(
                wires[0].begin(), wires[0].end(),
                wires[1].begin(), wires[1].end(),
                inserter(intersections, intersections.begin())
        );

        shortestDistance = abs(intersections[0].first) + abs(intersections[0].second);
        for (const auto & coord : intersections) {
                int distance = abs(coord.first) + abs(coord.second);
                if (distance < shortestDistance) {
                        shortestDistance = distance;
                }
        }

        cout << "The Manhattan distance from the central port to the closest intersection is "
                << shortestDistance << "." << endl;

        return 0;
}

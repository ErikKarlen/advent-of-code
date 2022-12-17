#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>


using namespace std;


void drawMap(
        const set<pair<int, int>> & rocks,
        const set<pair<int, int>> & sands,
        int xStart,
        int xEnd,
        int yStart,
        int yEnd,
        int floor,
        const pair<int, int> & sandSource)
{
        for (int y = yStart; y <= yEnd; ++y) {
                for (int x = xStart; x <= xEnd; ++x) {
                        pair<int, int> c = { x, y };
                        if (sands.count(c)) {
                                cout << "o";
                        } else if (c == sandSource) {
                                cout << "+";
                        } else if (rocks.count(c) || y == floor) {
                                cout << "#";
                        } else {
                                cout << ".";
                        }
                }
                cout << endl;
        }
}

bool dropSandUnit(
        const set<pair<int, int>> & rocks,
        set<pair<int, int>> & sands,
        const pair<int, int> & sandSource,
        int floor)
{
        bool sandStopped = false;
        pair<int, int> sand = sandSource;

        while (!sandStopped) {
                pair<int, int> nextTile = { sand.first, sand.second + 1 };
                bool nextBlocked = (rocks.count(nextTile) || sands.count(nextTile) || nextTile.second == floor);
                if (!nextBlocked) {
                        sand = nextTile;
                        continue;
                }
                nextTile = { sand.first - 1, sand.second + 1 };
                nextBlocked = (rocks.count(nextTile) || sands.count(nextTile) || nextTile.second == floor);
                if (!nextBlocked) {
                        sand = nextTile;
                        continue;
                }
                nextTile = { sand.first + 1, sand.second + 1 };
                nextBlocked = (rocks.count(nextTile) || sands.count(nextTile) || nextTile.second == floor);
                if (!nextBlocked) {
                        sand = nextTile;
                        continue;
                }
                sands.insert(sand);
                sandStopped = true;
        }

        return !sands.count(sandSource);
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        set<pair<int, int>> rocks;
        set<pair<int, int>> sands;
        pair<int, int> sandSource = { 500, 0 };
        int bottomRockLength = 0;
        bool sandIsPouring = true;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                vector<pair<int, int>> coords;

                size_t last = 0;
                size_t next = 0;
                while (next != string::npos) {
                        next = line.find(',', last);
                        int x = stoi(line.substr(last, next - last));
                        last = next + 1;
                        next = line.find(" -> ", last);
                        int y = stoi(line.substr(last, next - last));
                        if (y > bottomRockLength) {
                                bottomRockLength = y;
                        }
                        //cout << "x,y: " << x << "," << y << endl;
                        last = next + 4;
                        coords.push_back({ x, y });
                }

                //for (const auto & c : coords) {
                //        cout << "x,y: " << c.first << "," << c.second << endl;
                //}

                for (int i = 1; i < coords.size(); ++i) {
                        pair<int, int> start = coords[i - 1];
                        pair<int, int> end = coords[i];
                        int numX = end.first - start.first;
                        int dx = numX / abs(numX);
                        int numY = end.second - start.second;
                        int dy = numY / abs(numY);

                        for (int x = start.first; x != end.first + dx; x += dx) {
                                rocks.insert({ x, start.second });
                        }

                        for (int y = start.second; y != end.second + dy; y += dy) {
                                rocks.insert({ start.first, y });
                        }
                }
        }

        while (sandIsPouring) {
                sandIsPouring = dropSandUnit(rocks, sands, sandSource, bottomRockLength + 2);
        }

        //drawMap(rocks, sands, 488, 512, 0, 11, bottomRockLength + 2, sandSource);
        //drawMap(rocks, sands, 420, 580, 0, 180, bottomRockLength + 2, sandSource);

        //cout << "Rocks:" << endl;
        //for (const auto & rock : rocks) {
        //        cout << "x,y: " << rock.first << "," << rock.second << endl;
        //}

        cout << "The number of units of sand that come to rest before the source "
                << "of the sand becomes blocked is " << sands.size() << endl;

        return 0;
}

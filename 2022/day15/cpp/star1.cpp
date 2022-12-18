#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        vector<pair<int, int>> sensors;
        vector<pair<int, int>> closestBeacons;
        int yToCheck = 2000000; // yToCheck = 10 for test input
        int startX, endX;
        int numBeaconFreePositions = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                size_t last = 12;
                size_t next = line.find(',', last);
                int sensorX = stoi(line.substr(last, next - last));
                last = line.find('=', next) + 1;
                next = line.find(':', last);
                int sensorY = stoi(line.substr(last, next - last));
                last = line.find('=', next) + 1;
                next = line.find(',', last);
                int beaconX = stoi(line.substr(last, next - last));
                last = line.find('=', next) + 1;
                int beaconY = stoi(line.substr(last));

                sensors.push_back({ sensorX, sensorY });
                closestBeacons.push_back({ beaconX, beaconY });
        }

        startX = sensors[0].first;
        endX = sensors[0].first;
        for (int i = 0; i < sensors.size(); ++i) {
                pair<int, int> s = sensors[i];
                pair<int, int> b = closestBeacons[i];
                int left = s.first - abs(s.first - b.first) - abs(s.second - b.second);
                if (left < startX) {
                        startX = left;
                }
                int right = s.first + abs(s.first - b.first) + abs(s.second - b.second);
                if (right > endX) {
                        endX = right;
                }
        }

        for (int x = startX; x < endX; ++x) {
                pair<int, int> c = { x, yToCheck };
                for (int i = 0; i < sensors.size(); ++i) {
                        pair<int, int> s = sensors[i];
                        pair<int, int> b = closestBeacons[i];
                        if (b == c) {
                                continue;
                        }
                        int sbDist = abs(s.first - b.first) + abs(s.second - b.second);
                        int scDist = abs(s.first - c.first) + abs(s.second - c.second);
                        if (scDist <= sbDist) {
                                numBeaconFreePositions++;
                                break;
                        }
                }
        }

        cout << "In the row where y=" << yToCheck << ", the number of positions that cannot "
                << "contain a beacon is " << numBeaconFreePositions << endl;

        return 0;
}

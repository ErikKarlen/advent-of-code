#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <set>
#include <string>
#include <vector>


using namespace std;


void drawMap(
        const set<pair<int, int>> & emptyPositions,
        const set<pair<int, int>> & sensors,
        const set<pair<int, int>> & beacons,
        int xStart,
        int xEnd,
        int yStart,
        int yEnd)
{
        for (int y = yStart; y <= yEnd; ++y) {
                for (int x = xStart; x <= xEnd; ++x) {
                        pair<int, int> c = { x, y };
                        if (sensors.count(c)) {
                                cout << "S";
                        } else if (beacons.count(c)) {
                                cout << "B";
                        } else if (emptyPositions.count(c)) {
                                cout << "#";
                        } else {
                                cout << ".";
                        }
                }
                cout << endl;
        }
}

void addEdge(
        vector<pair<int, int>> & edge,
        const pair<int, int> & start,
        const pair<int, int> & end,
        int minX,
        int maxX,
        int minY,
        int maxY)
{
        int xLength = end.first - start.first;
        int yLength = end.second - start.second;
        int dx = xLength / abs(xLength);
        int dy = yLength / abs(yLength);
        for (int j = 0; j < abs(xLength) + 1; ++j) {
                int x = start.first + dx * j;
                int y = start.second + dy * j;
                if (minX <= x && x <= maxX && minY <= y && y <= maxY) {
                        edge.push_back({ x, y });
                }
        }
}

vector<pair<int, int>> beaconEdge(
        const pair<int, int> sensor,
        const pair<int, int> closestBeacon,
        int extraDistance,
        int minX,
        int maxX,
        int minY,
        int maxY)
{
        vector<pair<int, int>> edge;

        int dist = abs(sensor.first - closestBeacon.first) + abs(sensor.second - closestBeacon.second) + extraDistance;
        pair<int, int> start = { sensor.first, sensor.second - dist };
        pair<int, int> end = { sensor.first + dist, sensor.second };
        addEdge(edge, start, end, minX, maxX, minY, maxY);
        start = end;
        end = { sensor.first, sensor.second + dist };
        addEdge(edge, start, end, minX, maxX, minY, maxY);
        start = end;
        end = { sensor.first - dist, sensor.second };
        addEdge(edge, start, end, minX, maxX, minY, maxY);
        start = end;
        end = { sensor.first, sensor.second - dist };
        addEdge(edge, start, end, minX, maxX, minY, maxY);

        return edge;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        vector<pair<int, int>> sensors;
        vector<pair<int, int>> closestBeacons;
        set<pair<int, int>> outerBeaconEdge;
        set<pair<int, int>> sensorsSet;
        set<pair<int, int>> beaconsSet;
        long long tuningFrequency;
        int minX = 0;
        //int maxX = 20;
        int maxX = 4000000;
        int minY = 0;
        //int maxY = 20;
        int maxY = 4000000;

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

        cout << sensors.size() << endl;

        for (int j = 0; j < sensors.size(); ++j) {
                bool beaconFound = false;
                vector<pair<int, int>> edgeSensor = beaconEdge(sensors[j], closestBeacons[j], 1, minX, maxX, minY, maxY);
                //cout << j << endl;
                for (const auto & e : edgeSensor) {
                        beaconFound = true;
                        for (int i = 0; i < sensors.size(); ++i) {
                                if (i == j) {
                                        continue;
                                }
                                pair<int, int> s = sensors[i];
                                pair<int, int> b = closestBeacons[i];
                                int sbDist = abs(s.first - b.first) + abs(s.second - b.second);
                                int seDist = abs(s.first - e.first) + abs(s.second - e.second);
                                if (seDist <= sbDist) {
                                        beaconFound = false;
                                        break;
                                }
                        }
                        if (beaconFound) {
                                //cout << e.first << "," << e.second << endl;
                                tuningFrequency = e.first * 4000000ll + (long long)e.second;
                                break;
                        }
                }
                if (beaconFound) {
                        break;
                }
        }

        //drawMap(beaconOutside, sensorsSet, beaconsSet, -4, 26, 9, 11);

        cout << "The tuning frequency for the only possible position for the "
                << "distress beacon is " << tuningFrequency << "." << endl;

        return 0;
}

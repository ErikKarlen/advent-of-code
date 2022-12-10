#include <fstream>
#include <iostream>
#include <map>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int numLightsLit = 0;
        map<pair<int, int>, bool> lights;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                cout << line << endl;
                size_t start = line.find(' ', 5);
                size_t end = line.find(',', 5);
                int x0 = stoi(line.substr(start, end - start));
                start = end + 1;
                end = line.find(' ', start + 1);
                int y0 = stoi(line.substr(start, end - start));
                start = end + 9;
                end = line.find(',', start);
                int x1 = stoi(line.substr(start, end - start));
                start = end + 1;
                end = line.find(' ', start);
                int y1 = stoi(line.substr(start, end - start));
                //cout << "from (" << x0 << ',' << y0 << ") to (" << x1 << ',' << y1  << ")" << endl;

                for (int x = x0; x < x1 + 1; ++x) {
                        for (int y = y0; y < y1 + 1; ++y) {
                                if (line.substr(0, 7) == "turn on") {
                                        lights[{ x, y }] = 1;
                                } else if (line.substr(0, 8) == "turn off") {
                                        lights[{ x, y }] = 0;
                                } else if (line.substr(0, 6) == "toggle") {
                                        if (lights.count({ x, y })) {
                                                lights[{ x, y }] = 1 - lights[{ x, y }];
                                        } else {
                                                lights[{ x, y }] = 1;
                                        }
                                        //auto ep = lights.emplace({ x, y }, 
                                        //ep.first->second = 1 - ep.first->second;
                                }
                        }
                }
        }
        for (int x = 0; x < 1000; ++x) {
                for (int y = 0; y < 1000; ++y) {
                        numLightsLit += lights[{ x, y }];
                }
        }


        cout << "After following the instructions there are " << numLightsLit
                << " lights lit." << endl;

        return 0;
}

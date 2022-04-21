#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>


using namespace std;


static map<string, set<string>> caveConnections;
static set<string> bigCaves;
static set<string> passPaths;
static set<string> failPaths;


/**
 * Find a path from end of takenPath to endCave
 */
bool findPath(string takenPath, string currentCave, string endCave)
{
        for (auto const &cave : caveConnections.at(currentCave)) {
                bool visited = takenPath.find(cave) != std::string::npos;
                bool isBig = bigCaves.find(cave) != bigCaves.end();
                string newPath = takenPath + "," + cave;
                bool pathExists = passPaths.find(newPath) != passPaths.end() || failPaths.find(newPath) != failPaths.end();
                if ((!visited || isBig) && !pathExists) {
                        takenPath = newPath;
                        if (cave.compare(endCave) == 0) {
                                passPaths.insert(takenPath);
                                return true;
                        }
                        return findPath(takenPath, cave, endCave);
                }
        }

        failPaths.insert(takenPath);        
        return false;
}


bool checkUppercase(string s)
{
        return all_of(s.begin(), s.end(), [](unsigned char c){ return isupper(c); });
}


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line, cave1, cave2;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                cave1 = line.substr(0, line.find('-'));
                cave2 = line.substr(line.find('-') + 1, line.size());
                caveConnections[cave1].insert(cave2);
                caveConnections[cave2].insert(cave1);
                if (checkUppercase(cave1)) {
                        bigCaves.insert(cave1);
                } 
                if (checkUppercase(cave2)) {
                        bigCaves.insert(cave2);
                } 
        }

        for (int i = 0; i < 100000; ++i) {
                findPath("start", "start", "end");
        }

        cout << "Pass Paths:" << endl;
        for (auto const &path : passPaths) {
                cout << path << endl;
        }
        cout << "Total Pass Paths: " << passPaths.size() << endl;

        /*
        cout << endl << "Fail Paths:" << endl;
        for (auto const &path : failPaths) {
                cout << path << endl;
        }

        cout << "Big Caves:" << endl;
        for (auto const &cave : bigCaves) {
                cout << cave << endl;
        }

        cout << endl << "Cave Connections:" << endl;
        for (auto const &pair: caveConnections) {
                cout <<  pair.first << ": " << "[ ";
                for (string cave : pair.second) {
                        cout << cave << ", ";
                }
                cout << "]" << endl ;
        }
        */

        return 0;
}

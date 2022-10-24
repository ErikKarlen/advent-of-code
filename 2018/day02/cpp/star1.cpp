#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int twoCounts = 0, threeCounts = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                unordered_map<char, int> charToCount;
                int twoCount = 0, threeCount = 0;

                for (const auto & c : line) {
                        auto emplacePair = charToCount.emplace(c, 0);
                        emplacePair.first->second += 1;
                }
                for (const auto & pair : charToCount) {
                        twoCount = pair.second == 2 ? 1 : twoCount;
                        threeCount = pair.second == 3 ? 1 : threeCount;
                }
                twoCounts += twoCount;
                threeCounts += threeCount;
        }

        cout << "The checksum for the list of box IDs is " << twoCounts * threeCounts << "." << endl;

        return 0;
}

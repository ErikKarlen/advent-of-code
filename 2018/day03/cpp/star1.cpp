#include <iostream>
#include <fstream>
#include <map>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int doubleClaimed;
        map<pair<int, int>, int> claimsMap;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                size_t last = 1;
                size_t next = line.find(' ');
                int id = stoi(line.substr(last, next - last));
                last = next + 3;
                next = line.find(',');
                int left = stoi(line.substr(last, next - last));
                last = next + 1;
                next = line.find(':');
                int top = stoi(line.substr(last, next - last));
                last = next + 2;
                next = line.find('x');
                int width = stoi(line.substr(last, next - last));
                last = next + 1;
                next = line.size();
                int height = stoi(line.substr(last, next - last));

                for (int y = top; y < top + height; ++y) {
                        for (int x = left; x < left + width; ++x) {
                                pair<int, int> coord(x, y);
                                auto emplace_pair = claimsMap.emplace(coord, 0);
                                emplace_pair.first->second += 1;
                        }
                }
        }

        for (const auto & p : claimsMap) {
                doubleClaimed += p.second > 1 ? 1 : 0;
        }

        cout << "There is a total of " << doubleClaimed << " square inches"
                << " that are within two or more claims." << endl;

        return 0;
}

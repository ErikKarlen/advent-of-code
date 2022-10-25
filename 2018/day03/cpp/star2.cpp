#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>


using namespace std;

struct Claim
{
        int id;
        vector<pair<int, int>> points;

        Claim(int id) { this->id = id; }
};


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int unclaimedId;
        map<pair<int, int>, int> claimsMap;
        vector<Claim> claims;

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

                Claim claim(id);

                for (int y = top; y < top + height; ++y) {
                        for (int x = left; x < left + width; ++x) {
                                pair<int, int> coord(x, y);
                                claim.points.push_back(coord);
                                auto emplace_pair = claimsMap.emplace(coord, 0);
                                emplace_pair.first->second += 1;
                        }
                }
                claims.push_back(claim);
        }

        for (const auto & claim : claims) {
                bool unclaimed = true;
                for (const auto & coord : claim.points) {
                        if (unclaimed && claimsMap.at(coord) == 1) {
                                continue;
                        }
                        unclaimed = false;
                        break;
                }
                if (unclaimed) {
                        unclaimedId = claim.id;
                        break;
                }
        }

        cout << "The ID of the only claim that doesn't overlap is " << unclaimedId << endl;

        return 0;
}

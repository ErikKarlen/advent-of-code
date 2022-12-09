#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
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
        vector<pair<int, int>> knots(10, { 0, 0 });
        set<pair<int, int>> tailVisited = { knots.back() };
        map<char, pair<int, int>> direction{
                { 'L', { -1, 0} },
                { 'U', { 0, 1} },
                { 'R', { 1, 0} },
                { 'D', { 0, -1} }
        };

        inFile.open(argv[1]);

        while (getline(inFile, line)) {

                int dx = direction[line.front()].first;
                int dy = direction[line.front()].second;
                int numSteps = stoi(line.substr(2));
                for (int i = 0; i < numSteps; ++i) {
                        pair<int, int> step = { dx, dy };
                        knots[0].first += step.first;
                        knots[0].second += step.second;

                        /* Move each knot one at a time */
                        for (int k = 1; k < knots.size(); ++k) {
                                pair<int, int> & prevKnot = knots[k - 1];
                                pair<int, int> & knot = knots[k];
                                //cout << knot.first << "," << knot.second << endl;

                                if (abs(knot.first - prevKnot.first) + abs(knot.second - prevKnot.second) > 2) {
                                        knot.first += prevKnot.first - knot.first > 0 ? 1 : -1;
                                        knot.second += prevKnot.second - knot.second > 0 ? 1 : -1;
                                } else if (abs(knot.first - prevKnot.first) > 1 && knot.second == prevKnot.second) {
                                        knot.first += prevKnot.first - knot.first > 0 ? 1 : -1;
                                } else if (abs(knot.second - prevKnot.second) > 1 && knot.first == prevKnot.first) {
                                        knot.second += prevKnot.second - knot.second > 0 ? 1 : -1;
                                }
                                if (k == knots.size() - 1) {
                                        tailVisited.insert(knot);
                                }
                        }
                }
        }

        cout << "The number of positions the tail of the rope visits at least "
                << "once is " << tailVisited.size() << "." << endl;

        return 0;
}

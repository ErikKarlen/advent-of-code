#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int prioritySum = 0;
        set<char> common;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (common.size() == 1) {
                        char badge = *common.begin();
                        prioritySum += toupper(badge) - 'A' + 1;
                        if (isupper(badge)) {
                                prioritySum += 26;
                        }
                        common.clear();
                }
                if (common.size() == 0) {
                        common.insert(line.begin(), line.end());
                } else {
                        set<char> other(line.begin(), line.end());
                        set<char> intersection;
                        set_intersection(common.begin(), common.end(), other.begin(), other.end(),
                        std::inserter(intersection, intersection.begin()));
                        common = intersection;
                }
        }
        char badge = *common.begin();
        prioritySum += toupper(badge) - 'A' + 1;
        if (isupper(badge)) {
                prioritySum += 26;
        }
        
        cout << "The sum of the priorities of the item types that corresponds to "
                << "the badges of each three-Elf group is " << prioritySum << "." << endl;

        return 0;
}

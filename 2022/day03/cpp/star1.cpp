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

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                string first = line.substr(0, line.size() / 2);
                set<char> firstSet(first.begin(), first.end());
                string second = line.substr(line.size() / 2);
                for (const auto & c : second) {
                        if (firstSet.count(c)) {
                                prioritySum +=  toupper(c) - 'A' + 1;
                                if (isupper(c)) {
                                        prioritySum += 26;
                                }
                                break;
                        }
                }
        }
        
        cout << "The sum of the priorities of the item type that appears in both "
                << "compartments of each rucksack is " << prioritySum << "." << endl;

        return 0;
}

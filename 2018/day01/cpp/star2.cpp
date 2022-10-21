#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int frequency = 0;
        set<int> seen;
        vector<int> changes;
        bool finished = false;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                int sign = line[0] == '+' ? 1 : -1;
                int change = stoi(line.substr(1, line.size()));

                changes.push_back(sign * change);

                frequency += sign * change;

                if (seen.find(frequency) != seen.end()) {
                        finished = true;
                        break;
                }
                seen.insert(frequency);
        }

        while (!finished) {
                for (int c : changes) {
                        frequency += c;

                        if (seen.find(frequency) != seen.end()) {
                                finished = true;
                                break;
                        }
                        seen.insert(frequency);
                }
        }

        cout << "The first frequency seen twice is " << frequency << "." << endl;

        return 0;
}

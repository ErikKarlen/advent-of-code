#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string fullPolymer;
        set<char> types;
        int minPolymerSize;

        inFile.open(argv[1]);

        getline(inFile, fullPolymer);
        getline(inFile, fullPolymer);
        getline(inFile, fullPolymer);
        getline(inFile, fullPolymer);
        getline(inFile, fullPolymer);

        types.insert(fullPolymer.begin(), fullPolymer.end());

        minPolymerSize = fullPolymer.size();
        for (const auto & excludeType : types) {
                //cout << excludeType << endl;
                if (isupper(excludeType)) {
                        continue;
                }
                stringstream polyss;
                for (const auto & unit : fullPolymer) {
                        if (tolower(unit) != excludeType) {
                                polyss << unit;
                        }
                }
                string polymer = polyss.str();
                bool reactionDone = false;
                while (!reactionDone) {
                        reactionDone = true;
                        for (int i = 1; i < polymer.size(); ++i) {
                                if ((tolower(polymer[i - 1]) == tolower(polymer[i]))
                                && (isupper(polymer[i - 1]) && islower(polymer[i])
                                || (islower(polymer[i - 1]) && isupper(polymer[i])))) {
                                        polymer = polymer.substr(0, i - 1) + polymer.substr(i + 1);
                                        //cout << polymer << endl;
                                        reactionDone = false;
                                }
                        }
                }
                if (polymer.size() < minPolymerSize) {
                        minPolymerSize = polymer.size();
                }
        }
 
        cout << "After fully reacting the scanned polymer there are "
                << minPolymerSize << " units in the resulting polymer." << endl;

        return 0;
}

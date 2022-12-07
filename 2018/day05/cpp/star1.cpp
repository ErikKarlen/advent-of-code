#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string polymer;
        bool reactionDone = false;

        inFile.open(argv[1]);

        getline(inFile, polymer);
        //getline(inFile, polymer);
        //getline(inFile, polymer);
        //getline(inFile, polymer);
        //getline(inFile, polymer);

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

        cout << "After fully reacting the scanned polymer there are "
                << polymer.size() << " units in the resulting polymer." << endl;

        return 0;
}

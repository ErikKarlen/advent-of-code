#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;


bool checkNice(const string & str)
{
        bool containsDoublePair = false;
        bool containsRepeatLetter = false;

        for (int i = 0; i < str.size() - 2; ++i) {
                if (str.find(str.substr(i, 2), i + 2) != string::npos) {
                        containsDoublePair = true;
                        break;
                }
        }

        for (int i = 2; i < str.size(); ++i) {
                if (str[i - 2] == str[i]) {
                        containsRepeatLetter = true;
                        break;
                }
        }

        return containsDoublePair && containsRepeatLetter;
}

int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        vector<string> niceStrings;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (checkNice(line)) {
                        niceStrings.push_back(line);
                }
        }


        cout << "There are a total of " << niceStrings.size()
                << " nice strings under the new rules." << endl;

        return 0;
}

#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>


using namespace std;


bool checkNice(const string & str)
{
        set<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
        int numVowels = 0;
        bool containsDouble = false;
        char prev = str.front();
        if (vowels.count(prev)) {
                numVowels++;
        }
        for (const auto & c : str.substr(1)) {
                if (vowels.count(c)) {
                        numVowels++;
                }
                if (c == prev) {
                        containsDouble = true;
                }
                if ((prev == 'a' && c == 'b')
                        || (prev == 'c' && c == 'd')
                        || (prev == 'p' && c == 'q')
                        || (prev == 'x' && c == 'y')) {
                        return false;
                }
                prev = c;
        }
        if (numVowels < 3) {
                return false;
        }

        if (!containsDouble) {
                return false;
        }

        return true;
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


        cout << "There are a total of " << niceStrings.size() << " nice strings." << endl;

        return 0;
}

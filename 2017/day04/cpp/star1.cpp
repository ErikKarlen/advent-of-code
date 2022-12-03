#include <iostream>
#include <fstream>
#include <map>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int numValidPassphrases = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                bool valid = true;
                map<string, int> wordCounts;
                size_t last = 0;
                size_t next = line.find(' ', last);
                while (next != string::npos) {
                        string word = line.substr(last, next - last);
                        ////cout << word << " ";
                        auto emplace_pair = wordCounts.emplace(word, 0);
                        emplace_pair.first->second += 1;
                        if (wordCounts.at(word) > 1) {
                                valid = false;
                        }
                        last = next + 1;
                        next = line.find(' ', last);
                }
                string word = line.substr(last, next - last);
                ////cout << word << " ";
                auto emplace_pair = wordCounts.emplace(word, 0);
                emplace_pair.first->second += 1;
                ////cout << endl << "count " << wordCounts[word] << endl;
                if (wordCounts.at(word) > 1) {
                        valid = false;
                }
                //cout << endl;
                if (valid) {
                        numValidPassphrases++;
                }
        }

        cout << "There are a total of " << numValidPassphrases
                << " valid passphrases." << endl;

        return 0;
}

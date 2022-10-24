#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

string findCommonLetters(const string & id1, const string & id2)
{
        string commonLetters;
        for (int i = 0; i < id1.size(); ++i) {
                if (id1[i] == id2[i]) {
                        commonLetters.append(1, id1[i]);
                }
        }
        return commonLetters;
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        string commonLetters;
        vector<string> ids;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                ids.push_back(line);
        }

        for (int i = 0; i < ids.size(); ++i) {
                bool finished = false;
                bool foundDifference = false;
                for (int j = i + 1; j < ids.size(); ++j) {
                        commonLetters = findCommonLetters(ids[i], ids[j]);
                        if (commonLetters.size() == ids[i].size() - 1) {
                                finished = true;
                                break;
                        }
                }
                if (finished) {
                        break;
                }
        }

        cout << "The letters that are common between the two correct box IDs are '"
                << commonLetters << "'." << endl;

        return 0;
}

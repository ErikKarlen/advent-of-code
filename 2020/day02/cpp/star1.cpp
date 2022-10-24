#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


bool checkValidPassword(const string & password, int minOccurences, int maxOccurences, char restrictedChar)
{
        int restrictedOccurences = 0;

        for (const char c : password) {
                restrictedOccurences += c == restrictedChar ? 1 : 0;
        }

        return minOccurences <= restrictedOccurences && restrictedOccurences <= maxOccurences;
}

int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        vector<string> validPasswords;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                size_t last = 0;
                size_t next = line.find('-');
                int minOccurences = stoi(line.substr(last, next - last));
                last = next + 1;
                next = line.find(' ', last);
                int maxOccurences = stoi(line.substr(last, next - last));
                char restrictedChar = line[next + 1];
                string password = line.substr(next + 4);
                if (checkValidPassword(password, minOccurences, maxOccurences, restrictedChar)) {
                        validPasswords.push_back(password);
                }
        }

        cout << "There are a total of " << validPasswords.size() << "." << endl;

        return 0;
}

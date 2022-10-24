#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


bool checkValidPassword(const string & password, size_t pos1, size_t pos2, char requiredChar)
{
        int requiredOccurences = 0;

        requiredOccurences += password[pos1 - 1] == requiredChar ? 1 : 0;
        requiredOccurences += password[pos2 - 1] == requiredChar ? 1 : 0;

        return requiredOccurences == 1;
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
                int pos1 = stoi(line.substr(last, next - last));
                last = next + 1;
                next = line.find(' ', last);
                int pos2 = stoi(line.substr(last, next - last));
                char requiredChar = line[next + 1];
                string password = line.substr(next + 4);
                if (checkValidPassword(password, pos1, pos2, requiredChar)) {
                        validPasswords.push_back(password);
                }
        }

        cout << "There are a total of " << validPasswords.size()
                << " valid passwords according to the new interpretation." << endl;

        return 0;
}

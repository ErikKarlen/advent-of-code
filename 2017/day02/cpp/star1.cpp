#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int checksum = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                vector<int> row;
                size_t last = 0;
                size_t next = line.find_first_of(" \t\r", last);
                while (next != string::npos) {
                        int number = stoi(line.substr(last, next - last));
                        last = next + 1;
                        next = line.find_first_of(" \t\r", last);
                        row.push_back(number);
                }
                row.push_back(stoi(line.substr(last, next - last)));

                const auto [smallest, largest] = minmax_element(begin(row), end(row));
                checksum += *largest - *smallest;
        }

        cout << "The checksum for the spreadsheet is " << checksum << "." << endl;

        return 0;
}

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
        int sum = 0;

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

                for (int i = 0; i < row.size(); ++i) {
                        bool finished = false;
                        for (int j = i + 1; j < row.size(); ++j) {
                                int large = max(row[i], row[j]);
                                int small = min(row[i], row[j]);
                                if (large % small == 0) {
                                        sum += large / small;
                                        finished = true;
                                        break;
                                }
                        }
                        if (finished) {
                                break;
                        }
                }
        }

        cout << "The sum of each row's result is " << sum << "." << endl;

        return 0;
}

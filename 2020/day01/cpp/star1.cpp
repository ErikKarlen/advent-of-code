#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int sum, i, j;
        vector<int> expenses;
        bool finished = false;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                expenses.push_back(stoi(line));
        }

        for (i = 0; i < expenses.size(); ++i) {
                for (j = i + 1; j < expenses.size(); ++j) {
                        sum = expenses[i] + expenses[j];
                        if (sum == 2020) {
                                finished = true;
                                break;
                        }
                }
                if (finished) {
                        break;
                }
        }

        cout << "The product of the expenses that add to 2020 is " << expenses[i] * expenses[j]  << "." << endl;

        return 0;
}

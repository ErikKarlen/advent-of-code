#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int i, j, k;
        long long sum;
        vector<int> expenses;
        bool finished = false;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                expenses.push_back(stoi(line));
        }

        for (i = 0; i < expenses.size(); ++i) {
                for (j = i + 1; j < expenses.size(); ++j) {
                        for (k = j + 1; k < expenses.size(); ++k) {
                                sum = expenses[i] + expenses[j] + expenses[k];
                                if (sum == 2020) {
                                        finished = true;
                                        break;
                                }
                        }
                        if (finished) {
                                break;
                        }
                }
                if (finished) {
                        break;
                }
        }

        cout << "The product of the expenses that add to 2020 is " <<
                expenses[i] * expenses[j] * expenses[k] << "." << endl;

        return 0;
}

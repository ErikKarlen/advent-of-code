#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        int sum = 0, threeMaxCalories;
        ifstream inFile;
        string line;
        vector<int> calories;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                if (line == "") {
                        calories.push_back(sum);
                        sum = 0;
                } else {
                        sum += stoi(line);
                }
        }

        sort(calories.begin(), calories.end());
        
        threeMaxCalories = calories.end()[-1] + calories.end()[-2] + calories.end()[-3];

        cout << "The top three Elves carrying the most cre arrying in total "
                << threeMaxCalories << " calories." << endl;

        return 0;
}

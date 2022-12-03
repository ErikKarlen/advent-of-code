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
        int sum = 0, maxCalories;
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
        
        maxCalories = *max_element(calories.begin(), calories.end());

        cout << "The Elf carrying the most Calories is carrying " << maxCalories << " calories." << endl;

        return 0;
}

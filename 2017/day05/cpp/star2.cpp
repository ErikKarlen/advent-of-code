#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        vector<int> instructions;
        int steps = 0;
        int index = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                instructions.push_back(stoi(line));
        }

        while (0 <= index && index < instructions.size()) {
                //cout << index << endl;
                int next = index + instructions[index];
                instructions[index] += instructions[index] < 3 ? 1 : -1;
                index = next;
                steps++;
        }

        cout << "It takes a total of " << steps << " to reach the exit." << endl;

        return 0;
}

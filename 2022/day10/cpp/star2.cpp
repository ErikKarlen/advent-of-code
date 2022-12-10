#include <fstream>
#include <iostream>
#include <set>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        (void)argc;
        (void)argv;
        ifstream inFile;
        string line;
        int signalStrengthSum = 0;
        int cycle = 0;
        int registerX = 1;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                //cout << line << endl;
                string op = line.substr(0, 4);
                int numCycles = 0;
                int newX = registerX;
                if (op == "noop") {
                        numCycles = 1;
                } else if (op == "addx") {
                        numCycles = 2;
                        newX = registerX + stoi(line.substr(5));
                }
                for (int i = 0; i < numCycles; ++i) {
                        int pos = cycle % 40;
                        if (pos == registerX - 1 || pos == registerX || pos == registerX + 1) {
                                cout << "#";
                        } else {
                                cout << ".";
                        }
                        cycle++;
                        //cout << "cycle: " << cycle << ", x: " << registerX << endl;
                        if (pos == 39)
                                cout << endl;
                }
                registerX = newX;
                //cout << "signl strength sum: " << signalStrengthSum << endl;
        }
        //cout << "cycle: " << cycle << ", x: " << registerX << endl;

        cout << "The eight capital letters that appear on my CRT are shown above." << endl;

        return 0;
}

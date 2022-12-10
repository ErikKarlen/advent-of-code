#include <fstream>
#include <iostream>
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
                        cycle++;
                        //cout << "cycle: " << cycle << ", x: " << registerX << endl;
                        if ((cycle % 40) + 20 == 40)
                                signalStrengthSum += registerX * cycle;
                }
                registerX = newX;
                //cout << "signl strength sum: " << signalStrengthSum << endl;
        }
        //cout << "cycle: " << cycle << ", x: " << registerX << endl;

        cout << "The sum of the signal strengths during the 20th, 60th, 100th, 140th, "
                << "180th, and 220th cycles is " << signalStrengthSum << endl;

        return 0;
}

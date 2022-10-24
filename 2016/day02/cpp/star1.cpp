#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        string code;
        int x_pos = 1, y_pos = 1;
        char keypad[3][3] = {
                {'1', '2', '3'},
                {'4', '5', '6'},
                {'7', '8', '9'}
        };

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                for (const char & instruction : line) {
                        if (instruction == 'D') {
                                y_pos = min(2, y_pos + 1);
                        }
                        else if (instruction == 'R') {
                                x_pos = min(2, x_pos + 1);
                        }
                        else if (instruction == 'U') {
                                y_pos = max(0, y_pos - 1);
                        }
                        else if (instruction == 'L') {
                                x_pos = max(0, x_pos - 1);
                        }
                }
                char digit = keypad[y_pos][x_pos];
                code.append(1, digit);
        }

        cout << "The bathroom code is " << code << "." << endl;

        return 0;
}

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
        int x_pos = 0, y_pos = 2;
        char keypad[5][5] = {
                {' ', ' ', '1', ' ', ' '},
                {' ', '2', '3', '4', ' '},
                {'5', '6', '7', '8', '9'},
                {' ', 'A', 'B', 'C', ' '},
                {' ', ' ', 'D', ' ', ' '}
        };

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                for (const char & instruction : line) {
                        int x_tmp = x_pos, y_tmp = y_pos;
                        if (instruction == 'D') {
                                y_tmp = min(4, y_pos + 1);
                        }
                        else if (instruction == 'R') {
                                x_tmp = min(4, x_pos + 1);
                        }
                        else if (instruction == 'U') {
                                y_tmp = max(0, y_pos - 1);
                        }
                        else if (instruction == 'L') {
                                x_tmp = max(0, x_pos - 1);
                        }

                        if (keypad[y_tmp][x_tmp] != ' ') {
                                x_pos = x_tmp;
                                y_pos = y_tmp;
                        }
                }
                char digit = keypad[y_pos][x_pos];
                code.append(1, digit);
        }

        cout << "The correct bathroom code is " << code << "." << endl;

        return 0;
}

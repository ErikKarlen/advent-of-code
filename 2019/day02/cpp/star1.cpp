#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int intCode[512];
        size_t next = 0, last = 0, i = 0;

        inFile.open(argv[1]);

        getline(inFile, line);

        while (next != string::npos) {
                next = line.find(',', last);
                intCode[i++] = stoi(line.substr(last, next - last));
                last = next + 1;
        }

        intCode[1] = 12;
        intCode[2] = 2;

        for (i = 0; i < 512; i += 4) {
                if (intCode[i] == 99) {
                        break;
                } else if (intCode[i] == 1) {
                        intCode[intCode[i+3]] = intCode[intCode[i+1]] + intCode[intCode[i+2]];
                } else if (intCode[i] == 2) {
                        intCode[intCode[i+3]] = intCode[intCode[i+1]] * intCode[intCode[i+2]];
                }
        }

        cout << "The value left at position 0 after the program halts is " << intCode[0] << "." << endl;

        return 0;
}

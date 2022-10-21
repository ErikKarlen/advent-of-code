#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int frequency = 0;

        inFile.open(argv[1]);

        while (getline(inFile, line)) {
                int sign = line[0] == '+' ? 1 : -1;
                int change = stoi(line.substr(1, line.size()));

                frequency += sign * change;
        }

        cout << "The resulting frequency is " << frequency << "." << endl;

        return 0;
}

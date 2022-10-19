#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        int floor = 0;
        int position = 1;
        ifstream inFile;
        string line;

        inFile.open(argv[1]);

        getline(inFile, line);

        for (const auto & c : line) {
                switch(c) {
                        case '(':
                                floor++;
                                break;
                        case ')':
                                floor--;
                                break;
                }
                if (floor < 0) {
                        break;
                }
                position++;
        }

        cout << "Santa enters the basement in position " << position << endl;

        return 0;
}

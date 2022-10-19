#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        int floor = 0;
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
        }

        cout << "Santa ends up on floor " << floor << endl;

        return 0;
}

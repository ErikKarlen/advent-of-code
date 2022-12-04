#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int possiblePasswords = 0;

        inFile.open(argv[1]);

        getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);

        size_t next = line.find('-');
        int start = stoi(line.substr(0, next));
        int end = stoi(line.substr(next + 1));

        //cout << start << "-" << end << endl;

        for (int num = start; num <= end; ++num) {
                bool containsSameAdjacent = false;
                bool neverDecreases = true;
                int div = 100000;
                int prevDigit = (num / div) % 10;
                //cout << prevDigit << endl;
                for (int i = 0; i < 5; ++i) {
                        div /= 10;
                        int digit = (num / div) % 10;
                        //cout << digit << endl;
                        if (prevDigit == digit) {
                                containsSameAdjacent = true;
                        }
                        if (prevDigit > digit) {
                                neverDecreases = false;
                                break;
                        }
                        prevDigit = digit;
                }
                if (containsSameAdjacent && neverDecreases) {
                        possiblePasswords++;
                }
        }

        cout << "A total of " << possiblePasswords << " different passwords within "
                << "the range in the puzzle input meet the given criteria." << endl;

        return 0;
}

#include <iostream>
#include <fstream>
#include <set>
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
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);
        //getline(inFile, line);

        size_t next = line.find('-');
        int start = stoi(line.substr(0, next));
        int end = stoi(line.substr(next + 1));

        //cout << start << "-" << end << endl;

        for (int num = start; num <= end; ++num) {
                int sameCounter = 1;
                set<int> sameCounterSet;
                bool neverDecreases = true;
                int div = 100000, digit;
                int prevDigit = (num / div) % 10;
                //cout << prevDigit << endl;
                for (int i = 0; i < 5; ++i) {
                        div /= 10;
                        digit = (num / div) % 10;
                        //cout << digit << endl;
                        if (prevDigit == digit) {
                                sameCounter++;
                        } else {
                                sameCounterSet.insert(sameCounter);
                                sameCounter = 1;
                        }
                        if (prevDigit > digit) {
                                neverDecreases = false;
                                break;
                        }
                        prevDigit = digit;
                }
                if (prevDigit == digit) {
                        sameCounterSet.insert(sameCounter);
                }
                //for (const auto & e : sameCounterSet) {
                //        cout << e << endl;
                //}
                if (sameCounterSet.count(2) && neverDecreases) {
                        possiblePasswords++;
                }
        }

        cout << "A total of " << possiblePasswords << " different passwords within "
                << "the range in the puzzle input meet all the given criteria." << endl;

        return 0;
}

#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int sum = 0;
        char prev;

        inFile.open(argv[1]);

        getline(inFile, line);

        prev = line.back();

        for (const auto & c : line) {
                if (c == prev) {
                        sum += c - '0';
                }
                prev = c;
        }

        cout << "The solution to the captcha is " << sum << "." << endl;

        return 0;
}

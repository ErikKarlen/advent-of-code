#include <iostream>
#include <fstream>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
        ifstream inFile;
        string line;
        int sum = 0;
        int comparison_index;

        inFile.open(argv[1]);

        getline(inFile, line);

        comparison_index = line.size() / 2;

        for (const auto & c : line) {
                if (c == line[comparison_index]) {
                        sum += c - '0';
                }
                comparison_index = (comparison_index + 1) % line.size();
        }

        cout << "The solution to the new captcha is " << sum << "." << endl;

        return 0;
}
